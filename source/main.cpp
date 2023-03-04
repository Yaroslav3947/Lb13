#include <Student.hpp>

#include <Queue.hpp>
#include <Stack.hpp>
#include <Vector.hpp>

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

Option getOption() {
    int option;
    showPosibilities();
    std::cin >> option;
    return static_cast<Option>(option);
}

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
