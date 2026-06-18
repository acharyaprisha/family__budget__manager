#include<iostream>
#include "VIEWS/Menu.h"
#include "MODELS/Member.h"
#include "MODELS/Wallet.h"
#include "MODELS/Admin.h"
#include "REPOSITORIES/FileManager.h"
#include "SERVICES/Transaction.h"
#include "SERVICES/InputService.h"
#include "SERVICES/FilterSystem.h"

#include <limits>
#include<iostream>

using namespace std;

/**
 * @brief Opens the member operations menu.
 *
 * Displays the available member operations and
 * executes the selected operation until the user chooses to exit the menu.
 *
 * @param member Logged-in member object used to
 * perform account operations.
 */

void OpenMemberMenu(Member& member)
{
    bool running = true;

    while(running)
    {
        Menu menu;
        menu.showLoginMenu();

        int choice;
        cout << "Enter your choice: "<<endl;
        cin >> choice;

        cin >> choice;

        //Handles invalid inputs.
        if(cin.fail())
        {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid number." << endl;
        continue;
        }

        // Execute the selected member operation.
        switch(choice)
        {
            case 1:
                member.ViewAccount();
                break;

            case 2:
                member.ViewTransactionHistory();
                break;

            case 3:
                member.TopUp();
                break;

            case 4:
                member.TransferMoney();
                break;

            case 5:
                member.AdminAccess();
                break;

            case 6:
                member.FilterTransactions();
                break;

            case 7:
            // Exit the member menu loop.
                running = false;
                break;

            default:
                cout << "Invalid choice." << endl;
        }
        cout << endl;
    }
}

/**
 * @brief Handles the account creation workflow.
 *
 * Collects user information, creates either a
 * member or admin account, and stores the
 * account data in the corresponding files.
 */
void CreateAccountFlow()
{
    string name;
    string pin;
    string accno;

    int age;
    bool isAdmin;

    double balance;

    FileManager fm;
    InputService ip;

    // Collect account information from the user.
    cout << "Enter your first name: "<<endl;
    cin >> name;

    //Handles invalid input.
   while(true)
    {
        cout<< "Enter your age: "<<endl;
        cin>>age;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid age entered, please enter a number"<<endl;
        }

        //Set age limit.
        else if(age<18 || age>120)
        {
            cout<<"Age must be between 18 to 120"<<endl;
        }
        else
        {
            break;
        }
    }

    cout << "Enter pin you want to set for your account: "<<endl;
    pin = ip.inputPin();
    cout<<endl;

    cout << "Enter account number: "<<endl;
    cin >> accno;

 //Handles invalid balance input.
  while(true)
    {
        cout<< "Enter balance of your account: "<<endl;
        cin>>balance;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid balance entered"<<endl;
        }
        else
        {
            break;
        }
    }

    //Make sures that the status is no other number other 0 or 1.
  while(true)
    {
        cout<< "Enter Admin Status: "<<endl;
        cin>>isAdmin;

       if(isAdmin == 0 || isAdmin == 1)
       {
       break;
       }

       else
       {
       cout << "Please enter 0 or 1" << endl;
       }
    }

    Member* mem;

    // Create either a Member or Admin object depending on the selected account type.
    if(isAdmin)
    {
        mem = new Admin(name,age,accno,balance);
    }
    else
    {
        mem = new Member(name,age,false,accno,balance);
    }

    // Persist account information to files.
    fm.create_file(*mem, pin);

    cout << "Account created successfully!" << endl;
    char choice;

    cout << "Perform Operations (Y/N): "<<endl;
    cin >> choice;

    if(choice == 'Y' || choice == 'y')
    {
    OpenMemberMenu(*mem);
    }
}

/**
 * @brief Handles the login workflow.
 *
 * Authenticates the user, loads account details,
 * creates a member object, opens the configured
 * default screen, and optionally displays the
 * full member menu.
 */
void LoginFlow()
{
    FileManager fm;
    string accno;
    Menu menu;

    cout << "Enter Account Number: ";
    cin >> accno;

    // Authenticate the account before loading data
    if(!fm.authenticate(accno))
    {
        return;
    }

    string name;
    int age;
    bool isAdmin;
    double balance;

    // Load account information from storage.
    fm.readAccountDetails(name,age,isAdmin,accno,balance);

    Member member(name,age,isAdmin,accno,balance);

    // Open the user's configured default screen.
    member.configure_default_screen(accno);

    char choice;

    // Allow the user to access additional operations.
    cout << "Would you like to view the full menu? (Y/N): "<<endl;
    cin >> choice;

    if(choice == 'Y' || choice == 'y')
    {
       // Display available member operations.
       bool running = true;

    while(running)
    {
        menu.showLoginMenu();

        int choice;

        cout << "Enter your choice: "<<endl;
        cin >> choice;

        //Handles invalid input.
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input, enter a number." << endl;
            continue;
        }

        // Execute the selected member operation.
        switch(choice)
        {
            case 1:
                member.ViewAccount();
                break;

            case 2:
                member.ViewTransactionHistory();
                break;

            case 3:
                member.TopUp();
                break;

            case 4:
                member.TransferMoney();
                break;

            case 5:
                member.AdminAccess();
                break;

            case 6:
                member.FilterTransactions();
                break;

            case 7:
                member.changeDefaultScreen();
                break;

            case 8:
                member.configure_default_screen(accno);
                break;

            case 9:
            // Exit the member menu loop.
                running = false;
                break;

            default:
                cout << "Invalid choice." << endl;
        }
        cout << endl;
    }
}
}
        
 

/**
 * @brief Entry point of the Family Budget Manager.
 *
 * Displays the main menu and routes the user to
 * account creation, login, or application exit
 * based on the selected option.
 *
 * @return 0 on successful program termination.
 */
int main()
{
    Menu menu;
    
    // Handles wrong input cases.
    bool running = true;

    while(running)
    {
        int choice = menu.showMainMenu();

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input, enter a number." << endl;
            continue;
        }
    

    switch(choice)
    {
        case 1:
        //create account.
        CreateAccountFlow();
        break;

        case 2:
        //login.
        LoginFlow();
        break;

        case 3:
        // exit.
        running = false;
        cout<<"Thankyou for using Family Budget Manager"<<endl;
        break;

        default:
        cout<<"Invalid choice entered "<<endl;
        break;
    }
  }
}

