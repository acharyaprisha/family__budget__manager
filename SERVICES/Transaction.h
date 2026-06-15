#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

using namespace std;

class Member; 

/**
 * @brief Represents a financial transaction.
 *
 * Stores transaction information such as sender account,
 * receiver account, transferred amount, and timestamp.
 * Also provides functionality for wallet top-ups and
 * money transfers between members.
 */
class Transaction
{
    string sender_acc;
    string receiver_acc;
    double amount;
    time_t timestamp;

public:
    
/**
     * @brief Constructs a transaction object.
     *
     * Initializes the sender account, receiver account,
     * transaction amount, and timestamp.
     *
     * @param s Sender account number.
     * @param r Receiver account number.
     * @param amt Amount involved in the transaction.
     */
    Transaction(string s,string r, double amt); 

     /**
     * @brief Adds funds to a member's wallet.
     *
     * Updates the wallet balance, updates the stored
     * balance in the account file, and records the
     * transaction in the transaction history.
     *
     * @param m Member whose wallet is to be topped up.
     * @param amt Amount to be added to the wallet.
     */
    void topup(Member &m, double amt);

    /**
     * @brief Transfers funds between two members.
     *
     * Verifies account existence, checks sender balance,
     * updates both account balances, and records the
     * transaction in the corresponding account files.
     *
     * @param sender Member sending the funds.
     * @param receiver Member receiving the funds.
     * @param amount Amount to be transferred.
     */
    void money_transfer(Member &sender,Member &receiver,double amount);
};

#endif