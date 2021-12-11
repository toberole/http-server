#include "HttpServletRequest.h"

namespace com {
    namespace zw {
        HttpServletRequest::HttpServletRequest() {
            printf("HttpServletRequest()\n");
            heads = std::make_shared<std::map<std::string, std::string>>();
            params = std::make_shared<std::map<std::string, std::string>>();
        }

        HttpServletRequest::~HttpServletRequest() {
            printf("~HttpServletRequest()\n");
            heads = nullptr;
            params = nullptr;
        }
    }
}