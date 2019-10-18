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
int VNAME;
priority_queue<event> Ready, Input, Output;
queue<event> Entry;
event OActive, IActive, CActive;
int TIME = 0;

void CPU() {
  if (CActive.Priority == 0) {
    if (Ready.size() == 0) {

      // cout << "Nothing to beecome active" << endl;
      return;
    }
    CActive = Ready.top();
    CActive.CPUCount++;
    cout << "\n to active " << CActive.ProcessID << " at " << TIME << endl;
    Ready.pop();
  } else {

    CActive.CPUTotal++;

    CActive.CPUTimer++;

    if (CActive.History[CActive.Sub].second == CActive.CPUTimer) {
      //  cout << CActive.Sub << " ";
      CActive.Sub++;
      // cout << CActive.Sub << endl;
      CActive.CPUTimer = 0;
      char s = CActive.History[CActive.Sub].first;
      switch (s) {
      case 'I':
        Input.push(CActive); //      cout << "\nmoved to input" << endl;
        cout << "\n to Input " << CActive.ProcessID << " at " << TIME << endl;
        CActive = event();
        break;
      case 'O':
        Output.push(CActive); //      cout << "\nmoved to output" << endl;
        cout << "\n to output " << CActive.ProcessID << " at " << TIME << endl;
        CActive = event();
        break;
      case 'N':

        CActive.End = TIME;
        cout << endl;
        CActive.DataOutput();
        cout << "Terminate " << CActive.ProcessID << endl;
        CActive = event();
        break;
      default:
        cout << "bork C" << endl;
        exit(0);
      }
      //       CActive = event();
    } // else { // cout << "incremented ";
  }
  // CActive.CPUTotal++;

  // CActive.CPUTimer++;
}

void InputP() { // 60 - 90
                // IActive.debug();
  if (IActive.Priority == 0) {
    if (Input.size() == 0) {
      return;
    }
    IActive = Input.top();
    IActive.ICount++;
    cout << "\n to IActive " << IActive.ProcessID << " at " << TIME << endl;
    //  cout << "\n to Iactive" << IActive.ProcessID << endl;
    Input.pop();
  } else {

    IActive.ITotal++;
    IActive.IOTimer++;

    if (IActive.History[IActive.Sub].second == IActive.IOTimer) {
      IActive.Sub++;
      IActive.IOTimer = 0;
      char s = IActive.History[IActive.Sub].first;
      switch (s) {
      case 'C':
        Ready.push(IActive); //      cout << "\nmoved to input" << endl;
        cout << "\n From IActive to Ready " << IActive.ProcessID << " at "
             << TIME << endl;
        IActive = event();

        break;
      case 'O':
        Output.push(IActive); //      cout << "\nmoved to output" << endl;
        cout << "\n to Output " << IActive.ProcessID << " at " << TIME << endl;
        IActive = event();
        break;
      default:
        cout << "bork I" << endl;
        exit(0);
      }

      //  IActive = event();
    }
    // IActive.ITotal++;
    // IActive.IOTimer++;
  }
  // IActive.debug();
}

void OutputP() { // 95 - 125
  if (OActive.Priority == 0) {
    if (Output.size() == 0) {
      return;
    }
    OActive = Output.top();
    OActive.OCount++; //

    cout << "\n to Oactive " << OActive.ProcessID << " at " << TIME << endl;
    Output.pop();
  } else {
    OActive.OTotal++;
    OActive.IOTimer++;
    if (OActive.History[OActive.Sub].second == OActive.IOTimer) {
      OActive.Sub++;
      OActive.IOTimer = 0;
      char s = OActive.History[OActive.Sub].first;
      switch (s) {
      case 'I':
        Input.push(OActive); //      cout << "\nmoved to input" << endl;
        cout << "\n to Input " << OActive.ProcessID << " at " << TIME << endl;
        OActive = event();
        break;
      case 'C':
        Ready.push(OActive); //      cout << "\nmoved to output" << endl;
        cout << "\n from Oactive to Ready " << OActive.ProcessID << " at "
             << TIME << endl;
        OActive = event();
        break;
      default:
        cout << "bork O" << OActive.ProcessID << endl;
        exit(0);
      }
      //      OActive = event();
      return;
    }
  }
}
void Contents(priority_queue<event> Q) {
  // cout << Q.size() << endl;

  if (Q.size() == 0) {
    cout << "(Empty)" << endl;
  } else {
    vector<event> getsaname;
    while (Q.size() > 0) {
      getsaname.insert(getsaname.begin(), Q.top());
      Q.pop();
    }
    for (auto &e : getsaname)
      cout << e.ProcessID << "(" << e.Priority << ")    ";
  }
  cout << endl;
}

void Contents(queue<event> Q) {
  if (Q.size() == 0) {
    cout << "(Empty)" << endl;
  } else {
    while (Q.size() > 0) {
      event p = Q.front();
      cout << p << endl;
      Q.pop();
      //  p = Q.front();
    }
  }
}
// This gives the output of status for the requested interval of OFTEN
void Interval() {

  cout << "Active is " << CActive.ProcessID << endl;
  // CActive.Debug();
  cout << "IActive is " << IActive.ProcessID << endl;
  // IActive.Debug();
  cout << "OActive is " << OActive.ProcessID << endl;
  // OActive.Debug();
  cout << "Contents of the Entry Queue:" << endl;
  Contents(Entry);
  cout << "Contents of the Ready Queue:" << endl;
  Contents(Ready);
  cout << "Contents of the Input Queue:" << endl;
  Contents(Input);
  cout << "Contents of the Output Queue:" << endl;
  Contents(Output);
}

void terminate() {
  cout << "The run has ended.\n  The final value of the timer was:" << TIME
       << endl;
  cout << "The amount of time spent idle was: " << VNAME << endl;
  Interval();
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
  int clock = 0, i = 100;

  for (;;) {
    event temp(++i, clock, Infile);
    if (temp.ProcessName == "STOPHERE")
      break;
    Entry.push(temp);
  }
  cout << "Simulation of Priority Scheduling" << endl;

  event Process = Entry.front();
  while (TIME < MAZTIME) { // outer loo[
    while (Process.ArrivalTime <= TIME && 6 > IPlay() &&
           Entry.size() > 0) { // move into ready que
      Ready.push(Process);
      Process.Start = TIME;
      cout << "\nProcess " << Process.ProcessID
           << " moved from the Entry Queue into the Ready Queue at time "
           << TIME << endl;
      Entry.pop();
      if (Entry.size() == 0) {
        break;
      }
      Process = Entry.front();
    }

    if (TIME % OFTEN == 0) {
      cout << "\nStatus at time " << TIME << endl;
      Interval();
    }
    CPU();
    InputP();
    OutputP();
    if (CActive.ProcessID == 32767)
      cout << "32767 in Active" << endl;
    if (IActive.ProcessID == 32767)
      cout << "32767 in IActive" << endl;
    if (OActive.ProcessID == 32767)
      cout << "32767 in OActive" << endl;

    if (IPlay() == 0 && Entry.size() == 0) {
      terminate();
      //   cout << "End " << TIME << endl;
      return 0;
    }
    TIME++;
  }
  cout << TIME;

  return 0;
}
