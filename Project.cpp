#include<iostream>
#include "MODELS/Member.h"
#include "MODELS/Wallet.h"
#include "MODELS/Admin.h"
#include "REPOSITORIES/FileManager.h"
#include "SERVICES/Transaction.h"

using namespace std;

/**
 * @brief Represents the available menu options
 * in the Family Budget Manager application.
 *
 * Provides meaningful names for menu choices
 * used in the application's switch statement.
 */
enum MenuOption{             
    VIEW_ACCOUNT = 1,               
    VIEW_TRANSACTION_HISTORY,  
    TOP_UP,                  
    TRANSFER_MONEY,           
    ADMIN_ACCESS,             
    EXIT                     
};

enum SignIn{
    CREATE_ACCOUNT=0,
    LOGIN_ACCOUNT
};

int main()
{
    // declaration of variables to store the user input for creating a member and performing transactions
    string name, pin;
    int age, choice1,choice2;
    bool isAdmin=false;
    string accno;
    double balance;

    // Create a FileManager object to handle account,
   // authentication, transaction, and file operations.
    FileManager fm;

    // Create either a regular member or an administrator
    Member* mem;

    cout << "Create a new account (enter 0)"<< endl;
    cout << "Login if account already exists (enter 1)"<<endl;
    cin>>choice1;

    switch(choice1){
        
        case CREATE_ACCOUNT:
            
            // Collect account registration details from the user.
            cout << "Enter your first name: ";
            cin >> name;

            cout << "Enter age: ";
            cin >> age;

            cout << "Enter pin you want to set for your account: ";
            cin >> pin;
    
            cout << "Enter account number: ";
            cin >> accno;

            cout << "Enter balance: ";
            cin >> balance;

            cout << "Enter admin status (1/0): "<<endl;
            cin >> isAdmin;

            // account based on the user's selected role.
            // Demonstrates inheritance through the Admin class.
           if(isAdmin){ mem = new Admin(name, age, accno, balance);}
           else{ mem = new Member(name, age, false, accno, balance);}
 
            fm.create_file(*mem, pin);

            break;

        case LOGIN_ACCOUNT:
          
            cout << "Enter account number: ";
            cin >> accno;

            if(!fm.authenticate(accno))
            {
            cout << "Login Failed" << endl;
            return 0;
            }

            fm.readAccountDetails(name,age,isAdmin,accno,balance);

            if(isAdmin){ mem = new Admin(name, age, accno, balance);}
   
            else { mem = new Member(name,age,false,accno,balance);}

            break;

        default:
            cout <<"Invalid input"<< endl;
    }
 

   // Display available operations that can be
   // performed within the application.
    cout<<"\n";
    cout<< "1. View Account Details" << endl;
    cout<< "2. View Transaction History" << endl;
    cout<< "3. Top Up Wallet" << endl;
    cout<< "4. Transfer Money" << endl;
    cout<< "5. If you are admin access other accounts" << endl;
    cout<< "6. Exit" << endl;
    cout<<"\n";

    // Continue processing user requests until the Exit option is selected.
    do{
    cout << "Enter your choice: ";
    cin >> choice2;

    switch(choice2){

        case VIEW_ACCOUNT:
            // Authenticate the user before displaying account information.
                if(fm.authenticate(accno)){
                cout << "Name: " << name << endl;
                cout << "Age: " << age << endl;
                cout << "Admin: " << isAdmin << endl;
                cout << "Account Number: " << accno << endl;
                cout << "Balance: " << mem->w->getbalance() << endl;
            }
            break;
        

        case VIEW_TRANSACTION_HISTORY:
            // display transaction history associate dwith current account.
            fm.read_file(accno);
            break;

        case TOP_UP:
            // Authenticate the user and perform a wallet top up transaction.
            if(fm.authenticate(accno)){
             double amount;
             cout << "Enter amount to top up: ";
             cin >> amount;

             //create a transaction object and process requested topup. 
             Transaction t("", "", 0);
             t.topup(*mem, amount);
            }
            break;


        case TRANSFER_MONEY:

        // Authenticate the user and initiate a money transfer transaction.
        if(fm.authenticate(accno)){
        string receiverAccNo;
        double transferAmount;

        //get the user input for receiver account number and transfer amount for money transfer transaction
        cout << "Enter receiver account number: ";
        cin >> receiverAccNo;

        cout << "Enter transfer amount: ";
        cin >> transferAmount;
        
        // Retrieve the receiver's current balance from the account file.
        double receiverBalance = fm.getBalance(receiverAccNo);

        //if the receiver account number does not exist in the file then display an error message and break the loop
        if(receiverBalance == -1){
            cout << "Receiver account not found"<< endl;
            break;
        }

        // Create a temporary receiver object using the retrieved account information.
        Member receiver("",0,false,receiverAccNo,receiverBalance);

        // Process the money transfer between the sender and receiver accounts.
        Transaction t("", "", 0);
        t.money_transfer(*mem,receiver,transferAmount);
       }   
       break;

        case ADMIN_ACCESS:
            // Allow administrators to access account information belonging to other users.
            if(isAdmin){
                if(fm.authenticate(accno)) {
                string targetAcc;
                cout << "Enter the account number you want to access: ";
                cin >> targetAcc;
                fm.viewAccount(*mem, targetAcc);
            }
          }
          //denying access to member to check other members file
            else{
                cout << "Access denied. You are not an admin." << endl;
            }
            break;

         case EXIT:
         //exiting the loop
            cout << "Exiting" << endl;
            break;

        default:
            cout << "Invalid choice entered" << endl;
    }

//condition for loop to exit
} while(choice2!= EXIT);

// Release dynamically allocated memory
// before terminating the application.
    delete mem;
    return 0;
}
