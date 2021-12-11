#pragma once

#include "http_parser.h"

#ifdef __cplusplus
extern "C" {
#endif

void parser_init(http_parser *parser, enum http_parser_type type);

void parser_free(http_parser *parser);

size_t parse(http_parser *parser, http_parser_settings *settings, const char *buf, size_t len);

int onMessageBegin(http_parser *pParser);

int onHeaderComplete(http_parser *pParser);

int onMessageComplete(http_parser *pParser);

int onURL(http_parser *pParser, const char *at, size_t length);

int onStatus(http_parser *pParser, const char *at, size_t length);

int onHeaderField(http_parser *pParser, const char *at, size_t length);

int onHeaderValue(http_parser *pParser, const char *at, size_t length);

int onBody(http_parser *pParser, const char *at, size_t length);

#ifdef __cplusplus
}
#endif