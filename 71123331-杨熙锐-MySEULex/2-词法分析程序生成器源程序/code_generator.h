#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "structs.h"

// 生成C++词法分析器代码
void generateCode(const DriverTable& table, const std::string& outputFile);

#endif // CODE_GENERATOR_H
