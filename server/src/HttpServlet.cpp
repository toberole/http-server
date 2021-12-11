#include "HttpServlet.h"

namespace com {
    namespace zw {
        HttpServlet::HttpServlet() {

        }

        HttpServlet::~HttpServlet() {

        }

        void HttpServlet::doGet(com::zw::HttpServletRequest *request, com::zw::HttpServletResponse *response) {
            printf("HttpServlet#doGet\n");
        }

        void HttpServlet::doPost(com::zw::HttpServletRequest *request, com::zw::HttpServletResponse *response) {
            printf("HttpServlet#doPost\n");
        }
    }
}
