#include "Process.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
void event::TimerTick() { IOTimer += 1; }

void event::CPUTick() { CPUTimer++; }

void event::IncCPUTot() { CPUTotal += 1; }

void event::IncITot() { ITotal += 1; }

void event::IncOTot() { OTotal += 1; }

void event::ICountTick() { ICount += 1; }

void event::OCountTick() { OCount += 1; }

void event::CPUCountTick() { CPUCount += 1; }

void event::Begin(int clock) { Start = clock; }
int event::Acheck() {
  if (Priority > 0) {
    return ProcessID;
  } else
    return 0;
}

void event::Debug() {
  cout << "PID " << ProcessID << " Sub " << Sub << " History "
       << History[Sub].first << "," << History[Sub].second << endl;
  cout << "IOTimer " << IOTimer << " CPUTimer " << CPUTimer << endl;
}

void event::DataOutput() {
  cout << "A Procces has terminated.\n";
  cout << "Process ID is " << ProcessID;
  // cout << " Sub " << Sub;

  cout << "Process Name is " << ProcessName << endl;
  cout << "Priority is " << Priority << endl;
  cout << "Total cpu time = " << CPUTotal << " in " << CPUCount << "bursts.\n";
  cout << "Total output time = " << OTotal << " in " << OCount << " bursts\n";
  cout << "Total input time = " << ITotal << " in " << ICount << " bursts\n";
  cout << "Started at " << Start << " Terminated at " << End << endl;
  // there needs to be a cout somewhere for time waiting, and start nd end time
}
void event::SetEnd() { End = Start + ITotal + OTotal + CPUTotal; }
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
