#ifndef RE_STANDARDIZE_H
#define RE_STANDARDIZE_H

#include "structs.h"

// 正则表达式标准化
// 1. 展开花括号别名 {name}
// 2. 展开方括号字符集 [a-z]
// 3. 转换 ? 和 + 操作符
// 4. 插入显式连接符 $
void standardizeRegex();

#endif // RE_STANDARDIZE_H
