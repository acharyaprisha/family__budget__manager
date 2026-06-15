#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include "Wallet.h"

using namespace std;

class FileManager;

/**
 * @brief Represents a member of the family budget manager.
 *
 * Stores personal information such as name, age,
 * administrative privileges, and an associated wallet.
 */
class Member {
    string name;
    int age;
    bool admin;

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