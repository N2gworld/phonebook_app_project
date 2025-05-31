#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <regex>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

using namespace std;

class Phonebook {
private:
    string Name;
    string phonenumber;
    string Email;

public:
    void addContact() {
        bool nameExists = true;
        while (nameExists) {
            cout<<RED<<"\t----------------"<<endl;
            cout <<GREEN<<"\t  Enter Name : "<<endl;
            cout<<RED<<"\t----------------"<<RESET<<endl;
            cin >> Name;
            transform(Name.begin(), Name.end(), Name.begin(), ::tolower);

            ifstream file("Store.txt");
            vector<string> existingContacts;
            string line;
            nameExists = false;

            while (getline(file, line)) {
                size_t pos1 = line.find("  "); 

                string storedName = line.substr(0, pos1);

                if (storedName == Name) {
                    cout<<RED<<"\t-------------------------------------------------"<<RESET<<endl;
                    cout <<BLUE<< "\t   This Name Already Exists . Try Another..." << endl;
                    cout<<RED<<"\t-------------------------------------------------"<<RESET<<endl;
                    nameExists = true;
                    break;
                }
            }
            file.close();
        }

        bool validPhoneNumber = false;
        while (!validPhoneNumber) {
            cout<<RED<<"\t-----------------------------------"<<RESET<<endl;
            cout << GREEN<<"\t  Enter Phone number (10 digits): "<<endl;
            cout<<RED<<"\t-----------------------------------"<<RESET<<endl;
            cin >> phonenumber;

            if (phonenumber.length() == 10 && all_of(phonenumber.begin(), phonenumber.end(), ::isdigit)) {
                ifstream file("Store.txt");
                vector<string> existingContacts;
                string line;
                bool phoneExists = false;

                while (getline(file, line)) {
                    size_t pos1 = line.find("  "); 

                    string storedPhonenumber = line.substr(pos1 + 2, 10);

                    if (storedPhonenumber == phonenumber) {
                        cout<<RED<<"\t------------------------------------------------------------------"<<RESET<<endl;
                        cout << BLUE<<"\t  Phone Number Already Exists. Enter Different Phone-Number..." << endl;
                        cout<<RED<<"\t------------------------------------------------------------------"<<RESET<<endl;
                        phoneExists = true;
                        break;
                    }
                }
                file.close();

                if (!phoneExists) {
                    validPhoneNumber = true;
                }
            } else {
                cout<<RED<<"\t------------------------------------------------------------------"<<RESET<<endl;
                cout << BLUE<<"\t  Invalid phone number. Please enter a 10-digit phone number..." << endl;
                cout<<RED<<"\t------------------------------------------------------------------"<<RESET<<endl;
            }
        }

        bool validEmail = false;
        while (!validEmail) {
            cout<<RED<<"\t------------------"<<RESET<<endl;
            cout <<GREEN<< "\t   Enter Email : "<<endl;
            cout<<RED<<"\t------------------"<<RESET<<endl;
            cin >> Email;
            transform(Email.begin(), Email.end(), Email.begin(), ::tolower); 

            regex emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
            if (regex_match(Email, emailRegex)) {
                ifstream file("Store.txt");
                vector<string> existingContacts;
                string line;
                bool emailExists = false;

                while (getline(file, line)) {
                    size_t pos2 = line.find("  ", line.find("  ") + 2); 

                    string storedEmail = line.substr(pos2 + 2);

                    if (storedEmail == Email) {
                        cout<<RED<<"\t-----------------------------------------------------------------"<<RESET<<endl;
                        cout <<BLUE<<"\t Email already exists. Please enter a different email address.." << endl;
                        cout<<RED<<"\t-----------------------------------------------------------------"<<RESET<<endl;
                        emailExists = true;
                        break;
                    }

                }
                file.close();
            

                if (!emailExists) {
                    validEmail = true;
                }
            } else {
                cout<<RED<<"\t---------------------------------------------------------------"<<RESET<<endl;
                cout <<BLUE<<"\t  Invalid email address. Please enter a valid email address.." << endl;
                cout<<RED<<"\t---------------------------------------------------------------"<<RESET<<endl;
            }
        }


        ofstream file("Store.txt", ios::app);
        file << Name << "  " << phonenumber << "  " << Email << endl;
        file.close();
        cout<<RED<<"\t---------------------------------"<<RESET<<endl;
        cout <<BLUE<< "\t   Contact Successfully Added !" << endl;
        cout<<RED<<"\t---------------------------------"<<RESET<<endl;
    }

        void editContact() {
        string oldName;
        cout<<RED<<"\t-----------------------------------"<<endl;
        cout <<GREEN "\t  Enter Name , Number for Edit : "<<endl;
        cout<<RED<<"\t-----------------------------------"<<RESET<<endl;
        cin >> oldName;
        transform(oldName.begin(), oldName.end(), oldName.begin(), ::tolower); 

        ifstream file("Store.txt");
        vector<string> existingContacts;
        string line;
        bool contactFound = false;

        while (getline(file, line)) {
            size_t pos1 = line.find("  ");
            string storedName = line.substr(0, pos1);

            if (storedName == oldName) {
                contactFound = true;
                cout<<RED<<"\t-----------------"<<endl;
                cout << GREEN<<"\t Contact Found :     "<<RESET << line << endl;
                cout<<RED<<"\t-----------------"<<RESET<<endl;

                cout<<RED<<"\t---------------------"<<endl;
                cout <<GREEN<< "\t  Enter new Name : "<<endl;
                cout<<RED<<"\t---------------------"<<RESET<<endl;
                cin >> Name;
                cout<<RED<<"\t-------------------------------------------"<<endl;
                cout <<GREEN<< "\t  Enter new Phone number (10 digits) : "<<endl;
                cout<<RED<<"\t-------------------------------------------"<<RESET<<endl;
                cin >> phonenumber;
                cout<<RED<<"\t-------------------------"<<endl;
                cout <<GREEN<< "\t  Enter new Email : "<<endl;
                cout<<RED<<"\t-------------------------"<<RESET<<endl;
                cin >> Email;

                line = Name + "  " + phonenumber + "  " + Email;
            }
            existingContacts.push_back(line); 
        }
        file.close();

        if (!contactFound) {
            cout<<RED<<"\t------------------------"<<endl;
            cout <<BLUE<< "\tContact Not Found!" << endl;
            cout<<RED<<"\t------------------------"<<RESET<<endl;
            return;
        }

        ofstream outFile("Store.txt");
        for (const auto& contact : existingContacts) {
            outFile << contact << endl;
        }
        outFile.close();
        cout<<RED<<"\t--------------------------------"<<endl;
        cout <<BLUE<< "\t  Contact Successfully Updated!" << endl;
        cout<<RED<<"\t--------------------------------"<<RESET<<endl;
    }

    void displayContacts() {
        ifstream file("Store.txt");
        string line;
        cout<<RED << "Phonebook : "<<RESET << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
        cout<<GREEN<<"\n\tDisplay Successfully !"<<RESET<<endl;
    }

    void searchContact() {
        string searchName;
        cout<<RED<<"\t-------------------------"<<endl;
        cout<<GREEN << "\t| Enter name to search: |"<<endl;
        cout<<RED<<"\t-------------------------"<<RESET<<endl;
        cin.ignore();
        getline(cin,searchName);

        ifstream file("Store.txt");
        string line;
        bool found = false;
        int sn = 1;
        while (getline(file, line)) {
            size_t foundPos = line.find(searchName);
            if (foundPos != string::npos) {
                cout<<BLUE<<"----------------------"<<endl;
                cout<<GREEN << "| Contact found: | " <<sn<<" :"<< line << endl;
                cout<<BLUE<<"----------------------"<<RESET<<endl;
                found = true;
                sn++;
            }
        }
        if (!found) {
            cout<<RED << "\tContact not found !!!...."<<RESET << endl;
        }
        file.close();
    }

    void deleteContact() {
        string deleteName;
        cout<<RED<<"\t-------------------------"<<endl;
        cout <<GREEN<< "\t| Enter name to delete: |"<<endl;
        cout<<RED<<"\t-------------------------"<<RESET<<endl;
        cin.ignore();
        getline(cin,deleteName);

        ifstream file("Store.txt");
        ofstream temp("tempexe.txt");
        string line;
        bool found = false;
        while (getline(file, line)) {
            size_t foundPos = line.find(deleteName);
            if (foundPos == string::npos) {
                temp << line << endl;
            } else {
                found = true;
            }
        }
        file.close();
        temp.close();
        remove("Store.txt");
        rename("tempexe.txt", "Store.txt");
        if (found) {
            cout <<GREEN<< "\tContact Deleted Successfully!" << endl;
        } else {
            cout <<RED<< "\tContact Not Found !"<<RESET << endl;
        }
    }
};

void userManual(){
    cout << MAGENTA<<"--------------------------------------------------------------------------------\n";
    cout <<YELLOW<<BOLD<< "|\t\t\t\t   User Manual\t\t                       |\n";
        cout << "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t\t\t !! Read Carefully All Statement !!\t               |\n"<<RESET;
        cout<<BLUE<<BOLD << "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t\t\t !! How to use this application.!!\t               |\n";
    cout << "|\t\t\t !! How is this beneficial ?\t!!\t               |\n";
    cout << "|\t\t\t !! There are some steps here   !!\t               |\n";
    cout << "|\t\t\t !! which are very important.\t!!\t               |\n";
    cout << "|\t\t\t !! Read carefully\t\t!!\t               |\n"<<RESET;
        cout <<RED<< "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t step 1. You can Add Name , Phone number , Email of any people \t       |\n";
    cout << "|\t\t BY using (1) number key from your key board.\t               |\n"<<RESET;
        cout <<GREEN<< "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t step 2. You can see All the contact That are you save \t               |\n";
    cout << "|\t\t in this Application . It is done By easily in this  \t       |\n";
    cout << "|\t\t Application By using (2) number key from num pad.\t       |\n"<<RESET;
        cout <<RED<< "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t step 3. Ther is interesting Section Where you search any\t       |\n";
    cout << "|\t\t contact using Name , phone number  that you save in \t       |\n";
    cout << "|\t\t our application It is  done by using (3) number key.\t       |\n"<<RESET;
        cout <<GREEN<< "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t step 4. You can Also delete  a contact that is wrong or you \t       |\n";
    cout << "|\t\t dont talk to this person . by using  (4) number key.\t       |\n"<<RESET;
        cout <<RED<< "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t step 5. You can also update any contact that you want to\t       |\n";
    cout << "|\t\t change  Name , phone number , Email , by using  (5) number key|\n"<<RESET;
        cout <<GREEN<< "|\t\t\t\t\t\t\t\t\t       | \n";
    cout << "|\t step 6. And Finally You want to exit from our aplication,\t       |\n";
    cout << "|\t\t  you can do it by using (6) number key.\t               |\n"<<RESET;
        cout << "|\t\t\t\t\t\t\t\t\t       | \n";
        cout << "|\t\t\t\t\t\t\t\t\t       | \n";
    cout <<YELLOW<<BOLD<< "| This Application is Very  useful for you because you can save\t               |\n";
    cout << "| Any contact  that you want to save in this application .\t               |\n";
    cout << "| !! Thanks For Reading This User Manual . !!\t                               |\n"<<RESET;
    cout << MAGENTA<<"--------------------------------------------------------------------------------\n"<<RESET;
}


void help(){
    cout<<MAGENTA<<"--------------------------------------------------------------"<<endl;
    cout<<GREEN<<BOLD<<"|\t\t        !!!  HELP  !!! \t\t\t     |"<<endl;
    cout<<"|                                                            |"<<endl;
    cout<<"|\t Hii , I am Mohan Pandit !\t\t   \t     |"<<endl;
    cout<<"|\t I am here to help you .\t\t   \t     |"<<endl;
    cout<<"|\t You can ask any question To My developer Team.\t     |"<<endl;
    cout<<"|\t You can also Contact with my Team On :\t\t     |"<<RESET<<endl;
    cout<<"|                                                            |"<<endl;
    cout<<RED<<BOLD<<"|\t  MObile num  : +91 9999999999\t\t\t     |"<<endl;
    cout<<"|                                                            |"<<endl;
    cout<<"|\t  Email : mohanpandit@gmail.com\t\t\t     |"<<endl;
    cout<<"|                                                            |"<<endl;
    cout<<"|\t  Linkedin : https://www.linkedin.com/in/mohanpandit |"<<endl;
    cout<<"|                                                            |"<<endl;
    cout<<"|\t  Github : https://www.github.com/mohanpandit\t     |"<<endl;
    cout<<"|                                                            |"<<endl;
    cout<<"|\t  Youtube : https://www.youtube.com/ourn2gworld\t     |"<<endl;
    cout<<"|                                                            |"<<RESET<<endl;
    cout<<MAGENTA<<"--------------------------------------------------------------"<<RESET<<endl;
}

void phonebookMenu(Phonebook& phonebook) {
    int choose;
    while (true) {
        cout<<CYAN<<"\n------------------------------------------"<<endl;
        cout <<YELLOW<<BOLD<< "|\t  ==>>  Phonebook Menu  <<==     |"<<RESET << endl;
        cout<<RED<<"| \t\t\t\t\t |"<<endl;
        cout <<RED<<BOLD<< "|\t\t1. Add Contact   \t |" << endl;
        cout <<BLUE<<BOLD<< "|\t\t2. Display Contacts  \t |" << endl;
        cout <<GREEN<<BOLD<< "|\t\t3. Search Contact  \t |" << endl;
        cout <<RED<<BOLD<< "|\t\t4. Delete Contact  \t |" << endl;
        cout <<BLUE<<BOLD<< "|\t\t5. Edit contact \t |"<<endl;
        cout <<GREEN<<BOLD<< "|\t\t6. Exit \t         |"<<RESET << endl;
        cout<<CYAN<<"------------------------------------------"<<RESET<<endl;
        
        cout<<RED<<"\t----------------------"<<endl;
        cout <<GREEN<< "\t| Enter your choice: |"<<endl;
        cout<<RED<<"\t----------------------"<<RESET<<endl;
        cin >> choose;

        switch (choose) {
            case 1:
                phonebook.addContact();
                break;
            case 2:
                phonebook.displayContacts();
                break;
            case 3:
                phonebook.searchContact();
                break;
            case 4:
                phonebook.deleteContact();
                break;
            case 5:
                phonebook.editContact();
                break;
            case 6:
                return; 
            default:
                cout <<RED<<BOLD<< "Invalid choice. Please try again...."<<RESET << endl;
        }
    }
}

int main() {
    int choice;

    cout <<YELLOW << BOLD << "\t\t\t\t\t\t\tWELCOME\t\t\n";
    cout << "\t\t\t\t\t\t\t   TO\t\t\n";
    cout << "\t\t\t\t\t\t PHONEBOOK APPLICATION\t\t\n\n\n"<<RESET;

    cout << GREEN << "\t\t\t\t\t    ..... Press Enter to continue ....." << endl;
    cout << "\t\t\t\t\t           => Program On Hold <=       " << RESET << endl;
    cin.get();
    cout<< RED<<"\n\t============================================================="<<endl;
        cout << BLUE << " \t || Congratulations - Enjoy And Share Your Experinces ||" << endl;
        cout << RED <<"\t=============================================================\n"<<endl;
        cout << YELLOW << "\tAre You New User: " << endl;
        cout << "\t\t\t 1. YES (Include User Manual)\t\t\n";
        cout << "\t\t\t 2. NO (Only for Experinced Person)\t\t\n\n";
        cout << RED <<"\t============================================================="<<RESET<<endl;

        cout<< RED <<"\n\t====================================="<<endl;
        cout<< GREEN << "\t    Please Select One To Continue: "<<endl;
        cout<< RED <<"\t=====================================" << RESET <<endl;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Phonebook phonebook;
        int choice1;

        switch (choice) {
            case 1:
            while(true){
                cout<<BOLD<<YELLOW<<"\n\t\t\t   @@@  WARNING  @@@"<<endl;
                cout <<RED<< "\t\t==> Read First User Manual Then Continue <=="<<RESET << endl;
                userManual();
                cout<<GREEN << "\n\t.....Press Enter to continue....."<<RESET << endl;
                cin.get();
                cout<<RED<<"********************************************************************"<<endl;
                cout <<YELLOW<<BOLD << "\t\t    Thanks, for Reading Manual," << endl;
                cout<<"\t    And finally You know How to use Phonebook."<<RESET<<endl;

                cout<<YELLOW<<BOLD<<"\n\t    Thats Are Application Menu or Interfaces  "<<endl;
                cout<<BLUE<<"\n\t-----------------------------------------------------"<<endl;
                cout <<BOLD<<YELLOW<< "\t| 1. Admin   !!     2. User Manual  !!    3. Help   |" << endl;
                cout<<BLUE<<"\t-----------------------------------------------------\n"<<RESET<<endl; 
                cout<<RED<<"********************************************************************"<<RESET<<endl;

                cout<<RED<<"\n\t-----------------------------------------------"<<endl;
                cout <<GREEN<< "\t| Choose Any One (1.Admin is phonebook menu): |"<<endl;
                cout<<RED<<"\t-----------------------------------------------"<<RESET<<endl;
                cin >> choice1;
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice1) {
                    case 1:
                        cout<<RED<<"\n\t====================================="<<RESET<<endl;
                        cout <<YELLOW << BOLD<< "\t    You entered in Admin program"<<RESET << endl;
                        cout<<RED<<"\t====================================="<<RESET<<endl;
                        phonebookMenu(phonebook);
                        break;
                    case 2:
                        cout<<RED<<"\n\t========================================"<<RESET<<endl;
                        cout << YELLOW << BOLD << "\t   You are in the User Manual section"<<RESET << endl;
                        cout<<RED<<"\t========================================"<<RESET<<endl;
                        userManual();
                        break;
                    case 3:
                        cout<<RED<<"\n\t====================================="<<RESET<<endl;
                        cout<<YELLOW << BOLD << "\t    You are in the Help section"<<RESET << endl;
                        cout<<RED<< "\t====================================="<<RESET<<endl;
                        help();
                        break;
                    default:
                        cout <<RED<<BOLD<< "...!!!  Invalid choice  !!!..."<<RESET << endl;
                }
            }
                break;

            case 2:
            while(true){
                cout<<BLUE<<"\n----------------------------------------------------------"<<RESET<<endl;
                cout<<YELLOW<<BOLD<<"\tThese are Application Menu or Interfaces  "<<endl;
                cout << "\n\t1. Admin \t2. User Manual \t3. Help "<<RESET << endl;
                cout<<BLUE<<"----------------------------------------------------------"<<RESET<<endl;

                cout<<RED<<"\n\t-------------------------------------------"<<RESET<<endl;
                cout <<GREEN<< "\tChoose Any One (1.Admin is phonebook menu): "<<RESET<<endl;
                cout<<RED<<"\t-------------------------------------------"<<RESET<<endl;
                cin >> choice1;
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (choice1) {
                    case 1:
                        cout<<RED<<"\n\t====================================="<<RESET<<endl;
                        cout <<YELLOW << BOLD << "\t    You entered in Admin program"<< RESET << endl;
                        cout<<RED<<"\t====================================="<<RESET<<endl;
                        phonebookMenu(phonebook);
                        break;
                    case 2:
                        cout<<RED<<"\n\t========================================"<<RESET<<endl;
                        cout << YELLOW << BOLD << "\t   You are in the User Manual section"<<RESET << endl;
                        cout<<RED<<"\t========================================"<<RESET<<endl;
                        userManual();
                        break;
                    case 3:
                        cout<<RED<<"\n\t====================================="<<RESET<<endl;
                        cout << YELLOW << BOLD<< "\t    You are in the Help section"<<RESET << endl;
                        cout<<RED<<"\t====================================="<<RESET<<endl;
                        help();
                        break;
                    default:
                        cout<<RED<<BOLD << "...!!!  Invalid choice  !!!..." <<RESET<< endl;
                }
            }
                break;
        
            default:
                cout<<RED<<BOLD << "...!!!  Invalid choice  !!!..." <<RESET<< endl;
        }
    
    return 0;
}
