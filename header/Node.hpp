#pragma once

#include <Student.hpp>

struct Node {
    Student data;
    Node *next;

    Node(Student data): data(data), next(nullptr) {}
};