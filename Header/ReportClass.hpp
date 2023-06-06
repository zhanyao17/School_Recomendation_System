#include <iostream>
using namespace std;


struct favouriteUniNode
{
    string name;
    int occurance;
    favouriteUniNode* nextAdd;
};

class ReportList{
    favouriteUniNode* head = NULL;
    
public:
    // create new node
    favouriteUniNode* createNewNode(string name){
        favouriteUniNode* newNode = new favouriteUniNode;
        newNode->name = name;
        newNode->occurance = 1;
        newNode->nextAdd = NULL;
        return newNode;
    }

    // Insert to the front
    void push(string name){
        favouriteUniNode* newNode = createNewNode(name);

        // when the list is empty
        if(head == NULL)
        {
            head = newNode;
        }else{
            newNode -> nextAdd = head;
            head = newNode;
        }
    }    
 
    // check if the university existed in the linked list
    void checkExistance(string name){
        favouriteUniNode* current = head;

        while (current != NULL)
        {
            if(current->name == name){
                current->occurance = current->occurance + 1;
                return;
            }
            current = current->nextAdd;
        }
        // Add the university if not exist
        push(name);
    }
    
    // Display the top 10 university
    void displayList(){
        
        int counter = 1;
        head = mergeSort(head); // sort the university in descending order
        cout << string(100, '=') << endl;
        cout << string(38, ' ') << "Top 10 University Report" << string(38, ' ') << endl;
        cout << string(100, '=') << endl;
        cout << setw(1) << "|" << setw(5) << left << "No." << setw(1) << "|" << setw(82) << left << "Institution" << setw(1) << "|" << setw(9) << right << "Frequency" << setw(1) << "|" << endl;
        cout << string(100, '=') << endl;

        favouriteUniNode* current = head;

        while(current!= NULL && counter != 11){
            cout << setw(1) << "|" << setw(5) << left << counter << setw(1) << "|" << setw(82) << left << current->name << setw(1) << "|" << setw(9) << right << current->occurance << setw(1) << "|" << endl;         
            cout << string(100, '-') << endl;
            current = current->nextAdd;
            counter++;
        }
        cout << endl;
    }

    // Delete the entire linked list to free the memory
    void deleteList()
    {
        favouriteUniNode* current;
        while(head != NULL)
        {
            current = head;
            head = head->nextAdd;
            delete current;
        }
    }

    // Divide the linked list into half (left and right sub-list)
    favouriteUniNode* splitList(favouriteUniNode* currentHead){
        favouriteUniNode* fastPtr;
        favouriteUniNode* slowPtr;

        // when the linked list is empty or only have one node
        if(currentHead == NULL || currentHead ->nextAdd == NULL){
            return currentHead; // address of head pointer
        }else{
            slowPtr = fastPtr = currentHead;
            
            // stop when the fast pointer reach end or detected NULL
            while(fastPtr->nextAdd!=NULL && fastPtr->nextAdd->nextAdd!= NULL){
                fastPtr = fastPtr->nextAdd->nextAdd; // move 2 step
                slowPtr = slowPtr->nextAdd; // move 1 step
            }
        }
        return slowPtr; // return the middle node
    }

    // Merge the left and right sub-list
    favouriteUniNode* sortAndMergeList(favouriteUniNode* left, favouriteUniNode * right){
        favouriteUniNode* mergedList =NULL;
        // when left list is empty/ no more node left
        if(left == NULL){
            return right;
        } // when right list is empty/ no more node left
        else if(right == NULL){ 
            return left;
        }

        // compare node value of left and right list
        if (left->occurance >= right->occurance){
            // assign the left list to new linked list
            mergedList = left; 
            // call merge again without the node added to the list
            mergedList->nextAdd = sortAndMergeList(left->nextAdd, right); 
        }else{
            // assign the right list to new linked list
            mergedList = right; 
            // call merge again without the node added to the list
            mergedList->nextAdd = sortAndMergeList(left, right->nextAdd); 
        }
        // link next node's previous address to current node
        return mergedList;
    } 

    // main function of merge sort
    favouriteUniNode* mergeSort(favouriteUniNode* source){
        // when only the linked list is empty or only have one node
        if(source == NULL || source->nextAdd == NULL){
            return source;
        }

        favouriteUniNode* left = source;
        // split the linked list into sub list (left and right)
        favouriteUniNode* mid = splitList(source);
        favouriteUniNode* right = mid->nextAdd;
        
        mid->nextAdd = NULL;// break the linked list

        // recursively call the function with left sub-list to divide itself until one element left
        left = mergeSort(left);

        // recursively call the function with right sub-list to divide itself until one element left
        right = mergeSort(right);
        
        // sort and merge back the left and right sub-lists, always return the head of sorted list
        return sortAndMergeList(left,right);
    }


    
};


