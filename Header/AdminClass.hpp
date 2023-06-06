#include <iostream>
using namespace std;

struct adminNode
{
    string adminId;
    string password;
    string name;
    string registerDate;
    string lastLoginDate;
    adminNode* nextAdd;
};

class AdminList
{
    adminNode* head = NULL;

public:
    adminNode* CreateNewNode(
        string adminId,
        string password,
        string name,
        string registerDate,
        string lastLoginDate
    ){
        adminNode* newNode = new adminNode;
        newNode->adminId = adminId;
        newNode->password = password;
        newNode->name = name;
        newNode->registerDate = registerDate;
        newNode->lastLoginDate = lastLoginDate;
        newNode->nextAdd = NULL;
        return newNode;
    }

    // Insert to the front
    void push(
        string adminId,
        string password,
        string name,
        string registerDate,
        string lastLoginDate
    ){
        adminNode* newNode = CreateNewNode(adminId,password,name,registerDate,lastLoginDate);

        // when the list is empty
        if(head == NULL)
        {
            head = newNode;
        }else{
            newNode -> nextAdd = head;
            head = newNode;
        }
    }  

    // Read data from csv file
    void loadCSV()
    {
        string adminId, password, name, registerDate, lastLoginDate;
        // Read data from csv file
        ifstream file("./CSV_Data/Admin_Details.csv");

        while(file.good())
        {
            getline(file, adminId, ';');
            getline(file, password, ';');
            getline(file, name, ';');
            getline(file, registerDate, ';');
            getline(file, lastLoginDate);
        
            if(adminId == "Admin_ID")
            {
                continue; // skip the first row/ heading
            }
            else if (adminId == "") // empty data
            {
                break;
            }
        
            // Add data to linked list
            push(adminId, password, name, registerDate, lastLoginDate);
        }
    }

    bool login(string adminId, string password)
    {
        adminNode* current = head;
        while(current != NULL)
        {
            if(current->adminId == adminId)
            {
                return current->password == password;
            }
            current = current->nextAdd;
        }
        return false;
    }
};
