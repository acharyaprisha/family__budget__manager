#include "Menu.h"

#include<iostream>

using namespace std;

/**
 * @brief Displays the main menu and retrieves
 * the user's selection.
 *
 * Shows the available application options and
 * returns the selected menu choice.
 */
int Menu::showMainMenu()
{
    int choice;

    cout<<"FAMILY BUDGET MANAGER"<<endl;
    cout<<"\n";
    cout<<"1. Create Account"<<endl;
    cout<<"2. Login Account"<< endl;
    cout<<"3. Exit"<<endl;
    cout<<"\n";
    
    cout<<"Enter your choice:"<<endl;
    cin>>choice; 

    return choice;
}

/**
 * @brief Displays available member operations.
 *
 * Prints the list of actions that a logged-in
 * member can perform.
 */
void Menu:: showMemberMenu()
{
    cout<<"\n";
    cout<< "1. View Account Details" << endl;
    cout<< "2. View Transaction History" << endl;
    cout<< "3. Top Up Wallet" << endl;
    cout<< "4. Transfer Money" << endl;
    cout<< "5. If you are admin access other accounts" << endl;
    cout<< "6. Filter Transactions"<< endl;
    cout<< "7. Exit"<< endl;
    cout<<"\n";

}

/**
 * @brief Display the menu available after a user logs in.
 *
 * Shows the list of operations that can be
 * performed by a logged-in user, including
 * viewing account details, managing wallet
 * transactions, filtering transaction history,
 * accessing default screen settings, and exiting
 * the session.
 */
void Menu:: showLoginMenu()
{
    cout<<"\n";
    cout<< "1. View Account Details" << endl;
    cout<< "2. View Transaction History" << endl;
    cout<< "3. Top Up Wallet" << endl;
    cout<< "4. Transfer Money" << endl;
    cout<< "5. If you are admin access other accounts" << endl;
    cout<< "6. Filter Transactions"<< endl;
    cout<< "7. Change Default Screen"<< endl;
    cout<< "8. Open Default Screen"<< endl;
    cout<< "9. Exit"<< endl;
    cout<<"\n";
}

/**
 * @brief Displays the default screen configuration menu.
 *
 * Prompts the user to select the screen that
 * should automatically open after login.
 *
 * @return Selected default screen identifier.
 */
char Menu:: showDefaultScreenMenu()
{
    char screen;

    cout<<"Enter your choice to set default screen:"<<endl;
    cout<<"\n";
    cout<<"a. View Account Details"<<endl;
    cout<<"b. View Transaction History"<<endl;
    cout<<"c. Top Up wallet Screen"<<endl;
    cout<<"d. Money Transfer Screen"<<endl;
    cout<<"e. Admin Access Screen"<<endl;
    cout<<"f. Filter Tranasction History Screen"<<endl;
    cout<<"\n";

    cin>>screen;
    
    return screen;
}
