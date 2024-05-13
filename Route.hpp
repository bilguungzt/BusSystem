#ifndef ROUTE_HPP_
#define ROUTE_HPP_

#include "Stop.hpp"
#include <iostream>
#include <fstream>

//Note -- we need to write to an external file. This can be the bus' output or
//it can be the transaction list, after a sorting ? sent to a file in a format

class Route{
private:
	Stop* startLocation;
	Stop* currentLocation;
	Stop* stopLocation;
	int timeElapsed;
	void deleteList(Stop* stop);
//	void setCurrentLocation(Stop* currentLocation);
	void updateTime();		//will update timeElapsed
	void readFromFile(const string& fileName);
public:
	Route();
	Route(Stop* startLocation, Stop* currentLocation, Stop* stopLocation, int timeElapsed);
	virtual ~Route();
	void initializeRoute();
	string getName() const;
	int getTimeElapsed() const;
	Stop* getStartLocation() const;
	Stop* getCurrentLocation() const;
	Stop* getStopLocation() const;
	void nextStop();		// will set the currentLocation to be the next
	void displayStops();
	void updateTrafficFactors();
};

#endif /* ROUTE_HPP_ */
