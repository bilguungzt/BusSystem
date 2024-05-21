//
//  Transaction.hpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#ifndef TRANSACTION_HPP_
#define TRANSACTION_HPP_

#include "Passenger.hpp"

struct Node{
	//Node members/aspects
	Stop* boardLocation;
	int time;
	string name;
	Node* next;
	Node * prev;

	//constructors
	Node(Stop* boardLocation, int startTime, string name, Node* next, Node* prev){
		this->boardLocation = boardLocation;
		this->time = startTime;
		this->name = name;
		this->next = next;
		this->prev = prev;
	}

	Node(){
		Node(nullptr, 0, "", nullptr, nullptr);
	}

	friend ostream & operator << (ostream &out, const Node & node);
};

class Transaction {
private:
	Node* head;
	Node* tail;
	int size;
	void deleteList(Node* node);
	void displayTime(int time) const;
	void deleteNode(string passengerName);
public:
	Transaction();
	virtual ~Transaction();
	void pushback(Stop* passengerStop, int timeOfSwipe, string passengerName);    //passenger class will send the args
	void pushBack(Node* node);
	void display();
	void displayBackwards();
	void writeToFile(string filename="output.txt");
};

#endif /* TRANSACTION_HPP_ */

