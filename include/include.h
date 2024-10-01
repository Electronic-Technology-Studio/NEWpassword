//电子科技工作室2024-2030©版权所有
#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdint.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <map>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <random>
#include <array>
#include <stdexcept>
#include <fstream>
#include <direct.h>

void error_out();

#define pause system("pause");
#define eout error_out();
#define kill exit(0);

char str[2049] = {};
std::ofstream fout;
std::ofstream iout;
std::string vision;

#include "vision_setting.h"

using namespace std;

#endif