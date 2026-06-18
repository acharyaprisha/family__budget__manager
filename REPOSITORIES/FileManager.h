#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

using namespace std;

class Member;

/**
 * @brief Displays transaction history.
 *
 * Reads and prints all transactions stored
 * in the account's transaction history file.
 *
 * @param accountNo Account number whose
 * transaction history is to be displayed.
 */
class FileManager
{
   
public:

/**
 * @brief Creates a new account file.
 *
 * Stores member information and initializes
 * the required files for account management.
 *
 * @param mem Member whose information is stored.
 * @param pin PIN used for account authentication.
 */
    void create_file(Member &m, string pin);

/*
 * Generate the complete path to an
 * account information file stored
 * within the data directory.
 *
 * @param accountNo Unique account number.
 *
 * @return Full path to the account file.
 */
   string getAccountPath(string accountNo);

/*
 * Generate the complete path to a
 * transaction history file stored
 * within the data directory.
 *
 * @param accountNo Unique account number.
 *
 * @return Full path to the transaction file.
 */
   string getTransactionPath(string accountNo);

 /**
 * @brief Authenticates a user.
 *
 * Compares the entered PIN with the PIN stored
 * in the member's account file.
 *
 * @param accountNo Account number of the user.
 * @return true if authentication succeeds.
 * @return false if authentication fails.
 */
    bool authenticate(string accountNo);


/**
 * @brief Checks whether an account file exists.
 *
 * @param accountNo Account number to search for.
 * @return true if the account file exists.
 * @return false otherwise.
 */
    bool search_file(string accountNo);


/**
 * @brief Validates the existence of two account files.
 *
 * Used during money transfer operations to ensure
 * that both sender and receiver accounts exist.
 *
 * @param sender_acc Sender account number.
 * @param receiver_acc Receiver account number.
 * @return true if both account files exist.
 * @return false otherwise.
 */
    bool search_file(string sender_acc, string receiver_acc);

/**
 * @brief Retrieves the saved default screen.
 *
 * Reads the user's preferred screen
 * from the wallet file.
 *
 * @param accno Account number.
 * @return Stored default screen identifier.
 */
    char ReadDefaultScreen(string accno);
  
/**
 * @brief Stores the default screen preference.
 *
 * Saves or updates the user's preferred
 * default screen in the wallet file.
 *
 * @param accno Account number.
 * @param defaultScreen Selected screen identifier.
 */
    void StoreDefaultScreen(string accno, char defaultScreen);


/**
 * @brief Displays account file contents.
 *
 * Reads and prints the contents of the specified
 * account's transaction file.
 *
 * @param accountNo Account number whose file is
 * to be displayed.
 */
    void read_file(string accountNo);


/**
 * @brief Loads account information.
 *
 * Reads member information from the
 * wallet file and populates the
 * provided variables.
 *
 * @param name Member name.
 * @param age Member age.
 * @param isAdmin Administrative status.
 * @param accno Account number.
 * @param balance Wallet balance.
 */
void readAccountDetails(string& name,int& age,bool& isAdmin,string& accno,double& balance);


/**
 * @brief Records a money transfer transaction.
 *
 * Appends transaction details to both sender and
 * receiver account files.
 *
 * @param sender Member sending the funds.
 * @param receiver Member receiving the funds.
 * @param amount Amount transferred.
 * @param balance Updated sender balance.
 */
    void save_in_file(Member &sender, Member &receiver,double amount,double balance);


/**
 * @brief Records a top-up transaction.
 *
 * Appends top-up details to the account file.
 *
 * @param sender Account receiving the top-up.
 * @param receiver Transaction type identifier.
 * @param amount Amount added.
 * @param balance Updated account balance.
 */
    void save_in_file(string sender,string receiver,double amount,double balance);

    
 /**
 * @brief Displays account details based on access permissions.
 *
 * Administrators can access any account, while
 * regular members can only access their own.
 *
 * @param viewer Member requesting access.
 * @param targetAccount Account to be viewed.
 */
    void viewAccount(Member &viewer, string targetAccount);


/**
 * @brief Retrieves the current account balance.
 *
 * Reads the balance stored in the account file.
 *
 * @param accountNo Account number whose balance
 * is requested.
 * @return Account balance if found.
 * @return -1 if the account file does not exist.
 */
    double getBalance(string accountNo);


/**
 * @brief Updates the stored account balance.
 *
 * Replaces the balance value stored at the
 * beginning of the account file after a
 * successful transaction.
 *
 * @param accountNo Account number to update.
 * @param newBalance Updated balance value.
 */
    void updateBalance(string accountNo,double newBalance);
};

#endif