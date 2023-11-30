#include <iostream>
#include <memory>

class Node {
public:
  int data;
  std::unique_ptr<Node> next;

  Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
  std::unique_ptr<Node> head;

public:
  void append(int data) {
    auto newNode = std::make_unique<Node>(data);
    if (!head) {
      head = std::move(newNode);
    } else {
      auto curr = head.get();
      while (curr->next) {
        curr = curr->next.get();
      }
      curr->next = std::move(newNode);
    }
  }

  void print() const {
    for (auto curr = head.get(); curr != nullptr; curr = curr->next.get()) {
      std::cout << curr->data << " ";
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
