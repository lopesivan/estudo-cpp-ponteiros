#include <iostream>
#include <memory>

struct Node {
    int data;
    std::unique_ptr<Node> next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
    std::unique_ptr<Node> head;

public:
    void append(int data) {
        if (!head) {
            head = std::make_unique<Node>(data);
        } else {
            Node* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::make_unique<Node>(data);
        }
    }

    void print() const {
        for (Node* current = head.get(); current != nullptr; current = current->next.get()) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);

    list.print(); // Output: 1 2 3
    return 0;
}
