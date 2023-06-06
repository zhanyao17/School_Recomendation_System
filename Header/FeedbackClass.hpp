#include <iostream>
#include <iomanip>
using namespace std;
 
struct feedbackNode
{
    string userID;
    string feedback;
    string reply;
    string postDate;
    string replyDate;
    bool status;                     //true for replied, false for no reply 
    feedbackNode* prevAdd;
    feedbackNode* nextAdd;
};

class FeedbackList
{
    feedbackNode* head = NULL;
    feedbackNode* tail = NULL;

public:
    feedbackNode* CreateNewNode(
        string userID,
        string feedback,
        string reply,
        string postDate,
        string replyDate,
        bool status
    ){
        feedbackNode* newNode = new feedbackNode;
        newNode->userID = userID;
        newNode->feedback = feedback;
        newNode->reply = reply;
        newNode->postDate = postDate;
        newNode->replyDate = replyDate;
        newNode->status = status;
        newNode->nextAdd = NULL;
        newNode->prevAdd = NULL;

        return newNode;
    }

    void enqueue(
        string userID,
        string feedback,
        string reply,
        string postDate,
        string replyDate,
        bool status
    ){
        feedbackNode* newNode = CreateNewNode(userID, feedback, reply, postDate, replyDate, status);

        if(head == NULL){
            head = tail = newNode;
        }else{
            // insert to end
            tail->nextAdd = newNode;
            newNode->prevAdd = tail;
            tail = newNode;
        }
    }

    void displayFeedback(){
        feedbackNode* current = tail;
        int counter = 1;
        string choice, message;
        bool noFeedback = true;

        while(current!= NULL)
        {
            noFeedback = false;
            printFeedBackData(current, counter);

            while(true){
                cout << "Enter '<' for previous feedback, '>' for next feedback, 'r' to reply feedback, 'x' to exit" << endl;
                cout << "Choice: "; 
                cin >> choice;
                cout << endl;

                // the direction is reversed because start from tail to print from latest date
                if(choice == "<")
                {
                    // Move to previous feedback
                    if(counter == 1){
                        cout << "You are viewing the first feedback!" << endl;
                    }else{
                        counter--;
                        current = current->nextAdd;
                        break;
                    }
                       
                }
                else if(choice == ">")
                {
                    // Move to next feedback
                    if(current->prevAdd == NULL){
                        cout << "Opps... no more feedback" << endl;
                    }else{
                        counter++;
                        current = current->prevAdd;
                        break;
                    }
                   
                }
                else if(choice == "r")
                {
                    // Reply the feedback
                    if(current->status) // when the feedback has been reply
                    {
                        cout << "This feedback has been replied!" << endl;
                        cout << "New reply will overwrite the previous reply are you sure you want to continue? [Yes/No]: ";
                        while (true){
                            cin >> choice;
                            if(choice == "Yes" || choice == "yes")
                            {
                                cout << "Enter your message: ";
                                cin.ignore();
                                getline(cin, message);
                                current->reply = message;
                                current->replyDate = getTodayDate();
                                cout << "\nFeedback replied successfully!" << endl;
                                break;
                            }
                            else if(choice == "No" || choice == "no")
                            {
                                break;
                            }else
                            {
                                cout << "Invalid input! Please enter [Yes/No]: ";
                            }
                        }
                        
                    }else{
                        cout << "Enter your message: ";
                        cin.ignore();
                        getline(cin, message);
                        current->reply = message;
                        current->replyDate = getTodayDate();
                        cout << "\nFeedback replied successfully!" << endl;
                        current->status = true;
                    
                    }
                    break;
                }
                else if(choice == "x")
                {
                    // exit function
                    return;
                }
                else
                {
                    // handle invalid input
                    cout << "Invalid input!" << endl;
                }
            }
        }

        if (noFeedback) cout << "No feedback found..." << endl;
    }

    // # Function_Customer : Display Feedback
    void displayFeedback_customer(string userId){
        feedbackNode* current = tail;
        int counter = 1;
        string choice = "";
        bool moveNext = false, hasFeedback = false, deletedFeedback = false;

        while(current!= NULL)
        {
            if(current->userID == userId)
            {
                hasFeedback = true;
                printFeedBackData(current, counter);

                while(true){
                    cout << "Enter '<' for previous feedback, '>' for next feedback, 'd' to delete feedback, 'x' to exit" << endl;
                    cout << "Choice: "; 
                    cin >> choice;
                    cout << endl;

                    if(choice == "<")
                    {
                        // Move to previous feedback
                        if(counter == 1){
                            cout << "You are viewing the first feedback!" << endl;
                        }else{
                            counter--;
                            current = current->nextAdd; 
                            moveNext = true;
                            break;
                        }
                        
                    }
                    else if(choice == ">")
                    {
                        // backup the current node first
                        feedbackNode* temp = current;
                        // check if any more feedback for the user
                        while(current->prevAdd != NULL)
                        {   
                            if(current->prevAdd->userID == userId)
                            {          
                                counter++;
                                moveNext = false;
                                current = current->prevAdd;
                                break;
                            }
                            current = current->prevAdd;
                        }
                        if (current->prevAdd == NULL)
                        {
                            cout << "Opps... no more feedback" << endl;
                            current = temp;                           
                        }
                        else 
                        {
                            break;
                        }                  
                    }
                    else if (choice == "d")
                    {
                        while(true)
                        {
                            cout << "Are you sure you want to delete this feedback? [Yes/No]: ";
                            cin >> choice;

                            if(choice == "Yes" || choice == "yes")
                            { 
                                deletedFeedback = true;
                                feedbackNode* temp = current;
                                if(counter == 1)
                                {
                                    moveNext = false;
                                    current= current->prevAdd;
                                }
                                else
                                {
                                    moveNext = true;
                                    counter--;
                                    current = current->nextAdd;
                                }
                                deleteFeedback(temp);
                                break;
                            }
                            else if(choice == "No" || choice == "no") break;
                            else cout << "Error: Invalid Input!" << endl;
                        }
                        break;

                    }
                    else if(choice == "x")
                    {
                        return;
                    }
                    else
                    {
                        // handle invalid input
                        cout << "Invalid input!" << endl;
                    }
                }
            }
            else
            {
                if(moveNext)
                    current = current->nextAdd;
                else
                    current = current->prevAdd;
            }
                 
        }
        if(deletedFeedback) cout << "Opps... No more feedback. Post one now!" << endl; 
        if(!hasFeedback) cout << "You did not post any feedback yet. Post one now!" << endl;
    }

    // Add new feedback
    void postFeedBack(string userId)
    {
        string message;
        cout << "Enter your feedback: ";
        cin.ignore();
        getline(cin, message); // get feedback
        
        // add new data into linked list
        enqueue(userId, message,"", getTodayDate(), "", false);
        cout << "\nFeeback posted successfully!"<< endl;

    }

    // delete feedback from the list
    void deleteFeedback(feedbackNode* current, bool output = true)
    {
        // if feedback at head
        if(current == head)
        {
            head = head->nextAdd; 
            if(head == NULL)
                tail = NULL;
            else
                head->prevAdd = NULL;
            delete current;
        }
        // Feedback at end of the list
        else if (current == tail)
        {
            tail = tail->prevAdd;
            if(tail == NULL)
                head = NULL;
            else
                tail->nextAdd = NULL;
            delete current;
        }
        else
        {
            current->prevAdd->nextAdd = current->nextAdd;
            current->nextAdd->prevAdd = current->prevAdd;
            delete current;
        }
        // if deleted by admin don't display
        if(output) cout << "Feedback has been deleted!" << endl;
    }

    // search the user to delete feedback based on email
    void deleteFeedback(string email)
    {
        feedbackNode* current = head;
        while(current != NULL)
        {
            if(current->userID == email)
            {
                deleteFeedback(current, false);
            }
            current = current->nextAdd;
        }
    }
        
    // Read data from csv file
    void loadCSV()
    {
        string userId, feedback, reply, postDate, replyDate, status;
        // Read data from csv file
        ifstream file("./CSV_Data/Feedback_Details.csv");

        while(file.good())
        {
            getline(file, userId, ';');
            getline(file, feedback, ';');
            getline(file, reply, ';');
            getline(file, postDate, ';');
            getline(file, replyDate, ';');
            getline(file, status);
        

            if(userId == "User_ID")
            {
                continue; // skip the first row/ heading
            }
            else if (userId == "") // empty data
            {
                break;
            }
        
            // Add data to linked list
            enqueue(userId, feedback, reply, postDate, replyDate, status=="TRUE");
        }
    }

    // get today date
    string getTodayDate()
    {
        time_t t = time(NULL);
        struct tm currentDate = *localtime(&t);
        return to_string(currentDate.tm_year + 1900) + "-" + to_string(currentDate.tm_mon + 1) + "-" + to_string(currentDate.tm_mday);
    }
    
    // Print feedback details
    void printFeedBackData(feedbackNode* current, int counter)
    {
        cout << string(75, '=') << " Feedback - "<< counter << " " << string(75, '=') << endl; 
        cout << "Email: " << current->userID << "\tPosted At: " << current->postDate << endl;
        cout << string(164, '-') << endl;
        cout << "Feedback: " << endl;
        cout << current->feedback << endl;
        cout << string(164, '-') << endl;
        cout << "Reply:" << endl;
        if(current->status){
            cout << current->reply << endl;
        }else{
            cout << "* No reply yet :( *" << endl;
        }
        
        cout << string(164, '=') << endl;;
    }
};