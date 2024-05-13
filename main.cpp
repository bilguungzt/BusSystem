#include <iostream>
#include <string>
#include "Route.hpp"
#include "Passenger.hpp"
#include "Stop.hpp"
using namespace std;

		//functions to be used in bus class
void printRouteTime(Stop* stop, int elapsedTime);
int timeToInt(string time);
void runRouteBus(Route* route);
void runPassengerBus(Passenger* passenger);
int main()
{
	// Creating a Route and running the bus
	Route* route = new Route();
	runRouteBus(route);
	delete route;

	// Creating Stops and Passenger and running the bus
	Stop* exitStop = new Stop(nullptr, "19th Street", 0, 0);
	Stop* secondStop = new Stop(exitStop, "18th Street", 14, 2);
	Stop* entryStop = new Stop(secondStop, "17th Street", 20, 1);
	Passenger* coolGuy = new Passenger("CJ", "Conley", entryStop, exitStop, 540);

	runPassengerBus(coolGuy);

	// Cleanup
	delete exitStop;
	delete secondStop;
	delete entryStop;
	delete coolGuy;

	cout << "\n\n------------------------------------------\n";
	cout << "Program ending, have a nice day\n";
	cout << "------------------------------------------\n";

	return 0;
}

void runRouteBus(Route* route){
			//initialize route if it need be
	if(route == nullptr || route->getStartLocation() == nullptr){
		route->initializeRoute();
	}
	cout << "\n\n------------------------------------------\n\n\n";

			//Get the time the bus leaves
	string timeResp = "9:00";
	cout << "What time does the bus leave ? XX:XX format: ";
	cin >> timeResp;		//getline causes exception to be thrown
	int startTime = timeToInt(timeResp);
	cout << "\n\n------------------------------------------\n\n\n";

			//Run bus through stops and print out information
	cout << "Bus starts at " << route->getCurrentLocation()->getName() << " stop at ";
	printf ("%02d:%02d\n", startTime/60, startTime%60);

	while(route->getCurrentLocation() != route->getStopLocation()){
		if(route->getCurrentLocation()->getNextStop() != nullptr){
		cout << "driving to next stop...\t...Arrived!\n";	//don't display "traveling to next location" if you're at the last stop
		}
		route->nextStop();		//updates route->currentLocation to next & updates timeElapsed
		printRouteTime(route->getCurrentLocation(), route->getTimeElapsed() + startTime);
	}
	cout << "End of the line!\n";
}

void printRouteTime(Stop* stop, int elapsedTime){
	if(stop != nullptr){
	cout << "Currently at " << stop->getName();
	cout << " stop at ";
	int hrs = (elapsedTime / 60) % 12; //vals 0 - 11 allowed
	if(hrs == 0){
		hrs = 12;
	}
	int mins = elapsedTime % 60;
	printf ("%02d:%02d\n", hrs, mins);
	}
}

int timeToInt(string time){
	string hour = "";
	unsigned int i = 0;
	while(time.at(i) != ':'){
		hour += time.at(i);
		i++;
	}

	//now time.at(i) == ":"
	i++;
	string mins = "";
	while( i < time.size()){
		mins += time.at(i);
		i++;
	}

	//stoi("09") -> ret(9)
	int hourVal = stoi(hour) * 60;
	int minVal = stoi(mins);
	return hourVal + minVal;
}
void runPassengerBus(Passenger* passenger) {
	int timePassed = 0;
	int trafficFactor = 0;
	char userChoice = 'z';

	cout << "Would you like to select the traffic yourself, or use default values ? (y/n): ";
	cin >> userChoice;

	Stop* temp = passenger->getStartLocation();
	while (temp->getNextStop() != nullptr) {
		if (userChoice == 'y' || userChoice == 'Y') {
			cout << "How is the traffic, from 1 - 5, for the " << temp->getName() << " stop?: ";
			cin >> trafficFactor;
			temp->setTrafficFactor(trafficFactor);
		}
		timePassed += temp->updateTime();
		temp = temp->getNextStop();
	}

	passenger->setTimeOnBus(timePassed);
	passenger->displayTime();
}