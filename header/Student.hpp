#pragma once

#include <set>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include <Queue.hpp>
#include <Stack.hpp>
#include <Vector.hpp>

const int WIDTH = 15;
const int MAX_YEAR = 2010;

struct Student {
    std::string name;
    std::string country;
    int year;
    double cost;
};



void addStudent(const Student &student, Vector &list, Queue &queue, Stack &stack);
void printStudent(const Student &student);
void print(Vector list);
void sortByName(Vector &list);
void addStudentSorted(const Student &student, Vector &list);
void changeCountry(const int &index, const std::string &newCountry, Vector &list);
void printHeadLine();
void printQueue(Queue queue);
void printStack(Stack stack);
void printList(Vector &list);
std::set<std::string> getCountries(Vector list);
void printAllCounties(const std::set<std::string> &allCountries);
Student inputStudent();
// Option getOption();
std::string getNewCountry();
int getIndexOfCountryToChange();
