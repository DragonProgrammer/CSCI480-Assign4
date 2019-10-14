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
  int time = 0;

  ifstream Infile;
  Infile.open("testdata");

  //  event Process;

  int clock = 0;
  // vector<event> tasks;
  for (int i = 0; i < 15; i++) {
    Entry.push(event(i, clock, Infile));
  }
  cout << "Simulation start" << endl;
  while (time < MAZTIME) {
    event Process = Entry.front();
    while (Process.ArrivalTime <= time && 6 > IPlay()) {
      Ready.push(Process);

      Entry.pop();
      Process = Entry.front();
    }

    if (time % OFTEN == 0) {
      cout << time << "\t" << IPlay() << endl;
    }
    time++;
  }
  cout << time;

  return 0;
}
