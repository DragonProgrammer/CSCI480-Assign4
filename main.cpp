#include "Process.hpp"

int main() {
  int clock = 0;
  vector<event> tasks;
  for (int i = 0; i < 15; i++) {
    tasks.Setdata(i, clock);
    tasks.push_back();
  }
  `` for (auto &a : tasks) { a.Debug(); }

  return 0;
}
