#ifndef STOP_HPP_
#define STOP_HPP_

#include <string>

using namespace std;

class Stop {
private:
	Stop* nextStop;		//will point to the next adjacent stop, mapping
	string name;		//name of stop
	int timeToNextStop;	//initialize as time needed to go from this stop to next, no traffic
	int trafficFactor;	//factor to describe traffic level, will be used to update timeToNextStop in real time
						//accepts values of 0-5

//protected:
//	int updateTime();	//returns an updated timeToNextStop based upon trafficFactor
//		// updateTime, setTrafficFactor/NextStop to protected so it can't be done in main
//	void setNextStop(Stop* nextStop);
//	void setTimeToNextStop(int timeToNextStop);
//	void setTrafficFactor(int trafficFactor);
//	void setName(string name);
//	Stop* getNextStop() const;
//	string getName() const;
//	int getTimeToNextStop() const;
//	int getTrafficFactor() const;

public:
	Stop();
	Stop(Stop* nextStop, string name, int timeToNextStop, int trafficFactor = 0);
	Stop(Stop* stop);


//	Should be protected members ?
	int updateTime();	//returns an updated timeToNextStop based upon trafficFactor
			// updateTime, setTrafficFactor/NextStop to protected so it can't be done in main
	void setNextStop(Stop* nextStop);
	void setTimeToNextStop(int timeToNextStop);
	void setTrafficFactor(int trafficFactor);
	void setName(string name);
	Stop* getNextStop() const;
	string getName() const;
	int getTimeToNextStop() const;
	int getTrafficFactor() const;
};

#endif /* STOP_HPP_ */
