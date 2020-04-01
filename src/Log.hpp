#pragma once

#include <iostream>

#define LOG(s) do { std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " << (s) << std::endl; } while (0)

