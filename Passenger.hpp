//
//  Passenger.hpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#ifndef PASSENGER_HPP_
#define PASSENGER_HPP_

#include "People.hpp"
#include "Stop.hpp"
#include "MetroPass.hpp"
#include <iostream>
#include <cstdio>

class Passenger: public People {
private:
	Stop* startLocation;
	Stop* exitLocation;
	MetroPass pass;
	int startTime;
	int timeOnBus;
	bool swipePass();    //calls swipePass() from MetroPass class

public:
	Passenger();
	Passenger(string firstName, string lastName, Stop* startLocation, Stop* exitLocation, int startTime = 0, int timeOnBus = 0);
	//    virtul ~Passenger();
	void setStartLocation(Stop* startLocation);
	void setExitLocation(Stop* exitLocation);
	void setStartTime(int startTime);
	void setTimeOnBus(int timeOnBus);
	Stop* getStartLocation() const;
	Stop* getExitLocation() const;
	int getStartTime() const;
	int getTimeOnBus() const;
	string getName() const;
	void displayTime() const;

	//Functions to interact with MetroPass
	bool getOnBus(int startTime);        // calls swipePass() and calls setStartTime()
	void addFunds(double funds);        //next two functions will call MetroPass setters
	void declarePrice(double price);
};
#endif /* PASSENGER_HPP_ */

