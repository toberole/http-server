#pragma once

#include "HttpServletResponse.h"
#include "HttpServletRequest.h"

namespace com {
    namespace zw {
        class HttpServlet {
        public:
            HttpServlet();

            ~HttpServlet();

            virtual void doGet(com::zw::HttpServletRequest *request, com::zw::HttpServletResponse *response) = 0;

            virtual void doPost(com::zw::HttpServletRequest *request, com::zw::HttpServletResponse *response) = 0;
        };
    }
}



