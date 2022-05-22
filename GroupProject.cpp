#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::cin;
using std::string;
using std::vector;

class Admin {
private:
    string name = "a";
    string pwd = "a";

public:
    Admin(){}
    bool login(string name, string pwd){
        if(this->name == name && this->pwd == pwd){
            return true;
        }
        else{
            return false;
        }
    }
};

class Member {
private:
    string username;
    string pwd;
    string full_name;
    string phone_num;
    double credit;
    double rating;

public:
    Member(){};
    Member(string username, string pwd, string full_name, string phone_num) {
        this->username = username;
        this->pwd = pwd;
        this->full_name = full_name;
        this->phone_num = phone_num;
        this->credit = 500;
        this->rating = 0;
    }
    Member(string username, string pwd, string full_name, string phone_num, double cre, double rating) {
        this->username = username;
        this->pwd = pwd;
        this->full_name = full_name;
        this->phone_num = phone_num;
        this->credit = cre;
        this->rating = rating;
    }

    // Getters
    string getMemberUsername() { return username; }
    string getMemberPassword() { return pwd; }
    string getMemberFullname() { return full_name; }
    string getMemberPhoneNumber() { return phone_num; }
    double getMemberCredit() { return credit; }
    double getMemberRating() { return rating; }
    
    // Setters
    void setMemberUsername(string usrn) { username = usrn; };
    void setMemberPassword(string pass) { pwd = pass; };
    void setMemberFullname(string fn) { full_name = fn; }
    void setMemberPhoneNumber(string pn) { phone_num = pn; }
    void setMemberCredit(double cre) { credit = cre; }
    void setMemberRating(double rate) { rating = rate; }

    friend class System;
};

class House {
private:
    Member* owner;
    string city;
    string startDate;
    string endDate;
    double points;
    Member* occupier;
    double rating;
    double minRating;
public:
    House(){}
    House(Member* owner, string city, string startDate, string endDate, double points, Member* occupier, double rating, double minRating){
        this->owner = owner;
        this->city = city;
        this->startDate = startDate;
        this->endDate = endDate;
        this->points = points;
        this->occupier = occupier;
        this->rating = rating;
        this->minRating = minRating;
    }
    //Getters
    Member* getHouseOwner(){return owner;}
    Member* getHouseOccupier(){return occupier;}
friend class System;
};

//Function to calculate total credit points needed (This function is used in class System, so it has to be defined before it)
double totalPoints(string startDate, string endDate, double point){
    int startDay = std::stoi(startDate.substr(0, 2)) - 1; 
    int startMonth = std::stoi(startDate.substr(3, 2)); 
    int endDay = std::stoi(endDate.substr(0, 2));
    int endMonth = std::stoi(endDate.substr(3, 2));  
    int day = 0;
    bool stop = true;
    while (stop){
        if (startMonth == 1 || startMonth == 3 || startMonth == 5 || startMonth == 7 || startMonth == 8 || startMonth == 10 || startMonth == 12){
            if (startDay == 31){
                if (startMonth == 12){
                    startMonth = 1;
                    startDay = 0;
                } else {
                    startMonth++;
                    startDay = 0;
                }
            }
        } else if (startMonth == 2){ 
            if (startDay == 29) { //Assuming Febuary has 29 days
                startMonth++;
                startDay = 0;
            }
        } else {
            if (startDay == 30){
                startMonth++;
                startDay = 0;
            }
        }
        day++;
        startDay++;
        if (startMonth == endMonth){
            if (startDay == endDay){
                stop = false;
            }
        }
    }
    point = point * day;
    return point;
}
//Extra function, used to compare dates to search houses with specific time period
bool compareDates(string date1, string date2){
    int day1 = std::stoi(date1.substr(0, 2)); 
    int month1 = std::stoi(date1.substr(3, 2));
    int day2 = std::stoi(date2.substr(0, 2)); 
    int month2 = std::stoi(date2.substr(3, 2));
    if (month1 == month2 && day1 > day2){
        return true;
    } else if (month1 == month2 && day1 == day2) {
        return true;
    } else if (month1 > month2) {
        return true;
    } else { return false; }
}

class System {
public:
    vector<Member*> members;
    vector<House*> houses;
    System(){};

    void addMember(Member* member){
        members.push_back(member);
    }

    void addHouse(House* house){
        houses.push_back(house);
    }

    void viewMembers(){ //Only admin use this
        cout << "---------------------------------\n" 
            <<"List of members: \n";
        for (auto mem: members) {
            cout << "Username: " << mem->username << "\n" 
            << "Password: " << mem->pwd << "\n" 
            << "Full name: " << mem->full_name << "\n" 
            << "Phone number: " << mem->phone_num << "\n" 
            << "Credit point: " << mem->credit << "\n"
            << "Rating: " << mem->rating << "\n"
            << "---------------------------------\n";
        }
    }
    
    void viewHouses(string username, string startDate, string endDate, string city){
        //Get information fo the user (rating and credit points)
        double cre = 10000;
        double rating = 10000;
        if (username != "Guest" && username != "Admin"){
            cre = searchMemByUsername(username)->getMemberCredit();
            rating = searchMemByUsername(username)->getMemberRating();
        }
        bool check = false;
        cout << "---------------------------------\n" 
            <<"List of registered houses: \n";
        for (auto house: houses) {
            //Check user's rating and credit points, only print out if enough
            if (cre > totalPoints(house->startDate, house->endDate, house->points) && rating >= house->minRating){
                if (compareDates(startDate, house->startDate) && compareDates(house->endDate, endDate)) {
                    if (city == house->city || city == "ALL"){
                        cout << "Host username: " << house->owner->getMemberUsername() << "\n"
                        << "Location: " << house->city << "\n" 
                        << "Points consuming per day: " << house->points << "\n";
                        cout << "Minimum Rating required: " << house->minRating << "\n"; 
                        if (username == "Admin" || username != "Guest"){ //Guest restriction
                            cout << "Occupier: ";
                            if (house->occupier != NULL){
                                cout << house->occupier->getMemberUsername();
                            } else { cout << 0; }
                            cout << "\nStart date: " << house->startDate << "\n" 
                            << "End date: " << house->endDate << "\n" 
                            << "Rating: " << house->rating << "\n";
                            check = true;
                        }
                        cout << "---------------------------------\n";
                    }
                }
            
            }
        }
        if (!check){
            cout << "No house matches.\n";
        } 
    }

    Member* searchMemByUsername(string username){
        for (auto mem: members) {
            if (mem->username == username){return mem;}
        } return NULL;
    }

    void acceptRequest(string username, string occupier){
        vector<string> arrTemp; //Store lines that will be written in file
        for (auto house: houses) {
            arrTemp.push_back(house->owner->getMemberUsername() + ",");
            arrTemp.push_back(house->city + ",");
            arrTemp.push_back(house->startDate + ",");
            arrTemp.push_back(house->endDate + ",");
            arrTemp.push_back(std::to_string(house->points) + ",");
            if (house->owner->getMemberUsername() == username){
                //Change occupier value in arrTemp to write in file later 
                arrTemp.push_back(occupier + ",");
                //Change occupier value in vector houses
                house->occupier = searchMemByUsername(occupier);
            } else { arrTemp.push_back("0,"); }
            arrTemp.push_back(std::to_string(house->rating) + ",");
            arrTemp.push_back(std::to_string(house->minRating) + ",");
        }
        //Rewrite house.txt
        std::fstream myFile;
        myFile.open("house.txt", std::ios::out);
        for (string item: arrTemp){
            myFile << item;
        }
    }
    void deleteHouse(string username){
        vector<string> arrTemp; //Store lines that will be written in file
        for (int i = 0; i < houses.size(); i++){
            if (houses[i]->owner->getMemberUsername() != username){ //Get all other houses except the target house
                arrTemp.push_back(houses[i]->owner->getMemberUsername() + ",");
                arrTemp.push_back(houses[i]->city + ",");
                arrTemp.push_back(houses[i]->startDate + ",");
                arrTemp.push_back(houses[i]->endDate + ",");
                arrTemp.push_back(std::to_string(houses[i]->points) + ",");
                if (houses[i]->occupier != NULL){
                    arrTemp.push_back(houses[i]->occupier->getMemberUsername() + ",");
                    cout << "Oc";
                } else { arrTemp.push_back("0,");}
                arrTemp.push_back(std::to_string(houses[i]->rating) + ",");
                arrTemp.push_back(std::to_string(houses[i]->minRating) + ",");
            } else {
                houses.erase(houses.begin() + i); //Remove from houses vector
                i--;
            }
        }
        //Rewrite house.txt
        std::fstream myFile;
        myFile.open("house.txt", std::ios::out);
        for (string item: arrTemp){
            myFile << item;
        }
    }

};

//Function to check if username is taken
bool checkUsername(string username){   
    std::fstream myFile;
    myFile.open("account.txt", std::ios::in);
    string line;
    int count = 1;
    vector<string> a;
    while(getline(myFile, line, ',')){
        a.push_back(line);
    }
    for (int i = 0; i < a.size(); i++){
        if (count == 1){
            if (username == a[i]){
                return true;
            }
        }
        if (count == 6){ count = 0;}
        count++;
    }
    myFile.close();
    return false;
};

void denyRequest(string username, vector<string> requestArr){
    std::fstream myFile;
    string line;
    int count = 0;
    vector<int> deleteIndex; //A vector of index that will be removed in Eequest array
    for (int i = 0; i < sizeof(requestArr); i++){
        if (count == 1 && requestArr[i] == username){
            deleteIndex.push_back(i-1);
            deleteIndex.push_back(i);
            count = 0;
        } else if (count == 1){ count = 0; } 
        else { count++; }
    }
    count = 0;
    for (int index: deleteIndex){ //Delete those indexes
        index -= count;
        requestArr.erase(requestArr.begin() + index);
        count++;
    }
    //Re-write the file
    myFile.open("request.txt", std::ios::out);
    for (string request: requestArr){
        myFile << request << ",";
    }
    myFile.close();
}

bool validateDate(string date){
    if (isdigit(date[0]) && isdigit(date[1]) & date[2] == '-' & isdigit(date[3]) & isdigit(date[4])){
        int day = std::stoi(date.substr(0, 2)); 
        int month = std::stoi(date.substr(3, 2));
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
            if (day < 32){ return true; }
        } else if (month == 2){ //Assuming Febuary has 29 days
            if (day < 30){ return true; } 
        } else {
            if (month < 13 && day < 31){ return true; }
        }

    }
    return false;
}


int main() {
    //key and a are user's choices
    int key;
    int a = 99;
    
    Admin admin; //Default username and password are "a" (for fast testing)
    System appSys;
    //For Member
    string username, pwd, full_name, phone_num;
    double cre, memRating;
    char name[100] = {0};
    bool loggedin = false;
    //For House
    string city, startDate, endDate;
    double points;
    //For request
    vector<string> requestArr, requestTemp;

    //Read data from account.txt
    std::fstream myFile;
    string line;
    int count = 1;
    vector<string> arr;
    myFile.open("account.txt", std::ios::in);
    while(getline(myFile, line, ',')){
        arr.push_back(line);
    }
    myFile.close();

    for (int i = 0; i < arr.size(); i++){
        if (count == 1){
            username = arr[i];
        }
        if (count == 2){
            pwd = arr[i];
        }
        if (count == 3){
            full_name = arr[i];
        }
        if (count == 4){
            phone_num = arr[i];
        }
        if (count == 5){
            cre = std::stod(arr[i]);
        }
        if (count == 6){
            memRating = std::stod(arr[i]);
        }
        if (count == 7){
            appSys.addMember(new Member(username,pwd,full_name,phone_num,cre,memRating));
            username = arr[i];
            count = 1;
        }
        count++;
    }
    appSys.addMember(new Member(username,pwd,full_name,phone_num,cre,memRating));

    //Read data from house.txt
    arr.clear();
    string occupier;
    double rating, minRating;
    count = 1;
    vector<string> houseArr;
    myFile.open("house.txt", std::ios::in);
    while(getline(myFile, line, ',')){
        arr.push_back(line);
    }
    myFile.close();
    for (int i = 0; i < arr.size(); i++){
        if (count == 1){
            username = arr[i];
        }
        if (count == 2){
            city = arr[i];
        }
        if (count == 3){
            startDate = arr[i];
        }
        if (count == 4){
            endDate = arr[i];
        }
        if (count == 5){
            points = std::stod(arr[i]);
        }
        if (count == 6){
            occupier = arr[i];
        }
        if (count == 7){
            rating = std::stod(arr[i]);
        }
        if (count == 8){
            minRating = std::stod(arr[i]);
        }
        if (count == 9){
            if(occupier == "0"){
                appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,NULL,rating,minRating));
            } else {
                appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,appSys.searchMemByUsername(occupier),rating,minRating));
            }
            username = arr[i];
            count = 1;
        }
        count++;
    }
    if(occupier == "0"){
        appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,NULL,rating,minRating));
    } else {
        appSys.addHouse(new House(appSys.searchMemByUsername(username),city,startDate,endDate,points,appSys.searchMemByUsername(occupier),rating,minRating));
    }
    //Reset these variables for input validation later
    minRating = 11;
    points = -1;
    startDate = "";
    endDate = "";
    
    //Read data from request.txt
    myFile.open("request.txt", std::ios::in);
    while(getline(myFile, line, ',')){
        requestArr.push_back(line);
    }
    myFile.close();

    //Extra. Read data from requestWithTime.txt
    vector<string> requestWithTimeArr;
    myFile.open("requestWithTime.txt", std::ios::in);
    while(getline(myFile, line, ',')){
        requestWithTimeArr.push_back(line);
    }
    myFile.close();


    while(true) {
        cout << "EEET2482/COSC2082 ASSIGNMENT \n"
        <<"VACATION HOUSE EXCHANGE APPLICATION \n"
        <<"\n"
        <<"Instructor: Mr. Linh Tran \n"
        <<"Group: Group 22 \n"
        <<"s3881388, Phan Quoc Thang \n"
        <<"s3877673, Bui Nguyen Ngoc Tuan \n"
        <<"s3891637, Tran Chi Toan \n"
        <<"\n"
        << "Use the app as 1.Guest    2.Member    3.Admin \n"
        <<  "Enter your choice: ";
        cin >> key;
        switch(key) {
            case 1: //GUEST
                username = "Guest";
                while (a != 0){
                    cout << "This is your menu: \n"
                    << "0. Exit \n"
                    << "1. View all available vacation houses \n"
                    << "2. Register member \n"
                    << "Enter your choice: ";
                    cin >> a;
                    if (a == 2) {
                        //Register form
                        Member *newMem = new Member(username, pwd, name, phone_num);
                        cout << "-----Register account--------\n";

                        cout << "Please enter username: ";
                        cin >> username;
                        if (!checkUsername(username)){ //Check if username is already taken
                            newMem->setMemberUsername(username);

                            cout << "Please enter password: ";
                            cin >> pwd;
                            newMem->setMemberPassword(pwd);

                            cin.ignore();

                            cout << "Please enter your full name: ";
                            
                            getline(cin, full_name);
                            newMem->setMemberFullname(full_name);

                            cout << "Please enter your phone number: ";
                            cin >> phone_num;
                            newMem->setMemberPhoneNumber(phone_num);

                            //Store account into the system (if the registration is successful)
                            appSys.addMember(newMem);
                            std::ofstream myFile("account.txt", std::ios_base::app);
                            myFile << newMem->getMemberUsername() << "," << newMem->getMemberPassword() << "," 
                            << newMem->getMemberFullname() << "," << newMem->getMemberPhoneNumber() << "," << newMem->getMemberCredit() << "," << newMem->getMemberRating() << ",";
                            myFile.close();

                            //Reward 500 points for registration
                            cout<<"Your have been rewarded 500 credit points for registering your account!\n"
                            << "Register complete! System will automatically logged out.\n";
                            return 0;
                        } else {
                            cout << "Username has already taken.\n";
                        }
                    }
                    if (a == 1){
                        //View houses (Guest restrcition is in the function)
                        appSys.viewHouses(username, "31-12", "00-00", "ALL");
                    }
                } return 0;
            case 2: //MEMBER
                cout << "Please enter your username: ";
                cin >> username;
                cout << "Please enter your password: ";
                cin >> pwd;
                //Check username and password
                for (Member *eachMem : appSys.members) {
                    if(eachMem->getMemberUsername() == username && eachMem->getMemberPassword() == pwd) {
                        cout << "Login successful" << "\n";
                        loggedin = true;
                    }
                }
                if (loggedin == false){
                    cout << "Login failed" << "\n";
                    break;
                } else {
                    while (a != 0){
                        cout << "Welcome " << username << ":\n"
                        << "0. Exit \n"
                        << "1. See your information \n"
                        << "2. Register a house \n"
                        << "3. Search a house \n"
                        << "4. View requests \n"
                        << "5. Unregister a house \n"
                        << "6. See time period features \n"
                        << "Enter your choice: ";
                        cin >> a;
                        if(a == 1){
                            //Show all infromation except Password (for practical sucurity reason)
                            cout << "-----------------------\n";
                            cout << "Full name: " << appSys.searchMemByUsername(username)->getMemberFullname() << "\n"
                            << "Phone number: " << appSys.searchMemByUsername(username)->getMemberPhoneNumber() << "\n"
                            << "Credit points: " << appSys.searchMemByUsername(username)->getMemberCredit() << "\n"
                            << "Rating: " << appSys.searchMemByUsername(username)->getMemberRating() << "\n";
                            cout << "-----------------------\n";
                        }
                        if(a == 2) {
                            //Register a house
                            bool check = true; //A member can only register 1 house
                            for (auto house: appSys.houses){
                                if (house->getHouseOwner()->getMemberUsername() == username){ 
                                    cout << "You have already registered a house.\n";
                                    check = false;
                                    break;
                                }
                            }
                            if (check){
                                cin.ignore();
                                while (loggedin == true){ //Re-use this boolean variable for validation purpose
                                    cout << "Please enter the city your house: ";
                                    getline(cin, city);
                                    if (city == "Da Nang" || city == "Hanoi" || city == "Saigon"){
                                        loggedin = false;
                                    } else { cout << "Sorry this function is only available on cities: Hanoi, Saigon and Da Nang.\n"; }
                                } loggedin = true;
                                while (startDate == ""){
                                    cout << "Please enter start Date (dd-mm): ";
                                    cin >> startDate;
                                    if (!validateDate(startDate)){ 
                                        cout << "Invalid input. Please make sure to input with format: dd-mm\n";
                                        startDate = "";
                                    } 
                                }
                                while (endDate == ""){
                                    cout << "Please enter end Date (dd-mm): ";
                                    cin >> endDate;
                                    if (!validateDate(endDate)){ 
                                        cout << "Invalid input. Please make sure to input with format: dd-mm\n";
                                        endDate = "";
                                    } 
                                }
                                while (points <= 0){
                                    cout << "Please enter point consuming per day: ";
                                    cin >> points;
                                    if (points <= 0){ cout << "Points must be larger than 0 (You don't want your house to be free!)."; }
                                }
                                while (minRating > 10 || minRating < -10){
                                    cout << "Please enter minimum rating required: ";
                                    cin >> minRating;
                                    if (minRating > 10 || minRating < -10){ cout << "Rating must be between -10 and 10.\n"; }
                                }
                                House *newHouse = new House(appSys.searchMemByUsername(username), city, startDate, endDate, points, NULL, 0, minRating);
                                appSys.addHouse(newHouse);
                                //Write mewHouse to file
                                std::ofstream myFile("house.txt", std::ios_base::app);
                                myFile << username << "," << city << "," 
                                << startDate << "," << endDate << "," << points << "," << "0,0," << minRating << ",";
                                myFile.close();
                                cout << "House registered.\n";
                            } 
                            startDate = "";
                            endDate = "";
                        }
                        if(a == 3) {
                            bool check = true;
                            //Search for houses (Any restriction is in the function)
                            cin.ignore();
                            while (check){ //Re-use this boolean variable for validation purpose
                                cout << "Please enter the city you want to search for houses, type \"ALL\" if you want to view all: ";
                                getline(cin, city);
                                if (city == "Da Nang" || city == "Hanoi" || city == "Saigon" || city == "ALL"){
                                    check = false;
                                } else { cout << "Sorry this function is only available on cities: Hanoi, Saigon and Da Nang.\n"; }
                            } check = true;
                            appSys.viewHouses(username, "31-12", "00-00", city);
                             //A member can only occupy 1 house
                            for (auto house: appSys.houses){
                                if (house->getHouseOccupier() != NULL){
                                    if (house->getHouseOccupier()->getMemberUsername() == username){ 
                                        cout << "You are currently occupying a house, you cannot select another once.\n";
                                        check = false;
                                        break;
                                    }
                                }
                            }
                            if (check){
                                cout << "Enter owner username of the house you want to send request, or type \"CANCEL\" to cancel: ";
                                cin >> occupier;
                                if (occupier != "CANCEL"){
                                    if (checkUsername(occupier)){ //Check if input is correct
                                        //Store the request into file
                                        std::ofstream myFile("request.txt", std::ios_base::app);
                                        myFile << username << "," << occupier << ",";
                                        myFile.close();
                                        cout << "Request has been sent to " << occupier <<".\n";
                                    } else { cout << "Invalid username.\n"; }
                                }
                            }
                        }
                        if(a == 4) {
                            //See all requests
                            count = 0;
                            for (int i = 0; i < requestArr.size(); i++){
                                if (count == 1 && requestArr[i] == username){
                                    requestTemp.push_back(requestArr[i-1]);
                                    count = 0;
                                    loggedin = false; //Just re-use this boolean variable to print out information
                                } else if(count == 1){ count = 0; } else { count++; }
                            }
                            cout << "----------------------\n" <<"Requests:\n";
                            if (loggedin){ 
                                cout << "You have no request.\n"; 
                                loggedin = true; //Just re-use this boolean variable again to not ask user to deny or accept any request (since there is no request)
                            } else {
                                for (string request: requestTemp){
                                    cout << "User: " << request << "\n";
                                }
                            } requestTemp.clear();
                            cout << "----------------------\n";
                            if (!loggedin){
                                cout << "Type the username you want to Approve, or type \"DENY\" to deny all request: ";
                                cin >> occupier;
                                if (occupier == "DENY"){
                                    denyRequest(username, requestArr); //Reject all request
                                    cout << "All requests have been denied.";
                                } else {
                                    if (checkUsername(occupier)){ //Check if input is correct
                                        appSys.acceptRequest(username, occupier); //Accept that request
                                        denyRequest(username, requestArr); //Reject all other request
                                        cout << "You have accepted user " << occupier << " to occupy your house.\n";
                                    } else { cout << "Invalid username.\n"; }
                                }
                            } loggedin = true;
                        }
                        if (a == 5){ //Unregister a house
                            bool check = false; //Check if user has a house
                            for (auto house: appSys.houses){
                                if (house->getHouseOwner()->getMemberUsername() == username){
                                    check = true;
                                    break;
                                }
                            }
                            if (!check){
                                cout << "You haven't registered anyhouse.\n";
                            } else {
                                while (check) { //Validate answer
                                    cout << "Type \"CONFIRM\" to unregister your house or type \"CANCEL\" to cancel: \n";
                                    cin >> occupier; //REUSE variable as answer
                                    if (occupier == "CONFIRM" || occupier == "CANCEL"){
                                        check = false;
                                    } else { cout << "Sorry I couldn't get that, please try again.\n";}
                                } 
                                if (occupier == "CONFIRM") {
                                    appSys.deleteHouse(username);
                                    cout << "Your house has been unregistered.\n";
                                }
                            }
                        }
                        if (a == 6){ //Extra functions
                            int b = 0;
                            while (b != 3){
                                cout << "----------------------------- \n" 
                                << "Time period features menu: \n"
                                << "1. Search house with a time period \n"
                                << "2. View requests that have time period \n"
                                << "3. Go back \n"
                                << "Enter your choice: ";
                                cin >> b;

                                if (b == 1){ //Show houses that have the time period
                                    while (startDate == ""){
                                        cout << "Please enter start Date (dd-mm): ";
                                        cin >> startDate;
                                        if (!validateDate(startDate)){ 
                                            cout << "Invalid input. Please make sure to input with format: dd-mm\n";
                                            startDate = "";
                                        } 
                                    }
                                    while (endDate == ""){
                                        cout << "Please enter end Date (dd-mm): ";
                                        cin >> endDate;
                                        if (!validateDate(endDate)){ 
                                            cout << "Invalid input. Please make sure to input with format: dd-mm\n";
                                            endDate = "";
                                        } 
                                    }
                                    appSys.viewHouses(username, startDate, endDate, "ALL");
                                    bool check = true; //A member can only occupy 1 house
                                    for (auto house: appSys.houses){
                                        if (house->getHouseOccupier() != NULL){
                                            if (house->getHouseOccupier()->getMemberUsername() == username){ 
                                                cout << "You are currently occupying a house, you cannot select another once.\n";
                                                check = false;
                                                break;
                                            }
                                        }
                                    }
                                    if (check){ //Print out
                                        cout << "Enter owner username of the house you want to send request, or type \"CANCEL\" to cancel: ";
                                        cin >> occupier;
                                        if (occupier != "CANCEL"){
                                            if (checkUsername(occupier)){ //Check if input is correct
                                                //Store the request with time into file
                                                std::ofstream myFile("requestWithTime.txt", std::ios_base::app);
                                                myFile << username << "," << occupier << "," << startDate << "," << endDate << ",";
                                                myFile.close();
                                                cout << "Request has been sent to " << occupier << "with time from " << startDate << " to " << endDate << ".\n";
                                            } else { cout << "Invalid username.\n"; }
                                        }
                                    }
                                }
                                if (b == 2) { //View request from file requestWithTime (note that these time-requests are not associated with normal requests)
                                    count = 0;
                                    bool check = true;
                                    for (int i = 0; i < requestWithTimeArr.size(); i++){
                                        if (count == 1 && requestWithTimeArr[i] == username){
                                            requestTemp.push_back(requestWithTimeArr[i-1]);
                                            requestTemp.push_back(requestWithTimeArr[i+1]);
                                            requestTemp.push_back(requestWithTimeArr[i+2]);
                                            count = 0;
                                            check = false;
                                        } else if(count == 3){
                                            count = 0;
                                        } else { 
                                            count++; 
                                        }
                                    }
                                    cout << "--------------------------------------------\n" <<"Requests:\n";
                                    if (check){ 
                                        cout << "You have no request.\n"; 
                                    } else {
                                        count = 1;
                                        for (int i = 0; i < requestTemp.size(); i++){
                                            if (count == 1){
                                                cout << "User: " << requestTemp[i] << " requested your house from ";
                                            }
                                            if (count == 2){
                                                cout << requestTemp[i] << " to ";
                                            } 
                                            if (count == 3){
                                                cout << requestTemp[i] << ".\n";
                                                count = 0;
                                            }
                                            count++;
                                        }
                                    }
                                    requestTemp.clear();
                                    cout << "--------------------------------------------\n";
                                }
                            }
                            
                        }
                    } return 0;
                }
            case 3: //ADMIN
                cout << "Please enter your username: ";
                cin >> username;
                cout << "Please enter your password: ";
                cin >> pwd;
                
                //Check username and password
                if(admin.login(username, pwd)) {
                    cout << "Login successful" << "\n";
                    //Automatically show all users and houses (no input require and stop program after that - usually used for testing) 
                    appSys.viewMembers();
                    appSys.viewHouses("Admin", "31-12", "00-00", "ALL");
                    return 0;
                }
        }
    }
}