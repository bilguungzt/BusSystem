#include "Passenger.hpp"

Passenger::Passenger() {
	Passenger("GenericFirst", "GenericLast", nullptr, nullptr, 0, 0);
}

Passenger::Passenger(string firstName, string lastName, Stop* startLocation, Stop* exitLocation, int startTime, int timeOnBus){
	this->firstName = firstName;	//protected members of the parent class
	this->lastName = lastName;
	this->startLocation = startLocation;
	this->exitLocation = exitLocation;
	this->startTime = startTime;
	setTimeOnBus(timeOnBus);
}

//Passenger::~Passenger() {
//	// TODO Auto-generated destructor stub
//}

string Passenger::getName() const{
	return getLastName() + ", " + getFirstName();	//call methods from base class
}

Stop* Passenger::getStartLocation() const{
	return this->startLocation;
}

Stop* Passenger::getExitLocation() const{
	return this->exitLocation;
}

int Passenger::getStartTime() const{
	return this->startTime;
}

int Passenger::getTimeOnBus() const{
	return this->timeOnBus;
}

void Passenger::setStartLocation(Stop* startLocation){
	this->startLocation = startLocation;
}

void Passenger::setExitLocation(Stop* exitLocation){
	this->exitLocation = exitLocation;
}

void Passenger::setStartTime(int startTime){
	this->startTime = startTime;
}

void Passenger::setTimeOnBus(int timeOnBus){
	if(timeOnBus >= 0)
	{
		this->timeOnBus = timeOnBus;
	}
	else{
		this->timeOnBus = 0;
	}
}

void Passenger::displayTime() const{
	int hrs = startTime /60;
	int mins = startTime % 60;
	printf ("Board time: %02d:%02d\n", hrs, mins);

	if(timeOnBus > 0)
	{
		int temp = startTime + timeOnBus;
		printf ("Departure time: %02d:%02d\n", temp/60, temp % 60);
	}
	else{
		cout << "Waiting for depature...\n";
	}
}
