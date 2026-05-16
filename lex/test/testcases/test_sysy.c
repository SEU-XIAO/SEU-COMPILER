// SysY 词法分析测试文件
const int MAX = 100;
float pi = 3.14;

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    int x = 10;
    int y = 20;
    int result = x + y;

    /* 多行注释测试
       这是第二行
    */

    float f = 3.14;
    int hex = 0xFF;
    int oct = 077;

    while (x > 0) {
        x = x - 1;
        if (x == 5) {
            break;
        }
        continue;
    }

    for (int i = 0; i < 10; i++) {
        result = result + i;
    }

    return result;
}
