#pragma once
#undef UNICODE

#define _WIN32_WINNT 0x0A00 
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define NOMINMAX

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <algorithm>
#include <bitset>
#include <mutex>
#include <memory>
#include <functional>
#include <thread>
#include <future>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <chrono>
#include <random>
#include <filesystem>
#include <format>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;
namespace fs = std::filesystem;

#include <windows.h>
#include <WinSock2.h>

vector<string> Split(string s, string delimiter);
string Format(const char* fmt, ...);