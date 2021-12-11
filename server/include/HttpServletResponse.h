#pragma once

#include <string>
#include <map>

namespace com {
    namespace zw {
        class HttpServletResponse {
        private:
            int clientFD = 0;
            std::string body;
            std::map<std::string, std::string> heads;
        public:
            HttpServletResponse(int fd);

            void setHeader(std::string k, std::string v);

            void setBody(std::string str);

            void end();
        };
    }
}


