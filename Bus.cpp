//
// Created by Bilguun on 5/12/24.
//
#include "Bus.hpp"
#include <algorithm>

Bus::Bus(int bus_id, const Route& route) : bus_id(bus_id), route(route) {}

int Bus::getBusId() const {
    return bus_id;
}
Route Bus::getRoute() const {
    return route;
}
void Bus::addPassenger(const Passenger &passenger) {
    passengers.push_back(passenger);
}

void Bus::removePassenger(const std::string &name) {
    passengers.erase(
        std::remove_if(passengers.begin(), passengers.end(),
            [&name](const Passenger& p) {
                return p.getName() == name;
            }
            ),
            passengers.end()
            );
}

std::vector<Passenger> Bus::getPassenger() const {
    return passengers;
}

void Bus::logTransaction(const Transaction &transaction) {
    transactions.push_back(transaction);
}





