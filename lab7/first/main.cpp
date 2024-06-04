#include <iostream>
#include <fstream>
#include <sstream>

const int MAX_LENGTH = 100;

struct Node {
    std::string fullName;
    int age;
    std::string maritalStatus;
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
    }

    void add(const std::string& fullName, int age, const std::string& maritalStatus) {
        Node* newNode = new Node{fullName, age, maritalStatus, nullptr};
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
        if (!head) return;
        Node* temp = head;
        do {
            std::cout << "Full Name: " << temp->fullName << "; Age: " << temp->age << "; Marital Status: " << temp->maritalStatus << std::endl;
            temp = temp->next;
        } while (temp != head);
    }

private:
    Node* head;
};

void parseAndAddToList(CircularLinkedList& list, const std::string& line) {
    std::istringstream stream(line);
    std::string fullName, ageStr, maritalStatus;

    std::getline(stream, fullName, ';');
    std::getline(stream, ageStr, ';');
    std::getline(stream, maritalStatus, ';');

    int age = std::stoi(ageStr); //TODO добавить валидацию
    list.add(fullName, age, maritalStatus);
}

int main() {
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    CircularLinkedList list;
    std::string line;
    while (std::getline(file, line)) {
        parseAndAddToList(list, line);
    }

    file.close();

    list.display();

    return 0;
}
