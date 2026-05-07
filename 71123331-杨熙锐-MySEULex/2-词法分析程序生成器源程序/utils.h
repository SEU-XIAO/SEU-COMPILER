#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

// 字符串处理工具
std::string trim(const std::string& str);
std::vector<std::string> split(const std::string& str, char delimiter);
std::string replaceAll(std::string str, const std::string& from, const std::string& to);

// 文件读取
std::string readFile(const std::string& filepath);
void writeFile(const std::string& filepath, const std::string& content);

#endif // UTILS_H
