#include <iostream>

int main() {
    std::string a = "hello";
    std::cout << a << std::endl;
    a[0] = 'a';
    std::cout << a << std::endl;
}