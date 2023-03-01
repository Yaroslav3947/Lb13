#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>

const int WIDTH = 15;
const int MAX_YEAR = 2010;

struct Student {
    std::string name;
    std::string country;
    int year;
    double cost;
};

void addStudent(Student student, std::vector<Student> &list, std::queue<Student> &queue, std::stack<Student> &stack) {
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

void print(std::vector<Student> &list) {
    for(const auto& student: list) {
        printStudent(student);
    }
}
// void sortByName(std::vector<Student> &list) {
//     std::sort(list.begin(), list.end(), [](const Student &s1, const Student &s2) {
//         return s1.name < s2.name;
//     });
// }
void sortByName(std::vector<Student> &list) {
    for(int i = 0; i < list.size()-1; i++) {
        for(int j = 0; j < list.size()-i-1; j++) {
            if(list[j].name > list[j+1].name) {
                std::swap(list[j], list[j+1]);
            }
        }
    }
}

void addStudentSorted(Student student, std::vector<Student> &list) {
    auto it = std::lower_bound(list.begin(), list.end(), student, [](const Student& s1, const Student& s2) {
        return s1.name < s2.name;
    });
    list.insert(it, student);
}

void changeCountry(int index, std::string newCountry, std::vector<Student> &list) {
    list[index].country = newCountry;
}

void printHeadLine() {
    std::cout << std::setw(WIDTH) << "Name" << std::setw(WIDTH) << "Country" << std::setw(WIDTH) << "Year" << std::setw(WIDTH) << "Cost" << std::endl;
}

void printQueue(std::queue<Student> queue) {
    printHeadLine();
    while (!queue.empty()) {
        Student student = queue.front();
        printStudent(student);
        queue.pop();
    }
}

void printStack(std::stack<Student> stack) {
    printHeadLine();
    while (!stack.empty()) {
        Student student = stack.top();
        printStudent(student);
        stack.pop();
    }
}

void printList(const std::vector<Student> &list) {
    printHeadLine();
    for(const auto& student: list) {
        printStudent(student);
    }
}

std::set<std::string> getCountries(const std::vector<Student> &list) {
    std::set<std::string> allCountries;
    for(const auto &student: list) {
        allCountries.insert(student.country);
    }
    return allCountries;
}

void printAllCounties(const std::set<std::string> &allCountries) {
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
enum class Option {
    ADD_STUDENT = 1,
    SORT_BY_NAME = 2,
    PRINT_LIST = 3,
    ADD_STUDENT_SORTED = 4,
    CHANGE_COUNTRY = 5,
    PRINT_SUB_LISTS,
    PRINT_COUNTRIES = 7,
    EXIT
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
 
int main() {

    std::vector<Student> list;
    std::queue<Student> queue;
    std::stack<Student> stack;

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
                int index;
                std::string newCountry;
                std::cout << "Enter index of student to change country: ";
                std::cin >> index;
                std::cout << "Enter new country: ";
                std::cin >> newCountry;
                changeCountry(index, newCountry, list);
                break;
            }
            case Option::PRINT_SUB_LISTS: {
                if(list.size() == 0) {
                    std::cout << "No students in list\n" << std::endl;
                } else {
                    std::cout << "ALL LIST\n";
                    printList(list);
                    if(queue.size() == 0) {
                        std::cout << "No students in queue\n";
                    } else {
                        std::cout << "Printing sublist of students not from Ukraine:\n";
                        printQueue(queue);
                    }
                    if(stack.size() == 0) {
                        std::cout << "No students in stack\n";
                    } else {
                        std::cout << "Printing sublist of students who started after " << MAX_YEAR << ":\n";
                        printStack(stack);
                    }
                }
                break;
            }
            case Option::PRINT_COUNTRIES: {
                std::set<std::string> allCountries = getCountries(list);
                std::cout << "Printing list of countries:\n";
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
