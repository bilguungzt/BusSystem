#include <iostream>
#include <string>

#include "Passenger.hpp"
#include "Stop.hpp"

using namespace std;

void runBus(Passenger* passenger);

int main()
{
	Stop* exitStop = new Stop(nullptr, "19th Street", 0, 0);	//null next stop, end of the line
	Stop* secondStop = new Stop(exitStop, "18th Street", 14, 2);
	Stop* entryStop = new Stop(secondStop, "17th Street", 20, 1);
	Passenger* coolGuy = new Passenger("CJ", "Conley", entryStop, exitStop, 540);

	runBus(coolGuy);

	return 0;
}

void runBus(Passenger* passenger){
	int timePassed = 0;
	int trafficFactor = 0;
	char userChoice = 'z';

	cout << "Would you like to select the traffic yourself, or use default values ? (y/n): ";
	cin >> userChoice;

	Stop* temp = passenger->getStartLocation();
	while(temp->getNextStop() != nullptr)
	{
		if(userChoice == 'y' || userChoice == 'Y'){
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
