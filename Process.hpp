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
		int ITotal;
		int CPUTotal;
		int OTotal;
		int CPUCount;
		int ICount;
		int OCount;
		int Start;
		int End;
	friend	std::ostream &operator << (std::ostream &O, event const &rhs){
		return	O << rhs.ProcessID << " Priority = " << rhs.Priority << "arriving at time = " << rhs.ArrivalTime; 
		}
bool operator <(event const &rhs)const{return Priority < rhs.Priority;}	
		event(int iter, int clock, ifstream &somename); // takes input and puts them into ProcessName, Priority, ArrivalTime, History, and gives ProcessID, sets Sub, timers counts and total to zero.
	event(); //default constructor
		void TimerTick(); // Increment IOTimer 
		void CPUTick(); // increment CPU timer
		void IncCPUTot();
		void IncITot();
		void IncOTot(); //counts how much time was spent doing each
		void ICountTick();
		void OCountTick();
		void CPUCountTick(); //count the number of bursts for the process
		void DataOutput(); //write to screen
void SetEnd();// compute end time
void Debug();
void Begin(int clock);

int Acheck();
};
