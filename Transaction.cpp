//
//  Transaction.cpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#include "Transaction.hpp"
#include <fstream>

Transaction::Transaction() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

Transaction::~Transaction() {
    deleteList(head);
    head = nullptr;
    size = 0;
}

void Transaction::deleteList(Node* node){
    if(node == nullptr){        //if delete is called on an uninitialized node/Transaction obj
        return;
    }
    else if(node->next == nullptr){
        delete node;
        node = nullptr;
    }
    else if(node->next != nullptr){
        deleteList(node->next);
    }
}

void Transaction::pushback(Stop* passengerStop, int timeOfSwipe, string passengerName){
    // if list is empty
    if(head == nullptr){
        head = new Node(passengerStop, timeOfSwipe, passengerName, nullptr, nullptr);
        tail = head;
    }

    else{
        //find pushback location
        Node* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }

//      Node* add = new Node(passengerStop, timeOfSwipe. passengerName, nullptr, temp);
        Node* add = new Node();
        add->boardLocation = passengerStop;
        add->name = passengerName;
        add->time = timeOfSwipe;
        add->prev = temp;
        add->next = nullptr;
        tail = add;
    }
    size++;
}

void Transaction::display(){
    Node* temp = head;
    while(temp != nullptr){
        cout << "Name: " << temp->name << "\tEntry Stop: " << temp->boardLocation->getName();
        cout << "Board Time: ";
        displayTime(temp->time);        //display in XX:XX format
        cout << "\n";

        temp = temp->next;
    }
}

void Transaction::displayBackwards(){
    Node* temp = tail;

    while(temp != nullptr){    //head->prev == nullptr
        cout << "Name: " << temp->name << "\tEntry Stop: " << temp->boardLocation->getName();
        cout << "Board Time: ";
        displayTime(temp->time);        //display in XX:XX format
        cout << "\n";

        temp = temp->prev;
    }
}

void Transaction::displayTime(int time) const{
    int hrs = time / 60;
    int mins = time % 60;
    printf ("%02d:%02d", hrs, mins);
}

void Transaction::deleteNode(string passengerName){
    if(head == nullptr){
        return;
    }

    else if(head->name == passengerName){
        if(head->next != nullptr){
            Node* temp = head->next;
            delete head;
            head = nullptr;        //now temp->prev should be nullptr
            head = temp;
        }
        else{
            delete head;
            head = nullptr;        //now head & tail should be nullptr
        }
    }

    else{
        Node* temp = head;
        //iterate until you find the target
        while(temp->next->name != passengerName){
            temp = temp->next;
        }//here temp->next == target

        //delete the target node, but reinstate the linked list
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        if(temp->next->next != nullptr){
            temp->next->next->prev = temp;
        }
        delete toDelete;
        toDelete = nullptr;
    }
}

void Transaction::writeToFile(string fileName){
    fstream file;
    file.open(fileName, ios::app);

    if(file.is_open()){
        Node* temp = this->head;
        while(temp != nullptr){
            file << *temp;
            temp = temp->next;
        }
        file << "\nEnd of transactions list\n-----------------------------------------------------\n\n";
    }

    else{
        cout << "ERROR UNABLE TO OPEN FILE\n";
    }
}


ostream & operator << (ostream &out, const Node & node){
    out << "Stop Location: " << node.boardLocation->getName();

    int time = node.time;
    string result = "";
    if((time / 60) < 10){
        result += "0";
    }
    result += to_string(time / 60) + ":";

    if(time % 60 < 10 ){
        result += "0";
    }
    result += to_string(time % 60);

    out << "\tTime: " << result << "\tCustomer: " << node.name << endl;
    return out;
}
