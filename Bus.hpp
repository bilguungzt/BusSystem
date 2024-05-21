#ifndef BUS_HPP
#define BUS_HPP

#include "Route.hpp"
#include "Passenger.hpp"
#include "Transaction.hpp"
#include <vector>
#include <string>

class Bus {
private:
    int capacity;
    int numOfRiders;
    double rideCost;
    Passenger** passengers;
    Route* path;
    Transaction* log;
    int startTime;

public:
    Bus();
    Bus(Bus* otherBus);
    Bus(int capacity, double rideCost, Route* path, int startTime);
    ~Bus();

    bool acceptPassenger(Passenger* passenger);
    void offloadPassenger(Passenger* passenger, Stop* currentStop);
//    void startRoute();
    void writeLog();
    Route* getRoute() const;
    bool atEnd() const;
    bool isFull() const;
    Stop* getCurrentStop() const;
    void initializeRoute();
    int getStartTime() const;
    void offloadPassengers();
    void nextStop();
    void printRouteTime();
    std::vector<Passenger*> readPassengersFromFile(const std::string& fileName);
private:
    void shiftArray(int startPos, int endPos);
    int timeToInt(string time);
};

#endif // BUS_HPP
