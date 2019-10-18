/**
 * @author Michael Peterson
 *
 * @section DESCRIPTION
 *
 * In this assignment, we are simulating priority scheduling of processes on a
 * single-processor system.  The idea is that when a process ends its CPU burst
 * (or input burst or output burst), it is succeeded by the highest-priority
 * process that is waiting
 *
 * @section NOTES
 *
 * This functions with the specs but does not match the teacher's output; that
 * was found to NOT match the directions. It more closely matches a "fixed"
 * output. Matching the exact output would require cycle by cycle comparison and
 * tracking of each 'Program' and incrementing. Which "CANT" be done from just
 * the outfile.     Or doing a lot of guesswork.
 *
 */
#include "Process.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#define MAZTIME 500
#define MQ 6 // max things in play
#define OFTEN 25
using std::cout;
using std::endl;
using std::ifstream; // input file stream
using std::priority_queue;
using std::queue;

int VNAME = 0; // wait time named by tired coder
priority_queue<event> Ready, Input,
    Output; // using preimplemented priority queue
queue<event> Entry;
event OActive, IActive, CActive;
int TIME = 0;

/*
 * Moves things to and from an active event.
 *
 * Increments and tracks global variables to simulate process moving into,
 * happening, and moving from the CPU.
 *
 * @section NOTES
 *
 * Moving around when a timer is incremented, is the most likely fix to
 * differances between outputs.
 */
void CPU() {
  if (CActive.Priority == 0) {
    if (Ready.size() == 0) {
      // there is nothing to bring into a Active space
      return;
    }
    CActive = Ready.top();
    CActive.CPUCount++;
    Ready.pop(); // grabbed what was first in ready queue
  } else {
    // icrement apropriet counter
    CActive.CPUTotal++;
    CActive.CPUTimer++;
    if (CActive.History[CActive.Sub].second ==
        CActive.CPUTimer) { // see if it need to move some where
      CActive.Sub++;        // increment to next action
      CActive.CPUTimer = 0;
      char s = CActive.History[CActive.Sub].first;
      switch (s) { // do the action
      case 'I':
        Input.push(CActive); // Into input queue
        CActive = event();
        break;
      case 'O': // into output queue
        Output.push(CActive);
        CActive = event(); // empty active
        break;
      case 'N': // terminate process
        CActive.End = TIME;
        cout << endl;
        CActive.DataOutput();
        CActive = event();
        break;
      default:
        exit(0);
      }
    }
  }
}

/*
 * This does the same ass the CPU function for the Input side
 *
 * See Void CPU() for more disriptiona and coments
 */
void InputP() {
  if (IActive.Priority == 0) {
    if (Input.size() == 0) {
      return;
    }
    IActive = Input.top();
    IActive.ICount++;
    Input.pop();
  } else {
    IActive.ITotal++;
    IActive.IOTimer++;
    if (IActive.History[IActive.Sub].second == IActive.IOTimer) {
      IActive.Sub++;
      IActive.IOTimer = 0;
      char s = IActive.History[IActive.Sub].first;
      switch (s) {
      case 'C': // to ready que
        Ready.push(IActive);
        IActive = event();

        break;
      case 'O':
        Output.push(IActive);
        IActive = event();
        break; // no termination
      default:
        exit(0);
      }
    }
    // was old incement plass
  }
}

/*
 * This does the same ass the CPU function for the Output side
 *
 * See Void CPU() for more disriptiona and coments
 */
void OutputP() {
  if (OActive.Priority == 0) {
    if (Output.size() == 0) {
      return;
    }
    OActive = Output.top();
    OActive.OCount++; //

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
        Input.push(OActive);
        OActive = event();
        break;
      case 'C':
        Ready.push(OActive);
        OActive = event();
        break;
      default:
        cout << "bork O" << OActive.ProcessID << endl;
        exit(0);
      }
      return;
    }
  }
}

/*
 * THis is the que read out for the priority queues.
 *
 * @param Q The priority que being based in so that id and priority can be read
 * out.
 */

void Contents(priority_queue<event> Q) {

  if (Q.size() == 0) {
    cout << "(Empty)" << endl; // if empty say so
  } else {
    vector<event> getsaname;
    while (Q.size() > 0) {
      getsaname.insert(
          getsaname.begin(),
          Q.top()); // reverse the queue to print in example order GRRRRR
      Q.pop();
    }
    for (auto &e : getsaname)
      cout << e.ProcessID << "(" << e.Priority << ")    ";
  }
  cout << endl;
}

/*
 * This reads through the Entry queue
 *
 * Uses an overloaded << from the event class.
 *
 * @param Q The entry queue.
 */

void Contents(queue<event> Q) {
  if (Q.size() == 0) {
    cout << "(Empty)" << endl;
  } else {
    while (Q.size() > 0) {
      event p = Q.front(); // does not rwrse queue
      cout << p << endl;
      Q.pop();
    }
  }
}

/*
 * Tels what is in each location when called.
 *
 * Gives the Id of active processes, and the queues.
 */
void Interval() {

  cout << "Active is " << CActive.ProcessID << endl;
  cout << "IActive is " << IActive.ProcessID << endl;
  cout << "OActive is " << OActive.ProcessID << endl;
  cout << "Contents of the Entry Queue:" << endl;
  Contents(Entry);                                 // cals the que version
  cout << "Contents of the Ready Queue:" << endl;  // the
  Contents(Ready);                                 // rest
  cout << "Contents of the Input Queue:" << endl;  // are
  Contents(Input);                                 // priority
  cout << "Contents of the Output Queue:" << endl; // queue
  Contents(Output);                                // calls
}

/*
 * Gives detales on the total run of the simulator.
 */
void terminate() {
  cout << "The run has ended.\n  The final value of the timer was:" << TIME
       << endl;
  cout << "The amount of time spent idle was: " << VNAME << endl;
  Interval(); // also calls for cont
}

/*
 * Checks how many proces are in ques and active.
 *
 * @return N returns the number of process there are, if more then six tells
 * error
 */
int IPlay() {
  int N = 0;
  // check if there are actives, and add 1 for each
  if (IActive.Priority > 0) {
    N++;
  }
  if (OActive.Priority > 0) { // if priority is not zero something there
    N++;
  }
  if (CActive.Priority > 0) {
    N++;
  }
  N = N + Input.size() + Output.size() + Ready.size();
  if (N > 6) { // debug check
    cout << "To much in play";
    exit(0);
  }
  return N;
}

/*
 * Sets up event objects, entry que and loops throu simulating time.
 *
 * Data is from a file in the form of 2 lines per process. Runs till it gets to
 * a max time or there is nothing active mor in any que.
 */
int main() {

  ifstream Infile;
  Infile.open("testdata"); // open file
  int clock = 0, i = 100;

  for (;;) {
    event temp(++i, clock, Infile);
    if (temp.ProcessName == "STOPHERE") // creat events till end condition
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
      cout << "\nProcess "
           << Process.ProcessID // when moves from entry int o ready
           << " moved from the Entry Queue into the Ready Queue at time "
           << TIME << endl;
      Entry.pop();
      if (Entry.size() == 0) {
        break;
      }
      Process = Entry.front();
    }

    if (TIME % OFTEN ==
        0) { // Header the portion and tell what data is at each time interval
      cout << "\nStatus at time " << TIME << endl;
      Interval();
    }
    CPU();
    InputP();
    OutputP();

    if (IPlay() == 0 && Entry.size() == 0) {
      terminate(); // the no process terminator
      return 0;
    }
    if (CActive.Priority == 0) {
      cout << "At time " << TIME // tell if there is idle time
           << "Active is 0, so we have idle time for a while" << endl;
      VNAME++;
    }

    TIME++; // increment time
  }

  return 0;
}
