#include <iostream>
#include <string>
#include <memory>

template <typename T>
struct Node {
    T data;
    std::unique_ptr<Node> next = std::make_unique<Node>;
    Node(T data) : data(data), next(nullptr){};
    ~Node(){
        // output on delete
        std::cout << "Destroy node with data: " << data << std::endl; 
    }
};

int main () {
    auto n0{std::make_unique<Node<int>>(0)};
    auto n1{std::make_unique<Node<int>>(1)};
    n1->next = std::move(n0);
}