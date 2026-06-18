#ifndef WALLET_H
#define WALLET_H

#include <string>
using namespace std;

class FileManager; 
class Transaction; 

/**
 * @brief Represents a member's wallet.
 *
 * Stores the account number and current balance
 * associated with a member account.
 */

class Wallet {
    string accountNumber;
    double balance;

public:

    /**
     * @brief Constructs a wallet object.
     *
     * @param accno Unique account number assigned to the wallet.
     * @param bal Initial balance of the wallet.
     */
    Wallet(string accno, double bal);

    double getbalance();

    /**
     * @brief Grants Member access to private wallet data.
     */
    friend class Member;

    /**
     * @brief Grants FileManager access to private wallet data.
     */
    friend class FileManager;
    
    /**
     * @brief Grants Transaction access to private wallet data.
     */
    friend class Transaction;
};

#endif