#include "HttpServletResponse.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>

namespace com {
    namespace zw {
        HttpServletResponse::HttpServletResponse(int fd) : clientFD(fd) {}

        void HttpServletResponse::setBody(std::string str) {
            this->body = str;
        }

        void HttpServletResponse::setHeader(std::string k, std::string v) {
            heads.insert(std::make_pair(k, v));
        }

        void HttpServletResponse::end() {
            printf("HttpServletResponse::end clientFd: %d\n", clientFD);
            if (clientFD > 0) {
                std::string s = "HTTP/1.1 200 OK\r\n";
                std::stringstream ss;
                ss << s;

                if (body.size() > 0) {
                    ss << "Content-Length: ";
                    ss << body.size();
                }

                for (std::map<std::string, std::string>::iterator iter = heads.begin(); iter != heads.end(); ++iter) {
                    s = iter->first + ": " + iter->second + "\r\n";
                    ss << s;
                }
                s = "\r\n";
                ss << s;
                ss << body;
                send(clientFD, (void *) (ss.str().c_str()), ss.str().size(), 0);
                printf("response: %s\n", ss.str().c_str());
                close(clientFD);
                clientFD = 0;
            }
        }
    }
}
