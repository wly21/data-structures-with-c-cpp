#include <iostream>

using namespace std;

class Node
{
public:
    // constructors
    Node(int data): data(data), next(NULL){}
    Node(): data(0), next(NULL){}
    // destructor - default
    ~Node() {}
    // data members
    int data;
    Node* next;
};

class Ring{
private:
    int capacity;
    int size;
    Node* write_ptr;
    Node* read_ptr;

public:
    //constructor
    Ring(int c){
        if(c<=0) throw("illegal input");
        capacity = c;
        size = 0;
        write_ptr = new Node();
        read_ptr = write_ptr;
        Node* temp = write_ptr;
        for(int i = 1; i < c; i++){
            temp->next = new Node();
            temp = temp->next;
        }
        temp->next = write_ptr;
    };

    // destructor
    ~Ring(){
        Node* temp = write_ptr->next;
        Node* to_delete = temp;
        while(temp != NULL && temp != write_ptr){
            temp = temp->next;
            delete to_delete;
            to_delete=temp;
        }
        delete to_delete;
    };

    void put(int x){
        if(size == capacity) throw("Full list");

        write_ptr->data = x;
        write_ptr = write_ptr->next;
        size++;
        return;
    };

    int get(){
        if(size == 0) throw("Empty list");
        int x = read_ptr->data;
        read_ptr = read_ptr->next;
        size--;
        return x;
    };
};

int main(){
    Ring * r = new Ring(3);
    r->put(1);
    cout << r->get() << endl; // 1
    r->put(1);
    r->put(2);
    r->put(3);
    cout << r->get() << " " << r->get() << " " << r->get() << endl; // 1 2 3
    return 0;
}
