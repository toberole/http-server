#pragma once

#include "http_parser.h"
#include <string>
#include <map>

namespace com {
    namespace zw {
        typedef void (*ON_MESSAGE_COMPLETE_CB)(http_parser *p);

        class HttpServletRequest {
        public:
            std::string url;
            std::string status;
            std::string body;

            std::string fieldTmp;
            std::string requestPath;

            int method;// 1-GET,3-POST

            int httpMajor;
            int httpMinor;

            // std::map<std::string, std::string> heads;注意STL作为类成员变量时 malloc动态分配内存 初始化存在问题，必须使用new

            std::shared_ptr<std::map<std::string, std::string>> heads;
            std::shared_ptr<std::map<std::string, std::string>> params;;
        public:
            HttpServletRequest();

            ~HttpServletRequest();

        public:
            int clientFD = 0;
            ON_MESSAGE_COMPLETE_CB on_message_complete_cb = nullptr;
        };
    }
}


