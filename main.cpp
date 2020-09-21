#include <iostream>
#include <string>
#include <memory>

template <typename T = int>
struct Node {
    T data;
    std::unique_ptr<Node> next = std::make_unique<Node>(NULL);
    Node(T data) : data(data), next(nullptr){};

    ~Node(){
        // output on delete
        // std::cout << "Destroy node with data: " << data << std::endl; 
    }
};

template <typename T = int>
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
        auto temp{
            std::make_unique< Node<T> >(data)
        };
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
    
    int size(){ // Needs work
        int count = 0;
        Node<T> *temp = head.get();
        while(temp){
            count++;
            temp = temp->next.get();
        }
        return count;
    }

    void search(T data ){
        Node<T> *temp = head.get();
        while(temp){
            if ( temp->data == data){
                std::cout << "Data " << data << " was found.\n";
                return;
            }else{
                temp = temp->next.get();
            }
        }
        std::cout << "Data " << data << " was not found.\n";
        return;
    };
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
    
    list.search(5);

    for (int i = 0; i< 5; i++ )
    {
        list.pop();
    }
    std::cout << "The list with 5 nodes: " << list << '\n';

    list.clean();
    std::cout << "The list after clean(): " << list << '\n';
    
    int num = 0;
    std::cout << "Please enter a list of numbers delimited by whitespace (-1 to end): " << '\n';
    while ( std::cin >> num){
        if ( num != -1){
            list.push(num);
        }  
        else
            break;
    }
    
    std::cout << "LIST: " << list << "size: " << list.size()<< std::endl;
}