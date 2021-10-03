#include <iostream>

using namespace std;

class Node
{
public:
    // constructors
    Node(): data(0), next(NULL), previous(NULL) // default. Data is set to 0 by default
    {
    }
    Node(int data, Node* next, Node* previous): data(data), next(next), previous(previous) // personalized
    {
    }
    // destructor
    ~Node() 
    /* default because no data is allocated dynamically. 
    For the pointers, we only need to delete the pointers themselves (achieved by default) 
    because we do not necessarily want to delete the previous or the next Node in memory when we are removing "this" Node.
    */
    {
    }
    // data members
    int data;
    Node* next;
    Node* previous;
};

class DLLStructure
{
public:
    // constructors
    DLLStructure():first(NULL),last(NULL) // default, an empty list
    {}
    DLLStructure(int array[] , int size)
    /**
     * personalized constructor that will create a list from an array
     * 
     * @param an array of int containing the data for the list
     * @param size, the size of the list to be constructed
     */ 
    {
        // check if the array has content (assuming accurate size info)
        if(size<1){
            this->first = NULL;
            this->last = NULL;
        }
        // desired personalized input
        else{
            for(int i=0;i<size;i++){

                Node* newNode = new Node();
                newNode->data = array[i];

                // for the first element
                if(i==0){
                    // for the linked list:
                    this->first = newNode;

                    // for the node:
                    // previous = null by default
                    // "next" to be filled, or remains null if it is the last node
                }
                else{
                    // for the "last" node:
                    this->last->next = newNode; // The "next" of the last node in the list is this new node.
                    
                    // for the new node:
                    newNode->previous = this->last; // The "previous" of the new node is the last node in the original list.
                    // the "next" of this new node to be filled, or remains null if it is the last node
                }
                // update the last node of the list
                this->last = newNode;
            }
        }
    };

    // destructor
    ~DLLStructure(){
        Node* temp;
        while(this->first != NULL && this->first->next != NULL){
            temp = this->first->next;
            delete this->first;
            this->first=temp;
        }
        //temp would point to NULL after the loop. No need to delete. (reference: https://stackoverflow.com/questions/13223399/deleting-a-pointer-in-c)
    };

    
    void PrintDLL(){
    /**
     * loop over all the elements in the list and print their values to the screen
     */ 
        if(this->first == NULL){
            cout << "Empty List" << endl;
        }
        else{
            Node* print = this->first;
            while(print->next != NULL){
                cout << print->data << " ";
                print = print->next;
            }
            cout << print->data << endl;
        }
    }
    
    
    void InsertAfter(int valueToInsertAfter, int valueToBeInserted){
    /**
     * Insert a new element in the linked list, after the first occurence of the value 
     * provided by the first argument, and having the value provided in the second argument.
     * 
     * If valueToInsertAfter was not found in the list, new value will be added at the end of the list.
     * 
     * @param valueToInsertAfter
     * @param valueToBeInserted
     */

        // if the list is empty
        if(this->first == NULL){
            Node* newNode = new Node(valueToBeInserted,NULL,NULL);
            this->first = newNode;
            this->last = newNode;
        }
        else{
            Node* NodeToInsertAfter = this->first;
            while(NodeToInsertAfter!=NULL){
                if(NodeToInsertAfter->data == valueToInsertAfter){
                    Node* newNode = new Node(valueToBeInserted,NULL,NULL);
                    // check if already at the end of the list
                    if(NodeToInsertAfter->next == NULL){
                        this->last = newNode;
                    }
                    else{ //in the middle of the list
                        NodeToInsertAfter->next->previous = newNode;
                        newNode->next = NodeToInsertAfter->next;
                    }  

                    NodeToInsertAfter->next = newNode;
                    newNode->previous = NodeToInsertAfter;
                    break;
                }
                else{
                    NodeToInsertAfter=NodeToInsertAfter->next;
                }
            }
            // value to insert after not found
            if(NodeToInsertAfter==NULL){
                Node* newNode = new Node(valueToBeInserted,NULL,this->last);
                this->last->next = newNode;
                this->last = newNode;
            }
        }
    }


    void Delete(int value){
    /**
     * Delete the first occurence of the value provided as argument. 
     * If the value does not exist, do nothing.
     * 
     * @param value: value to be deleted
     */ 
        if(this->first != NULL){ // if the list is empty, do nothing
            Node* find = this->first;

            // if the value is at the head
            if(find->data == value){
                find->next->previous = NULL;
                this->first = find->next;
                delete find;
            }

            else{           
                while(find != NULL){
                    if(find->data == value){
                        find->previous->next = find->next;
                        //if the value is at the end
                        if(find->next == NULL){
                            this->last = find->previous;
                        }
                        else{//in the middle
                            find->next->previous = find->previous;
                        }
                        delete find;
                        break;
                    }
                    find = find->next;
                }
            }
        }
    }

    
    void Sort(){
    /**
     * Sort the elements in ascending order
     */ 
        if(this->IsEmpty()==false || this->first->next==NULL){ //if empty or only one node, do nothing
            Node* current;
            Node* index;
            for(current = this->first; current->next != NULL; current = current->next) {  
                //Index will point to the node next to current  
                for(index = current->next; index != NULL; index = index->next) {  
                    //If current's data is greater than index's data, swap the data of current and index  
                    if(current->data > index->data) {  
                        int swap = current->data;  
                        current->data = index->data;  
                        index->data = swap;  
                    }  
                }  
            }  

        }
    }

    
    bool IsEmpty(){
    /**
     * @return TRUE if the list is empty, and FALSE otherwise    
     */ 
        if(this->first == NULL){
            return true;
        }
        else{
            return false;
        }
    }

    
    int getHead(){
    /**
     * @return value at the head element, or NULL if the list is empty
     */   
        if(this->first == NULL){
            return NULL;
        }
        else{
            return this->first->data;
        }
    }

    int getTail(){
    /**
     * @return value at the tail element, or NULL if the list is empty
     */   
        if(this->first == NULL){
            return NULL;
        }
        else{
            return this->last->data;
        }
    }

    
    int getSize(){
    /**
     * @return the number of elements present in the list
     */    
        if(this->first == NULL ){
            return 0;
        }
        else{
            int i=1;
            Node* count = this->first;
            while(count->next!=NULL){
                i++;
                count = count->next;
            }
        }
    }

    
    int getMax(){
    /**
     * @return the maximum data value present in the list, or NULL if the list is empty
     */ 
        if(this->IsEmpty()){
            return NULL;
        }
        else{
            int max = this->first->data;
            Node* count = this->first->next;
            while(count!=NULL){
                if(count->data > max){
                    max = count->data;
                }
                count=count->next;
            }
            return max;
        }
    }

    int getMin(){
    /**
     * @return the minimum data value present in the list, or NULL if the list is empty
     */ 
        if(this->IsEmpty()){
            return NULL;
        }
        else{
            int min = this->first->data;
            Node* count = this->first->next;
            while(count!=NULL){
                if(count->data < min){
                    min = count->data;
                }
                count=count->next;
            }
            return min;
        }
    }

    
    DLLStructure(DLLStructure& dlls){
    /**
     * Copy constructor for a Doubly Linked List
     * Copy all elements to a newly created DLLStructure
     * 
     * @param dlls, a reference to the DLLStructure object to be copied
     */ 
        if(dlls.IsEmpty()){
            this->first = NULL;
            this->last = NULL;
        }
        else{
            Node* current = dlls.first;
            //for the head node
            Node* newNode = new Node();
            newNode->data=current->data;
            this->first = newNode;
            this->last = newNode;

            //for the rest
            for(current = dlls.first->next; current != NULL; current = current->next){

                Node* newNode = new Node();
                newNode->data =current->data;

                this->last->next = newNode; 
                    
                newNode->previous = this->last; 

                // update the last node of the list
                this->last = newNode;
            }
        }
    }
private:
    // data members
    Node* first;
    Node* last;
};

int main(){
    int array[5] = {11, 2, 7, 22, 4};
    DLLStructure dll(array,5);
    dll.PrintDLL();
    
    dll.InsertAfter(7,13);
    dll.PrintDLL();
    dll.InsertAfter(25,7);
    dll.PrintDLL();
    
    dll.InsertBefore(7,26);
    dll.PrintDLL();
    dll.InsertBefore(19,12);
    dll.PrintDLL();
    
    dll.Delete(22);
    dll.PrintDLL();
    
    dll.Sort();
    dll.PrintDLL();
    
    if(dll.IsEmpty()){
        cout << "The list is empty" << endl;
    }
    
    cout << "Head element is: " << dll.getHead() << endl;
    cout << "Tail element is: " << dll.getTail() << endl;
    
    cout << "Number of elements in the list is: " << dll.getSize()<<endl;
    
    cout << "Max element is: " << dll.getMax() << endl;
    cout << "Min element is: " << dll.getMin() << endl;
    
    DLLStructure dll2(dll);
    dll2.PrintDLL();
    return 0;
}