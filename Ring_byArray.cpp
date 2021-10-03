#include <iostream>

using namespace std;

class Ring{
private:
    int size;
    int capacity;
    int* data; 
    int write_ptr;
    int read_ptr;
    
public:
    //constructor
    Ring(int c){
        if(c<=0) throw("Illegal input");
        capacity = c;
        data = new int[capacity]();
        write_ptr=read_ptr=-1;        
        size = 0;
    }

    //destructor
    ~Ring(){
        delete data;
    }

    void put(int x){
        if(size == capacity) throw("Ring is full.");

        if(size==0){
            write_ptr = read_ptr = 0;
        }
        else{
            write_ptr = (write_ptr+1)%capacity;
        }
        *(data+write_ptr) = x;
        size++;
        return;
    }

    int get(){
        if(size == 0) throw("Ring is empty");
        
        int i = *(data+read_ptr);
        read_ptr = (read_ptr+1)%capacity;
        size--;
        return i;
    }

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
