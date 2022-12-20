#include "pch.h"

vector<string> Split(string s, string delimiter)
{
    size_t pos = 0;
    std::string token;
    vector<string> tokens;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    
    if (s.empty() == false) {
        tokens.push_back(s);
    }

    return tokens;
}

string Format(const char* fmt, ...)
{
    char buff[1024];
    memset(buff, 0, sizeof(buff));
    va_list args;
    va_start(args, fmt);
    vsnprintf_s(buff, _countof(buff), _TRUNCATE, fmt, args);
    va_end(args);

    return string(buff);
}