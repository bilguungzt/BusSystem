//
//  MetroPass.hpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#ifndef METROPASS_HPP_
#define METROPASS_HPP_

#include <string>
#include <iostream>
//#include "Transaction.hpp"
using namespace std;

class MetroPass
{
private:
    double balance;
    //    bool swipeCheck;
    double price;
public:
    MetroPass();
    MetroPass(double balance, double price);
    void setBalance(double balance);
    void setPrice(double price);
    double getBalance();
    double getPrice();
    void withdrawl(double amount);
    void add(double amount);
    bool swipe(double price);
    bool swipe();
};

#endif /* METROPASS_HPP_ */
