#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include "Wallet.h"

using namespace std;

class FileManager;

/**
 * @class Member
 * @brief Represents a user account in the Family Budget Manager.
 *
 * Stores member information and provides functionality
 * for viewing account details, managing transactions,
 * configuring default screens, and accessing account
 * services after login.
 */
class Member {
    string name;
    int age;
    bool admin;
    char screen;

public:
    
    /**
 * @brief Wallet associated with the member.
 *
 * Dynamically allocated to demonstrate composition
 * and dynamic memory management.
 */
    Wallet* w;

    /**
 * @brief Constructs a member object.
 *
 * Initializes the member's personal information
 * and creates an associated wallet.
 *
 * @param n Name of the member.
 * @param a Age of the member.
 * @param ad Administrative status of the member.
 * @param accno Account number associated with the wallet.
 * @param bal Initial wallet balance.
 */
    Member(string n,int a,bool ad, string accno,double bal);

    /**
 * @brief Opens the specified default screen.
 *
 * Executes the operation associated with the
 * provided screen identifier. The screen can
 * correspond to account viewing, transaction
 * history, wallet top-up, money transfer,
 * administrative access, or transaction filtering.
 *
 * @param screen Character representing the
 * screen to be opened.
 */
    void OpenScreen(char screen);

    void changeDefaultScreen();

    /**
 * @brief Opens or configures the member's default screen.
 *
 * Reads the saved default screen from the wallet file.
 * If a default screen exists, the corresponding operation
 * is opened automatically. Otherwise, the user is prompted
 * to select and save a default screen.
 *
 * @param accno Account number associated with the member.
 */
    void configure_default_screen(string accno);

    /**
 * @brief Displays member account information.
 *
 * Prints the member's personal details and
 * wallet information to the console.
 */
    void ViewAccount();

    /**
 * @brief Displays transaction history.
 *
 * Reads and displays all transactions associated
 * with the member's account.
 */
    void ViewTransactionHistory();

    /**
 * @brief Adds funds to the member's wallet.
 *
 * Prompts the user for an amount and updates
 * the wallet balance through a top-up transaction.
 */
    void TopUp();

    /**
 * @brief Transfers money to another account.
 *
 * Collects receiver account information and
 * transfer amount, then performs a money
 * transfer transaction.
 */
    void TransferMoney();

    /**
 * @brief Allows administrators to access other accounts.
 *
 * Provides administrative functionality for
 * viewing account information belonging to
 * other members.
 */
    void AdminAccess();

    /**
 * @brief Filters transactions by amount.
 *
 * Displays transactions whose amount matches
 * the value specified by the user.
 */
    void FilterTransactions();
        
      
    /**
 * @brief Destroys a member object.
 *
 * Releases the dynamically allocated wallet object.
 */
    ~Member();

     /**
 * @brief Grants FileManager access to private member data.
 */
    friend class FileManager;
};

#endif