#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m;

class Node
{
public:
    // constructor
    Node(int data): data(data), next(NULL)
    {
    }
    // destructor - default
    ~Node() {}
    // data members
    int data;
    Node* next;
};

class Queue
{
public:
    // constructor
    Queue():first(NULL),last(NULL) // default, an empty queue
    {}

    // destructor
    ~Queue(){
        Node* temp;
        while(first != NULL && first->next != NULL){
            temp = first->next;
            delete first;
            first=temp;
        }
        delete first;
    };

    void enqueue(int x){
        m.lock();
        cout << "enqueue starts" << x <<  endl; 
        Node* n = new Node(x);

        // empty queue
        if (last == NULL){
            first = last = n;
        }
        // non-empty queue - add to the end of the queue
        else{
            last->next = n;
            last = n;
        }
        cout << "enqueue ends"<< x <<  endl; 
        m.unlock();
    }

    void dequeue(){
        m.lock();
        cout << "dequeue starts" <<  endl; 
        // empty queue
        if(first != NULL){
            Node* temp = first;
            first = first->next;
            delete temp;

            if(first == NULL) last = NULL;
        }
        cout << "dequeue ends" <<  endl; 
        m.unlock();
        return;
    }

    void findAndRemove(Node* node){
        m.lock();
        if( first != NULL ) {
            Node* temp = first;
            Node* prev = NULL;
            while(temp != NULL){
                if(temp->data == node->data){
                    // if the target is the first node
                    if(prev == NULL) first = temp->next;

                    else prev->next = temp->next;

                    // if the target is the last node
                    if(temp == last) last = prev;

                    delete temp;
                    m.unlock();
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
        }
        m.unlock();
        return;
    }

    // data members
    Node* first;
    Node* last;
};

int main()
{
    Queue * q = new Queue();
    /*
    q->enqueue(1);
    q->enqueue(2);
    cout << "Queue Head: " << q->first->data << endl; //1
    cout << "Queue Last: " << q->last->data << endl; //2
    q->dequeue();
    q->dequeue();
    q->enqueue(3);
    q->enqueue(4);
    q->enqueue(5);
    q->findAndRemove(new Node(3));
    cout << "Queue head: " << q->first->data << endl; //4
    cout << "Queue Last: " << q->last->data; //5
    */

    //thread en1(q,Queue::enqueue(1)); // error: cannot call member function 'void Queue::enqueue(int)' without object
    //thread en1(q.enqueue(1)); // error: invalid use of void expression
    thread en1(&Queue::enqueue, q, 1); // or en1(Queue::enqueue,...)?
    int a = 5;
    thread en2(&Queue::enqueue, q, 2);
    int b = 2;
    thread de1(&Queue::dequeue, q);
    int c = 3;
    thread en3(&Queue::enqueue, q, 3);
    int d = 4;
    thread en4(&Queue::enqueue, q, 4);
    int e = 1;
    thread de2(&Queue::dequeue, q);
    //thread rmv3(Queue::findAndRemove, q, (new Node(2)));


    en1.join();
    en2.join();
    de1.join();
    en3.join();
    en4.join();
    de2.join();
    //rmv3.join();

    cout << "Queue Head: " << q->first->data << endl; 
    cout << "Queue Last: " << q->last->data << endl; 
    return 0;
}