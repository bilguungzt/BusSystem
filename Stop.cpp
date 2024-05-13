#include "Stop.hpp"

Stop::Stop() {
	Stop(nullptr, "GenericStopName", 0, 0);
}

Stop::Stop(Stop* nextStop, string name, int timeToNextStop, int trafficFactor)
{
	setNextStop(nextStop);
	this->name = name;
	setTimeToNextStop(timeToNextStop);
	setTrafficFactor(trafficFactor);
}

Stop::Stop(Stop* stop){
	if(stop != nullptr){
		setNextStop(stop->nextStop);
		this->name = stop->name;
		setTimeToNextStop(stop->timeToNextStop);
		setTrafficFactor(stop->trafficFactor);
	}

//	this->nextStop = stop->nextStop;
//	this->name = stop->name;
//	this->timeToNextStop = stop->timeToNextStop;
//	this->trafficFactor = stop->trafficFactor;
}

int Stop::updateTime(){
	//increase/decrease the projected time using the trafficFactor
	//will be converted back into an int and stored in timeToNextStop
	//ex timeToNextStop * 1.2 or timeToNextStop * 1.6, etc.
	return double(this->timeToNextStop) * double(this->trafficFactor * 0.2 + 1);
}

void Stop::setNextStop(Stop* nextStop){
	if(nextStop != this){
	this->nextStop = nextStop;
	}
	else{
		this->nextStop = nullptr;
	}
}

void Stop::setTimeToNextStop(int timeToNextStop){
	if(timeToNextStop > -1){
		this->timeToNextStop = timeToNextStop;
	}
	else{
		this->timeToNextStop = 0;
	}
}

void Stop::setTrafficFactor(int trafficFactor)
{
	if(trafficFactor < 6 && trafficFactor > -1){
		this->trafficFactor = trafficFactor;
	}
	else{
		this->trafficFactor = 0;
	}
}

void Stop::setName(string name){
	this->name = name;
}

Stop* Stop::getNextStop() const{
	return this->nextStop;
}

string Stop::getName() const{
	return this->name;
}

int Stop::getTimeToNextStop() const{
	return this->timeToNextStop;
}

int Stop::getTrafficFactor() const{
	return this->trafficFactor;
}
