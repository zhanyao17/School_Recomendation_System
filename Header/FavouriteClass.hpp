#include <iostream>
using namespace std;


struct favouriteNode
{
    string name;
    favouriteNode* nextAdd;
};

class FavouriteList{
    favouriteNode* head = NULL;
    int size = 0;
    
public:
    // create new node
    favouriteNode* createNewNode(string name){
        favouriteNode* newNode = new favouriteNode;
        newNode->name = name;
        newNode->nextAdd = NULL;
        return newNode;
    }

    // Insert to the front
    void push(string name){
        favouriteNode* newNode = createNewNode(name);

        // when the list is empty
        if(head == NULL)
        {
            head = newNode;
        }else{
            newNode -> nextAdd = head;
            head = newNode;
        }
        size++;
    }    
 
    // check if the university existed in the linked list
    bool checkDuplicate(string name){
        favouriteNode* current = head;

        while (current != NULL)
        {
            if(current->name == name){
                return false;
            }
            current = current->nextAdd;
        }
        // return true if not duplicated
        return true;
    }

    void printList()
    {
        // check if any favourited university
        if (size == 0)
            cout << "Favourite University: None" << endl;
        else
        {
            favouriteNode* current = head;
            int numUniversity = 1;
            
            // print favourited university
            cout <<  "Favourite University: " << endl;
            cout << string(58, '-') << endl;

            while (current != NULL)
            {
                cout << numUniversity++ << ".\t" << current->name << endl;
                current = current->nextAdd;
            }
        }
        cout << string(58, '-') << endl;
    }

    string* getList()
    {
        if (size == 0)
            return NULL;

        string* arrayList = new string[size];
        int count = 0;
        favouriteNode* current = head;
        while (current != NULL)
        {
            arrayList[count++] = current->name;
            current = current->nextAdd;
        }
        return arrayList;
    }

    int getSize()
    {
        return size;
    }
    
    
};


