#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

int main() {
  std::ifstream in("input");
  std::string entry;
  std::vector<std::string> log;
  while (std::getline(in, entry)) {
    log.push_back(entry);
  }
  std::sort(log.begin(), log.end());
  std::map<int, std::array<int, 60>> naptimes;
  std::map<int, int> total_asleep;
  int guard_id = 0;
  int the_sleepiest_guard = 0;
  int the_sleepiest_minute = 0;
  int max_counter = 0;
  auto it = log.begin();
  while (it != log.end()) {
    if ((*it).find("Guard") != std::string::npos) {
      guard_id = std::stoi((*it).substr((*it).find('#') + 1));
      if (naptimes.find(guard_id) == naptimes.end()) {
        naptimes[guard_id] = std::array<int, 60>{};
      }
      ++it;
    } else {
      std::string nap_start_entry = *it;
      int begin_nap = std::stoi(nap_start_entry.substr(nap_start_entry.find(':') + 1));
      std::string nap_end_entry = *(++it);
      int end_nap = std::stoi(nap_end_entry.substr(nap_end_entry.find(':') + 1));
      for (int i = begin_nap; i < end_nap; i++) {
        int counter = ++naptimes[guard_id][i];
        if (counter > max_counter) {
          max_counter = counter;
          the_sleepiest_minute = i;
          the_sleepiest_guard = guard_id;
        }
      }
      if (it != log.end()) {
        ++it;
      }
    }
  }
  int result =  the_sleepiest_minute * the_sleepiest_guard;
  std::cout << result << '\n';
}