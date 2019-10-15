#include "Process.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
void event::TimerTick() { IOTimer += 1; }

void event::CPUTick() { CPUTimer++; }

void event::Begin(int clock) { Start = clock; }

void event::Debug() {
  cout << "PID " << ProcessID << " Sub " << Sub << " History "
       << History[Sub].first << "," << History[Sub].second << endl;
  cout << "IOTimer " << IOTimer << " CPUTimer " << CPUTimer << endl;
}

void event::DataOutput() {
  //  cout << "A Procces has terminated.\n";
  cout << "Process ID is " << ProcessID;
  cout << " Sub " << Sub;

  //  cout << "Process Name is " << ProcessName << endl;
  //  cout << "Priority is " << Priority << endl;
  //  cout << "Total cpu time = " << CPUTotal << " in " << CPUCount << "
  //  bursts.\n"; cout << "Total output time = " << OTotal << " in " << OCount
  //  << " bursts\n"; cout << "Total input time = " << ITotal << " in " <<
  //  ICount << " bursts\n"; cout << "Started at " << Start << " Terminated at "
  //  << End << endl;
  // there needs to be a cout somewhere for time waiting, and start nd end time
}
event::event(int iter, int clock, ifstream &somename) {
  ProcessID = 99 + iter;
  Start = clock;

  somename >> ProcessName >> Priority >> ArrivalTime;
  for (int h = 0; h < 10; h++) {
    char letter;
    int value;
    somename >> letter >> value;
    History.push_back({letter, value});
  }
  Sub = 0;
}
event::event() { Priority = 0; };
