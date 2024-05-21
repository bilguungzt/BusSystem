#include "Bus.hpp"
#include "Route.hpp"
#include "Passenger.hpp"
#include "MetroPass.hpp"
#include "Transaction.hpp"
#include <vector>
#include <algorithm>

int MAXSTOPS = 5;

Bus::Bus(){
	this->passengers = nullptr;
	this->numOfRiders = 0;
	this->capacity = 0;
	this->rideCost = 0.0;
	this->path = nullptr;
	this->startTime = 0;
	this->log = nullptr;
}

Bus::Bus(int capacity, double rideCost, Route* path, int startTime) {
	this->numOfRiders = 0;
    this->capacity = capacity;
    this->rideCost = rideCost;
    this->path = path;
    this->startTime = startTime;
    this->passengers = new Passenger*[this->capacity];
    this->log = new Transaction();
}

Bus::Bus(Bus* otherBus){
	this->capacity = otherBus->capacity;
	this->log = otherBus->log;
	this->numOfRiders = otherBus->numOfRiders;
	this->passengers = otherBus->passengers;
	this->path = otherBus->path;
	this->rideCost = otherBus->rideCost;
	this->startTime = otherBus->startTime;
}

Bus::~Bus() {
    delete path;
    delete passengers;
    delete log;
}

int Bus::getStartTime() const{
	return this->startTime;
}

bool Bus::atEnd() const{
	return path->getCurrentLocation() == path->getStopLocation();
}

bool Bus::isFull() const{
	return this->numOfRiders == this->capacity;
}

Stop* Bus::getCurrentStop() const{
	return path->getCurrentLocation();
}

bool Bus::acceptPassenger(Passenger* passenger) {
	if(this->passengers == nullptr){
		this->passengers = new Passenger*[capacity];
	}
	passenger->declarePrice(this->rideCost);
    if (this->numOfRiders < this->capacity && passenger->getOnBus(path->getTimeElapsed())) {
    	passenger->setStartTime(this->startTime + this->path->getTimeElapsed());
    	passengers[this->numOfRiders] = passenger;
    	this->numOfRiders++;
    	if(log == nullptr){
    		log = new Transaction();
    	}
        log->pushback(passenger->getStartLocation(), passenger->getStartTime(), passenger->getName());
        return true;
    }
    return false;
}

//void Bus::offloadPassenger(Passenger* passenger, Stop* currentStop) {
//    auto it = find(passengers.begin(), passengers.end(), passenger);
//    if (it != passengers.end()) {
//        passengers.erase(it);
//        log.deleteNode(passenger->getName(), currentStop);
//        delete passenger;
//    }
//}

void Bus::offloadPassengers(){
	for(int i = 0; i < this->numOfRiders; i++){
		if(passengers[i]->getExitLocation() == path->getCurrentLocation())
		{
			delete passengers[i];
			passengers[i] = nullptr;
			shiftArray(i, this->numOfRiders);
		}
	}
}

void Bus::nextStop(){
	path->nextStop();
}

//void Bus::startRoute() {
//    path->initializeRoute();
//    while (path->getCurrentLocation() != path->getStopLocation()) {
//        path->nextStop();
//        Stop* currentStop = path->getCurrentLocation();
//
//        // Offload passengers at the current stop
//        vector<Passenger*> toOffload;
//        for (Passenger* p : passengers) {
//            if (p->getExitLocation() == currentStop) {
//                toOffload.push_back(p);
//            }
//        }
//        for (Passenger* p : toOffload) {
//            offloadPassenger(p, currentStop);
//        }
//
//        // Accept new passengers at the current stop
//        // (assuming you have a function to read passengers from a file)
//        vector<Passenger*> newPassengers = readPassengersFromFile(currentStop->getName() + ".txt");
//        for (Passenger* p : newPassengers) {
//            acceptPassenger(p);
//        }
//    }
//}
void Bus::writeLog() {
    log->writeToFile();
}

Route* Bus::getRoute() const {
    return path;
}

int Bus::timeToInt(string time){
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
	int hourVal = stoi(hour) * 60;
	int minVal = stoi(mins);
	return hourVal + minVal;
}

void Bus::initializeRoute(){
	if(path == nullptr){
		path = new Route();
	}
	path->initializeRoute();
	string res = "9:00";
	cout << "What time does the bus start? (XX:XX format): ";
//	cin >> res;
	this->startTime = timeToInt(res);
}

vector<Passenger*> Bus::readPassengersFromFile(const string& fileName) {
    vector<Passenger*> passengers;
    ifstream file(fileName);
    int i = 0;

    if(file.is_open()) {
        string firstName, lastName;
        int startStop, exitStop;;

        Stop* stStop = nullptr;
        Stop* exStop = nullptr;
        while (!file.eof()) {
        	file >> firstName;
        	file >> lastName;
        	file >> startStop;
        	file >> exitStop;
        	stStop = this->path->getStartLocation();
        	exStop = this->path->getStartLocation();

        	if(exitStop > MAXSTOPS || exitStop < 0){
        		exStop = nullptr;
        	}
        	if(startStop > MAXSTOPS || startStop < 0){
        		stStop = nullptr;
        	}
        	if(exitStop <= MAXSTOPS && exitStop >= 0){
        		for(int i = 0; i < exitStop; i++){
        			exStop = exStop->getNextStop();
        		}
        	}
        	if(startStop <= MAXSTOPS && startStop >= 0){
        		for(int i = 0; i < startStop; i++){
        			stStop = stStop->getNextStop();
         		}
        	}
            Passenger* p = new Passenger(firstName, lastName, stStop, exStop);
            passengers.push_back(p);
            i++;
        }

        //extraPassenger added
        passengers.pop_back();

        file.close();
    }
    else {
        cout << "Unable to open file: " << fileName << endl;
    }

    return passengers;
}

//.printRouteTime(bus.getCurrentStop(), bus.getRoute()->getTimeElapsed() + bus.getStartTime());
void Bus::printRouteTime(){
	if(this->path != nullptr && this->path->getCurrentLocation() != nullptr){
		cout <<"Currently at " << path->getCurrentLocation()->getName();
		cout << " stop at ";
		int elapsedTime = this->startTime + this->path->getTimeElapsed();
		int hrs = (elapsedTime / 60) % 12; //vals 0 - 11 allowed
			if(hrs == 0){
				hrs = 12;
			}
			int mins = elapsedTime % 60;
			printf ("%02d:%02d\n", hrs, mins);
	}
}

void Bus::shiftArray(int startPos, int endPos){
	for(int i = startPos; i < endPos; i++){
		passengers[i] = passengers[i+1];
	}
}
