//
//  People.cpp
//  Presentation_Bus
//
//  Created by Junyoung Kim on 5/14/24.
//

#include "People.hpp"

People::People() {
	People("GenericFirst", "GenericLast");

}

People::People(string firstName, string lastName)
{
	this->firstName = firstName;
	this->lastName = lastName;
}

string People::getFirstName() const
{
	return this->firstName;
}

string People::getLastName() const{
	return this->lastName;
}

void People::setFirstName(string firstName)
{
	this->firstName = firstName;
}

void People::setLastName(string lastName)
{
	this->lastName = lastName;
}

