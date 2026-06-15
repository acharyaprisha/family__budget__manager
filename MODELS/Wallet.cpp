#include "Wallet.h"

/*
 * Initialize wallet details using the values
 * provided during account creation.
 */
Wallet::Wallet(string accno, double bal) {
    accountNumber = accno;
    balance = bal;
}

double Wallet:: getbalance(){
    return balance;
}