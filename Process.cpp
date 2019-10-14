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

void event::Debug() {
  cout << "Name\t" << ProcessName << endl;
  cout << "Priority\t" << Priority << endl;
  cout << "ID\t" << ProcessID << endl;
  cout << "Arrival\t" << ArrivalTime << endl;
  for (auto &e : History) {
    cout << "(" << e.first << "," << e.second << ")  ";
  }
  // more for later
}

void event::Begin(int clock) { Start = clock; }

void event::DataOutput() {
  cout << "A Procces has terminated.\n";
  cout << "Process ID is " << ProcessID << endl;
  cout << "Process Name is " << ProcessName << endl;
  cout << "Priority is " << Priority << endl;
  cout << "Total cpu time = " << CPUTotal << " in " << CPUCount << " bursts.\n";
  cout << "Total output time = " << OTotal << " in " << OCount << " bursts\n";
  cout << "Total input time = " << ITotal << " in " << ICount << " bursts\n";
  cout << "Started at " << Start << " Terminated at " << End << endl;
  // there needs to be a cout somewhere for time waiting, and start nd end time
}
void event::SetEnd() { End = Start + ITotal + OTotal + CPUTotal; }
void event::Setdata(int iter, int clock) {
  ProcessID = 99 + iter;
  Start = clock;
  //	int  L=F.find(" ");
  //	ProcessName = F.substr(0,L);
  //	F.erase(0,L+1);
  // L=F.find(" ");
  //	Priority = F.substr(0,L); //need string to int?
  //	F.erase(0,L+1);
  //	ArrivalTime = F;

  //		string S=l2;
  cin >> ProcessName >> Priority >> ArrivalTime;
  for (int h = 0; h < 15; h++) {
    //	History[h][0]=strtok(S, " ");
    //	History[h][1]=strtok(S, " ");
    char letter;
    int value;
    cin >> letter >> value;
    History.push_back({letter, value});
  }
  Sub = 0;
  // while ((int r=strtok(S, " ")) >0){ // should loop through strings till no
  // more spaces
}
