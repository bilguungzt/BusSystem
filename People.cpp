#include "People.hpp"

People::People() {
	// TODO Auto-generated constructor stub
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
