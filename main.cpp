#include "Process.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#define MAZTIME 500
#define MQ 6
#define OFTEN 1
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
  if (CActive.Priority == 0) {
    if (Ready.size() == 0) {

      cout << "Nothing to beecome active" << endl;
      return;
    }
    CActive = Ready.top();
    Ready.pop();
  } else if (CActive.History[CActive.Sub].second == CActive.CPUTimer) {
    CActive.Sub++;
    CActive.CPUTimer = 0;
    char s = CActive.History[CActive.Sub].first;
    switch (s) {
    case 'I':
      Input.push(CActive); //      cout << "\nmoved to input" << endl;
      break;
    case 'O':
      Output.push(CActive); //      cout << "\nmoved to output" << endl;
      break;
    case 'N':
      cout << "Terminate " << CActive.ProcessID << endl;
      break;
    default:
      cout << "bork C" << endl;
      exit(0);
    }
    CActive = event();
  } else { // cout << "incremented ";
    CActive.CPUTick();
  }
}

void InputP() { // 60 - 90
                // IActive.debug();
  if (IActive.Priority == 0) {
    if (Input.size() == 0) {
      cout << "nothing for IActive" << endl;
      return;
    }
    IActive = Input.top();
    Ready.pop();
  } else if (IActive.History[IActive.Sub].second == IActive.IOTimer) {
    IActive.Sub++;
    IActive.IOTimer = 0;
    char s = IActive.History[OActive.Sub].first;
    switch (s) {
    case 'C':
      Ready.push(IActive); //      cout << "\nmoved to input" << endl;
      break;
    case 'O':
      Output.push(IActive); //      cout << "\nmoved to output" << endl;
      break;
    case 'N':
      cout << "Terminate " << IActive.ProcessID << endl;
      break;
    default:
      cout << "bork I" << endl;
      exit(0);
    }
    IActive = event();
  } else { // cout << "incremented ";
    IActive.TimerTick();
  }
}

void OutputP() { // 95 - 125
  if (OActive.Priority == 0) {
    if (Output.size() == 0) {
      return;
    }
    OActive = Output.top();
    Ready.pop();
  } else if (OActive.History[OActive.Sub].second == OActive.IOTimer) {
    OActive.Sub++;
    OActive.IOTimer = 0;
    char s = OActive.History[OActive.Sub].first;
    switch (s) {
    case 'I':
      Input.push(OActive); //      cout << "\nmoved to input" << endl;
      break;
    case 'C':
      Ready.push(OActive);
      break;
    case 'N':
      cout << "Terminate " << OActive.ProcessID << endl;
      break;
    default:
      cout << "bork O" << OActive.ProcessID << endl;
      exit(0);
    }
    OActive = event();
    return;
  } else {
    OActive.TimerTick();
  }
}

void Contents(priority_queue<event> Q) {
  if (Q.size() == 0) {
    cout << "(Empty)" << endl;
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
      cout << p.ProcessID << "(" << p.Priority << ")  ";
      Q.pop();
      p = Q.front();
    }
  }
  cout << endl;
}
// This gives the output of status for the requested interval of OFTEN
void Interval() {
  cout << "Status at time " << TIME << endl;

  cout << "Active is " << CActive.ProcessID << endl;
  if (CActive.Priority > 0) {
    CActive.Debug();
  }
  cout << "IActive is " << IActive.ProcessID << endl;
  if (IActive.Priority > 0) {
    IActive.Debug();
  }
  cout << "OActive is " << OActive.ProcessID << endl;
  if (OActive.Priority > 0) {
    OActive.Debug();
  }
  cout << "The entry QUEUE is:" << endl;
  Contents(Entry);
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
  }
  if (OActive.Priority > 0) {
    N++;
  }
  if (CActive.Priority > 0) {
    N++;
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

  for (int i = 0; i < 3; i++) {
    Entry.push(event(i, Infile));
  }
  cout << "Simulation start" << endl;

  event Process = Entry.front();
  while (TIME < MAZTIME) { // outer loo[
    while (Process.ArrivalTime <= TIME && 6 > IPlay() &&

           Entry.size() > 0) { // move into ready que
      Ready.push(Process);
      cout << "At " << TIME << " process " << Process.ProcessID
           << " Moved from Entry Queue to Ready Queue" << endl;
      Entry.pop();
      if (Entry.size() == 0) {
        cout << "Nothing left in Entry" << endl;
        break;
      }
      Process = Entry.front();
    }

    if (TIME % OFTEN == 0) {
      Interval();
    }

    CPU();
    InputP();
    OutputP();
    TIME++;
  }
  cout << TIME;

  return 0;
}
