#pragma once

#include <vector>
#include <string>

//str为需要截断的string，pattern为分隔符
std::vector<std::string> split(std::string str, std::string pattern);

size_t strnlen(const char *s, size_t maxlen);

size_t strlncat(char *dst, size_t len, const char *src, size_t n);

