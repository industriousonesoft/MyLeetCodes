#include <iostream>

int fib(int n) {
    if (n < 0) {
        throw "Invalid Input.";
    }else if (n == 0) {
        return 0;
    }else if (n == 1) {
        return 1;
    }
    int sum = 0;
    int pre = 0;
    int cur = 1;
    for (int i = 2; i <= n; i++) {
        sum = pre + cur;
        pre = cur;
        cur = sum;
    }
    return sum;
}

int main(int argc, const char * argv[]) {
	int n = 12;
    std::cout << "fib(" << n << ") = " << fib(n) << std::endl;
}