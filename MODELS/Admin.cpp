#include "Admin.h"
#include <iostream>

using namespace std;

/*
 * Construct an administrator account by
 * initializing the inherited Member data
 * and automatically enabling administrative
 * privileges.
 */
Admin::Admin(string n, int a, string accno, double bal) : Member(n, a, true, accno, bal) {}
