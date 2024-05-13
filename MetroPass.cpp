//
// Created by Bilguun on 5/12/24.
//

#include "MetroPass.hpp"
MetroPass::MetroPass(int id, double balance) : id(id), balance(balance) {}

int MetroPass::getId() const {
    return id;
}

double MetroPass::getBalance() const {
    return balance;
}

void MetroPass::addBalance(double amount) {
    balance += amount;
}

void MetroPass::deductBalance(double amount) {
    if (amount <= balance) {
        balance -= amount;
    }
}

// bool swipe(double rideCost) {
//     if (balance >= rideCost) {
//         deductBalance(rideCost);
//         return true;
//     }
//     return false;
// }

