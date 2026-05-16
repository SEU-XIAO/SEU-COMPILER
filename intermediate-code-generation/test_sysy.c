// test_sysy.c - SysY 语言测试文件
// 测试基本变量声明、表达式、控制流和函数定义

int global_var;

int add(int a, int b) {
    return a + b;
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    // 变量声明和初始化
    int x = 10;
    int y = 20;
    int result;

    // 表达式计算
    result = add(x, y);

    // 常量声明
    const int MAX = 100;

    // if-else 语句
    if (result > MAX) {
        result = MAX;
    } else {
        result = result + 1;
    }

    // while 循环
    int i = 0;
    int sum = 0;
    while (i < 10) {
        sum = sum + i;
        i = i + 1;
    }

    // for 循环
    int product = 1;
    for (int j = 1; j <= 5; j = j + 1) {
        product = product * j;
    }

    // 函数调用
    int fact = factorial(5);

    return result;
}
