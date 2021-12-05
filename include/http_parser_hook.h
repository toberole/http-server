#pragma once

struct http_parser_hook
{
    int fd;
    void *data;
    void( *on_message_complete_cb)(http_msg *msg);
};