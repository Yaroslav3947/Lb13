#pragma once

#include <Node.hpp>

struct Stack {
    
    Stack(): top{nullptr} {}

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