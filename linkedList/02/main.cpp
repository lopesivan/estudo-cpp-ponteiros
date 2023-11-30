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
        std::unique_ptr<Node> newNode = std::make_unique<Node>(data);
        if (!head) {
            head = std::move(newNode);
        } else {
            std::unique_ptr<Node>* curr = &head;
            while ((*curr)->next) {
                curr = &((*curr)->next);
            }
            (*curr)->next = std::move(newNode);
        }
    }

    void print() const {
        const Node* curr = head.get();
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next.get();
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
