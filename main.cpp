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
        // std::cout << "Destroy node with data: " << data << std::endl; 
    }
};

template <typename T>
struct List {
    List() : head{nullptr} {};

    friend std::ostream& operator<<(std::ostream &os, const List<T> &list)
    {
        Node<T> *head = list.head.get();
        while(head){
            os << head->data << ' ';
            head = head->next.get();
        }
        return os;
    }

    void clean(){
        while(head){
            head = std::move(head->next);
        }
    }

    void push(T data){
        auto temp{std::make_unique< Node<T> >(data)};
        if(head){
            temp->next = std::move(head);
            head = std::move(temp);
        } else {
            head = std::move(temp);
        }
    }

    void insertAfter(Node<T> prev_node, T new_data){
        if (prev_node == NULL)
        {
            std::cout << "the given previous node cannot be NULL\n";
            return;
        }
        std::unique_ptr< Node<T> >new_node = std::make_unique< Node<T> >;
        new_node->data = new_data;
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }

    void reverse(){
        List<T> temp;
        Node<T> *root = head.get();
        while (root){
            temp.push(root->data);
            root = root->next.get();
        }
        clean();
        head = std::move(temp.head);
    }

    void pop(){
        if(head == nullptr){
            return;
        }
        std::unique_ptr< Node<T> > temp = std::move(head);
        head = std::move(temp->next);
    }

    ~List(){
        clean();
    }
private:
    std::unique_ptr< Node<T> > head = std::make_unique< Node<T> >;
};

int main () {
    List<int> list;
    std::cout << "The list is empty: " << list << '\n';
    for (int i = 0; i< 10; i++ )
    {
        list.push(i);
    }
    std::cout << "The list with 10 nodes: " << list << '\n';
    list.reverse();
    std::cout << "The list with 10 nodes reversed: " << list << '\n';
    list.reverse();
    for (int i = 0; i< 5; i++ )
    {
        list.pop();
    }
    std::cout << "The list with 5 nodes: " << list << '\n';

    list.clean();
    std::cout << "The list after clean(): " << list << '\n';
}