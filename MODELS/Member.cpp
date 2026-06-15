#include "Member.h"

/*
 * Initialize member information and create
 * an associated wallet object.
 */
Member::Member(string n,int a,bool ad, string accno,double bal){
    name = n;
    age = a;
    admin = ad;

    w = new Wallet(accno,bal);
}

/*
 * Release dynamically allocated resources
 * owned by the member.
 */
Member::~Member() {
    delete w;
}