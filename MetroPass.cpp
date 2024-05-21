//
//  MetroPass.cpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#include "MetroPass.hpp"
using namespace std;

//Constructor
MetroPass::MetroPass()
{
    MetroPass(0.0, 0.0);
}

MetroPass::MetroPass(double balance, double price){
    setBalance(balance);
    setPrice(price);
//    this->balance = balance;
//    this->price = price;
}

void MetroPass::setBalance(double balance){
    if(balance >= 0.0){
        this->balance = balance;
    }
    else{
        this->balance = 0.0;
    }
}

void MetroPass::setPrice(double price){
    if(price >= 0.0){        //maybe one day you're allowed to ride for free ?
        this->price = price;
    }
    else{
        this->price = 0.0;
    }
}

void MetroPass::withdrawl(double amount)
{
    if(amount < this->balance || amount == this->balance)
    {
        this->balance = this->balance - amount;
        cout<< "$" << this->balance << " is withdrawled." <<endl;
    }
    else
    {
        cout<< "The balance is not enough. You only have $" << this->balance << "." <<endl;
    }
}

void MetroPass::add(double amount)
{
    if(amount >= 0.0){
        this->balance = this->balance + amount;
        cout<< "$" << this->balance <<" is added on your MetroPass." <<endl;
    }
    else{
        cout << "Error, invalid amount attempted to be added" << endl;
    }
}

bool MetroPass::swipe(double price)
{
    bool check = false;
    if(this->balance > price || this->balance == price)
    {
        this->balance = this->balance - price;
        check = true;
        cout<< "Pass Swiped!" <<endl;
    }
    else
    {
        check = false;
        cout<< "Balance is not enough!"<<endl;
    }
    return check;
}

bool MetroPass::swipe()
{
    bool check = false;
    if(this->balance > this->price || this->balance == this->price)
    {
        this->balance = this->balance - this->price;
        check = true;
        cout<< "Pass Swiped!" <<endl;
    }
    else
    {
        check = false;
        cout<< "Balance is not enough!"<<endl;
    }
    return check;
}
