#include <iostream>
#include "lab2.h"

int main(){
    while (true)
    {
        std::cout << "ВВедите номер  задания: ";
        int num;
        std::cin >> num;
        if (num == 1) my_fact();
        else if (num == 2) sequence();
        else if (num == 3) sequence2();
        else break;
    }
    
    
    return 0;
}