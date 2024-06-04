#include <iostream>
#include <string>
#include "valid.h"

using namespace std;

void first(){

    int n = getN("Введите n: ");

    string s = lineCheck(n);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << "Введите символ №" << i + 1 << ": ";
    //     s += getChar();
    // }
    


    string result;
    bool insideBrackets = false;

    for (char ch : s) {
        if (ch == '(') {
            insideBrackets = true;
        } else if (ch == ')') {
            insideBrackets = false;
        } else if (!insideBrackets) {
            result += ch;
        }
    }

    cout << "Исходная строка: " << s << endl;
    cout << "Новая строка: " << result << endl;
    
}

void second(){

    int n = getN("Введите n: ");

    double array[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Введите число: ";
        array[i] = getDouble();
    }
    
    cout << "Новая последовательность: ";
    for (int i = n - 1; i >= 0; i--)
    {
        cout << array[i] << " ";
    }
    
    cout << endl;
}

bool isPalindrome(string str) {
    int left = 0;
    int right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}


void findPalindromicPrefixes(string sequence) {
    int n = sequence.length();
    string prefixes;

    for (int i = 0; i < n; ++i) {
        string prefix = sequence.substr(0, i + 1);
        if (isPalindrome(prefix)) {
            prefixes += " " + prefix;
        }
    }

    cout << "Палиндромические начальные отрезки:" << endl;
    cout << prefixes << endl;
}

void third(){
    int n = getN("Введите n: ");

    string s = lineCheck(n);
    // string s;
    // for (int i = 0; i < n; i++)
    // {
    //     cout << "Введите символ №" << i + 1 << ": ";
    //     s += getChar();
    // }
    findPalindromicPrefixes(s);
    
}