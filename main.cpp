//
//  main.cpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#include "Passenger.hpp"
#include "Route.hpp"
#include "Transaction.hpp"
#include <vector>
#include <iostream>
using namespace std;

void runBus1(Passenger* passenger);
void runBus2(Route* route);
//void runBus(vector<Passenger*>, Bus myBus);
void printRouteTime(Stop* stop, int elapsedTime);
int timeToInt(string time);

class Bus{
    Transaction log;
};

int main(){

    //Phase 1 Dev Driver Program
    Stop* exitStop = new Stop(nullptr, "19th Street", 0, 0);    //null next stop, end of the line
    Stop* secondStop = new Stop(exitStop, "18th Street", 14, 2);
    Stop* entryStop = new Stop(secondStop, "17th Street", 20, 1);
    Passenger* coolGuy = new Passenger("CJ", "Conley", entryStop, exitStop, 540);

    runBus1(coolGuy);

    delete entryStop;
    delete secondStop;
    delete exitStop;        // need access to all 3 pointers, deallocators don't have ability to delete mem


    //Phase 2 Dev Driver Program
    Route* r = new Route();
    runBus2(r);
    cout << "\n\n------------------------------------------\n";
    cout << "Program ending, have a nice day\n";
    cout << "------------------------------------------\n";
    delete r;

    //Right here?
    //Phase 3 coming..
    //Build the bus class to hold the various object of classes we've built
    //Build the transaction class to log MetroPass swipes

    //smaller testing section for .writeToFile()
    Stop* exitStop1 = new Stop(nullptr, "19th Street", 0, 0);    //null next stop, end of the line
    Stop* secondStop1 = new Stop(exitStop, "18th Street", 14, 0);
    Stop* entryStop1 = new Stop(secondStop, "17th Street", 20, 0);

    Transaction t;
    t.pushback(entryStop1, 540, "Jesse");
    t.pushback(secondStop1, 555, "James");
    t.pushback(exitStop1, 620, "Meowth");
    t.display();
    cout << "---------------------------------------------------------\n";
    //    t.displayBackwards();
    t.writeToFile();

    delete entryStop;
    delete secondStop;
    delete exitStop;

    cout << "Program ending\n";
    return 0;
}

void runBus1(Passenger* passenger){
    int timePassed = 0;
    int trafficFactor = 0;
    char userChoice = 'z';

    cout << "Would you like to select the traffic yourself, or use default values ? (y/n): ";
    cin >> userChoice;

    Stop* temp = passenger->getStartLocation();
    while(temp != passenger->getExitLocation())
    {
        if(userChoice == 'y' || userChoice == 'Y')
        {
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

void runBus2(Route* route){
            //initialize route if it need be
    if(route == nullptr || route->getStartLocation() == nullptr){
        route->initializeRoute();
    }
    cout << "\n\n------------------------------------------\n\n\n";

            //Get the time the bus leaves
    string timeResp = "9:00";
    cout << "What time does the bus leave ? XX:XX format: ";
    cin >> timeResp;        //getline causes exception to be thrown
    int startTime = timeToInt(timeResp);
    cout << "\n\n------------------------------------------\n\n\n";

            //Run bus through stops and print out information
    cout << "Bus starts at " << route->getCurrentLocation()->getName() << " stop at ";
    printf ("%02d:%02d\n", startTime/60, startTime%60);

    while(route->getCurrentLocation() != route->getStopLocation()){
        if(route->getCurrentLocation()->getNextStop() != nullptr){
        cout << "driving to next stop...\t...Arrived!\n";    //don't display "traveling to next location" if you're at the last stop
        }
        route->nextStop();        //updates route->currentLocation to next & updates timeElapsed
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


