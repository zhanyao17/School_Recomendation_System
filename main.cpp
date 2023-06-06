#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <chrono>
#include <iomanip>
#include <sstream>
#include "Header/UserClass.hpp"
#include "Header/FeedbackClass.hpp"
#include "Header/UniversityClass.hpp"
#include "Header/AdminClass.hpp"
using namespace std;
using namespace std::chrono;

// intialize classes
// UserList ul;
UserList* ul = new UserList();
FeedbackList feedbackList;
UniversityList uni;
AdminList adminList;


// # Print R customer sort menu Page
void customer_sort_menu_page(){
    cout << string(50,'-') << endl; 
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout <<"   ** Sort by Ascending or Descending Order **" << endl;
    cout << "Enter 1: Ascending order."<< endl;
    cout << "Enter 2: Descending order."<< endl;
    cout << "Enter 00: Back" << endl << endl;
}


void adminMenu(){
    int choice , position= 0;
    string userInput, account, adminId, password;

    while(true)
    {   
        cout << string(50, '-') << endl;
        cout<<  string(14, ' ') << "** Login as Admin **" << endl << endl;
        cout << "Please enter your admin ID and password (Enter [x] to exit)" << endl;
        cout << "Admin ID: ";
        cin >> adminId;
        if (adminId == "x") return;
        cout << "Password: ";
        cin >> password;
        if (password == "x") return;

        if(adminList.login(adminId, password)) break;
        else cout << "Invalid email or password" << endl;
    }

    cout << "Login Successfully!" << endl;

    while(true){
        cout << string(50, '-') << endl;
        cout << string(14, ' ') << "** Admin Main Page **" << endl << endl;
        cout << "Enter 1: View all registered users' details" << endl; 
        cout << "Enter 2: Sort register user record" << endl;        
        cout << "Enter 3: Search user" << endl;                                  
        cout << "Enter 4: Delete inactive accounts" << endl;                         
        cout << "Enter 5: View latest feedback" << endl;                         
        cout << "Enter 6: Add new university" << endl;                                                     
        cout << "Enter 7: Generate top 10 favorite universities report" << endl; 
        cout << "Enter 8: View all university" << endl; 
        cout << "Enter 9: Sort university" << endl; 
        cout << "Enter 10: Search university" << endl; 
        cout << "Enter 11: Logout" << endl << endl;
        cout << string(15, '=') << endl;
        cout << "Type Here: ";
        cin >> choice;
        cout << string(15, '=') << endl;

        switch (choice)
        {
        case  1:
            ul->displayList();
            break;
        case  2:
            while(true)
            {
                cout << string(50,'-') << endl; 
                cout << "\t  ** Sort Menu Page **" << endl<<endl;
                cout << "1. Sort by ascending order." << endl;
                cout << "2. Sort by descending order." << endl;
                cout << "00. Back." << endl;
                cout <<string(15,'=') << endl;
                cout << "Type Here: ";
                cin >> userInput;
                cout << string(15,'=') << endl;
                cout << string(50,'-') << endl << endl; 
                if (userInput == "1")
                {
                    ul->callMergeSort(false);
                    ul->displayList(); 
                    break;
                }
                else if (userInput == "2") 
                {
                    ul->callMergeSort(true);
                    ul->displayList(); 
                    break;
                }
                else if (userInput == "00") break;
                else cout << "Error: Invalid input!" << endl;
            }
            break;
        case  3:
            cout << "Search Anything: ";
            cin.ignore();
            getline(cin, userInput);
            ul->searchUser(userInput);
            break;
        case  4:
            account = ul->DeleteInactiveAccount();
            
            while(account.length() != 0){
                position = account.find("|");
                // delete feedback based on deleted account
                feedbackList.deleteFeedback(account.substr(0, position));
                account.erase(0, position+1);
            }
            break;
        case  5:
            feedbackList.displayFeedback();
            break;
        case  6:
            uni.addNewUniversity();
            break;
        case  7:
            ul->generateReport();  
            break;
        case  8:
            uni.displayData(false);
            
            break;
        case  9:
            while (true)
                {
                    // Sort based on what score
                    string action_1;
                    cout << string(50,'-') << endl; 
                    cout <<"\t  ** Sort Score Menu Page **" << endl<<endl;
                    cout << "Enter 1: Sort by Academic Reputation Score (ArScore)."<< endl; 
                    cout << "Enter 2: Sort by Faculty/Student Ratio Score (FsrScore)."<< endl; 
                    cout << "Enter 3: Sort by Employer Reputation Score (ErScore)."<< endl;
                    cout << "Enter 00: Back."<< endl<< endl;
                    cout <<string(15,'=') << endl;
                    cout << "Type Here: ";
                    cin >> action_1;
                    cout << string(15,'=') << endl;
                    cout << string(50,'-') << endl << endl; 

                    if (action_1 == "1")
                    {
                        customer_sort_menu_page(); // print sort menu page
                        string action_2;
                        cout <<string(15,'=') << endl;
                        cout << "Type Here: ";
                        cin >> action_2;
                        cout <<endl<<string(15,'=') << endl;
                        cout << string(50,'-') << endl; 

                        if (action_2 == "00") break;

                        if (action_2 == "1"){uni.rUser_sort_university("ArScore",false);} // show in asc order
                        else{uni.rUser_sort_university("ArScore",true);} // else show in desc order
                    }
                    else if (action_1 == "2")
                    {
                        customer_sort_menu_page(); 
                        string action_2;
                        cout <<string(15,'=') << endl;
                        cout << "Type Here: ";
                        cin >> action_2;
                        cout <<endl<<string(15,'=') << endl;
                        cout << string(50,'-') << endl; 

                        if (action_2 == "1"){uni.rUser_sort_university("FsrScore",false);} 
                        else{uni.rUser_sort_university("FsrScore",true);} 
                    }
                    else if (action_1 == "3")
                    {
                        customer_sort_menu_page();
                        string action_2;
                        cout <<string(15,'=') << endl;
                        cout << "Type Here: ";
                        cin >> action_2;
                        cout << endl<< string(15,'=') << endl;
                        cout << string(50,'-') << endl; 

                        if (action_2 == "1"){uni.rUser_sort_university("ErScore",false);} 
                        else{uni.rUser_sort_university("ErScore",true);}
                    }
                    else if (action_1=="00")
                    {
                        break;
                    }
                } 
            break;
        case  10:
            uni.rUser_search_university();
            break;
        case  11:
            return;  
        default:
            cout << "Error: Invalid Input" << endl;
            break;
        }
    }
}

// USER INTERFACE

// # Print R Customer Menu Page
void customer_menu(){
    cout << string(50,'-') << endl;
    cout <<"\t ** Register Customer Menu Page **" << endl<<endl;
    cout << "Enter 1: View university information."<< endl;
    cout << "Enter 2: Search University Details"<< endl;
    cout << "Enter 3: Favorite University Page."<< endl;
    cout << "Enter 4: Feedback Page."<< endl;
    cout << "Enter 5: Post Feedback."<< endl;
    cout << "Enter 00: Log Out." << endl << endl;
}


// # Customer register page
void customerRegister(UserList& userObject)
{
    string email,pass,name,gender,country;
    bool valid;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    
    while (true)
    {
        cout << "Enter your email :";
        getline(cin,email);
        // validate email format
        regex gamailPattern(R"([a-zA-Z0-9._%+-]+@gmail.com)");
        regex yahooPattern(R"([a-zA-Z0-9._%+-]+@yahoo.com)");
        regex hotmailPattern(R"([a-zA-Z0-9._%+-]+@hotmail.com)");
        valid = regex_match(email,gamailPattern);
        if (!valid)
        {
            valid = regex_match(email,yahooPattern);
            if (!valid)
            {
                valid = regex_match(email,hotmailPattern);
                if (!valid)
                {
                    cout << "Fail to proceed! Email format wrong, please enter again."<< endl<< endl;
                }
            }
        }
        // check repeat email
        if (valid)
        {
            valid = userObject.checkRepeatEmail(email);
            if (valid)
                break;
            cout << "Fail to proceed! Email had been used, please enter again."<< endl << endl;
        }
        

    }
    
    while (true)
    {
        regex containUpper{ "[A-Z]"};
        regex containLower{ "[a-z]"};
        regex containNumber{ "[0-9]"};
        regex containSpecial{ "[!@#$%^&*()?]"};
        cout << endl << "Enter your passwords :";
        getline(cin,pass);

        if (pass.length() < 8)
        {
            cout << "Password need to have at least 8 character!"<< endl << endl;
        }
        else if (!regex_search(pass, containUpper))
        {
            cout << "Password should contain at least one uppercase character!"<< endl << endl;
        }
        else if (!regex_search(pass, containLower))
        {
            cout << "Password should contain at least one lowercase character!"<< endl << endl;
        }
        else if (!regex_search(pass, containNumber))
        {
            cout << "Password should contain at least one number!"<< endl << endl;
        }
        else if (!regex_search(pass, containSpecial))
        {
            cout << "Password should contain at least one special character!"<< endl << endl;
        }
        else{
            break;
        }
    }
    while (true)
    {
        cout << endl << "Enter your name :";
        getline(cin,name);
        if (name.length() == 0)
        {
            cout << "Fail to proceed! name can't be null, please enter again."<< endl << endl;
        }else{
            break;
        }
    } 

    while (true)
    {
        cout << endl << "Enter your gender (Male / Female) :";
        getline(cin,gender); 
        if (name.length() == 0)
        {
            cout << "Fail to proceed! gender can't be null, please enter again."<< endl << endl;
        }else{
            if (gender == "Male" | gender == "male" | gender=="Female" | gender=="female")
            {
                break;
            }else{
                cout << "Fail to proceed! Gender format wrong."<<endl;
            }
        }
    }
    
    while (true)
    {
        cout << endl << "Enter which country do you live in :"; 
        getline(cin,country);
        if (country.length() == 0)
        {
            cout << "Fail to proceed! country can't be null, please enter again."<< endl << endl;
        }else{
            break;
        }
    }
    
    // save record
    userObject.register_cutomer(email,pass,name,gender,country);
}

// # Non register function
void nonRegisterFunction(UniversityList& uni){
    while(true)
    {
        // Print out menu
        cout << string(50,'-') << endl;
        cout <<"\t ** Non-register Customer Menu Page **" << endl<<endl;
        cout << "Enter 1: View university Information."<< endl;
        cout << "Enter 2: View university Information (order university name with merge sort)."<< endl;
        cout << "Enter 3: View university Information (order university name with bubble sort)."<< endl;
        cout << "Enter 4: Search University Details"<< endl;
        cout << "Enter 00: Back." << endl << endl;
        string action;
        cout << string(15,'=')<<endl;
        cout << "Type here: ";
        cin >> action;
        cout <<string(15,'=') << endl;
        cout << string(50,'-')<<endl<<endl;

        if (action == "1") // outptu all data
        {
            uni.displayData(false); 
        }
        else if (action == "2") // merge sort data
        {
            while (true)
            {
                cout << "Enter 1: University Name in Ascending Order (Merge Sort)"<< endl;
                cout << "Enter 2: University Name in Descending Order (Merge Sort)"<< endl;

                cout << "Enter 00: Back" << endl;
                string action_1;
                cout << string(15,'=')<<endl;
                cout << "Type here: ";
                cin >> action_1;
                cout <<string(15,'=') << endl;
                cout << string(50,'-')<<endl<<endl;
                
                if (action_1 == "00")
                    break;

                // merge sort
                auto start = high_resolution_clock::now();
                uni.callMergeSort_nonRegis();
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop-start);
                cout << endl << string(39,'=') << endl;
                cout << "Execution time : " << duration.count() << " micro-seconds. " << endl;
                cout << string(39,'=') << endl << endl; 
                // display data in desc or asc
                if (action_1 == "1")
                {
                    uni.displayData(false);
                }
                else if (action_1 == "2")
                {
                    uni.displayData(true);
                }
                else{
                    cout << "Invalid input."<< endl;
                }
            }
        }
        else if (action == "3") // bubble sort data
        {
            cout << "Enter 1: University Name in Ascending Order (Bubble Sort)"<< endl;
            cout << "Enter 2: University Name in Descending Order (Bubble Sort)"<< endl;
            cout << "Enter 00: Back" << endl;
            string action_1;
            cout << string(15,'=')<<endl;
            cout << "Type here: ";
            cin >> action_1;
            cout <<string(15,'=') << endl;
            cout << string(50,'-')<<endl<<endl;
            
            if (action_1 == "00")
                break;
            
            auto start = high_resolution_clock::now();
            uni.bubbleSort(); // call bubble sort
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop-start);
            cout << endl << string(39,'=') << endl;
            cout << "Execution time : " << duration.count() << " micro-seconds. " << endl;
            cout << string(39,'=') << endl << endl; 
            
            // display data in desc or asc
            if (action_1 == "1")
            {
                uni.displayData(false);
            }
            else if (action_1 == "2")
            {
                uni.displayData(true);
            }
            else{
                cout << "Invalid input."<< endl;
            }
        }
        
        else if (action == "4") // searh uni
        {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            while (true)
            {                
                cout << endl <<string(50,'-') << endl;
                cout << "\tSelect search by which details"<< endl << endl;
                cout << "Enter 1: Search based on Institution name." << endl; // NOTE:
                cout << "Enter 2: Search based on Location name."<< endl;   // NOTE:
                cout << "Enter 00: Back" << endl;
                cout << string(50,'-') << endl;
                // Validate input
                string action_1;
                cout << string(15,'=')<<endl;
                cout << "Type here: ";
                getline(cin,action_1);
                cout << string(15,'=')<<endl;
                if (action_1 == "00")
                    break;
                
                if (action_1 == "1" || action_1 == "2")
                {
                    while (true)
                    {
                        cout << endl << string(50,'-') << endl;
                        cout << "\tSelect Search Algorithms" << endl << endl;
                        cout << "Enter 1: Linear Search Algorithms."<<endl;
                        cout << "Enter 2: Jump Search Algorithms."<<endl;
                        cout << "Enter 3: Linear Transition Search Algorithms."<<endl;
                        cout << "Enter 00: Back."<< endl;
                        cout << string(50,'-') << endl;
                        string action_2;
                        cout << string(15,'=')<<endl;
                        cout << "Type here: ";
                        getline(cin,action_2);
                        cout << string(15,'=')<<endl;

                        if (action_2 == "00")
                            break;
                        
                        try
                        {
                            int int_action_2 = stoi(action_2);
                            if (int_action_2 >=1 && int_action_2 <=3)
                            {
                                string attri;
                                if (action_1 == "1")
                                {
                                    attri = "Institution";
                                }
                                else{
                                    attri = "Location";
                                }
                                
                                // get keywords
                                string keywords;
                                cout << "Type the "<< attri<<" keywords here :";
                                getline(cin,keywords);
                                cout << endl;
                                if (int_action_2 == 1)
                                {
                                    auto start = high_resolution_clock::now();
                                    uni.linearSearch(keywords,attri); // Linear search
                                    auto stop = high_resolution_clock::now();
                                    auto duration = duration_cast<microseconds>(stop-start);
                                    cout << endl << string(39,'=') << endl;
                                    cout << "Execution time : " << duration.count() << " micro-seconds. " << endl;
                                    cout << string(39,'=') << endl;
                                }
                                else if (int_action_2 == 2)
                                {
                                    auto start = high_resolution_clock::now();
                                    uni.jumpSearch(keywords,attri,"string"); // jump search 
                                    auto stop = high_resolution_clock::now();
                                    auto duration = duration_cast<microseconds>(stop-start);
                                    cout << endl << string(39,'=') << endl;
                                    cout << "Execution time : " << duration.count() << " micro-seconds. " << endl;
                                    cout << string(39,'=') << endl;
                                }else
                                {
                                    auto start = high_resolution_clock::now();
                                    uni.linearTransition_nonRegis(keywords,attri,"string"); // linear transition search
                                    auto stop = high_resolution_clock::now();
                                    auto duration = duration_cast<microseconds>(stop-start);
                                    cout << endl << string(39,'=') << endl;
                                    cout << "Execution time : " << duration.count() << " micro-seconds. " << endl;
                                    cout << string(39,'=') << endl;
                                }
                            }
                            else{
                                cout << "Invalid input. (Out of range)"<< endl;
                            }
                        }
                        catch(const std::exception& e)
                        {
                            cout << "Invalid input."<< endl;
                        }
                    }
                }
                else{
                    cout << "Invalid Input." << endl;
                }
            }
        }
        
        else if (action == "00")
        {
            cout << "Back to previous page" << endl; 
            break;
        }

        else{
            cout << "Invalid Input."<< endl;
        }
    }
}

void userMenu(){
    // Customer variables
    bool loginResult = false;
    string userId,userPass;
    
    while (true)
    {
        // NOTE: Ouput menu 
        while (true) // Enter user menu
        {
            cout << string(50,'-')<<endl;
            cout <<"\t  ** Customer Main Page **" << endl << endl;
            cout << "Enter 1: Login."<< endl;
            cout << "Enter 2: First time? Reigster new account."<< endl;
            cout << "Enter 3: Continue without Register/Login." << endl;
            cout << "Enter 00: Back." << endl << endl;
            cout << string(15,'=')<<endl;
            string cust_action;
            cout << "Type Here: ";
            cin >> cust_action;
            cout <<string(15,'=') << endl;
            cout << string(50,'-')<<endl<<endl;
            
            if (cust_action== "1") // login page
            {
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                while (true)
                {
                    cout << string(50,'-') << endl;
                    cout << "\t  ** Customer Login Page **"<<endl<<endl;;
                    cout << "Enter your user email [X to cancel] : "; // johndoe@gmail.com
                    getline(cin,userId);
                    // wheen user cancel login action
                    if (userId == "X") 
                        break;
                    cout << "Enter your user password :"; // P@ssw0rd123
                    getline(cin,userPass);
                    
                    cout << string(50,'-') << endl; 
                    

                    
                    // validate login result
                    loginResult = ul->login_customer(userId,userPass);
                    if (!loginResult)
                    {
                        cout <<string(30,'=') << endl;
                        cout << "Invalid Email or Passwords !"<<endl;
                        cout << "Please try again." << endl;
                        cout <<string(30,'=') << endl;
                        continue;
                    }else{
                        break;
                    }
                }
                break;
            }

            else if (cust_action == "2") // Register
            {
                customerRegister(*ul);
                cout << "Congrats! You had register successfully."<<endl;
            }

            else if (cust_action == "3") // All user
            {  
                // call non register function
                nonRegisterFunction(uni);
            }

            else if (cust_action == "00")
            {
                cout << "Bye. "<< endl << endl;
                return;
            }
            
            else{ // NOTE: Should update
                cout << "Invalid Input" << endl;
            }
            
        }

        // Enter Customer Menu page
        while (loginResult)
        {   
            cout << endl << "Welcome back! "<< userId<< endl << endl;
            // Print customer menu
            customer_menu();
            
            // variables
            string action,action_1;

            // capture action
            cout <<string(15,'=') << endl;
            cout << "Type Here: ";
            cin >> action;
            cout <<string(15,'=') << endl;
            cout << string(50,'-') << endl; 
            cout << endl;
            // string* tempArray; 
            // Call sort university function
            if (action == "1")
            {
                while (true)
                {
                    // Sort based on what score
                    cout << string(50,'-') << endl; 
                    cout <<"\t  ** Sort Score Menu Page **" << endl<<endl;
                    cout << "Enter 1: View all University (page by page)."<< endl; 
                    cout << "Enter 2: Sort by Academic Reputation Score (ArScore)."<< endl; 
                    cout << "Enter 3: Sort by Faculty/Student Ratio Score (FsrScore)."<< endl; 
                    cout << "Enter 4: Sort by Employer Reputation Score (ErScore)."<< endl;
                    cout << "Enter 00: Back."<< endl<< endl;
                    cout <<string(15,'=') << endl;
                    cout << "Type Here: ";
                    cin >> action_1;
                    cout << string(15,'=') << endl;
                    cout << string(50,'-') << endl << endl; 

                    if (action_1 == "1")
                    {
                        int size = 0;
                        string* tempArray = ul->displayFavList_customer(userId, size); // get this to prevent user add this item twices
                        uni.rUser_display_seq_uni(tempArray,*ul,userId); // display uni in seq way (+favourite features) s
                        delete [] tempArray;
                    }
                    else if (action_1 == "2")
                    {
                        customer_sort_menu_page(); // print sort menu page
                        string action_2;
                        cout <<string(15,'=') << endl;
                        cout << "Type Here: ";
                        cin >> action_2;
                        cout <<endl<<string(15,'=') << endl;
                        cout << string(50,'-') << endl; 

                        if (action_2 == "00") break;

                        if (action_2 == "1"){uni.rUser_sort_university("ArScore",false);} // show in asc order
                        else{uni.rUser_sort_university("ArScore",true);} // else show in desc order
                    }
                    else if (action_1 == "3")
                    {
                        customer_sort_menu_page(); 
                        string action_2;
                        cout <<string(15,'=') << endl;
                        cout << "Type Here: ";
                        cin >> action_2;
                        cout <<endl<<string(15,'=') << endl;
                        cout << string(50,'-') << endl; 

                        if (action_2 == "1"){uni.rUser_sort_university("FsrScore",false);} 
                        else{uni.rUser_sort_university("FsrScore",true);} 
                    }
                    else if (action_1 == "4")
                    {
                        customer_sort_menu_page();
                        string action_2;
                        cout <<string(15,'=') << endl;
                        cout << "Type Here: ";
                        cin >> action_2;
                        cout << endl<< string(15,'=') << endl;
                        cout << string(50,'-') << endl; 

                        if (action_2 == "1"){uni.rUser_sort_university("ErScore",false);} 
                        else{uni.rUser_sort_university("ErScore",true);}
                    }
                    else if (action_1=="00")
                    {
                        break;
                    }
                }
            }
            // call search university function
            else if (action == "2"){uni.rUser_search_university();}
            
            // call favourite page 
            else if (action == "3")
            {
                int size = 0;
                // get fav list
                string* tempArray = ul->displayFavList_customer(userId, size);
                if (tempArray == NULL)
                {
                    cout << "** There is no favourite university added" << endl;
                    continue;
                }

                // display list
                uni.rUser_display_favourite_list(tempArray, size);   
                delete [] tempArray; // free memory       //NOTE:      
            }
            
            // Call Feedback page
            else if (action=="4")
            {
                feedbackList.displayFeedback_customer(userId);
            }
            // Post Feedback
            else if (action=="5")
            {
                feedbackList.postFeedBack(userId);
            }
            else if (action == "00")
            {
                break;
                cout << "**4 bye"<<endl;
            }
            
        }  
    
    }
}


int main(){
    ul->loadCSV();
    feedbackList.loadCSV();
    uni.loadCSV();
    adminList.loadCSV();

    while (true)
    {
        cout << "** Enter the system in which user? **" << endl <<endl;
        cout << "1. Admin User"<< endl;
        cout << "2. Normal User"<< endl;
        cout << "00. Back"<< endl << endl;
        cout << string(50,'-')<<endl;
        cout << "Type here :";
        string choices;
        cin >> choices;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << string(50,'-')<<endl<<endl;


        if (choices == "1")
        {
            adminMenu();
        }else if (choices == "2")
        {
            userMenu();
        }
        else if (choices == "00")
        {
            cout << "Bye."<< endl;
            break;
        }
        
        else
        {
            cout << "Invalid Input"<< endl;
        }
    }
    


    

    return 0;
}