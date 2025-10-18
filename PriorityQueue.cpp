

#include "PriorityQueue.hpp"
#include <algorithm>

void PriorityQueue::build(){
    std::sort(entries_.begin(), entries_.end(),
              [](const auto& a, const auto& b){
                  if (a.second != b.second) return a.second > b.second; // frequency desc
                  return a.first < b.first; // tie-breaker: word asc (deterministic)
              }
    );
}