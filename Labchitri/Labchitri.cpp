#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Skobki {
    int lev;  // Position of "("
    int prav; // Position of ")"
};

class Stack {
private:
    struct StackNode {
        Skobki data;
        StackNode* next;
    };

    StackNode* top;

public:
    Stack() : top(nullptr) {}

    void init() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const Skobki& y) {
        StackNode* newNode = new StackNode{ y, top };
        top = newNode;
    }

    Skobki pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty" << std::endl;
            return Skobki{ -1, -1 };  // Placeholder values for an empty stack
        }

        StackNode* tmp = top;
        top = top->next;
        Skobki data = tmp->data;
        delete tmp;
        return data;
    }

    void clear() {
        init();
    }

    void printSortedPairs() const {
        std::vector<Skobki> pairs;
        StackNode* current = top;

        while (current != nullptr) {
            pairs.push_back(current->data);
            current = current->next;
        }

        // Sorting pairs based on the position of the opening "("
        std::sort(pairs.begin(), pairs.end(), [](const Skobki& a, const Skobki& b) {
            return a.lev < b.lev;
            });

        // Printing sorted pairs
        for (const Skobki& pair : pairs) {
            std::cout << pair.lev << " " << pair.prav;
            if (&pair != &pairs.back()) {
                std::cout << "; ";
            }
        }

        std::cout << std::endl;
    }
};

std::string readStr(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening the file" << std::endl;
        return "";
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        for (char ch : line) {
            if (ch == '(' || ch == ')') {
                content += ch;
            }
        }
    }

    return content;
}

int main() {
    const char* filePath = "C:\\Users\\Dell\\OneDrive\\Documents\\Stack.txt";  // Replace with the full path to your file

    std::string stroka = readStr(filePath);
    if (stroka.empty()) {
        std::cerr << "Error reading file content" << std::endl;
        return 1;
    }

    std::cout << "Input Text: " << stroka << std::endl;

    Stack stack;
    Skobki data;
    int i = 0;

    for (char ch : stroka) {
        i++;
        switch (ch) {
        case '(':
            data.lev = i;
            stack.push(data);
            break;

        case ')':
            data = stack.pop();
            data.prav = i;
            break;
        }
    }

    std::cout << "Result: ";
    stack.printSortedPairs();

    return 0;
}
