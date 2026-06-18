#include "Member.h"
#include "../REPOSITORIES/FileManager.h"
#include "../SERVICES/FilterSystem.h"
#include "../SERVICES/Transaction.h"
#include "../SERVICES/InputService.h"
#include "../VIEWS/Menu.h"

#include<iostream>

using namespace std;

FileManager fm;
FilterSystem fs;

/**
 * @brief Constructs a member object.
 *
 * Initializes member information and creates
 * an associated wallet object.
 *
 * @param n Member name.
 * @param a Member age.
 * @param ad Administrative status.
 * @param accno Account number.
 * @param bal Initial wallet balance.
 */
Member::Member(string n,int a,bool ad, string accno,double bal)
{
    name = n;
    age = a;
    admin = ad;

    w = new Wallet(accno,bal);
}

enum DefaultScreen
{
    VIEW_ACCOUNT = 'a',
    VIEW_TRANSACTION_HISTORY = 'b',
    TOP_UP_WALLET = 'c',
    MONEY_TRANSFER = 'd',
    ADMIN_ACCESS = 'e',
    FILTER_TRANSACTION_HISTORY = 'f'
};

/**
 * @brief Displays account information.
 *
 * Prints the member's name, age, administrative
 * status, account number, and wallet balance.
 */
void Member::ViewAccount()
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Admin: " << admin << endl;
    cout << "Account Number: "<< w->accountNumber<< endl;
    cout << "Balance: "<< w->getbalance()<< endl;
}

/**
 * @brief Displays transaction history.
 *
 * Retrieves and displays all transactions
 * associated with the member's account.
 */
void Member::ViewTransactionHistory()
{
    fm.read_file( w->accountNumber);
}

/**
 * @brief Performs a wallet top-up operation.
 *
 * Prompts the user for an amount and updates
 * the wallet balance through a transaction.
 */
void Member::TopUp()
{
    double amount;
    cout << "Enter amount to top up: "<<endl;
   
    //Handles invalid input.
    while(true)
    {
        cin >> amount;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>:: max(), '\n');
            cout<<"Enter a valid amount."<<endl;
        }

        else if(amount<=0)
        {
            cout<<"Amount must be greater than 0"<<endl;
        }

        else
        {
            break;
        }
    }

    Transaction t("", "", 0);
    t.topup(*this,amount);
}

/**
 * @brief Transfers funds to another account.
 *
 * Collects receiver account information,
 * validates the account, and performs
 * the money transfer transaction.
 */
void Member::TransferMoney()
{
    string receiverAccNo;
    double transferAmount;

    cout << "Enter receiver account number: "<<endl;
    cin >> receiverAccNo;

    cout << "Enter transfer amount: "<<endl;

    //Handles invalid inputs.
    while(true)
    {
       cin >> transferAmount;
       if(cin.fail())
       {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>:: max(), '\n');
        cout<<"Enter valid transfer amount: "<<endl;
       }

       else if(transferAmount<=0)
       {
        cout<<"Transfer amount must be more than 0."<<endl;
       }

       else
       {
        break;
       }

    }

    // Retrieve receiver balance from file.
    double receiverBalance = fm.getBalance(receiverAccNo);

    // Check whether receiver account exists.
    if(receiverBalance == -1)
    {
        cout << "Receiver account not found."<< endl;
        return;
    }

    // Create temporary receiver object.
    Member receiver("",0,false,receiverAccNo, receiverBalance);

    // Perform money transfer.
    Transaction t("", "", 0);

    t.money_transfer(*this,receiver, transferAmount);
}

/**
 * @brief Provides administrative account access.
 *
 * Allows administrators to view information
 * belonging to another account. Access is
 * denied for non-administrative users.
 */
void Member::AdminAccess()
{
    if(admin)
    {
    string targetAcc;
    cout << "Enter the account number you want to access: "<<endl;
    cin >> targetAcc;
    fm.viewAccount(*this, targetAcc);
    }

    else
    {
    cout << "Access denied. You are not an admin." << endl;
    }
}

/**
 * @brief Filters transaction history by amount and date.
 *
 * Prompts the user for an amount and date and then displays
 * matching transactions from the transaction log.
 */
void Member::FilterTransactions()
{
    double minamount;
    double maxamount;

    string startDate;
    string endDate;

    // Obtain minimum amount.
    while(true)
    {
        cout << "Enter minimum amount: ";
        cin >> minamount;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a valid amount." << endl;
        }

        else if(minamount < 0)
        {
            cout << "Amount cannot be negative." << endl;
        }

        else
        {
            break;
        }
    }

    // Obtain maximum amount.
    while(true)
    {
        cout << "Enter maximum amount: ";
        cin >> maxamount;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a valid amount." << endl;
        }

        else if(maxamount < minamount)
        {
            cout << "Maximum amount must be greater than or equal to minimum amount."<< endl;
        }

        else
        {
            break;
        }
    }

    // Obtain start date.
    cout << "Enter start date (DD-MM-YYYY): ";
    cin >> startDate;

    // Obtain end date.
    cout << "Enter end date (DD-MM-YYYY): ";
    cin >> endDate;

    fs.FilterByAmountDate(w->accountNumber,minamount,maxamount,startDate,endDate);
}

/**
 * @brief Executes the operation associated with
 * a default screen selection.
 *
 * Routes the member to the requested screen by
 * invoking the corresponding member operation.
 *
 * @param screen Character identifying the screen
 * to open.
 */
void Member::OpenScreen(char screen)
{
    switch(screen)
    {
        case VIEW_ACCOUNT:
            ViewAccount();
            break;

        case VIEW_TRANSACTION_HISTORY:
            ViewTransactionHistory();
            break;

        case TOP_UP_WALLET:
            TopUp();
            break;

        case MONEY_TRANSFER:
            TransferMoney();
            break;

        case ADMIN_ACCESS:
            AdminAccess();
            break;

        case FILTER_TRANSACTION_HISTORY:
            FilterTransactions();
            break;
    }
}

void Member:: changeDefaultScreen()
{
   char choice, screen;

    cout<<"Change Default Screen (Y/N): "<<endl;
    cin>> choice;

    if(choice=='Y' || choice=='y')
    {
        Menu menu;
        screen= menu.showDefaultScreenMenu();
        
        if(screen>='a' && screen<='f')
        {
           fm.StoreDefaultScreen(w->accountNumber, screen);
           cout<<"Default screen saved successfully"<<endl;
        }

        else
        {
           cout<<"Invalid screen selection"<<endl;
        }
    }
}

/**
 * @brief Opens or configures the default screen.
 *
 * Loads the member's preferred screen from storage.
 * If a valid default screen exists, it is opened
 * automatically. Otherwise, the user is prompted
 * to select and save a default screen preference.
 *
 * @param accno Account number associated with the member.
 */
 void Member::configure_default_screen(string accno)
 {
    char screen= fm.ReadDefaultScreen(accno);

    if(screen>='a' && screen<='f')
    {
        cout<<"Your Default Screen is opened!"<<endl;
        OpenScreen(screen);
    }

    else
    {
        Menu menu;
        char screen= menu.showDefaultScreenMenu();
        
        if(screen>='a' && screen<='f')
        {
           fm.StoreDefaultScreen(accno, screen);
           cout<<"Default screen saved successfully"<<endl;
           OpenScreen(screen);
        }

        else
        {
           cout<<"Invalid screen selection"<<endl;
        }
      
    }
 }

/*
 * Release dynamically allocated resources
 * owned by the member.
 */
Member::~Member()
{
    delete w;
}