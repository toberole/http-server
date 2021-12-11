#include <cstdlib>
#include <cstdio>
#include <memory.h>

#include "Util.h"
#include "HttpServletRequest.h"
#include "HttpMsgHandler.h"

void parser_init(http_parser *parser, enum http_parser_type type) {
    printf("parser_init ......\n");
    http_parser_init(parser, type);
}

void parser_free(http_parser *parser) {
    printf("parser_free ......\n");
    free(parser);
    parser = NULL;
}

size_t parse(http_parser *parser, http_parser_settings *settings,
             const char *buf, size_t len) {
    printf("parse ......\n");
    size_t nparsed = http_parser_execute(parser, settings, buf, len);
    return nparsed;
}

int onMessageBegin(http_parser *pParser) {
    printf("@onMessageBegin call \n");
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    return 0;
}

int onHeaderComplete(http_parser *pParser) {
    printf("@onHeaderComplete call method: %d,httpMajor: %d,httpMinor: %d\n", pParser->method, pParser->http_major,
           pParser->http_minor);
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    request->method = pParser->method;
    request->httpMajor = pParser->http_major;
    request->httpMinor = pParser->http_minor;
    return 0;
}

int onURL(http_parser *pParser, const char *at, size_t length) {
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    request->url.assign(at, length);
    printf("@onURL url:%s \n", request->url.c_str());

    std::vector<std::string> vec = split(request->url, "?");
    if (vec.size() >= 1) {
        request->requestPath = vec.at(0);
        printf("@onURL queryPath:%s \n", request->requestPath.c_str());

        if (vec.size() > 1) {
            std::string s = vec.at(1);
            vec = split(s, "&&");
            for (auto it = vec.begin(); it != vec.end(); it++) {
                std::string kv = *it;
                printf("@onURL kv:%s \n", kv.c_str());
                std::vector<std::string> kvs = split(kv, "=");
                if (kvs.size() == 2) {
                    request->params->insert(std::make_pair(kvs.at(0), kvs.at(1)));
                }
            }
        }
    }

    return 0;
}

int onStatus(http_parser *pParser, const char *at, size_t length) {
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    request->status.assign(at, length);
    printf("@onStatus status:%s \n", request->status.c_str());
    return 0;
}

int onHeaderField(http_parser *pParser, const char *at, size_t length) {
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    request->fieldTmp = std::string(at, length);
    return 0;
}

int onHeaderValue(http_parser *pParser, const char *at, size_t length) {
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    std::string strValue(at, length);
    printf("@onHeaderValue field: %s,value:%s\n", request->fieldTmp.c_str(), strValue.c_str());
    request->heads->insert(std::make_pair(request->fieldTmp, strValue));
    return 0;
}

int onBody(http_parser *pParser, const char *at, size_t length) {
    printf("@onBody call, length:%d \n", length);
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    printf("@onBody recv:%s \n", std::string(at, length).c_str());
    request->body.append(at, length);
    return 0;
}

int onMessageComplete(http_parser *pParser) {
    printf("@onMessageComplete call \n");
    auto *request = static_cast<com::zw::HttpServletRequest *>(pParser->data);
    if (request->on_message_complete_cb) {
        request->on_message_complete_cb(pParser);
    }
    return 0;
}