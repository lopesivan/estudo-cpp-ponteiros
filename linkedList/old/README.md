Para implementar uma lista encadeada em C++ usando ponteiros
tradicionais com `new` e `delete`, a estrutura e a classe
podem ser assim:

```cpp
#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void append(int data) {
        Node* newNode = new Node(data);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
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
```

Neste exemplo, cada nó da lista é alocado dinamicamente
usando `new`. O destrutor da classe `LinkedList` libera a
memória alocada para cada nó ao percorrer a lista e usar
`delete` em cada nó. Isso garante que não haja vazamento
de memória.
