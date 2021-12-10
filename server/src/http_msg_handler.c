#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

#include "http_msg.h"
#include "http_msg_handler.h"
#include "http_parser_hook.h"

void parser_init(http_parser *parser, enum http_parser_type type) {
    printf("parser_init ......\n");
    http_parser_init(parser, type);
}

void parser_free(http_parser *parser) {
    printf("parser_free ......\n");
    free(parser);
    parser = NULL;
}

size_t parse(http_parser *parser, http_parser_settings *settings,
             const char *buf, size_t len) {
    printf("parse ......\n");
    size_t nparsed = http_parser_execute(parser, settings, buf, len);
    return nparsed;
}

int message_begin_cb(http_parser *p) {
    printf("message_begin_cb ......\n");
    struct http_parser_hook *hook = (http_parser_hook *) (p->data);
    struct http_msg *m = (http_msg *) (hook->data);
    m->message_begin_cb_called = 1;
    return 0;
}

size_t strnlen(const char *s, size_t maxlen) {
    const char *p = (const char *) memchr(s, '\0', maxlen);
    if (p == NULL)
        return maxlen;

    return p - s;
}

size_t strlncat(char *dst, size_t len, const char *src, size_t n) {
    size_t slen = strnlen(src, n);
    size_t dlen = strnlen(dst, len);

    if (dlen < len) {
        size_t rlen = len - dlen;
        size_t ncpy = slen < rlen ? slen : (rlen - 1);
        memcpy(dst + dlen, src, ncpy);
        dst[dlen + ncpy] = '\0';
    }

    assert(len > slen + dlen);
    return slen + dlen;
}

int header_field_cb(http_parser *p, const char *buf, size_t len) {
    printf("header_field_cb ......\n");
    struct http_parser_hook *hook = (struct http_parser_hook *) (p->data);
    struct http_msg *m = (http_msg *) (hook->data);
    if (m->last_header_element != FIELD)
        m->num_headers++;

    strlncat(m->headers[m->num_headers - 1][0], sizeof(m->headers[m->num_headers - 1][0]), buf, len);
    m->last_header_element = FIELD;
    return 0;
}

int header_value_cb(http_parser *p, const char *buf, size_t len) {
    printf("header_value_cb ......\n");
    http_parser_hook *hook = (http_parser_hook *) (p->data);
    http_msg *m = (http_msg *) (hook->data);

    strlncat(m->headers[m->num_headers - 1][1], sizeof(m->headers[m->num_headers - 1][1]), buf, len);
    m->last_header_element = VALUE;
    return 0;
}

int request_url_cb(http_parser *p, const char *buf, size_t len) {
    printf("request_url_cb ......\n");
    http_parser_hook *hook = (http_parser_hook *) (p->data);
    http_msg *m = (http_msg *) (hook->data);

    strlncat(m->request_url, sizeof(m->request_url), buf, len);
    return 0;
}

int response_status_cb(http_parser *p, const char *buf, size_t len) {
    printf("response_status_cb ......\n");
    http_parser_hook *hook = (http_parser_hook *) (p->data);
    http_msg *m = (http_msg *) (hook->data);
    strlncat(m->response_status, sizeof(m->response_status), buf, len);
    return 0;
}

void check_body_is_final(const http_parser *p) {
    printf("check_body_is_final ......\n");
    http_parser_hook *hook = (http_parser_hook *) (p->data);
    http_msg *m = (http_msg *) (hook->data);
    if (m->body_is_final) {
        fprintf(stderr, "\n\n *** Error http_body_is_final() should return 1 "
                        "on last on_body callback call "
                        "but it doesn't! ***\n\n");
        assert(0);
        abort();
    }
    m->body_is_final = http_body_is_final(p);
}

int body_cb(http_parser *p, const char *buf, size_t len) {
    printf("body_cb ......\n");
    http_parser_hook *hook = (http_parser_hook *) (p->data);
    http_msg *m = (http_msg *) (hook->data);
    strlncat(m->body, sizeof(m->body), buf, len);
    m->body_size += len;
    check_body_is_final(p);
    return 0;
}

int headers_complete_cb(http_parser *p) {
    printf("headers_complete_cb ......\n");
    http_parser_hook *hook = (http_parser_hook *) (p->data);
    http_msg *m = (http_msg *) (hook->data);
    m->method = p->method;
    m->status_code = p->status_code;
    m->http_major = p->http_major;
    m->http_minor = p->http_minor;
    m->headers_complete_cb_called = 1;
    m->should_keep_alive = http_should_keep_alive(p);
    return 0;
}

int message_complete_cb(http_parser *p) {
    printf("message_complete_cb ......\n");
    http_parser_hook *hook = (http_parser_hook *) (p->data);
    http_msg *m = (http_msg *) (hook->data);
    if (m->should_keep_alive != http_should_keep_alive(p)) {
        fprintf(stderr, "\n\n *** Error http_should_keep_alive() should have same "
                        "value in both on_message_complete and on_headers_complete "
                        "but it doesn't! ***\n\n");
        assert(0);
        abort();
    }

    if (m->body_size && http_body_is_final(p) && !m->body_is_final) {
        fprintf(stderr, "\n\n *** Error http_body_is_final() should return 1 "
                        "on last on_body callback call "
                        "but it doesn't! ***\n\n");
        assert(0);
        abort();
    }

    m->message_complete_cb_called = 1;
    m->message_complete_on_eof = 1;

    if (hook) {
        hook->on_message_complete_cb(p);
    }

    return 0;
}
