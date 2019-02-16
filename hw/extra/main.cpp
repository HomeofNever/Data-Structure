#include <iostream>

int cache[500];

long fibo(int n)
{
    if (n == 1 || n == 2)
        return 1;
    if (cache[n] != 0)
    {
        std::cout << "Cache hit! @ " << n << std::endl; 
        return cache[n];
    }
    
    cache[n] = fibo(n - 1) + fibo(n - 2);

    return cache[n];
}

int main() {
    std::cout << fibo(500);
}