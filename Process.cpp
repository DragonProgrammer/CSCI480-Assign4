#include "Process.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
/*
 * Tells data about each proccess after it has terminated.
 *
 * Matches the format of example output.
 */
void event::DataOutput() {
  cout << "A Procces has terminated.\n";
  cout << "Process ID is " << ProcessID << endl;
  // cout << " Sub " << Sub;
  int w = End - Start - ITotal - OTotal -
          CPUTotal; // find the time a process was not doing something, it was
                    // in a que
  cout << "Process Name is " << ProcessName << endl;
  cout << "Priority is " << Priority << endl;
  cout << "Total cpu time = " << CPUTotal << " in " << CPUCount << " bursts.\n";
  cout << "Total output time = " << OTotal << " in " << OCount << " bursts\n";
  cout << "Total input time = " << ITotal << " in " << ICount << " bursts\n";
  cout << "Started at " << Start << " Terminated at " << End << endl;
  cout << "Time spent wating " << w << endl; // output the iddle
}

/*
 * Constructer for creating events from input file.
 *
 * input set up in format:
 * Processname Priority ArrivalTime
 * 10 pairs of C, O, I and a number or N 0
 *
 * @param iter a number that increments for each event made
 * @param clock TIME being pased in
 * @param &somename the file stream being pasted in.
 * */
event::event(int iter, int clock, ifstream &somename) {
  ProcessID = iter; // crate a differnt number for each
  Start = clock;

  somename >> ProcessName >> Priority >> ArrivalTime;
  for (int h = 0; h < 10; h++) { // for the 10 items
    char letter;
    int value;
    somename >> letter >> value;        // read each pair in
    History.push_back({letter, value}); // put in vector
  }
  Sub = 0;
  OCount = 0; // other stuff needing to be zero firs
  ICount = 0;
  CPUCount = 0;
}
/*
 * COnstructoer for a black event.
 *
 * Used to remove an event when dead, moved to a diferent queue, or as a place
 * an event will be put later
 */
event::event() {
  Priority = 0;
  ProcessID = 0;
};
