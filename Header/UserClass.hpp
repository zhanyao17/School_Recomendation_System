#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <string>
#include "ReportClass.hpp"
#include "FavouriteClass.hpp"
using namespace std;

struct UserNode
{
    string email;
    string password;
    string name;
    string gender;
    string country;
    FavouriteList favouriteList;
    string registerDate;
    string lastLoginDate;
    UserNode* nextAdd;
    UserNode* prevAdd;
};


class UserList
{
    UserNode* head = NULL;
    UserNode* tail = NULL;
    ReportList reportList;
public:
    UserNode* CreateNewNode(
        string email,
        string password,
        string name,
        string gender, 
        string country, 
        string favouriteUniversity[],
        string registerDate, 
        string lastLoginDate
    )
    {
        UserNode* newNode = new UserNode;
        newNode->email = email;
        newNode->password = password;
        newNode->name = name;
        newNode->gender = gender;
        newNode->country = country;
        
        for (int i = 0; i < 100; i++)
        {
            if (favouriteUniversity[i] == "") break;
            
            newNode->favouriteList.push(favouriteUniversity[i]);
        }

        newNode->registerDate = registerDate;
        newNode->lastLoginDate = lastLoginDate;
        newNode->nextAdd = NULL;
        newNode->prevAdd = NULL;
        return newNode;
    }

    void push(
        string email,
        string password,
        string name,
        string gender, 
        string country, 
        string favouriteUniversity[],
        string registerDate, 
        string lastLoginDate
    ){
        // create new node
        UserNode* newNode = CreateNewNode(email, password, name, gender, country, favouriteUniversity, registerDate, lastLoginDate);
        
        // when the list is empty
        if(head == NULL)
        {
            head = tail = newNode;
        }else{
            // insert to end
            tail->nextAdd = newNode;
            newNode->prevAdd = tail;
            tail = newNode;
        }
    }

    void displayList()
    {
        UserNode* current = head;
        int counter = 0, numOfUserPerPage = 10;
        string choice;
        
        cout << string(58, '=') << endl;
        cout << string(25,' ') << "User List" << string(25,' ') << endl;

        while(current != NULL){
            // print user details
            printUserDetail(current, counter);

            // keep track of printed No. of user
            counter++;

            // show 10 user for every page
            if (counter %numOfUserPerPage == 0 || current->nextAdd == NULL)
            {
                while(true){
                    // Action
                    cout << "Enter '<' for previous page, '>' for next page, 'm' to modify user detail, 'x' to exit" << endl;
                    cout << "Choice: "; 
                    cin >> choice;

                    if(choice == "<")
                    {
                        // show 10 previous User
                        if (counter == 10)
                        {
                            cout << "You are viewing the first page!" << endl;
                        }else{
                            int num = numOfUserPerPage*2 - 1;

                            // E.g 11-15, move 9 + 5 (remainder user) times instead of 9 only
                            if (current->nextAdd == NULL && counter%numOfUserPerPage != 0){
                                int difference = counter%numOfUserPerPage;

                                while (difference !=0){
                                    difference--;
                                    counter--;
                                    current = current->prevAdd;
                                }
                                num = numOfUserPerPage - 1;
                            }
                            for (int i = 0; i < num; i ++)
                            {
                                cout << i << endl;
                                // move backward 19 times
                                current = current->prevAdd;
                            }
                            counter -= num;
                            cout << "Counter: " << counter <<endl;
                            break;
                        }   
                    }
                    else if(choice == ">")
                    {
                        // Move to next 10 user
                        if(current->nextAdd == NULL){
                            cout << "You are at the end of the list!" << endl;
                        }else{
                            counter++;
                            current = current->nextAdd;
                            break;
                        }
                    }
                    else if(choice == "m")
                    {
                        string userInput;
                        // modify the user
                        int remainderList = counter%numOfUserPerPage;
                        int numOfMoveBack = numOfUserPerPage - 1;

                        while(true)
                        {
                            cout << "Which user you want to edit? Enter No. ";

                            if (remainderList !=0)
                                // Display the range of user to be modify (only show the user at the current page)
                                cout << counter - remainderList + 1 << " - " << counter;
                            else
                                // Display the range of user to be modify (only show the user at the current page)
                                cout << counter - 9 << " - " << counter;

                            cout << " (Enter 'x' to cancel): ";

                            cin >> userInput;

                            try
                            {
                                int difference = counter - stoi(userInput);
                                
                                // when the current page/list do not have 10 user
                                if(remainderList != 0)
                                {
                                    numOfMoveBack = remainderList - 1;

                                    // check if the user input is in the correct range
                                    if(difference >= remainderList || difference < 0)
                                    {   
                                        // out of the current range
                                        // E.g. Page: 21 - 25 | input: 19 | remainder = 5 | different = 25 - 19 = 6 >= 5 (remainder)
                                        cout << "Out of range!" << endl;
                                        continue;
                                    }
                                }
                                else
                                {
                                    // check if the user input is in the correct range
                                    // out of the current range
                                    // E.g. Page: 21 - 30 | input: 20 | different = 30 - 20 = 10 > 9 
                                    if(difference > 9 || difference < 0)
                                    {
                                        cout << "Out of range!" << endl;
                                        continue;
                                    }
                                }
                                                                   
                                for (int j = 0; j < numOfMoveBack; j ++){ 
                                    if (difference == 0){
                                        ModifyUserData(current);

                                        // to avoid it edit again
                                        difference = 99;
                                        // move pointer backward one time
                                    
                                    }
                                    current = current->prevAdd;
                                    counter--;
                                    difference--;
                                }
                                // If difference == 0, means no modification made which also mean it is the first user out of the 10 user
                                // This is required because for-loop above exited when it reach the first user out of the 10 user, thus, modify function is not called
                                if (difference == 0){
                                    ModifyUserData(current);                                        
                                }
                            }
                            catch(const exception& e)
                            {   
                                if (userInput == "x"){
                                    break;
                                }
                                cout << "Invalid input, please enter number only!" << endl; 
                            }
                            break;
                        }
                        break;
                        
                    }
                    else if(choice == "x") return;
                    else cout << "Invalid input!" << endl; // handle invalid input
                    
                }
                counter--;
                continue;
            }
            current = current->nextAdd;
        }
    }

    void ModifyUserData(UserNode* current)
    {
        string userInput;
        cout << "What you want to edit?" << endl;
        cout << "1. Name" << endl; 
        cout << "2. Gender" << endl;
        cout << "3. Country" << endl ;
        cout << "4. Cancel Edit" << endl;
        cout << "Choice: ";
        
        while(true){
            cin.ignore();
            cin >> userInput;
            if(userInput == "1")
            {
                cout << "New Name: ";
                cin.ignore();
                getline(cin, userInput);
                current->name = userInput;
                cout << "Name updated successfully!" << endl;
                break;
            }
            else if(userInput == "2") 
            {
                if(current->gender == "Male")
                {
                    current->gender = "Female";
                }
                else
                {
                    current->gender = "Male";
                }
                cout << "Gender updated successfully!" << endl;
                break;
            }
            else if(userInput == "3") 
            {
                cout << "New Country: ";
                cin.ignore();
                getline(cin, userInput);
                current->country = userInput;
                cout << "Country updated successfully!" << endl;
                break;
            }
            else if(userInput == "4")
            {
                break;
            }
            else
            {
                cout << "Invalid Input!" << endl;
            }
        }
    }

    // # Function_Customer : Login 
    bool login_customer(string userId, string userPass){
        UserNode* current = head;
        // get today date
        time_t t = time(NULL);
        struct tm currentDate = *localtime(&t);
        string today = to_string(currentDate.tm_year + 1900) + "-" + to_string(currentDate.tm_mon + 1) + "-" + to_string(currentDate.tm_mday);
        
        while (current!=NULL)
        {
            if (current->email == userId && current->password == userPass)
            {
                current->lastLoginDate = today; // update login date
                return true;
            }
            current = current->nextAdd;
        }
        return false;
    }

    // # Function_Customer : Register
    void register_cutomer(string userId, string userPass,string name, string gender, string country) {
        // get today date
        time_t t = time(NULL);
        struct tm currentDate = *localtime(&t);
        string today = to_string(currentDate.tm_year + 1900) + "-" + to_string(currentDate.tm_mon + 1) + "-" + to_string(currentDate.tm_mday);
        
        // Create empty favourite list
        string newFavouriteList[100] = {};

        // push new node into it 
        push(userId,userPass,name,gender,country,newFavouriteList,today,today);
    }

    // # Function_Customer : Check repeat email
    bool checkRepeatEmail(string email){
        UserNode* current = head;
        while (current!=NULL)
        {
            if (current->email == email)
            {
                return false;
            }
            current = current->nextAdd;
        }
        return true;
    }

    // # Fuction_Customer : Return favorite list
    string* displayFavList_customer(string userId, int& size)
    {
        bool detected = false;
        UserNode* current = head;
        while (current != NULL && detected == false)
        {
            if (current->email== userId)
            {
                detected = true;
                size = current->favouriteList.getSize();
                return current->favouriteList.getList();
            }
            current = current->nextAdd;
        }
        return NULL;
    }

    // # Fucntion_Customer : Add new favourite item
    void addFavList_customer(string userId, string insti){
        UserNode* current = head;
        while (current!=NULL)
        {
            if (current->email == userId)
            {   
                if (current->favouriteList.getSize() == 100)
                    cout << "Opps.. your list is full. Removed some university to save new university";
                else if (current->favouriteList.checkDuplicate(insti))
                    cout << "This university had been favourited, so you can't favourite it again!" << endl;
                else 
                    current->favouriteList.push(insti);
                break;
            }
            current = current->nextAdd;
        }
    }

    string DeleteInactiveAccount()
    {
        UserNode* current = head;
        UserNode* temp = NULL;
        bool deletion = false;
        string accountDeleted = "";

        // Get today's date in time point
        auto today = std::chrono::system_clock::now();
        
        // if list is empty
        if(current == NULL)
        {
            cout << "The list is empty!" << endl;
            return "";
        }

        while(current != NULL){
            tm loginDate = {};
            istringstream ss(current->lastLoginDate);
            ss >> get_time(&loginDate, "%Y-%m-%d");

            // Convert the selected date to system_clock time
            auto login_time = chrono::system_clock::from_time_t(mktime(&loginDate));

            // Calculate the duration between selected time and today's time
            chrono::duration<double> elapsed_seconds =  today - login_time;

            // Convert the duration to days
            int days = chrono::duration_cast<chrono::hours>(elapsed_seconds).count() / 24;

            // delete the user if user has been inactive for a year 
            if (days >= 365)
            {
                if(current == head) // mean it is a head node
                {
                    head = head->nextAdd; // move head pointer to second node
                }
                else if(current == tail) // delete at end of the list
                {
                    tail = tail->prevAdd;
                }
                else
                { 
                    // delete in middle
                    current->prevAdd->nextAdd = current->nextAdd;
                    current->nextAdd->prevAdd = current->prevAdd;

                }

                cout << "Deleted User: " << setw(30) << left << current->name;
                cout << " - Inactive days: " << days << endl;
                temp = current;
                current = current->nextAdd;

                // record the deleted account email to delete their feedback
                accountDeleted += temp->email+"|";
                // delete the user feedback
                delete temp;

                deletion = true; 
            }else{
                current = current->nextAdd;
            }
        }
        if (!deletion){
            cout << "There is no inactive user currently - End delete action"<< endl;
        }
        return accountDeleted;
    }

    // search user
    void searchUser(string searchWord)
    {
        UserNode* current = head;
        bool noUserFound = true;
        int counter = 0;
        // print header/column
        cout << string(63, '=') << endl;
        cout << string(25,' ') << "Search Result" << string(25,' ') << endl;

        while(current!=NULL)
        {   
            string userDetail = current->name + current->country + current->gender;
            // if the detail contain the search keyword
            if(userDetail.find(searchWord) != string::npos)
            {
                // print row
                printUserDetail(current, counter);
                counter++;
                noUserFound = false;
            }
            current = current->nextAdd;
        }

        if(noUserFound)
        {
            cout << "No user found" << endl;
            cout << string (63, '=') << endl << endl;
        }
    }

    void loadCSV()
    {
        int position;

        string email, password, name, gender, country, favourite, registerDate, lastLoginDate;
        // Read data from csv file
        ifstream file("./CSV_Data/User_Details.csv");
        
        while(file.good())
        {
            string favouriteList[100];
            getline(file, email, ',');
            getline(file, password, ',');
            getline(file, name, ',');
            getline(file, gender, ',');
            getline(file, country, ',');
            getline(file, favourite, ',');
            getline(file, registerDate, ',');
            getline(file, lastLoginDate);

            if(email == "Email")
            {
                continue; // skip the first row/ heading
            }
            else if (email == "") // empty data
            {
                break;
            }
            int x = 0;
            while(favourite.length() != 0){
                position = favourite.find("|");
                favouriteList[x++] = favourite.substr(0, position);
                favourite.erase(0, position+1);
            }
            
            // Add data to linked list
            push(email, password, name, gender, country, favouriteList, registerDate, lastLoginDate);
        }
    }

    // Generate report for top 10 university prefered by parent
    void generateReport(){
        UserNode* current = head;
        
        // find top 10 favourited university
        while(current!= NULL){
            string* uniList = current->favouriteList.getList();

            for (int i = 0; i < current->favouriteList.getSize(); i++)
            {
                reportList.checkExistance(uniList[i]);
            }
            current = current->nextAdd;

            delete uniList; // free memory
        }
        
        reportList.displayList(); // show report
        reportList.deleteList(); // Delete list to free memory
    }

    void printUserDetail(UserNode* user, int counter){
        // print user details
        cout << string(58, '=') << endl;
        cout << "No. " << counter+1 << " - " << user->name << endl;
        cout << string(58, '=') << endl;
        cout << setw(22) << left << "Email: " << user->email << endl;
        cout << setw(22) << left << "Gender: " << user->gender << endl;
        cout << setw(22) << left << "Country: " << user->country << endl;
        cout << setw(22) << left << "Register Date: " << user->registerDate << endl;
        cout << setw(22) << left << "Last Login: " << user->lastLoginDate << endl;

        user->favouriteList.printList();
    }

    // void printFavList(UserNode* user)
    // {
    //     // check if any favourited university
    //     if (user->favouriteUniversity[0] == "")
    //     {
    //         cout << "Favourite University: None" << endl;
    //     }
    //     else
    //     {
    //         // print favourited university
    //         int numUniveristy = 1;
    //         cout <<  "Favourite University: " << endl;
    //         cout << string(58, '-') << endl;
    //         for (string university: user->favouriteUniversity){
    //             if (university == ""){
    //                 break;
    //             }
    //             cout << numUniveristy++ << ".\t" << university << endl;
    //         }
    //     }
    //     cout << string(58, '-') << endl;
    // }

    UserNode* splitList(UserNode* currentHead){
        UserNode* fastPtr;
        UserNode* slowPtr;

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

    UserNode* sortAndMergeList(UserNode* left, UserNode * right, bool desOrder){
        UserNode* mergedList =NULL;
        bool compareResult;
        // when left list is empty/ no more node left
        if(left == NULL){
            tail = right;
            return right;
        } // when right list is empty/ no more node left
        else if(right == NULL){ 
            tail = left;
            return left;
        }

        compareResult = left->name <= right->name;
        if (desOrder) compareResult = !compareResult;

        // compare node value of left and right list
        if (compareResult){
            // assign the left list to new linked list
            mergedList = left; 
            // call merge again without the node added to the list
            mergedList->nextAdd = sortAndMergeList(left->nextAdd, right, desOrder); 
        }else{
            // assign the right list to new linked list
            mergedList = right; 
            // call merge again without the node added to the list
            mergedList->nextAdd = sortAndMergeList(left, right->nextAdd, desOrder); 
        }

        // link next node's previous address to current node
        mergedList->nextAdd->prevAdd = mergedList; 
        mergedList->prevAdd = NULL;
        return mergedList;
    } 

    UserNode* mergeSort(UserNode* source, bool desOrder){
        // when only the linked list is empty or only have one node
        if(source == NULL || source->nextAdd == NULL){
            return source;
        }

        UserNode* left = source;

        // split the linked list into sub list (left and right)
        UserNode* mid = splitList(source);

        // break the linked list
        UserNode* right = mid->nextAdd;
        mid->nextAdd = NULL;
        right->prevAdd = NULL;

        // recursively call the function with left sub-list to divide itself until one element left
        left = mergeSort(left, desOrder);

        // recursively call the function with right sub-list to divide itself until one element left
        right = mergeSort(right, desOrder);
        
        // sort and merge back the left and right sub-lists, always return the head of sorted list
        return sortAndMergeList(left, right, desOrder);
    }

    void callMergeSort(bool desOrder)
    {
        head = mergeSort(head, desOrder);
        while(tail->nextAdd != NULL) tail = tail->nextAdd;
    }
};

#endif

