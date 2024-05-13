//
// Created by Bilguun on 5/12/24.
//

#include "Transaction.hpp"
Transaction::Transaction(int transaction_id, int pass_id, double amount, std::time_t timestamp): transaction_id(transaction_id), pass_id(pass_id), amount(amount), timestamp(timestamp) {}

int Transaction::getTransactionId() const {
    return transaction_id;
}

int Transaction::getPassId() const {
    return pass_id;
}

double Transaction::getAmount() const {
    return amount;
}

std::time_t Transaction::getTimestap() const {
    return timestamp;
}


