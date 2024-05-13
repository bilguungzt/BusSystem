//
// Created by Bilguun on 5/12/24.
//

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <ctime>

class Transaction {
public:
    Transaction(int transaction_id, int pass_id, double amount, std::time_t timestamp);
    int getTransactionId() const;
    int getPassId() const;
    double getAmount() const;
    std::time_t getTimestap() const;
private:
    int transaction_id;
    int pass_id;
    double amount;
    std::time_t timestamp;
};
#endif //TRANSACTION_H
