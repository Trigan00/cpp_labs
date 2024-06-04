#include <iostream>
#include <cmath>

void my_fact(){

    int n, res = 1;
    std::cout << "Введите натуральное число: ";
    std::cin >> n;
    if (n % 2 == 0) for (int i = 2; i <= n; i+=2) res *= i;
    else for (int i = 1; i <= n; i+=2) res *= i;
    
    std::cout << "а) " << res << std::endl;
    std::cout << "б) " << (std::pow(-1, n+1) * res) << std::endl;
}

void sequence(){
    std::cout << "Введите натуральное число: ";
    int n;
    std::cin >> n;

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Элемент последовательности #" << i+1 << ": ";
        int el;
        std::cin >> el;
        std::cout << "Замененный элемент последовательности #" << i+1 << ": " << std::fmod(std::pow(el, 2), n) << std::endl;
    }

    
}

void sequence2(){
    std::cout << "Введите натуральное число: ";
    int n;
    std::cin >> n;
    double a = 0.0;
    int b = 0;
    int c = n + 1;
    for (int i = 0; i < n; i++)
    {
        std::cout << "Элемент последовательности #" << i+1 << ": ";
        double el;
        std::cin >> el;
        if (a == 0.0) a = el;
        if (b == 0 && std::fmod(el, 2) == 0 ) b = i + 1;
        if (std::fmod(el, 2) != 0) c = el;
    }
    if(a != 0.0) std::cout << (a > 0 ? "а) Раньше встречается положительное" : "б) Раньше встречается отрицательное") << std::endl;
    else std::cout << "б) Все члены равны нулю" << std::endl;
    std::cout << "б) Номер первого четного " << b << std::endl;
    std::cout << "в) Номер последнего нечетного " << c << std::endl;
    
}