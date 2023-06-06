#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include <regex>
#include <iomanip>
using namespace std;
// using namespace std::chrono;


const string country[] = {"Argentina", "Armenia", "Australia", "Austria", "Azerbaijan", "Bahrain", "Bangladesh", "Belarus", "Belgium", "Bolivia", "Bosnia and Herzegovina", "Brazil", "Brunei", "Bulgaria", "Canada", "Chile", "China (Mainland)", "Colombia", "Costa Rica", "Croatia", "Cuba", "Cyprus", "Czech Republic", "Denmark", "Dominican Republic", "Ecuador", "Egypt", "Estonia", "Finland", "France", "Georgia", "Germany", "Ghana", "Greece", "Guatemala", "Honduras", "Hong Kong SAR", "Hungary", "India", "Indonesia", "Iran, Islamic Republic of", "Iraq", "Ireland", "Israel", "Italy", "Japan", "Jordan", "Kazakhstan", "Kenya", "Kuwait", "Kyrgyzstan", "Latvia", "Lebanon", "Lithuania", "Macau SAR", "Malaysia", "Malta", "Mexico", "Morocco", "Netherlands", "New Zealand", "Norway", "Oman", "Pakistan", "Palestinian Territory, Occupied", "Panama", "Paraguay", "Peru", "Philippines", "Poland", "Portugal", "Puerto Rico", "Qatar", "Romania", "Russia", "Saudi Arabia", "Serbia", "Singapore", "Slovakia", "Slovenia", "South Africa", "South Korea", "Spain", "Sri Lanka", "Sudan", "Sweden", "Switzerland", "Syrian Arab Republic", "Taiwan", "Thailand", "Tunisia", "Turkey", "Uganda", "Ukraine", "United Arab Emirates", "United Kingdom", "United States", "Uruguay", "Venezuela", "Vietnam"};
const string countryCode[] = {"AR", "AM", "AU", "AT", "AZ", "BH", "BD", "BY", "BE", "BO", "BA", "BR", "BN", "BG", "CA", "CL", "CN", "CO", "CR", "HR", "CU", "CY", "CZ", "DK", "DO", "EC", "EG", "EE", "FI", "FR", "GE", "DE", "GH", "GR", "GT", "HN", "HK", "HU", "IN", "ID", "IR", "IQ", "IE", "IL", "IT", "JP", "JO", "KZ", "KE", "KW", "KG", "LV", "LB", "LT", "MO", "MY", "MT", "MX", "MA", "NL", "NZ", "NO", "OM", "PK", "PS", "PA", "PY", "PE", "PH", "PL", "PT", "PR", "QA", "RO", "RU", "SA", "RS", "SG", "SK", "SI", "ZA", "KR", "ES", "LK", "SD", "SE", "CH", "SY", "TW", "TH", "TN", "TR", "UG", "UA", "AE", "UK", "US", "UY", "VE", "VN"};


// # university structure
struct universityNode
{
    // Attributes
    int Rank; 
    string Institution; 
    string LocationCode;
    string Location;
    float ArScore; int ArRank;
    float ErScore; int ErRank;
    float FsrScore; int FsrRank;
    float CpfScore; int CpfRank;
    float IfrScore; int IfrRank;
    float IsrScore; int IsrRank;
    float IrnScore; int IrnRank;
    float GerScore;int GerRank;
    float ScoreScaled;


    // next address
    universityNode* nextAdd;
    universityNode* prevAdd;
};

// * university class
class UniversityList
{
    universityNode* head = NULL;
    universityNode* tail = NULL;
    int size = 0;
public:
    // Create New Node
    universityNode *createNode(int Rank, string Institution, string LocationCode, string Location, float ArScore,
                       int ArRank, float ErScore, int ErRank, float FsrScore, int FsrRank, float CpfScore, int CpfRank,
                       float IfrScore, int IfrRank, float IsrScore, int IsrRank, float IrnScore, int IrnRank, float GerScore, int GerRank, float ScoreScaled)
    {
        universityNode* newNode = new universityNode;
        newNode->Rank = Rank;
        newNode->Institution = Institution;
        newNode->LocationCode = LocationCode;
        newNode->Location = Location;
        newNode->ArScore = ArScore;
        newNode->ArRank = ArRank;
        newNode->ErScore = ErScore;
        newNode->ErRank = ErRank;
        newNode->FsrScore = FsrScore;
        newNode->FsrRank = FsrRank;
        newNode->CpfScore = CpfScore;
        newNode->CpfRank = CpfRank;
        newNode->IfrScore = IfrScore;
        newNode->IfrRank = IfrRank;
        newNode->IsrScore = IsrScore;
        newNode->IsrRank = IsrRank;
        newNode->IrnScore = IrnScore;
        newNode->IrnRank = IrnRank;
        newNode->GerScore = GerScore;
        newNode->GerRank = GerRank;
        newNode->ScoreScaled = ScoreScaled;
        newNode -> nextAdd = NULL;
        newNode->prevAdd = NULL;
        
        return newNode;
    }

    // Insert list
    void insertList (int Rank, string Institution, string LocationCode, string Location, float ArScore, int ArRank, float ErScore, int ErRank, float FsrScore, int FsrRank, float CpfScore, int	CpfRank, float IfrScore, int IfrRank, float IsrScore, int IsrRank, 
                     float IrnScore, int IrnRank, float GerScore, int GerRank, float ScoreScaled, bool update = false)
    {
        universityNode *newNode = createNode(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore,
                                        ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore,
                                        IrnRank, GerScore, GerRank, ScoreScaled);

        // Insert to the list now 
        if( head == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->nextAdd = newNode;
            newNode->prevAdd = tail;
            tail = newNode;
        }

        // Update the rank if new record added (not from CSV File)
        if(update)
        {
            updateRank(Rank, Institution, ArRank, ErRank, FsrRank, CpfRank, IfrRank, IsrRank, IrnRank, GerRank);
        }
        size++; // increase size of list
    }

    void updateRank(int Rank, string Institution, int ArRank, int ErRank, int FsrRank, int CpfRank, int IfrRank, int IsrRank, 
                    int IrnRank, int GerRank)
    {
        universityNode* current = head;
        while (current!= NULL)
        {
            if(current->Institution != Institution)
            {
                // Increase their rank by 1 if their rank is higher than the newNode rank
                // To replace the original rank. E.g. Insert newNode (Rank = 500). Old record of Rank 500 will become 501
                // Dont increase rank if they are more than 500 or 600 based on the attribute
                if(current->Rank >= Rank)                         current->Rank = current->Rank + 1;
                if(current->ArRank >= ArRank && current->ArRank != 501)    current->ArRank = current->ArRank + 1;
                if(current->ErRank >= ErRank && current->ErRank != 501)    current->ErRank = current->ErRank + 1;
                if(current->FsrRank >= FsrRank && current->FsrRank != 601) current->FsrRank = current->FsrRank + 1;
                if(current->CpfRank >= CpfRank && current->CpfRank != 601) current->CpfRank = current->CpfRank + 1;
                if(current->IfrRank >= IfrRank && current->IfrRank != 601) current->IfrRank = current->IfrRank + 1;
                if(current->IsrRank >= IsrRank && current->IsrRank != 601) current->IsrRank = current->IsrRank + 1;
                if(current->IrnRank >= IrnRank && current->IrnRank != 601) current->IrnRank = current->IrnRank + 1;
                if(current->GerRank >= GerRank && current->GerRank != 601) current->GerRank = current->GerRank + 1;
            }
            current = current->nextAdd;
        }
        
    }

    // # Load CSV
    void loadCSV()
    {
        // list should start from empty
        head = NULL;

        //copy the file name
        string temp, Rank,Institution,LocationCode,Location,ArScore,ArRank,ErScore,ErRank,FsrScore,FsrRank,CpfScore,CpfRank,IfrScore,IfrRank,IsrScore,IsrRank,IrnScore,IrnRank,GerScore,GerRank,ScoreScaled;
        ifstream file("./CSV_Data/University_Details.csv");

        while(file.good())
        {
            getline(file, Rank, ','); // when you have comma, it tell the system to go to second column
            getline(file, Institution, ',');
            // handle comma in string
            if (Institution.at(0)=='"'){
                getline(file, temp, '"');
                Institution = Institution + "," + temp;
                Institution.erase(0,1); // remove first character which is '"'
                getline(file, temp, ','); // ignore the comma after '"' E.g. "Harvard, university", US
            }

            getline(file, LocationCode, ',');
            getline(file, Location, ',');
            
            //handle comma in string
            if (Location.at(0)=='"'){
                getline(file, temp, '"');
                Location = Location + "," + temp;
                Location.erase(0,1); // remove first character which is '"'
                getline(file, temp, ','); // ignore the comma after '"' E.g. "Iran, Islamic Republic of, 5
            }

            getline(file, ArScore, ',');
            getline(file, ArRank, ',');
            getline(file, ErScore, ',');
            getline(file, ErRank, ',');
            getline(file, FsrScore, ',');
            getline(file, FsrRank, ',');
            getline(file, CpfScore, ',');
            getline(file, CpfRank, ',');
            getline(file, IfrScore, ',');
            getline(file, IfrRank, ',');
            getline(file, IsrScore, ',');
            getline(file, IsrRank, ',');
            getline(file, IrnScore, ',');
            getline(file, IrnRank, ',');
            getline(file, GerScore, ',');
            getline(file, GerRank, ',');
            getline(file, ScoreScaled); // no more column, so comma is no need

            if(Institution == "Institution")
            {
                continue; // skip the first row/ heading
            }
            else if (Institution == "") // empty data
            {
                break;
            }
            //InsertToFrontOfList(EmpID, EmpName, stod(EmpSalary));
            insertList(stoi(Rank),Institution,LocationCode,Location,stof(ArScore),stoi(ArRank),stof(ErScore),
                            stoi(ErRank),stof(FsrScore),stoi(FsrRank),stof(CpfScore),stoi(CpfRank),stof(IfrScore),
                            stoi(IfrRank),stof(IsrScore),stoi(IsrRank),stof(IrnScore),stoi(IrnRank),stof(GerScore),
                            stoi(GerRank),stof(ScoreScaled));
            
        }

        universityNode* current = head;
        while (current!=NULL)
        {
            current = current->nextAdd;
        }
        
    }

    // # Merge Sort [compare]
    void callMergeSort_nonRegis(){

        head = mergeSort(head,"Institution");

        
        arrangeTail();
    }
    
    // # Bubble Sort [compare]
    void bubbleSort(){
        universityNode *tmp, *current, *nextItem,*temp1;
        int count = size;
        int i,j;
        for ( i = 0; i < count; i++)
        {
            current = head;
            for(j=0;j<count-1-i;j++ )
            {
                if(current->Institution > current->nextAdd->Institution)
                {
                    nextItem = current->nextAdd;
                    temp1 = current->prevAdd;
                    
                    current->nextAdd = nextItem->nextAdd;
                    current->prevAdd = nextItem;
                    
                    if (current->nextAdd == NULL)
                    {
                        tail = current;
                    }else{
                        current->nextAdd->prevAdd = current;
                    }
                    
                    nextItem->nextAdd = current;
                    nextItem->prevAdd = temp1;


                    if(current == head)
                    {
                        head = nextItem;
                        current = nextItem;
                    }
                    
                    else
                    {
                        current = nextItem;
                        tmp->nextAdd = nextItem;
                    }
                }
                tmp = current;
                current = current->nextAdd;
            }
        }
    }

    // # Merge sort
    void arrangeTail()
    {
        while(tail->nextAdd != NULL) tail = tail->nextAdd;
    }
    // Compare by institution name
    bool compareInstitution(universityNode* left, universityNode* right){
        return left->Institution <= right-> Institution;
    }

    // Compare by location code
    bool compareLocationCode(universityNode* left, universityNode* right){
        return left->LocationCode <= right-> LocationCode;
    }

    // Compare by location
    bool compareLocation(universityNode* left, universityNode* right){
        return left->Location <= right-> Location;
    }

    // Compare by academic reputation score
    bool compareArScore(universityNode* left, universityNode* right){
        return left->ArScore <= right-> ArScore;
    }

    // Compare by academic reputation rank
    bool compareArRank(universityNode* left, universityNode* right){
        return left->ArRank <= right-> ArRank;
    } 
    // Compare by faculty/student ratio score
    bool compareFsrScore(universityNode* left, universityNode* right){
        return left->FsrScore <= right-> FsrScore;
    }

    // Compare by Employer reputation Score
    bool compareErScore(universityNode* left, universityNode* right){
        return left->ErScore <= right-> ErScore;
    }

    // Divide the linked list into half (left and right sub-list)
    universityNode* splitList(universityNode* currentHead){
        universityNode* fastPtr;
        universityNode* slowPtr;

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
    universityNode* sortAndMergeList(universityNode* left, universityNode * right, string sortBy){
        universityNode* mergedList =NULL;
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

        if (sortBy == "Institution")       { compareResult = compareInstitution(left, right);  } 
        else if (sortBy == "LocationCode") { compareResult = compareLocationCode(left, right); }
        else if (sortBy == "Location")     { compareResult = compareLocation(left, right);     }
        else if (sortBy == "ArScore") { compareResult = compareArScore(left, right); }
        else if (sortBy == "FsrScore")     { compareResult = compareFsrScore(left, right);     }
        else if (sortBy == "ErScore") { compareResult = compareErScore(left, right); }

        // compare node value of left and right list
        if (compareResult){
            // assign the left list to new linked list
            mergedList = left; 
            // call merge again without the node added to the list
            mergedList->nextAdd = sortAndMergeList(left->nextAdd, right, sortBy); 
        }else{
            // assign the right list to new linked list
            mergedList = right; 
            // call merge again without the node added to the list
            mergedList->nextAdd = sortAndMergeList(left, right->nextAdd, sortBy); 
        }

        // link next node's previous address to current node
        mergedList->nextAdd->prevAdd = mergedList; 
        mergedList->prevAdd = NULL;
        return mergedList;
    } 

    // main function of merge sort
    universityNode* mergeSort(universityNode* source, string sortBy){
        // when only the linked list is empty or only have one node
        if(source == NULL || source->nextAdd == NULL){
            return source;
        }
        universityNode* left = source;

        // split the linked list into sub list (left and right)
        universityNode* mid = splitList(source);

        // break the linked list
        universityNode* right = mid->nextAdd;
        mid->nextAdd = NULL;
        right->prevAdd = NULL;

        // recursively call the function with left sub-list to divide itself until one element left
        left = mergeSort(left, sortBy);

        // recursively call the function with right sub-list to divide itself until one element left
        right = mergeSort(right, sortBy);
        
        // sort and merge back the left and right sub-lists, always return the head of sorted list
        return sortAndMergeList(left,right, sortBy);
    }

    // # Display data in table format
    void displayData(bool displayDesc)
    {
        // print table format
        universityNode* current = NULL;
        
        // Check display asc or desc
        if (displayDesc) {
            current = tail;
        } else {
            current = head;
        }

        // Print table header
        cout << "+======+=====================================================================================+=================================+=========+========+=========+========+==========+=========+==========+=========+==========+=========+==========+=========+==========+=========+==========+=========+=============+" << endl;
        cout << "|  No. |                                     Institution                                     |             Location            | ArScore | ArRank | ErScore | ErRank | FsrScore | FsrRank | CpfScore | CpfRank | IfrScore | IfrRank | IsrScore | IsrRank | IrnScore | IrnRank | GerScore | GerRank | ScoreScaled |" << endl;
        cout << "+======+=====================================================================================+=================================+=========+========+=========+========+==========+=========+==========+=========+==========+=========+==========+=========+==========+=========+==========+=========+=============+" << endl;
        int counter = 1;
        while (current != NULL) {
            // Print table rows with data
            cout << "| " << setw(4) << counter << " | " << setw(83) << current->Institution << " | "
            
            << setw(31) << current->Location << " | " << setw(7) << current->ArScore << " | " 
            << setw(6) << current->ArRank << " | " << setw(7) << current->ErScore << " | " 
            << setw(6) << current->ErRank << " | " << setw(8) << current->FsrScore << " | " 
            << setw(7) << current->FsrRank << " | " << setw(8) << current->CpfScore << " | " 
            << setw(7) << current->CpfRank << " | " << setw(8) << current->IfrScore << " | " 
            << setw(7) << current->IfrRank << " | " << setw(8) << current->IsrScore << " | " 
            << setw(7) << current->IsrRank << " | " << setw(8) << current->IrnScore << " | " 
            << setw(7) << current->IrnRank << " | " << setw(8) << current->GerScore << " | " 
            << setw(7) << current->GerRank << " | " << setw(11) << current->ScoreScaled << " |" <<endl;
            cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

            // Move to the next node
            if (displayDesc) {
                current = current->prevAdd;
            } else {
                current = current->nextAdd;
            }
            counter++;
        }

        // Print table footer
        cout << "+======+=====================================================================================+=================================+=========+========+=========+========+==========+=========+==========+=========+==========+=========+==========+=========+==========+=========+==========+=========+=============+" << endl;
    }

    // # Calculate len of string
    int returnFloatLen (string stringF){
        regex decimalPointRegex("\\.");
        return (regex_replace(stringF, decimalPointRegex, "").length()); 
    }

    // # Search Institution info [Register Users' Function]  
    void linearTransitionSearch(string keywords, string condi, string menu)
    {
        universityNode* current = head;
        universityNode* temp = NULL;
        universityNode* temp2 = NULL;
        universityNode* keyList = NULL; // store final node into this list
        string tempStr; int tempInt; float tempFloat;
        string searchType; // determine search type (range search, specific search)
        bool searchResult = false;
        bool found = false;
        bool found_specific = false;
        string dataType;

        if (condi == "Institution" || condi == "Location")
        {
            dataType = "string";
        }else
        {
            dataType = "";
        }


        while (current != NULL)
        {
            if (dataType == "string")
            {
                searchType = "normalSearch";
                tempStr = tempNodeInfo_string(condi,current);
            }
            else{
                if (menu == "Rank")
                {
                    tempInt = getRank(current, condi);
                    searchType = "rangeSearch";
                }
                else{
                    tempFloat = getScore(current, condi);
                    searchType = "rangeSearch_2";
                }
            }
            
            
            // comparing search result with keywords
            if (searchType == "normalSearch" && tempStr == keywords)
            {
                if(current!=head)
                {
                    if (current->prevAdd == head)
                    {
                        temp = current->prevAdd;
                        temp2 = current->nextAdd;
                        head = current;
                        current->prevAdd = NULL;
                        current->nextAdd = temp;
                        current->nextAdd->prevAdd = current;
                        current->nextAdd->nextAdd = temp2;
                        current->nextAdd->nextAdd->prevAdd = current->nextAdd;
                    }
                    else if (current->nextAdd != NULL)
                    {
                        temp = current->nextAdd; // Current Next items
                        temp2 = current->prevAdd; // Previous item
                        current->prevAdd = current;
                        current->prevAdd = temp2->prevAdd;
                        current->prevAdd->nextAdd = current;
                        current->nextAdd = temp2;
                        current->nextAdd->prevAdd = current;
                        current->nextAdd->nextAdd = temp;
                        current->nextAdd->nextAdd->prevAdd = temp2;
                    }else{
                        temp2 = current->prevAdd; // Previous item
                        current->prevAdd = current;
                        current->prevAdd = temp2->prevAdd;
                        current->prevAdd->nextAdd = current;
                        current->nextAdd = temp2;
                        current->nextAdd->prevAdd = current;
                        current->nextAdd->nextAdd = NULL; 
                        tail = current->nextAdd; 
                    }
                }
                
                // call display result methods
                displaySearchResult(current);
                found = true;
                found_specific = true;
            }
            else if (found_specific !=true && searchType == "normalSearch" && tempStr.find(keywords)!=string::npos && condi == "Institution")
            {
                // call display result methods
                displaySearchResult(current);
                found = true;
            }
            else if (searchType == "rangeSearch") // Search by rank
            {
                if (keywords == "1"){if (tempInt>=1 && tempInt<=50){searchResult=true;}}
                else if (keywords == "2"){if (tempInt>=51 && tempInt<=100){searchResult=true;}}
                else if (keywords == "3"){if (tempInt>=101 && tempInt<=200){searchResult=true;}}
                else if (keywords == "4"){if (tempInt>=201 && tempInt<=300){searchResult=true;}}
                else if (keywords == "5"){if (tempInt>=301 && tempInt<=400){searchResult=true;}}
                else if (keywords == "6"){if (tempInt>=401 && tempInt<=499){searchResult=true;}}
                else if (keywords == "7"){if (tempInt>=500){searchResult=true;}}
                
                // check search result & call display result methods
                if (searchResult){displaySearchResult(current);}
                found = true;
            }
            else if (searchType == "rangeSearch_2") // Search by score
            {
                if (keywords == "1"){if (tempFloat>=80){searchResult = true;}}
                else if (keywords == "2"){if (tempFloat>=60 && tempFloat <80){searchResult = true;}}
                else if (keywords == "3"){if (tempFloat>=40 && tempFloat <60){searchResult = true;}}
                else if (keywords == "4"){if (tempFloat>=20 && tempFloat <40){searchResult = true;}}
                else if (keywords == "5"){if (tempFloat <20){searchResult = true;}}
                
                // check search result & call display result methods
                if (searchResult){displaySearchResult(current);}
                found = true;
            }

            tempStr.clear(); 
            current = current-> nextAdd;
            searchResult = false;
        }
        if (!found)
        {
            cout << "Result not found!" << endl;
        }
    }

    // # Return node info fucntion
    string tempNodeInfo_string(string condi, struct universityNode* current){
        string tempStr;
        if (condi == "Institution") tempStr = current->Institution;
        else if (condi == "Location") tempStr = current->Location;
        return tempStr;
    }

    // # Linear Search Algorithms [Compare]
    void linearSearch(string keywords, string condi)
    {
        universityNode* current = head;
        string tempStr;
        bool searchResult = false;
        while (current != NULL)
        {
            // capture linked list attri to a temp
            tempStr = tempNodeInfo_string(condi, current); 
            
            // comparing search result with keywords
            if (tempStr == keywords)
            {
                // call display result methods
                displaySearchResult(current);
                searchResult = true;
            }

            tempStr.clear(); 
            current = current-> nextAdd;
        }
        if (!searchResult)
        {
            cout << "Result not found!"<< endl;
        }
        
    }

    // # Jump Search [compare]
    void jumpSearch(string keywords, string condi, string dataType)
    {
        universityNode* current = head;
        string searchType; // determine search type (range search, specific search)
        bool searchResult = false;

        int nRow = size;
        
        head = mergeSort(head,condi);
        arrangeTail();

        // Reset current 
        current = head;

        // define attributes
        int step = sqrt(nRow);
        int totStep = 1;
        int prevTotStep = 0;
        bool found = false;
        bool end = false;
        universityNode* prev = head;
        string tempValue; int tempInt; float tempFloat;
        int newKeyWords; float newKeyWords_flt; 

        // capture linked list attri and define search type
        if (dataType == "string")
        {
            tempValue = tempNodeInfo_string(condi,current);
        }

        // define search type 
        if (condi == "Institution")
        {
            searchType = "normalSearch"; // searchMoreThanOne
        }else{
            searchType = "searchMoreThanOne"; // searchMoreThanOne
        }
        

        // js algo
        if (dataType == "string")
        {   
            if (searchType == "normalSearch") // jump after target value
            {
                // while temp value is < than keywords <jump next>
                while (tempValue < keywords && end == false)
                {
                    prev = current;
                    prevTotStep = totStep;

                    for (int i = 1; i <= step; i++)
                    {   
                        if (current->nextAdd != NULL)
                        {
                            current = current -> nextAdd; // pass to next node
                            totStep += 1;   
                        }else{
                            end = true;
                        }
                    }
                    tempValue = tempNodeInfo_string(condi,current);
                }

                // capture prev value
                tempValue = tempNodeInfo_string(condi,prev);

                // while temp value is > than keywords <jump back>
                for (int i = prevTotStep; i <= min(totStep,nRow); i++)
                {
                    if (tempValue == keywords)
                    {
                        displaySearchResult(prev);
                        searchResult = true;
                    }
                    // next node based on step <linear>
                    prev = prev -> nextAdd;
                    tempValue = tempNodeInfo_string(condi,prev);
                }
                
                if (!searchResult)
                {
                    cout << "Result Not Found! " << endl;
                }
            }
            else if (searchType == "searchMoreThanOne")
            {
                // while temp value is < than keywords <jump next>
                while (tempValue <= keywords && end == false)
                {
                    prev = current;
                    prevTotStep = totStep;

                    for (int i = 1; i <= step; i++)
                    {   
                        if (current->nextAdd != NULL)
                        {
                            current = current -> nextAdd; // pass to next node
                            totStep += 1;   
                        }else{
                            end = true;
                        }
                    }
                    tempValue = tempNodeInfo_string(condi,current);
                }

                // capture prev value
                tempValue = tempNodeInfo_string(condi,prev);
                
                bool end_1 = false;
                // check whether the jump back value equal to our target anot
                while (tempValue == keywords && end_1 == false)
                {
                    for (int i = 1; i <= step; i++)
                    {
                        if (prev->prevAdd !=NULL)
                        {
                            prev = prev ->prevAdd;
                            prevTotStep --;
                        }else{
                            end = true; // break if it was the first item
                        }
                    }
                    tempValue = tempNodeInfo_string(condi,prev);
                }

                // do linear search
                for (int i = prevTotStep; i <= min(totStep,nRow); i++)
                {
                    if (tempValue == keywords)
                    {
                        displaySearchResult(prev);
                        searchResult = true;
                    }
                    // next node based on step <linear>
                    prev = prev -> nextAdd;
                    tempValue = tempNodeInfo_string(condi,prev);
                } 
                
                if (!searchResult)
                {
                    cout << "Result Not Found! " << endl;
                }
            }
        }
    }

    // # Linear Transition Search [compare]
    void linearTransition_nonRegis(string keywords, string condi, string dataType){
        universityNode* current = head;
        universityNode* temp = NULL;
        universityNode* temp2 = NULL; 
        // Define var
        string tempValue;
        
        int counter = 0; 
        // linear transition search algo
        if (dataType == "string")
        {
            while (current != NULL)
            {
                // Capture temp value 
                tempValue = tempNodeInfo_string(condi,current); 
                counter++;
                if (tempValue == keywords)
                {
                    cout << "Found in position : "<< counter << endl;
                    if(current!=head)
                    {
                        if (current->prevAdd == head)
                        {
                            temp = current->prevAdd;
                            temp2 = current->nextAdd;
                            head = current;
                            current->prevAdd = NULL;
                            current->nextAdd = temp;
                            current->nextAdd->prevAdd = current;
                            current->nextAdd->nextAdd = temp2;
                            current->nextAdd->nextAdd->prevAdd = current->nextAdd;
                        }
                        else if (current->nextAdd != NULL)
                        {
                            temp = current->nextAdd; // Current Next items
                            temp2 = current->prevAdd; // Previous item
                            current->prevAdd = current;
                            current->prevAdd = temp2->prevAdd;
                            current->prevAdd->nextAdd = current;
                            current->nextAdd = temp2;
                            current->nextAdd->prevAdd = current;
                            current->nextAdd->nextAdd = temp;
                            current->nextAdd->nextAdd->prevAdd = temp2;
                        }else{
                            temp2 = current->prevAdd; // Previous item
                            current->prevAdd = current;
                            current->prevAdd = temp2->prevAdd;
                            current->prevAdd->nextAdd = current;
                            current->nextAdd = temp2;
                            current->nextAdd->prevAdd = current;
                            current->nextAdd->nextAdd = NULL; 
                            tail = current->nextAdd; 
                        }
                    }
                    // display result
                    displaySearchResult(current);
                }
                current = current->nextAdd;
            }   
        }
    }

   
    // # Display all searched result 
    void displaySearchResult(struct universityNode* targetNode){
        if (targetNode != NULL)
        {
            cout<< string(22, '=') << " university List "<< string(28,'=') << endl;
            cout << "\tInstitution : "<< targetNode->Institution << endl; 
            cout << "\tLocation : "<< targetNode->Location << endl;
            cout << string(67,'-')<< endl; 

            // output ArRank and Score
            cout << "\t" <<left<< setw(13) << "Ar Score : " << fixed << setprecision(2) << setw(10) << targetNode->ArScore
            << left << setw(10) << "Ar Rank : " << targetNode->ArRank << endl;

            // ouput Er Score and Rank 
            cout << "\t" <<left << setw(13) << "Er Score : " << fixed << setprecision(2) << setw(10) << targetNode->ErScore
            << left << setw(10) <<  "Er Rank :" << targetNode->ErRank<< endl;

            // output Fsr Score and Rank
            cout << "\t" <<left << setw(13) << "Fsr Score : " << fixed << setprecision(2) << setw(10) << targetNode->FsrScore
            << left << setw(10) <<  "Fsr Rank :" << targetNode->FsrRank << endl; 

            // output Cpf Score and Rank
            cout << "\t" <<left << setw(13) <<"Cpf Score : " << fixed << setprecision(2) << setw(10) << targetNode->CpfScore
            << left << setw(10) <<  "Cpf Rank :" <<  targetNode->CpfRank << endl;

            // output Ifr Score and Rank
            cout << "\t" <<left << setw(13) <<"Ifr Score : " << fixed << setprecision(2) << setw(10) <<targetNode->IfrScore
            << left << setw(10) <<  "Ifr Rank :" <<  targetNode->IfrRank << endl;

            // output Isr Score and Rank
            cout << "\t" <<left << setw(13) <<"Isr Score : " << fixed << setprecision(2) << setw(10) <<targetNode->IsrScore
            << left << setw(10) <<  "Isr Rank :" <<  targetNode->IsrRank << endl;

            // output Irn Score and Rank
            cout << "\t" <<left << setw(13) <<"Irn Score : " << fixed << setprecision(2) << setw(10) <<targetNode->IrnScore 
            << left << setw(10) <<  "Irn Rank :" <<  targetNode->IrnRank << endl;

            // output Ger Score and Rank
            cout << "\t" <<left << setw(13) <<"Ger Score : " << fixed << setprecision(2) << setw(10) <<targetNode->GerScore
            << left << setw(10) <<  "Ger Rank :" <<  targetNode->GerRank << endl;

            cout << "\tScore Scaled : "<< targetNode->ScoreScaled << endl << endl;
            cout << string(67, '=') << endl << endl;
        }
        else if (targetNode == NULL)
        {
            cout << "Result Not Found!"<< endl;
        }
    }

    
    // # Function : Register User Search university details
    void rUser_search_university();

    void searchMenu(string type);

     // # Function : Register User Search university details
    void searchByRankScore(string title, string menu);

    void searchByInstiLocation(string title);
    
    // # Function : Register User Sort university detials
    void rUser_sort_university(string action, bool displayDesc);

    // # Function : Display favorite list
    void rUser_display_favourite_list(string* tempList, int numOfUni){
        int pos = 0, counter = 1;
        universityNode* current = tail;
        string choice = "";
        bool cont;

        while (numOfUni > 0)
        {
            // inner loop for linked list
            current = tail;
            cont = true;
            while (current!=NULL)
            {
                // break this while loop while previous or next action detected
                if(!cont){break;}   

                while (current->Institution != tempList[pos])
                {
                    current = current->prevAdd;
                }

                cout << string(25, '=') << " Favourite List - "<< counter << " " << string(25, '=') << endl;
                displaySearchResult(current);

                while (true)
                {
                    cout << "Enter '<' for previous page, '>'for next page, 'x' to exit" << endl;
                    cout << "Choice: "; 
                    cin >> choice;
                    cout << endl;

                    if(choice == "<")
                    {
                        // Move to previous page 
                        if(counter == 1){
                            cout << "You are viewing the first page!" << endl;
                        }else{
                            counter--;
                            pos--;
                            cont = false;
                            break;
                        }
                    }
                    else if(choice == ">")
                    {
                        // Move to next page 
                        if(pos+1 == numOfUni){
                            cout << "Opps... no more page" << endl;
                        }else{
                            counter++;
                            pos++;
                            cont = false;
                            break;
                        }
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
        }
    }

    // # Function : Display Uni data in sequences way - version 2
    void rUser_display_seq_uni(string* tempList, UserList& userObject ,string userId){
        universityNode* current = head;
        int counter = 0, numOfUniPerPage = 10;
        string choice;

        while (current != NULL)
        {
            cout<< string(22, '=') << " university List "<< string(28,'=') << endl << endl;
            cout << "No. " << counter+1 << ") ";
            cout << "Institution : "<< current->Institution << endl; 
            cout << "\tLocation : "<< current->Location << endl;
            cout << string(67,'-')<< endl;
            // output ArRank and Score
            cout << "\t" <<left<< setw(13) << "Ar Score : " << fixed << setprecision(2) << setw(10) << current->ArScore
            << left << setw(10) << "Ar Rank : " << current->ArRank << endl;

            // ouput Er Score and Rank 
            cout << "\t" <<left << setw(13) << "Er Score : " << fixed << setprecision(2) << setw(10) << current->ErScore
            << left << setw(10) <<  "Er Rank :" << current->ErRank<< endl;

            // output Fsr Score and Rank
            cout << "\t" <<left << setw(13) << "Fsr Score : " << fixed << setprecision(2) << setw(10) << current->FsrScore
            << left << setw(10) <<  "Fsr Rank :" << current->FsrRank << endl; 

            // output Cpf Score and Rank
            cout << "\t" <<left << setw(13) <<"Cpf Score : " << fixed << setprecision(2) << setw(10) << current->CpfScore
            << left << setw(10) <<  "Cpf Rank :" <<  current->CpfRank << endl;

            // output Ifr Score and Rank
            cout << "\t" <<left << setw(13) <<"Ifr Score : " << fixed << setprecision(2) << setw(10) <<current->IfrScore
            << left << setw(10) <<  "Ifr Rank :" <<  current->IfrRank << endl;

            // output Isr Score and Rank
            cout << "\t" <<left << setw(13) <<"Isr Score : " << fixed << setprecision(2) << setw(10) <<current->IsrScore
            << left << setw(10) <<  "Isr Rank :" <<  current->IsrRank << endl;

            // output Irn Score and Rank
            cout << "\t" <<left << setw(13) <<"Irn Score : " << fixed << setprecision(2) << setw(10) <<current->IrnScore 
            << left << setw(10) <<  "Irn Rank :" <<  current->IrnRank << endl;

            // output Ger Score and Rank
            cout << "\t" <<left << setw(13) <<"Ger Score : " << fixed << setprecision(2) << setw(10) <<current->GerScore
            << left << setw(10) <<  "Ger Rank :" <<  current->GerRank << endl;

            cout << "\tScore Scaled : "<< current->ScoreScaled << endl << endl;

            cout << string(67, '=') << endl << endl;

            // keep track no of page
            counter++;

            // show 10 uni each page
            if (counter %numOfUniPerPage == 0 || current->nextAdd == NULL)
            {
                while (true)
                {
                    cout << "Enter '<' for previous feedback, '>' for next feedback, '*' to add this to favourite, 'x' to exit" << endl;
                    cout << "Choice: "; 
                    cin >> choice;
                    cout << endl;

                    if (choice == "<")
                    {
                        // show 10 previous user
                        if (counter == 10)
                        {
                            cout << "You are viewwing the first page!" << endl;
                        }else{
                            int num = numOfUniPerPage*2-1;
                            if (current->nextAdd == NULL && counter%numOfUniPerPage !=0)
                            {
                                int difference = counter%numOfUniPerPage;

                                while (difference !=0)
                                {
                                    difference--;
                                    counter--;
                                    current = current->prevAdd;
                                }
                                num = numOfUniPerPage - 1;
                            }

                            for (int i = 0; i < num; i++)
                            {
                                current = current->prevAdd;
                            }
                            counter -= num;
                            break;
                        }
                    }
                    else if (choice == ">")
                    {
                        if (current->nextAdd == NULL)
                        {
                            cout << "You are at the end of the list!" << endl;
                        }else{
                            counter++;
                            current = current->nextAdd;
                            break;
                        }
                    }
                    else if (choice == "*")
                    {
                        string userInput;
                        int remainderList = counter%numOfUniPerPage;
                        int numOfMoveBack = numOfUniPerPage - 1;

                        while (true)
                        {
                            cout << "Which university you want to favourite? Enter No. ";

                            if (remainderList !=0)
                            {
                                cout << counter - remainderList+1 << " - " << counter;
                            }else{
                                cout << counter - 9 << " - " << counter;
                            }
                            cout << "(Enter 'x' to cancel): ";

                            cin >> userInput;

                            try
                            {
                                int difference = counter - stoi(userInput);
                                if(remainderList != 0)
                                {
                                    numOfMoveBack = remainderList - 1;

                                    if (difference >= remainderList || difference <0)
                                    {
                                        cout << "Out of range!"<< endl;
                                        continue;
                                    }
                                }
                                else
                                {
                                    if(difference>9 || difference < 0){
                                        cout << "out of range"<<endl;
                                        continue;
                                    }
                                }
                            
                                for(int j=0; j < numOfMoveBack; j++){
                                    if (difference == 0)
                                    {
                                        userObject.addFavList_customer(userId, current->Institution);
                                        // int pos = 0;
                                        // while (tempList[pos]!="")
                                        // {
                                        //     if (current->Institution == tempList[pos])
                                        //     {
                                        //         cout << "This university had been favourited, so you can't favourite it again!"<< endl << endl;
                                        //         break;
                                        //     }
                                        //     else if (current->Institution != tempList[pos] && tempList[pos+1]=="")
                                        //     {
                                        //         cout << "*** Successfully favourited this university. ***"<< endl<<endl;
                                        //         userObject.addFavList_customer(userId,current->Institution);
                                        //         break;

                                        //     }
                                        //     pos++;
                                        // }
                                        difference = 99;
                                        break; 
                                    }
                                    current = current->prevAdd;
                                    counter--;
                                    difference--;
                                }

                                if (difference == 0)
                                {
                                    userObject.addFavList_customer(userId, current->Institution);
                                    // int pos = 0;
                                    // while (tempList[pos]!="")
                                    // {
                                    //     if (current->Institution == tempList[pos])
                                    //     {
                                    //         cout << "This university had been favourited, so you can't favourite it again!"<< endl << endl;
                                    //         break;
                                    //     }
                                    //     else if (current->Institution != tempList[pos] && tempList[pos+1]=="")
                                    //     {
                                    //         cout << "*** Successfully favourited this university. ***"<< endl<<endl;
                                    //         userObject.addFavList_customer(userId,current->Institution);
                                    //         break;
                                    //     }
                                    //     pos++;
                                    // }
                                }

                            }
                            catch(const exception& e)
                            {
                                if(userInput == "x"){
                                    break;
                                }
                                cerr << e.what() << '\n';
                                cout << "Invalid input, please enter number only!" << endl;
                            }
                            break;
                            
                        }
                        break;
                    }
                    else if (choice == "x")
                    {
                        return;
                    }
                    else{
                        cout << "Invalid Input!"<< endl;
                    }
                }
                counter--;
                continue;
            }
            current = current->nextAdd;
        }
        
    }

    void printList()
    {
        universityNode* current = head;
        while(current != NULL)
        {
            cout << "Rank: " << current->Rank << "\t " << current->Institution;   
            cout << "\tScoreScaled: " << current->ScoreScaled << "\t" << current->Location << "\t" << current->LocationCode;
            cout << "\tArScore: " << current->GerScore << "\t ArRank: " << current->GerRank << endl; 
            current = current->nextAdd;
        }
    }

    void addNewUniversity(){
        int Rank;
        string Institution;
        string LocationCode;
        string Location;
        float ArScore; int ArRank;
        float ErScore; int ErRank;
        float FsrScore; int FsrRank; 
        float CpfScore; int CpfRank;
        float IfrScore; int IfrRank; 
        float IsrScore; int IsrRank; 
        float IrnScore; int IrnRank; 
        float GerScore; int GerRank; 
        float ScoreScaled;

        int userChoice;
        string userInput;

        cout << string(50, '=') << " Add university" << string(50, '=') << endl;
        cout << "Please provide the following details" << endl;
        cout << string(100 , '-') << endl;

        while(true)
        {
            cout << "Institution Name: ";
            cin.ignore();
            getline(cin, Institution);
        
            // validate input - avoid duplicated university
            if(checkUniversityDuplicate(Institution))
                cout << "Record Exist! Please try another name " << endl;
            else
                break;
        }

        // get location from user
        pair<string, string> result = getLocation();
        Location = result.first;
        LocationCode = result.second;

        // set the score
        ArScore = setScore("Academic Reputation");
        ErScore = setScore("Employer Reputation");
        FsrScore = setScore("Faculty/Student Ratio");
        CpfScore = setScore("Citations Per Faculty");
        IfrScore = setScore("International Faculty Ratio");
        IsrScore = setScore("International Student Ratio");
        IrnScore = setScore("International Research Network");
        GerScore = setScore("Employment Outcome");
        // Calculate average score
        ScoreScaled = (ArScore + ErScore + FsrScore + CpfScore + IfrScore + IsrScore + IrnScore + GerScore)/8; 
        ScoreScaled = static_cast<int>(ScoreScaled*10)/10.0; // cut decimal off to one decimal only

        // set the rank
        ArRank = setRank(ArScore, "Ar");
        ErRank = setRank(ErScore, "Er");
        FsrRank = setRank(FsrScore, "Fsr");
        CpfRank = setRank(CpfScore, "Cpf");
        IfrRank = setRank(IfrScore, "Ifr");
        IsrRank = setRank(IsrScore, "Isr");
        IrnRank = setRank(IrnScore, "Irn");
        GerRank = setRank(GerScore, "Ger");
        Rank = setRank(ScoreScaled, "Rank");
        
        insertList(Rank, Institution, LocationCode, Location, ArScore, ArRank, ErScore,
                   ErRank, FsrScore, FsrRank, CpfScore, CpfRank, IfrScore, IfrRank, IsrScore, IsrRank, IrnScore,
                   IrnRank, GerScore, GerRank, ScoreScaled, true);
    }

    // check if the university name has existed 
    bool checkUniversityDuplicate(string institutionName)
    {
        universityNode* current = head;
        while(current != NULL)
        {
            if(current->Institution == institutionName)
                return true;
            
            current = current->nextAdd;
        }
        return false;

    }

    float setScore(string title)
    {
        string userInput;
        float score;
        while(true)
        {   
            cout << title << " Score: ";
            cin >> userInput;

            try
            {
                // convert to float
                score = stof(userInput);

                if(score >= 0 && score <= 100)
                {
                    // cut decimal off to one decimal only
                    score = static_cast<int>(score*10.0)/10.0;
                    break;
                }
                else
                    cout << "Error: Invalid input, Please enter <1-100>" << endl;
                
            }
            catch(const std::exception& e)
            {
                cout << "Error: Invalid input, Please enter number only" << endl;
            }
        }
        return score;
    }

    int setRank(float score, string title)
    {
        universityNode* current = head;
        float minScore = 0, currentScore, currentRank;
        int rank;

        while(current != NULL)
        {
            currentScore = getScore(current, title);
            currentRank = getRank(current, title);
            // Condition 1: Same score found
            if(currentScore == score)
            {
                return currentRank; // return rank
            }
            // Condition 2: No same score, find lower bound of the score and determine the rank
            else if (score > currentScore )
            {
                // At the end, replace the lower bound's node rank
                if (currentScore >= minScore)
                {
                    minScore = currentScore;
                    rank = currentRank;
                }
            }
            // Condition 3: Score less than current score and the rank is 500, classify as 501+
            else if ((title == "Ar" || title == "Er") && currentRank == 500)
            {
                return currentRank+1;
            }
            else if(currentRank == 600) 
            {
                // cout << "2" << current->Institution << endl;
                return currentRank+1;
            }
            current = current->nextAdd;
        }
        return rank;
    }

    // Utility function
    int getRank(universityNode* currentNode,string title)
    {
        if(title == "Rank") return currentNode->Rank;
        if(title == "Ar") return currentNode->ArRank;
        if(title == "Er") return currentNode->ErRank;
        if(title == "Fsr") return currentNode->FsrRank;
        if(title == "Cpf") return currentNode->CpfRank;
        if(title == "Ifr") return currentNode->IfrRank;
        if(title == "Isr") return currentNode->IsrRank;
        if(title == "Irn") return currentNode->IrnRank;
        if(title == "Ger") return currentNode->GerRank;
        
        return 0;
    }

    // Utility function
    float getScore(universityNode* currentNode, string title)
    {
        if(title == "Rank") return currentNode->ScoreScaled;
        if(title == "Ar") return currentNode->ArScore;
        if(title == "Er") return currentNode->ErScore;
        if(title == "Fsr") return currentNode->FsrScore;
        if(title == "Cpf") return currentNode->CpfScore;
        if(title == "Ifr") return currentNode->IfrScore;
        if(title == "Isr") return currentNode->IsrScore;
        if(title == "Irn") return currentNode->IrnScore;
        if(title == "Ger") return currentNode->GerScore;
        return 0.0;
    }

    // provide location list to be selected
    pair<string, string> getLocation()
    {
        pair<string, string> location;
        string userInput;
        int userChoice;

        // print country list
        cout << string(75, '=')  << " Country List " << string(75, '=') << endl;
        for (int i = 1; i <= 100; i++)
        {
            cout << setw(3) << left << i << ". " << setw(25) << left << country[i-1] << setw(1) << left <<" ";
            if(i%5 == 0)
                cout << endl;
        }
        cout << string(164, '=') << endl;

        while(true)
        {   
            cout << "Please enter the university location <1-100>: ";
            cin >> userInput;
            
            try
            {
                userChoice = stoi(userInput);
                // validate input 
                if(userChoice >= 1 && userChoice <= 100)
                {
                    location.first = country[userChoice-1];
                    location.second = countryCode[userChoice-1];
                    break;
                }
                else
                {
                    cout << "Invalid input, Please enter <1-100>" << endl;
                    cin.ignore();
                }
            }
            catch(const std::exception& e)
            {
                cout << "Invalid input, Please enter <1-100>" << endl;
            }               
        }

        return location;
    }
};

// print menu for search rank by range
void searchRangeRankMenu()
{
    // print rank range selection 
    cout << "*** Choose the Rank's range ***" << endl;
    cout << "1. Range from 1 - 50." << endl;
    cout << "2. Range from 51 - 100." << endl;
    cout << "3. Range from 101 - 200." << endl;
    cout << "4. Range from 201 - 300." << endl;
    cout << "5. Range from 301 - 400." << endl;
    cout << "6. Range from 401 - 500." << endl;
    cout << "7. Range More than 501." << endl; // Search 501+
    cout << "00. Back." << endl; // Search 501+
    cout << endl << string(39,'=') << endl;
}

// print menu for search score by range
void searchRangeScoreMenu()
{
    // print score range selection 
    cout << "*** Choose the Score's range ***" << endl;
    cout << "1. Score more than 80." << endl;
    cout << "2. Score between 60 - 80." << endl;
    cout << "3. Score between 40 - 60." << endl;
    cout << "4. Score between 20 - 40." << endl;
    cout << "5. Score between less than 20." << endl;
    cout << "00. Back." << endl;
    cout << endl << string(39,'=') << endl;
}
// # Function : R User Search university details 
void UniversityList::rUser_search_university()
{
    // Define variables
    int cont_action;

    // Determine action of the user
    while (true)
    {
        string action;
        cout << string(50,'-') << endl; 
        cout << " ** Search based on which university's details? **" << endl;
        cout << "Enter 1: Search by Institution."<< endl;
        cout << "Enter 2: Search by Location."<< endl;
        cout << "Enter 3: Search by university's rank."<< endl;
        cout << "Enter 4: Search by university's score."<< endl;
        cout << "Enter 00: Go back." << endl;

        cout << endl << string(15,'=') << endl;
        cout << "Type here : ";
        cin >> action;
        cout << string(15,'=') << endl;
        cout << string(60,'-') << endl; 
       
        if (action == "1") searchByInstiLocation("Institution"); // search based on institution       
        else if (action == "2") searchByInstiLocation("Location"); // Search based on Location 
        else if (action == "3") searchMenu("Rank"); // Search based on university rank
        else if (action == "4") searchMenu("Score"); // Search based on university score
        // Back to menu
        else if (action == "00")
        {
            cout << "\033[1J\033[H"; // clear previous line
            break;
        }
        else{
            cout << "Invalid Input." << endl << endl;
        }
    }
}


// # Function : R User Sort university details
void UniversityList::rUser_sort_university(string targetScore, bool displayDesc){
    // Call sort methods
    if (targetScore == "ArScore"){ head = mergeSort(head,"ArScore");arrangeTail();}
    else if (targetScore == "FsrScore"){head = mergeSort(head,targetScore);arrangeTail();}
    else if (targetScore == "ErScore"){head = mergeSort(head,targetScore);arrangeTail();}
    else if (targetScore == "Institution"){head = mergeSort(head,"Institution");arrangeTail();}
    
    // Call display data methods
    if (displayDesc){displayData(true);}
    else{displayData(false);}
}

// Handle search on location and institution
void UniversityList::searchByInstiLocation(string title)
{
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    while (true)
    {
        // Get institution name
        string userInput = "";

        if (title == "Institution")
        {
            cout << "Please enter the university's institution (or keywords) : " ;
            getline(cin, userInput);
            cout << endl;
        }
        else if (title == "Location")
        {
            userInput = getLocation().first;
        }
        
        // Call search linear transition methods
        linearTransitionSearch(userInput, title,"");
        cout << "Search result end here !" << endl;
        // Keep track repeat action
        while (true)
        {
            cout << "Press <1> to continue or <0> to exit" << endl;
            cout << "Type here: ";
            string cont_action;
            if (title == "Location")
            {
                cin >> cont_action;
            }else{
                getline(cin, cont_action);
            }
            
            if (cont_action=="0")
            {
                cout << endl;
                cout << "\033[1J\033[H"; // clear previous line
                cout << "Exiting..." << endl;
                return;
            }else if (cont_action == "1")
            {
                cout << "\033[1J\033[H"; // clear previous line
                cout << "Search countinue.." << endl;
                break;
            }else{
                cout << "Invalid Input." << endl<< endl;
            }
        }
    }
}

// hand search on university attribute
void UniversityList::searchMenu(string type)
{
    // type = Rank or Score
    while(true)
    {
        // Print search by rank menu
        cout << "Search based on which university's " << type << "?" <<endl;
        cout << "Enter 1: Search by Academic Reputation "<< type << "." <<endl;
        cout << "Enter 2: Search by Employer Reputation "<< type << "." <<endl;
        cout << "Enter 3: Search by Faculty/Student Ratio "<< type << "." <<endl;
        cout << "Enter 4: Search by Citations per Faculty "<< type << "." <<endl;
        cout << "Enter 5: Search by International Faculty Ratio "<< type << "." <<endl;
        cout << "Enter 6: Search by International Student Ratio "<< type << "." <<endl;
        cout << "Enter 7: Search by International Research Network "<< type << "." <<endl;
        cout << "Enter 8: Search by Employment Outcome "<< type << "." <<endl;
        cout << "Enter 00: Go Back."<< endl;
        // Capture input
        string action_1;
        
        cout << endl << string(39,'=') << endl;
        cout << "Type here : ";
        // getline(cin,action_1);
        cin >> action_1;
        cout << endl;
        
        if      (action_1 == "1") searchByRankScore("Ar", type); // search based on ArRank 
        else if (action_1 == "2") searchByRankScore("Er", type); // search based on ErRank 
        else if (action_1 == "3") searchByRankScore("Fsr", type); // search based on FsrRank   
        else if (action_1 == "4") searchByRankScore("Cpf", type); // search based on CpfRank 
        else if (action_1 == "5") searchByRankScore("Ifr", type); // search based on IfrRank 
        else if (action_1 == "6") searchByRankScore("Isr", type); // search based on IsrRank                
        else if (action_1 == "7") searchByRankScore("Irn", type); // search based on IrnRank                
        else if (action_1 == "8") searchByRankScore("Ger", type); // search based on GerRank 
        else if (action_1 == "00")
        {
            cout << "\033[1J\033[H"; // clear previous line
            cout << "Back to previous page" << endl;
            break;
        }
        else{
            cout << "Invalid Input."<< endl << endl;
        }
    }
}

// handle search on rank and score range
void UniversityList::searchByRankScore(string title, string menu)
{
    while (true)
    {   
        // print menu to select what they need to search
        if      (menu == "Rank")  searchRangeRankMenu();
        else if (menu == "Score") searchRangeScoreMenu();
        
        // Get range from user
        string rangeIndex = "";
        bool valid = false;
        cout << "Please enter your selection : " ;
        cin >> rangeIndex;
        cout << endl;

        if(rangeIndex == "00")
            break;
        
        try
        {
            int rangeChoices = stoi(rangeIndex);
            if (menu == "Rank" && (rangeChoices>=1 && rangeChoices <= 7))
                valid = true;
            
            else  if (menu == "Score" && (rangeChoices>=1 && rangeChoices <=5))
                valid = true;
        }
        catch(const std::exception& e)
        {
            cout << "Invalid input."<< endl <<endl;
        }
        
        if (valid) // if input valid
        {
            // Call search linear transition methods
            linearTransitionSearch(rangeIndex, title,menu);

            cout << "Search result end here !" << endl;
            // Keep track repeat action
            while (true)
            {
                cout << "Press <1> to continue or <0> to exit" << endl;
                cout << "Type here: ";
                string cont_action;
                cin >> cont_action;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                if (cont_action=="0")
                {
                    cout << endl;
                    cout << "\033[1J\033[H"; // clear previous line
                    cout << "Exiting..." << endl;
                    return;
                }
                else if (cont_action == "1")
                {
                    cout << "\033[1J\033[H"; // clear previous line
                    cout << "Search countinue.." << endl;
                    break;
                }else{
                    cout << "Invalid Input." << endl<< endl;
                }
            }
        }else{
           cout << "Invalid input."<< endl <<endl; 
        }
        


    }
}

