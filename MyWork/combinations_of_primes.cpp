#include <iostream>

bool Is_simple(int n) {
    if (n == 1) return false;
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

int divide_by_2_with_1(int n) {
    if (n % 2 == 0) {
        return n / 2;
    } else {
        return (n - 1) / 2 + 1;
    }
}

int main() {
    const int Range = 10000;
    std::cout << "[";
    for (int i = 0; i < Range; ++i) {
        if (i != 0 && i % 2 == 0 && i != 2) {
            int count_simple_nums = 0;
            for (int j = 1; j < i; ++j) {
                if (Is_simple(j) && Is_simple(i - j)) {
                    count_simple_nums++;
                }
            }
            std::cout << divide_by_2_with_1(count_simple_nums) << ", ";
        }
    }
    std::cout << "]" << std::endl;
    return 0;
}
