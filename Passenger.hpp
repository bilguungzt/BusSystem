#ifndef PASSENGER_HPP_
#define PASSENGER_HPP_

#include "People.hpp"
#include "Stop.hpp"
#include <iostream>
#include <cstdio>

class Passenger: public People {
private:
	Stop* startLocation;
	Stop* exitLocation;
//	MetroPass pass;
	int startTime;
	int timeOnBus;

public:
	Passenger();
	Passenger(string firstName, string lastName, Stop* startLocation, Stop* exitLocation, int startTime = 0, int timeOnBus = 0);
//	virtul ~Passenger();
	void setStartLocation(Stop* startLocation);
	void setExitLocation(Stop* exitLocation);
	void setStartTime(int startTime);
	void setTimeOnBus(int timeOnBus);
	Stop* getStartLocation() const;
	Stop* getExitLocation() const;
	int getStartTime() const;
	int getTimeOnBus() const;
	string getName() const;
//	bool swipePass();
//	bool getOnBus(int startTime);	// calls swipePass() and calls setStartTime()
	void displayTime() const;
};
#endif /* PASSENGER_HPP_ */
