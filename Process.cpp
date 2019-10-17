#include "Process.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

void event::DataOutput() {
  cout << "A Procces has terminated.\n";
  cout << "Process ID is " << ProcessID << endl;
  // cout << " Sub " << Sub;
  int w = End - Start - ITotal - OTotal - CPUTotal;
  cout << "Process Name is " << ProcessName << endl;
  cout << "Priority is " << Priority << endl;
  cout << "Total cpu time = " << CPUTotal << " in " << CPUCount << " bursts.\n";
  cout << "Total output time = " << OTotal << " in " << OCount << " bursts\n";
  cout << "Total input time = " << ITotal << " in " << ICount << " bursts\n";
  cout << "Started at " << Start << " Terminated at " << End << endl;
  cout << "Time spent wating " << w << endl;
}
event::event(int iter, int clock, ifstream &somename) {
  ProcessID = iter;
  Start = clock;

  somename >> ProcessName >> Priority >> ArrivalTime;
  for (int h = 0; h < 10; h++) {
    char letter;
    int value;
    somename >> letter >> value;
    History.push_back({letter, value});
  }
  Sub = 0;
  OCount = 0;
  ICount = 0;
  CPUCount = 0;
}
event::event() {
  Priority = 0;
  ProcessID = 0;
};
