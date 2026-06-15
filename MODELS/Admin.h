#ifndef ADMIN_H
#define ADMIN_H

#include "Member.h"

/**
 * @brief Represents an administrator account.
 *
 * An Admin is a specialized type of Member
 * that inherits all member attributes and
 * functionality while having elevated access
 * privileges within the Family Budget Manager.
 *
 * Demonstrates inheritance by extending the
 * Member class.
 */
class Admin : public Member{

    public:

        /**
     * @brief Constructs an administrator account.
     *
     * Initializes the inherited Member data and
     * automatically grants administrative privileges.
     *
     * @param n Name of the administrator.
     * @param a Age of the administrator.
     * @param accno Account number associated with
     *              the administrator's wallet.
     * @param bal Initial wallet balance.
     */
    Admin(string n, int a, string accno, double bal);

};

#endif