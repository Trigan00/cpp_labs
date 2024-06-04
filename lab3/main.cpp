#include <iostream>
#include "lab3.h"
#include "valid.h"

int main(){
    while (true)
    {
        int num = getN("ВВедите номер  задания: ");
        if (num == 1) first();
        else if (num == 2) second();
        else if (num == 3) third();
        else{
            std::cout << "Некоректный ввод" << std::endl;
            continue;
        }
    }
    
    
    return 0;
}