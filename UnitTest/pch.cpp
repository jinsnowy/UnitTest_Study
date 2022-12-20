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
