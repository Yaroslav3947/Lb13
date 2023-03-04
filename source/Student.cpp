#include "Student.hpp"


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