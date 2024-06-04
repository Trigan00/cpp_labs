#include <iostream>
#include <fstream>
#include <cstring>
#include "valid.h"

struct Node {
    char fullName[MAX_LENGTH];
    int age;
    char maritalStatus[MAX_LENGTH];
    Node* next;
};

class CircularLinkedList {
public:
    CircularLinkedList() : head(nullptr) {}

    ~CircularLinkedList() {
        if (!head) return;
        Node* current = head->next;
        while (current != head) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        delete head;
        head = nullptr;
    }

    void add(const char* fullName, int age, const char* maritalStatus) {
        Node* newNode = new Node;
        strncpy(newNode->fullName, fullName, MAX_LENGTH);
        newNode->age = age;
        strncpy(newNode->maritalStatus, maritalStatus, MAX_LENGTH);
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
            head->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void display() const {
        if (!head) {
            std::cout << "Список пуст" << std::endl;
            return;
        }
        int i {0};
        Node* temp = head;
        do {
            std::cout << i << ") ФИО: " << temp->fullName << "; Возраст: " << temp->age << "; Семейное положение: " << temp->maritalStatus << std::endl;
            temp = temp->next;
            i++;
        } while (temp != head);
    }

    void writeToFile(const char* filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла" << std::endl;
            return;
        }

        if (!head) {
            file.close();
            return;
        }

        Node* temp = head;
        do {
            file << temp->fullName << ";" << temp->age << ";" << temp->maritalStatus << std::endl;
            temp = temp->next;
        } while (temp != head);

        file.close();
    }


    void removeByIndex(int index) {
        if (!head) {
            std::cerr << "Список пуст" << std::endl;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        if (index == 0) {
            if (head->next == head) { // Один узел в списке
                delete head;
                head = nullptr;
                std::cout << "Узел удален" << std::endl;
                return;
            } else { // Несколько узлов
                Node* last = head;
                while (last->next != head) {
                    last = last->next;
                }
                Node* temp = head;
                head = head->next;
                last->next = head;
                delete temp;
                std::cout << "Узел удален" << std::endl;
                return;
            }
        }

        int count = 0;
        do {
            prev = current;
            current = current->next;
            count++;
            if (count == index) {
                prev->next = current->next;
                delete current;
                std::cout << "Узел удален" << std::endl;
                return;
            }
        } while (current != head);

        std::cerr << "Узел под номером " << index << " не найден" << std::endl;
    }
    void sort() {
        if (!head || head->next == head){
            std::cout << "Список отсортирован" << std::endl;
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            Node* next = head->next;

            do {
                if (current->age > next->age) {
                    std::swap(current->fullName, next->fullName);
                    std::swap(current->age, next->age);
                    std::swap(current->maritalStatus, next->maritalStatus);
                    swapped = true;
                }
                current = next;
                next = next->next;
            } while (current->next != head);

        } while (swapped);
        std::cout << "Список отсортирован" << std::endl;
    }
    void reset() {
        if (!head){
            std::cout << "Список обнулен" << std::endl;
            return;
        }
        Node* current = head;
        do {
            memset(current->fullName, 0, MAX_LENGTH);
            current->age = 0;
            memset(current->maritalStatus, 0, MAX_LENGTH);
            current = current->next;
        } while (current != head);
        std::cout << "Список обнулен" << std::endl;
    }

private:
    Node* head;
};

void parseAndAddToList(CircularLinkedList& list, char* line) {
    char* fullName = strtok(line, ";");
    char* ageStr = strtok(nullptr, ";");
    char* maritalStatus = strtok(nullptr, ";");

    if (fullName && ageStr && maritalStatus) {
        if(!isValidInteger(ageStr)){
            std::cout << "Ошибка: Неверный возраст!" << std::endl;
            exit(1);
        }
        int age = std::stoi(ageStr);
        list.add(fullName, age, maritalStatus);
    }
}


int main() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    CircularLinkedList list;
    char line[MAX_LENGTH];
    while (file.getline(line, MAX_LENGTH)) {
        parseAndAddToList(list, line);
    }

    file.close();

    std::cout << "Файл загружен" << std::endl;
    while (true)
    {
        std::cout << "Выберете действие из предложенных ниже:" << std::endl;
        std::cout << "1) Печатать список\n2) Удалить узел\n3) Сортировка списка по возрасту\n4) Cброс значений всех узлов\n5) Выход" << std::endl;
        int inputSource = getN("Номер действия: ");
        if (inputSource == 1) {
            list.display();
        }else if (inputSource == 2){
            int index = getN("Введите индекс узла, который требуется удалить из списка: ");
            list.removeByIndex(index);
        }else if (inputSource == 3){
            list.sort();
        }else if (inputSource == 4){
            list.reset();
        }else if (inputSource == 5){
            list.writeToFile(dataFile);
            exit(0);
        }else {
            std::cout << "Неверное действие. Введите один из приведенных ниже.\n";
            continue;
        }
    }

    return 0;
}
