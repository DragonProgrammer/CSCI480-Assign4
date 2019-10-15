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
