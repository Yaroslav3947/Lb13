#include <set>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>

const int WIDTH = 15;
const int MAX_YEAR = 2010;

enum class Option {
    ADD_STUDENT = 1,
    SORT_BY_NAME,
    PRINT_LIST,
    ADD_STUDENT_SORTED,
    CHANGE_COUNTRY,
    PRINT_SUB_LISTS,
    PRINT_COUNTRIES,
    EXIT
};


struct Student {
    std::string name;
    std::string country;
    int year;
    double cost;
};
struct Node {
    Student data;
    Node *next;

    Node(Student data): data(data), next(nullptr) {}
};

void showPosibilities() {
    std::cout << "1. Add student\n"
                  << "2. Sort list by name\n"
                  << "3. Print list\n"
                  << "4. Add student to sorted list\n"
                  << "5. Change country of selected student\n"
                  << "6. Print sub-lists\n"
                  << "7. Print countries\n"
                  << "8. Quit\n"
                  << "Choose an option:\n";
}

Option getOption() {
    int option;
    showPosibilities();
    std::cin >> option;
    return static_cast<Option>(option);
}

struct Queue {
    Node *head;
    Node *tail;

    Queue(): head(nullptr), tail(nullptr) {}

    void push(Student data) {
        Node *newNode = new Node(Student(data));
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop() {
        if (empty()) {
            std::cout << "Queue is empty\n";
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        if (empty()) {
            tail = nullptr;
        }
    }

    Student& front() {
        if (empty()) {
            std::cout << "Queue is empty\n";
        }
        return head->data;
    }

    bool empty() {
        return head == nullptr;
    }
};

struct Stack {
    
    Stack(): top(nullptr) {}

    Node *top;

    void push(Student data) {
        Node *newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (empty()) {
            std::cout << "Stack is empty\n";
        }
        Node *temp = top;
        top = top->next;
        delete temp;
    }

    Student &getTop() {
        if (empty()) {
            std::cout << "Stack is empty\n";
        }
        return top->data;
    }

    bool empty() {
        return top == nullptr;
    }
};
struct Vector {
    Node *head;
    int size;
    Vector(): head(nullptr), size(0) {}

    void push_back(Student data) {
        Node *newNode = new Node(Student(data));
        if (head == nullptr) {
            head = newNode;
        } else {
            Node *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }


    Student& operator[](int index) {
        if (index < 0 || index >= size) {
            std::cout << "Index non found\n";
        }
        Node *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    int getSize() {
        return size;
    }
};


void addStudent(const Student &student, Vector &list, Queue &queue, Stack &stack) {
    list.push_back(student);

    if(student.country != "Ukraine") {
        queue.push(student);
    }

    if(student.year > MAX_YEAR) {
        stack.push(student);
    }

}
void printStudent(const Student &student) {
    std::cout << std::setw(WIDTH) << student.name << std::setw(WIDTH) 
              << student.country << std::setw(WIDTH) << student.year
              << std::setw(WIDTH) << student.cost << '\n';
}

void print(Vector list) {
    for(int student = 0;student<list.getSize();student++) {
        printStudent(list[student]);
    }
}

void sortByName(Vector &list) {
    for(int i = 0; i < list.getSize()-1; i++) {
        for(int j = 0; j < list.getSize()-i-1; j++) {
            if(list[j].name > list[j+1].name) {
                std::swap(list[j], list[j+1]);
            }
        }
    }
}

void addStudentSorted(const Student &student, Vector &list) {
    Node* current = list.head;
    Node* prev = nullptr;
    while (current != nullptr && current->data.name < student.name) {
        prev = current;
        current = current->next;
    }
    if (prev == nullptr) {
        list.push_back(student);
    } else {
        prev->next = new Node(student);
        prev->next->next = current;
        list.size++;
    }
}

void changeCountry(const int &index, const std::string &newCountry, Vector &list) {
    list[index].country = newCountry;
}

void printHeadLine() {
    std::cout << std::setw(WIDTH) << "Name" << std::setw(WIDTH) << "Country" << std::setw(WIDTH) << "Year" << std::setw(WIDTH) << "Cost" << std::endl;
}

void printQueue(Queue queue) {
    std::cout << "Printing sublist of students not from Ukraine:\n";
    printHeadLine();
    while (!queue.empty()) {
        Student student = queue.front();
        printStudent(student);
        queue.pop();
    }
}

void printStack(Stack stack) {
    std::cout << "Printing sublist of students who started after " << MAX_YEAR << ":\n";
    printHeadLine();
    while (!stack.empty()) {
        Student student = stack.getTop();
        printStudent(student);
        stack.pop();
    }
}

void printList(Vector &list) {
    std::cout << "ALL LIST\n";
    printHeadLine();
    for(int i = 0;i<list.getSize();i++) {
        printStudent(list[i]);
    }
}

std::set<std::string> getCountries(Vector list) {
    std::set<std::string> allCountries;
    for(int i = 0;i<list.getSize();i++) {
        allCountries.insert(list[i].country);
    }
    return allCountries;
}

void printAllCounties(const std::set<std::string> &allCountries) {
    std::cout << "Printing list of countries:\n";
    for(const auto &country: allCountries) {
        std::cout << country << '\n';
    }
}

Student inputStudent() {
    Student student;
    std::cout << "Enter name: ";
    std::cin >> student.name;
    std::cout << "Enter country: ";
    std::cin >> student.country;
    std::cout << "Enter year: ";
    std::cin >> student.year;
    std::cout << "Enter cost: ";
    std::cin >> student.cost;
    return student;
}

std::string getNewCountry() {
    std::string newCountry;
    std::cout << "Enter new country: ";
    std::cin >> newCountry;
    return newCountry;
}

int getIndexOfCountryToChange() {
    int index;
    std::cout << "Enter index of coutry to change: ";
    std::cin >> index;
    return index;
}

int main() {

    Vector list;
    Queue queue;
    Stack stack;

    Option option;
    do {
        option = getOption();
        switch (option) {
            case Option::ADD_STUDENT: {
                Student student = inputStudent();
                addStudent(student, list, queue, stack);
                break;
            }
            case Option::SORT_BY_NAME: {
                sortByName(list);
                break;
            }
            case Option::PRINT_LIST: {
                printList(list);
                break;
            }
            case Option::ADD_STUDENT_SORTED: {
                Student student = inputStudent();
                addStudentSorted(student, list);
                break;
            }
            case Option::CHANGE_COUNTRY: {
                int index = getIndexOfCountryToChange();
                std::string newCountry = getNewCountry();
                changeCountry(index, newCountry, list);
                break;
            }
            case Option::PRINT_SUB_LISTS: {
                if(list.getSize() == 0) {
                    std::cout << "No students in list\n" << std::endl;
                } else {
                    printList(list);
                    if(queue.empty()) {
                        std::cout << "No students in queue\n";
                    } else {
                        printQueue(queue);
                    }
                    if(stack.empty()) {
                        std::cout << "No students in stack\n";
                    } else {
                        printStack(stack);
                    }
                }
                break;
            }
            case Option::PRINT_COUNTRIES: {
                std::set<std::string> allCountries = getCountries(list);
                printAllCounties(allCountries);
                break;
            }
            case Option::EXIT: {
                std::cout << "Quitting program.\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while(option != Option::EXIT);

    return 0;
}
