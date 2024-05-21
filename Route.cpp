//
//  Route.cpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#include "Route.hpp"
#include <iostream>
#include <fstream>

using namespace std;

string DEFAULT_FILE = "default.txt";

Route::Route() {
//    Route(nullptr, nullptr, nullptr, 0);    //const() with args to be called then deconstructor right after ?
    this->startLocation = nullptr;
    this->currentLocation = nullptr;
    this->stopLocation = nullptr;
    this->timeElapsed = 0;
}

Route::Route(Stop* startLocation, Stop* currentLocation, Stop* stopLocation, int timeElapsed){
    this->startLocation = new Stop(startLocation);    //deconstructor for this class
    this->currentLocation = new Stop(currentLocation);//expects allocated mem
    this->stopLocation = new Stop(stopLocation);// or else delete behavior is
    this->timeElapsed = timeElapsed;            // undefined
}                                    // so must allocate new memory in constructor

Route::~Route() {
    deleteList(this->startLocation);
    this->startLocation = nullptr;
    this->currentLocation = nullptr;
    this->stopLocation = nullptr;
}

void Route::deleteList(Stop* stop){
    if(stop == nullptr){
        return;
    }
    else if(stop->getNextStop() == nullptr){
        Stop* temp = stop;
        delete temp;
        temp = nullptr;
    }
    else if(stop->getNextStop() != nullptr){
        deleteList(stop->getNextStop());
    }
}

//Stop* Route::initializeRoute(){
//    char resp = 'y';
////    cout << "Do you want to use the default routes? (y/n): ";
////    cin >> resp;
//
//    if(resp == 'n' || resp == 'N'){
//        string name;
//        Stop* current = nullptr;
//        Stop* previous = nullptr;
//        Stop* returnValue = nullptr;
//        int distance = 0;
//        int trafficFactor = 0;
//        current = new Stop();
//        returnValue = current;                //record the first stop(head) to return from func
//        this->startLocation = returnValue;
//        this->currentLocation = returnValue;
//        do{
//            //set up allows for us to recover the head value of linked list
//            if(current == nullptr){
//                current = new Stop();
//
//            }
//
//            //get class attribute values
//            cout << "What is the name of this stop?: ";
//            cin.ignore();
//            getline(cin, name);
//            cout << "How many minutes away is the next stop?: ";
//            cin >> distance;
//            cout << "How is the traffic level from 0-5: ";
//            cin >> trafficFactor;
//            //set class attribute values
//            current->setName(name);
//            current->setTimeToNextStop(distance);
//            current->setTrafficFactor(trafficFactor);
//            if(previous != nullptr){        // if(!on first iteration)
//                previous->setNextStop(current);
//            }
//            previous = current;                //update for next iteration of loop
//
//            cout << "Ok, add next Stop? (y/n): ";
//            cin >> resp;
//            if(resp == 'n' || resp == 'N'){    //in which case we don't loop again
//                this->stopLocation = current;
//            }
//
//            current = nullptr;                //set up case for current to be allocated again at start of loop
//        }while(resp != 'n' && resp != 'N');
//
//        //when the while loop is exited, the last stop->nextStop == nullptr via default constructor
//        return returnValue;
//    }
//
//    else{
//        //default route setup    -- needs to be converted to reading from a file
//        Stop* temp3 = new Stop(nullptr, "19th Street", 20, 1);
//        Stop* temp2 = new Stop(temp3, "18th Street", 12, 0);
//        Stop* retVal = new Stop(temp2, "17th Street", 8, 3);    //null next stop, end of the line
//        this->startLocation = retVal;
//        this->currentLocation = retVal;
//        this->stopLocation = temp3;
//
//        curr = nullptr;
//        prev = new Stop();
//        if(curr == nullptr){
//            prev->setName(name);
//            this->startLocation = prev;
//        }
//        curr = new Stop()
//        prev->next = curr;
//        prev = curr
//
//        return retVal;
//    }
//}

void Route::initializeRoute(){
    if(this->startLocation != nullptr){
        deleteList(this->startLocation);
    }
    char resp = 'y';
    cout << "Do you want to use the default route? (y/n): ";
    cin >> resp;

    if(resp == 'y' || resp == 'Y'){
        readFromFile(DEFAULT_FILE);
    }
    else{
        string fileName = "";
        cout << "What is the name of the file that has your route? (make sure to add .txt): ";
        cin >> fileName;
        readFromFile(fileName);
    }
    // ask user if they want to update the traffic levels manually
    char userChoice = 'z';
    cout << "Would you like to select the traffic yourself, or use default values ? (y/n): ";
    cin >> userChoice;
    if(userChoice == 'y' || userChoice == 'Y'){
        updateTrafficFactors();
    }
}


void Route::readFromFile(string fileName){
    //format will be: name \n distance \n trafficFactor \n
    string name = "";
    int distance = 0;
    int trafficFactor = 0;

    ifstream file(fileName);

    if(!file.is_open()){
        cout << "File failed to open, using default values\n";
        return readFromFile(DEFAULT_FILE);
    }
    else{
        Stop* current = nullptr;
        Stop* prev = new Stop();
        while(!file.eof()){
            getline(file, name);
            file >> distance;
            file >> trafficFactor;
            file.ignore();

            //set class attribute values
            if(current == nullptr){
                prev->setName(name);
                prev->setTimeToNextStop(distance);
                prev->setTrafficFactor(trafficFactor);
                this->startLocation = prev;                    // don't set stopLocation == startLocation
                this->currentLocation = this->startLocation;// initialize currLocation
            }
            else{
                current->setNextStop(nullptr);    //crashes without this line (default constructor tho??)
                current->setName(name);
                current->setTimeToNextStop(distance);
                current->setTrafficFactor(trafficFactor);
                prev->setNextStop(current);
                prev = current;
            }
            current = new Stop();    //assumes atleast 2 Stops will be read
        }// while loop
        //update stopLocation
        this->stopLocation = prev;
        delete current;                //on last iteration, current is not added to the linked list and thus never called upon in deconstructor
    }// outer else
}

Stop* Route::getStartLocation() const{
    return this->startLocation;
}

Stop* Route::getCurrentLocation() const{
    return this->currentLocation;
}

Stop* Route::getStopLocation() const{
    return this->stopLocation;
}

void Route::updateTime(){
//    int extraTime = updateTime();
    if(this->currentLocation != nullptr){
        this->timeElapsed += this->currentLocation->updateTime();
    }
}

void Route::nextStop(){
    if(this->currentLocation == nullptr){
        this->currentLocation = this->startLocation;
    }
    else if(this->currentLocation != this->stopLocation){
        updateTime();
        this->currentLocation = this->currentLocation->getNextStop();
    }
    else if(this->currentLocation == this->stopLocation){
        updateTime();//update the time spent driving, if you're at the end of
    }                 //the line: don't go to next stop(nullptr)
}

string Route::getName() const{
    return currentLocation->getName();
}

int Route::getTimeElapsed() const{
    return this->timeElapsed;
}

void Route::displayStops(){
    cout << "In order:\n";
    Stop* temp = this->startLocation;
    bool flag = true;
    while(flag){
        cout << temp->getName() << endl;

        if(temp->getNextStop() == nullptr){
            flag = false;
        }
        temp = temp->getNextStop();
    }
}

void Route::updateTrafficFactors(){
    Stop* temp = this->getStartLocation();
    int trafficFactor;
//    while(temp != nullptr)
//    {
//        if(temp->getNextStop() != nullptr)
//        {
//            cout << "How is the traffic, from 1 - 5, for the " << temp->getName() << " stop?: ";
//            cin >> trafficFactor;
//            temp->setTrafficFactor(trafficFactor);
//        }
//        temp = temp->getNextStop();
//    }
    while(temp->getNextStop() != nullptr)
    {
        cout << "How is the traffic, from 1 - 5, for the " << temp->getName() << " stop?: ";
        cin >> trafficFactor;
        temp->setTrafficFactor(trafficFactor);
        temp = temp->getNextStop();
    }
}

