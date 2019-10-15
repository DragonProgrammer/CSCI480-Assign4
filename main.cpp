#include "Process.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#define MAZTIME 500
#define MQ 6
#define OFTEN 25
using std::cout;
using std::endl;
using std::ifstream; // input file stream
using std::priority_queue;
using std::queue;

priority_queue<event> Ready, Input, Output;
queue<event> Entry;
event OActive, IActive, CActive;
int TIME = 0;
void CPU() {
  if (CActive.Acheck() == 0) {
    CActive = Ready.top();
    cout << "\nMoved to active" << CActive.ProcessID << endl;
    Ready.pop();
  } else if (CActive.History[CActive.Sub].second == CActive.CPUTimer) {
    //  cout << CActive.Sub << " ";
    CActive.Sub++;
    // cout << CActive.Sub << endl;
    CActive.CPUTimer = 0;
    char s = CActive.History[CActive.Sub].first;
    switch (s) {
    case 'I':
      Input.push(CActive);
      cout << "\nmoved to input" << endl;
      break;
    case 'O':
      Output.push(CActive);
      cout << "\nmoved to output" << endl;
      break;
    case 'N':
      cout << "Terminate " << CActive.ProcessID << endl;
      break;
    default:
      cout << "bork" << endl;
      exit(0);
    }
    CActive = event();
  } else { // cout << "incremented ";
    CActive.IncCPUTot();
    CActive.CPUTick();
  }
}

void Contents(priority_queue<event> Q) {
  if (Q.size() == 0) {
    cout << "(Empty)";
  } else {
    event p = Q.top();
    while (Q.size() > 0) {
      cout << p.ProcessID << "(" << p.Priority << ")  ";
      Q.pop();
      p = Q.top();
    }
    cout << endl;
  }
}

void Contents(queue<event> Q) {
  if (Q.size() == 0) {
    cout << "(Empty)";
  } else {
    event p = Q.front();
    while (Q.size() > 0) {
      cout << p << endl;
      Q.pop();
      p = Q.front();
    }
  }
}
// This gives the output of status for the requested interval of OFTEN
void Interval() {
  cout << "Status at time " << TIME << endl;
  int C = CActive.Acheck(), O = OActive.Acheck(), I = IActive.Acheck();

  cout << "Active is " << C << endl;
  cout << "IActive is " << I << endl;
  cout << "OActive is " << O << endl;
  cout << "The entry QUEUE is:" << endl;
  // Contents(Entry);
  cout << "The ready QUEUE is:" << endl;
  Contents(Ready);
  cout << "The input QUEUE is:" << endl;
  Contents(Input);
  cout << "The output QUEUE is:" << endl;
  Contents(Output);
}
int IPlay() {
  int N = 0;
  // check if there are actives, and add 1 for each
  if (IActive.Priority > 0) {
    N++;
    ;
  }
  if (OActive.Priority > 0) {
    N++;
    ;
  }
  if (CActive.Priority > 0) {
    N++;
    ;
  }
  // add in sizes
  N = N + Input.size() + Output.size() + Ready.size();
  if (N > 6) { // debug check
    cout << "To much in play";
    exit(0);
  }
  return N;
}

int main() {

  ifstream Infile;
  Infile.open("testdata");
  int clock = 0;
  // vector<event> tasks;
  for (int i = 0; i < 15; i++) {
    Entry.push(event(i, clock, Infile));
  }
  cout << "Simulation start" << endl;
  while (TIME < MAZTIME) { // outer loo[
    event Process = Entry.front();
    while (Process.ArrivalTime <= TIME && 6 > IPlay()) { // move into ready que
      Ready.push(Process);
      Process.Start = TIME;
      cout << "At " << Process.Start << " process " << Process.ProcessID
           << " Moved from Entry Queue to Ready Queue" << endl;
      Entry.pop();
      Process = Entry.front();
    }

    if (TIME % OFTEN == 0) {
      //     Interval();
    }

    CPU();

    TIME++;
  }
  cout << TIME;

  return 0;
}
