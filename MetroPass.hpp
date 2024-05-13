//
// Created by Bilguun on 5/12/24.
//

#ifndef METROPASS_H
#define METROPASS_H
class MetroPass {
public:
    MetroPass(int id, double balance);
    int getId() const;
    double getBalance() const;
    void addBalance(double amount);
    void deductBalance(double amount);
    // bool swipe(double rideCost);
private:
    int id;
    double balance;
};
#endif //METROPASS_H
