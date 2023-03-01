#include <iostream>

struct Stack {
    int data;
    Stack *next;
};

 

void push(Stack *&top, int value) { 
    Stack* newElement = new Stack;
    newElement->data = value;
    newElement->next = top;

    top = newElement;
}

bool pop(Stack *&top, int& value) {
    if (top) { // isEmpty()
        value = top->data;
        Stack* temp = top;
        top = top->next;
        delete temp;
        return true;
    }
    else {
        return false;
    }
}

void subtract(Stack *&top1, Stack *&top2, Stack *&resTop) {
    int borrow {0};
    while (top1 || top2) {
        int num1{0}, num2{0};
        if (pop(top1, num1)) { 
            num1 -= borrow;
        }
        else { 
            num1 = 0;
        }
        pop(top2, num2); 
        int diff = num1 - num2;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        push(resTop, diff);
    }
}

std::string getStack(Stack *top) {
    std::string result;
    while (top && top->data == 0) {
        top = top->next; 
    }
    while (top) {
        result += top->data + '0'; // convert to char
        top = top->next;
    }
    if (result.empty()) {
        result = "0"; 
    }
    return result;
}

void pushNumberToStack(Stack *&top, const std::string &number) {
    for (int i = 0; i < number.size(); i++) {
        push(top, number[i] - '0');
    }
}

std::string getNumber(const std::string& message) {
    std::string num;
    std::cout << message;
    std::cin >> num;
    return num;
}

int main() {
    Stack *top1 = nullptr; 
    Stack *top2 = nullptr; 
    Stack *resTop = nullptr;

    std::string num1 = getNumber("Input first number: ");
    std::string num2 = getNumber("Input second number: ");
    
    pushNumberToStack(top1, num1);
    pushNumberToStack(top2, num2);

    subtract(top1, top2, resTop);
    std::string result = getStack(resTop);
    std::cout << result << '\n';

    return 0;
}


