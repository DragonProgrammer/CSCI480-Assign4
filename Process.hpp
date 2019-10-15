//#include <Process.cpp>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
using std::ifstream;
using std::string;
using std::vector;
using std::pair;
class event{
	public:
		string ProcessName;
		int Priority;
		int ProcessID;
		int ArrivalTime;
		vector<pair<char /*letter*/,int /*value*/>> History;
		int Sub;
		int IOTimer;
		int CPUTimer;
bool operator <(event const &rhs)const{return Priority < rhs.Priority;}	
		event(int iter, ifstream &somename); // takes input and puts them into ProcessName, Priority, ArrivalTime, History, and gives ProcessID, sets Sub, timers counts and total to zero.
	event(); //default constructor
		void TimerTick(); // Increment IOTimer 
		void CPUTick(); // increment CPU timer
void Debug();

//int Acheck();
};
