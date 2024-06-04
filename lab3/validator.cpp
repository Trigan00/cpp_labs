#include <iostream>
#include <limits>
#include <string>

using namespace std;

string lineCheck(int n){
    string s;
    while (true)
    {
        cout << "Введите строку: ";
        getline(cin, s);
        if (cin.fail()) continue;
        if (s.length() != n) cout << "Ошибка: не равна n!\n";
        else return s;
    }
    
    
}

int getN(string str){
    while (true){
        cout << str;
        int n;
        cin >> n;
        if (cin.peek() != '\n') {
            cout << "Ошибка ввода!" << endl;
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            continue;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (n > 0) return n;
        else cout << "Ошибка: Должно быть больше 0" << endl;

    }
}

char getChar(){
    char c;
    
    while (true) {
        cin >> c;
        
        if (cin.fail() || cin.get() != '\n') {
            cout << "Ошибка: введите только один символ!\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        } else {
            return c;
        }
    }
}

double getDouble(){
    double d;
    
    while (true) {
        cin >> d;
        
        if (cin.fail() || cin.get() != '\n') {
            cout << "Ошибка: ввода!\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        } else {
            return d;
        }
    }
}