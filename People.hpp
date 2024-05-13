#ifndef PEOPLE_HPP_
#define PEOPLE_HPP_

#include <string>

using namespace std;

class People {
protected:
	string firstName;
	string lastName;

public:
	People();
	People(string firstName, string lastName);
	string getFirstName() const;
	string getLastName() const;
	void setFirstName(string firstName);
	void setLastName(string lastName);
};

#endif /* PEOPLE_HPP_ */
