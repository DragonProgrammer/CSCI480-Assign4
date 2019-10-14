//#include <Process.cpp>
#include <string>
#include <vector>
#include <utility>
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

		void Setdata(int iter, int clock); // parses lines and puts them into ProcessName, Priority, ArrivalTime, History, and gives ProcessID, sets Sub, timers counts and total to zero.
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
};
