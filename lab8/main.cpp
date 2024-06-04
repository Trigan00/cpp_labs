#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include "valid.h"

struct Person {
    std::string fullName;
    int age;
    std::string maritalStatus;
};

class PersonDeque {
public:
    void add(const std::string& fullName, int age, const std::string& maritalStatus) {
        people.push_back({fullName, age, maritalStatus});
    }

    void display() const {
        if (people.empty()) {
            std::cout << "Список пуст" << std::endl;
            return;
        }
        int i {0};
        for (const auto& person : people) {
            std::cout << i << ") ФИО: " << person.fullName 
                      << "; Возраст: " << person.age 
                      << "; Семейное положение: " << person.maritalStatus << std::endl;
            i++;
        }
    }

    void writeToFile(const char* filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла" << std::endl;
            return;
        }

        for (const auto& person : people) {
            file << person.fullName << ";" << person.age << ";" << person.maritalStatus << std::endl;
        }

        file.close();
    }

    void remove(int index) {
        if (index >= people.size()) {
            std::cerr << "Индекс вне диапазона" << std::endl;
            return;
        }
        people.erase(people.begin() + index);
        std::cout << "Узел удален" << std::endl;
    }

    void sortByAge() {
        std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
            return a.age < b.age;
        });
        std::cout << "Список отсортирован" << std::endl;
    }

    void assignDefaultValues() {
        for (auto& person : people) {
            person.fullName = "Ayaz Mubarak";
            person.age = 20;
            person.maritalStatus = "Single";
        }
        std::cout << "Список обновлен" << std::endl;
    }

private:
    std::deque<Person> people;
};

void parseAndAddToDeque(PersonDeque& deque, const std::string& line) {
    std::istringstream stream(line);
    std::string fullName, ageStr, maritalStatus;

    std::getline(stream, fullName, ';');
    std::getline(stream, ageStr, ';');
    std::getline(stream, maritalStatus, ';');

    if(!isValidInteger(ageStr)){
        std::cout << "Ошибка: Неверный возраст!" << std::endl;
        exit(1);
    }
    int age = std::stoi(ageStr);
    deque.add(fullName, age, maritalStatus);
}

int main() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    PersonDeque deque;
    std::string line;
    while (std::getline(file, line)) {
        parseAndAddToDeque(deque, line);
    }

    file.close();

    std::cout << "Файл загружен" << std::endl;
    while (true)
    {
        std::cout << "Выберете действие из предложенных ниже:" << std::endl;
        std::cout << "1) Печатать список\n2) Удалить узел\n3) Сортировка списка по возрасту\n4) Присвоить всем элементам предустановленные значения\n5) Выход" << std::endl;
        int inputSource = getN("Номер действия: ");
        if (inputSource == 1) {
            deque.display();
        }else if (inputSource == 2){
            int index = getN("Введите индекс узла, который требуется удалить из списка: ");
            deque.remove(index);
        }else if (inputSource == 3){
            deque.sortByAge();
        }else if (inputSource == 4){
            deque.assignDefaultValues();
        }else if (inputSource == 5){
            deque.writeToFile(dataFile);
            exit(0);
        }else {
            std::cout << "Неверное действие. Введите один из приведенных ниже.\n";
            continue;
        }
    }

    return 0;
}
