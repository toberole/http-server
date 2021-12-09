#pragma once

#include "http_parser.h"

#ifdef __cplusplus
extern "C" {
#endif

void parser_init(http_parser *parser, enum http_parser_type type);

void parser_free(http_parser *parser);

size_t parse(http_parser *parser, http_parser_settings *settings,const char *buf, size_t len);

int message_begin_cb(http_parser *p);

size_t strnlen(const char *s, size_t maxlen);

size_t strlncat(char *dst, size_t len, const char *src, size_t n);

int header_field_cb(http_parser *p, const char *buf, size_t len);

int header_value_cb(http_parser *p, const char *buf, size_t len);

int request_url_cb(http_parser *p, const char *buf, size_t len);

int response_status_cb(http_parser *p, const char *buf, size_t len);

void check_body_is_final(const http_parser *p);

int body_cb(http_parser *p, const char *buf, size_t len);

int headers_complete_cb(http_parser *p);

int message_complete_cb(http_parser *p);

#ifdef __cplusplus
}
#endif
