#pragma once
#include "http_msg_handler.h"
#include "http_msg.h"
#include "http_parser_hook.h"

void parser_init(http_parser *parser, http_parser_type type)
{
    http_parser_init(parser, type);
}

void parser_free(http_parser *parser)
{
    free(parser);
    parser = NULL;
}

size_t parse(http_parser *parser, const char *buf, size_t len)
{
    size_t nparsed = http_parser_execute(parser, &settings, buf, len);
    return nparsed;
}

int message_begin_cb(http_parser *p)
{
    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);
    m.message_begin_cb_called = true;
    return 0;
}

size_t strnlen(const char *s, size_t maxlen)
{
    const char *p = (const char *)memchr(s, '\0', maxlen);
    if (p == NULL)
        return maxlen;

    return p - s;
}

size_t strlncat(char *dst, size_t len, const char *src, size_t n)
{
    size_t slen = strnlen(src, n);
    size_t dlen = strnlen(dst, len);

    if (dlen < len)
    {
        size_t rlen = len - dlen;
        size_t ncpy = slen < rlen ? slen : (rlen - 1);
        memcpy(dst + dlen, src, ncpy);
        dst[dlen + ncpy] = '\0';
    }

    assert(len > slen + dlen);
    return slen + dlen;
}

int header_field_cb(http_parser *p, const char *buf, size_t len)
{

    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);
    if (m->last_header_element != m->FIELD)
        m->num_headers++;

    strlncat(m->headers[m->num_headers - 1][0], sizeof(m->headers[m->num_headers - 1][0]), buf, len);
    m->last_header_element = m->FIELD;
    return 0;
}

int header_value_cb(http_parser *p, const char *buf, size_t len)
{

    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);

    strlncat(m->headers[m->num_headers - 1][1], sizeof(m->headers[m->num_headers - 1][1]), buf, len);
    m->last_header_element = m->VALUE;
    return 0;
}

int request_url_cb(http_parser *p, const char *buf, size_t len)
{

    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);

    strlncat(m.request_url, sizeof(m.request_url), buf, len);
    return 0;
}

int response_status_cb(http_parser *p, const char *buf, size_t len)
{

    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);
    strlncat(m.response_status, sizeof(m.response_status), buf, len);
    return 0;
}

void check_body_is_final(const http_parser *p)
{
    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);
    if (m.body_is_final)
    {
        fprintf(stderr, "\n\n *** Error http_body_is_final() should return 1 "
                        "on last on_body callback call "
                        "but it doesn't! ***\n\n");
        assert(0);
        abort();
    }
    m.body_is_final = http_body_is_final(p);
}

int body_cb(http_parser *p, const char *buf, size_t len)
{

    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);
    strlncat(m.body, sizeof(m.body), buf, len);
    m.body_size += len;
    check_body_is_final(p);
    return 0;
}

int headers_complete_cb(http_parser *p)
{

    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);
    m.method = (http_method)parser->method;
    m.status_code = parser->status_code;
    m.http_major = parser->http_major;
    m.http_minor = parser->http_minor;
    m.headers_complete_cb_called = true;
    m.should_keep_alive = http_should_keep_alive(parser);
    return 0;
}

int message_complete_cb(http_parser *p)
{

    http_parser_hook *hook = (http_parser_hook *)(p->data);
    http_msg *m = (http_msg *)(hook->data);
    if (m.should_keep_alive != http_should_keep_alive(p))
    {
        fprintf(stderr, "\n\n *** Error http_should_keep_alive() should have same "
                        "value in both on_message_complete and on_headers_complete "
                        "but it doesn't! ***\n\n");
        assert(0);
        abort();
    }

    if (m.body_size && http_body_is_final(p) && !m.body_is_final)
    {
        fprintf(stderr, "\n\n *** Error http_body_is_final() should return 1 "
                        "on last on_body callback call "
                        "but it doesn't! ***\n\n");
        assert(0);
        abort();
    }

    m.message_complete_cb_called = true;
    m.message_complete_on_eof = currently_parsing_eof;

    return 0;
}
