#pragma once

#undef UNICODE

#define _WIN32_WINNT 0x0A00 
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
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

using namespace std;
namespace fs = std::filesystem;

#include <windows.h>
#include <WinSock2.h>