#pragma once 

#include <Node.hpp>

struct Vector {
    Node *head;
    int size;
    Vector(): head{nullptr}, size{0} {}

    void push_back(Student data) {
        Node *newNode = new Node(data);
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