#pragma once

#include "http_msg.h"

typedef void (*ON_MESSAGE_COMPLETE_CB)(http_parser *p);

typedef struct http_parser_hook
{
    int fd;
    void *data;
    ON_MESSAGE_COMPLETE_CB on_message_complete_cb;
}http_parser_hook;