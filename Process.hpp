/*
 * The definition of the event class.
 *
 * Set up so that we can get the aprprient data to the screen such ass ID an name, and use other variable to keep track of where it goes and for how long.
 */

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
		string ProcessName; /*!<The title of the process*/
		int Priority; /*!<What priority it is for the priority queues*/
		int ProcessID; /*!< The process id so that you do not need to always refer to longer name outputs*/
		int ArrivalTime; /*!< A simulation for whe the process is requested*/
		vector<pair<char /*letter*/,int /*value*/>> History; /*!< Records the order of places each process goes and for howlong it is there*/
		int Sub; /*!< Records what spot in history you are at*/
		int IOTimer; /*!< A timer for tracking how long it has been active in the input or output*/
		int CPUTimer;/*!< Tracks how long it is in the cpu this time around*/
		int ITotal; /*!< the total time in imput*/
		int CPUTotal; /*!< ... in CPU */
		int OTotal; /*!< ... in output*/
		int CPUCount; /*!< how many times in cpu*/
		int ICount;/*!< ...in input*/
		int OCount;/*!< ... in output*/
		int Start;/*!< when process moved into ready*/
		int End;/*!< when terminated*/
/*
 * Overloading the << operater to get the correct output we want for ready que.
 */
		friend	std::ostream &operator << (std::ostream &O, event const &rhs){
		return	O << rhs.ProcessID << " Priority = " << rhs.Priority << " arriving at time = " << rhs.ArrivalTime; 
		}
/*
 * Define what bool < means to order the priority queue
 */
		bool operator <(event const &rhs)const{return Priority < rhs.Priority;}	
		event(int iter, int clock, ifstream &somename);// takes input and puts them into ProcessName, Priority, ArrivalTime, History, and gives ProcessID, sets Sub, timers counts and total to zero.
	event(); //default constructor
		void DataOutput(); //write to screen
};
