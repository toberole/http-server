#include "Util.h"

//str为需要截断的string，pattern为分隔符
std::vector<std::string> split(std::string str,std::string pattern) {
    std::string::size_type pos;
    std::vector <std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

size_t strnlen(const char *s, size_t maxlen) {
    const char *p = (const char *) memchr(s, '\0', maxlen);
    if (p == NULL)
        return maxlen;

    return p - s;
}

size_t strlncat(char *dst, size_t len, const char *src, size_t n) {
    size_t slen = strnlen(src, n);
    size_t dlen = strnlen(dst, len);

    if (dlen < len) {
        size_t rlen = len - dlen;
        size_t ncpy = slen < rlen ? slen : (rlen - 1);
        memcpy(dst + dlen, src, ncpy);
        dst[dlen + ncpy] = '\0';
    }

    assert(len > slen + dlen);
    return slen + dlen;
}

