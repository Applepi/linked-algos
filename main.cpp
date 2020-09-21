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

template <typename T>
struct List {
    List() : head{nullptr} {};
    void push(T data){
        auto temp{std::make_unique< Node<T> >(data)};
        if(head){
            temp->next -> std::move(head);
            head = std::move(temp);
        } else {
            head == std::move(temp);
        }
    }
    void pop(){

    }
    ~List(){
        // output on delete
        std::cout << "Destroyed list" << std::endl; 
    }
private:
    std::unique_ptr< Node<T> > head = std::make_unique< Node<T> >;
};

int main () {
    List<int> list;
    list.push(0);
    list.push(1);
    list.push(2);
    list.push(3);
}