#pragma once 

#include <Node.hpp>
#include "Student.hpp"


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