#include "Transaction.h"
#include "../MODELS/Member.h"
#include "../REPOSITORIES/FileManager.h"

#include <iostream>

using namespace std;

/*
 * Initialize transaction details and capture
 * the creation timestamp.
 */

Transaction::Transaction(string s, string r, double amt){ 
        this->receiver_acc = r;
        this->amount = amt;
        this->timestamp = time(0);
    }


/*
 * Perform a wallet top-up operation by validating
 * the account, updating the balance, persisting
 * the new balance, and recording the transaction.
 */

void Transaction::topup(Member &m, double amt){

    FileManager fm;

    // Prevent balance updates for non-existent accounts.
    if(!fm.search_file(m.w->accountNumber)){
        cout << "Account not found" << endl;
        return;
    }

    // Apply the top-up amount to the wallet balance.
    m.w->balance += amt;

    fm.updateBalance(m.w->accountNumber,m.w->balance);

    // Refresh transaction timestamp before recording history.
    timestamp = time(0);
    tm* local_time = std::localtime(&timestamp);
 
    // Record the top-up in the transaction history file.
    fm.save_in_file(m.w->accountNumber,m.w->accountNumber,amt,m.w->balance);

    cout << "Top up successful!" << endl;
}


/*
 * Transfer funds between two member accounts after
 * validating account existence and available balance.
 */
void Transaction::money_transfer(Member &sender, Member &receiver,double amount) { // this function is used to transfer money from one account to another account
    FileManager fm;
    
    // Ensure both accounts exist before processing transfer.
    if(!fm.search_file(sender.w->accountNumber, receiver.w->accountNumber)){ 
     cout << "One or both accounts not found" << endl;
     return;
    }
    
    // Reject transfer if sender lacks sufficient funds.
    if(sender.w->balance < amount){ 
    cout << "Insufficient Balance" << endl;
    return;
    }

    // Deduct funds from sender and credit receiver.
    else{  
    sender.w->balance -= amount;
    receiver.w->balance += amount;
    }

    fm.updateBalance(sender.w->accountNumber,sender.w->balance);
    fm.updateBalance(receiver.w->accountNumber,receiver.w->balance);

    fm.save_in_file(sender,receiver,amount,sender.w->balance);
    }