//
// Created by Bilguun on 5/12/24.
//

#ifndef BUS_H
#define BUS_H

#include "Route.hpp"
#include "Passenger.hpp"
#include "MetroPass.hpp"
#include "Transaction.hpp"
#include <vector>


class Bus {
public:
    Bus(int bus_id, const Route& route);
    int getBusId() const;
    Route getRoute() const;
    void addPassenger(const Passenger& passenger);
    void removePassenger(const std::string& name);
    std::vector<Passenger> getPassenger() const;
    void logTransaction(const Transaction& transaction);
private:
    int bus_id;
    Route route;
    std::vector<Passenger> passengers;
    std::vector<Transaction> transactions;
};



#endif //BUS_H
