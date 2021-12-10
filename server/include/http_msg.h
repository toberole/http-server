#pragma once

#include "http_parser.h"

#define MAX_ELEMENT_SIZE (1024 * 4)
#define MAX_HEADERS 32
#define MAX_CHUNKS 128

typedef struct http_msg {
    const char *name; // for debugging purposes
    const char *raw;
    enum http_parser_type type;
    enum http_method method;
    int status_code;
    char response_status[MAX_ELEMENT_SIZE];
    char request_path[MAX_ELEMENT_SIZE];
    char request_url[MAX_ELEMENT_SIZE];
    char fragment[MAX_ELEMENT_SIZE];
    char query_string[MAX_ELEMENT_SIZE];
    char body[MAX_ELEMENT_SIZE];
    size_t body_size;
    const char *host;
    const char *userinfo;
    uint16_t port;
    int num_headers;
    enum {
        NONE = 0,
        FIELD,
        VALUE
    } last_header_element;
    char headers[MAX_HEADERS][2][MAX_ELEMENT_SIZE];
    int should_keep_alive;

    int num_chunks;
    int num_chunks_complete;
    int chunk_lengths[MAX_CHUNKS];

    const char *upgrade; // upgraded body

    unsigned short http_major;
    unsigned short http_minor;

    int message_begin_cb_called;
    int headers_complete_cb_called;
    int message_complete_cb_called;
    int status_cb_called;
    int message_complete_on_eof;
    int body_is_final;


} http_msg;