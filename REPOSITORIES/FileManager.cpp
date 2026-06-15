/**
 * @file FileManager.cpp
 * @brief Implements file management operations for the
 * Family Budget Manager application.
 */
#include "FileManager.h"
#include "../MODELS/Member.h"
#include "../MODELS/Wallet.h"

#include <iostream>
#include <fstream>
#include<filesystem>
#include <ctime>

using namespace std;
namespace fs= std:: filesystem;

// Position of the balance field within the account file.
const int index_for_balance  = 5;

char buffer[100];

/*
 * Create and initialize account and transaction
 * files for a newly registered member.
 */
void FileManager::create_file(Member &m, string pin){

    // Ensure the data folder exists.
   if(!fs::exists("DATA")){
      fs:: create_directory("DATA");
   }

    string accountFolder= "DATA/" + m.w->accountNumber;
   
   //Check whether account folder exits.
   if(fs::exists(accountFolder)){
    cout<<"Account already exists."<<endl;
    return;
   }
   
   //Create account folder.
    fs:: create_directory(accountFolder);
   
   string filename = accountFolder +"/" +  "Wallet.txt";
   string transactionFile=  accountFolder +"/"+ "Transactions.txt";

        ofstream TransactionFile(transactionFile);
        ofstream AccountFile(filename);

        if(AccountFile.is_open() && TransactionFile.is_open()) {
            // Write account information in a fixed format
            // to support future retrieval and updates.

            AccountFile << pin << endl;
            AccountFile << m.name << endl;
            AccountFile << m.age << endl;
            AccountFile << m.admin << endl;
            AccountFile << m.w->accountNumber << endl;
            AccountFile << m.w->balance << endl;

            AccountFile.close();
            TransactionFile.close();
        }

        else {
            cout << "Unable to create file"<< endl;
        }
}


/*
 * Construct the storage path for a
 * member's account information file.
 *
 * Example:
 * data/12345/Wallet.txt
 */
string FileManager :: getAccountPath(string accountNo){
    return "DATA/" + accountNo + "/Wallet.txt";
}

/*
 * Construct the storage path for a
 * member's transaction history file.
 *
 * Example:
 * data/12345/Transactions.txt
 */
string FileManager :: getTransactionPath(string accountNo){
    return "DATA/" + accountNo  + "/Transactions.txt";
}

/*
 * Validate user credentials against the
 * PIN stored in the account file.
 */
bool FileManager::authenticate(string accountNo){ 

    string filename = getAccountPath(accountNo);
    ifstream file(filename);

    // Verify that the account file exists.
    if(!file.is_open()){      
        cout << "Account not found" << endl;
        return false;
    }

    string storedPin;
    string enteredPin;

    // Read the stored PIN from the first line of the file.
    getline(file, storedPin); 

    cout << "Enter PIN: ";
    cin >> enteredPin;

    file.close();

    // Grant access only if the supplied PIN matches.
    if(storedPin == enteredPin){ 
        cout << "Authentication Successful" << endl;
        return true;
    }
    else{
        cout << "Incorrect PIN" << endl;
        return false;
    }
 }

/*
 * Check whether an account file exists.
 */
bool FileManager::search_file(string accountNo){  
        string filename = getAccountPath(accountNo);
        ifstream file(filename);

        if(file.is_open()){
            file.close();
            return true;
        }
        return false;
    }

/*
 * Verify the existence of both sender and
 * receiver account files before a transfer.
 */
bool FileManager::search_file(string sender_acc, string receiver_acc){ 
        return search_file(sender_acc) && search_file(receiver_acc);
    }

/*
 * Display the transaction history associated
 * with the specified account.
 */
void FileManager::read_file(string accountNo)
    {
        string filename = getTransactionPath(accountNo);
        ifstream file(filename);

        //check if the file exists or not
        if(!file.is_open()){ 
            cout << "File not found" << endl;
            return;
        }

        string line;

        //read the file line by line and display it on the console
        while(getline(file,line)){
            cout << line << endl;
        }

        file.close();
    }

/*
 * Load persisted account details from
 * storage and populate the supplied
 * references with member information.
 *
 * Supports reconstruction of Member
 * or Admin objects during login.
 */
void FileManager::readAccountDetails(string& name, int& age, bool& isAdmin, string& accno, double& balance){
    ifstream file(getAccountPath(accno));

    if(!file.is_open())
    {
        return;
    }

    string pin;

    getline(file, pin);      // Skip PIN
    getline(file, name);

    file >> age;
    file >> isAdmin;

    file.ignore();

    getline(file, accno);

    file >> balance;

    file.close();
}

/*
 * Record a money transfer in both account histories.
 */
void FileManager::save_in_file(Member &sender,Member &receiver,double amount,double balance) { 
    time_t now = time(0);
    tm* local_time = std::localtime(&now);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",local_time);

    // Append transaction details to sender history.
    ofstream senderFile(getTransactionPath(sender.w->accountNumber),ios::app);
    if(senderFile.is_open()) {
        senderFile<< sender.w->accountNumber << "|"<< receiver.w->accountNumber << "|"<< amount << "|"<< sender.w->balance << "|"<< buffer << endl;
        senderFile.close();
    }

    // Append transaction details to receiver history.
    ofstream receiverFile(getTransactionPath(receiver.w->accountNumber),ios::app);
    if(receiverFile.is_open()){ 
        receiverFile << receiver.w->accountNumber << "|"<< sender.w->accountNumber << "|"<< amount << "|"<< receiver.w->balance << "|"<< buffer << endl;
        receiverFile.close();
    }
}

/*
 * Record a wallet top-up transaction.
 */
void FileManager::save_in_file(string sender,string receiver,double amount,double balance){
    time_t now = time(0);
    tm* local_time = std::localtime(&now);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",local_time);

    ofstream file(getTransactionPath(sender), ios::app);

// Preserve a chronological transaction history.
    if(file.is_open()) { 
        file << sender << "|"<< receiver << "|"<< amount << "|"<< balance << "|"<< buffer << endl;
        file.close();
    }
}

/*
 * Enforce account access permissions based
 * on the member's administrative privileges.
 */
void FileManager::viewAccount(Member &viewer, string targetAccount)
{
    // Administrators are allowed to access any account.
    if(viewer.admin)
    {
        read_file(targetAccount);
    }

    // Regular members are restricted to their own account.
    else if(viewer.w->accountNumber == targetAccount)
    {
        read_file(targetAccount);
    }

    else
    {
        cout << "Access Denied! Members can only view their own account."<< endl;
    }
}

/*
 * Retrieve the current balance stored
 * in an account file.
 */
double FileManager::getBalance(string accountNo)
{
    string filename = getAccountPath(accountNo);
    ifstream file(filename);

    // Verify that the account file exists.
    if(!file.is_open()) {
        return -1;
    }

    string pin, name, acc;
    int age;
    bool admin;
    double balance;

    // Read account metadata to reach the stored balance field.
    getline(file, pin);
    getline(file, name);

    file >> age;
    file >> admin;
    file >> acc;
    file >> balance;
    
    file.close();

    return balance;
}

/*
 * Update the balance field stored near the
 * beginning of the account file while preserving
 * transaction history.
 */
void FileManager::updateBalance(string accountNo,double newBalance) {
    string filename = getAccountPath(accountNo);

    ifstream inFile(filename);

// Ensure the target account file exists.
    if(!inFile.is_open()){
        cout << "File not found" << endl;
        return;
    }

    vector<string> lines;
    string line;

// Load the entire file so the balance line
// can be modified without losing history.
    while(getline(inFile,line)){
        lines.push_back(line);
    }

    inFile.close();

// Replace the existing balance entry.
    lines[index_for_balance] = to_string(newBalance);

    ofstream outFile(filename);

// Rewrite the updated contents back to disk.
    for(string line : lines){
        outFile << line << endl;
    }

    outFile.close();
}
