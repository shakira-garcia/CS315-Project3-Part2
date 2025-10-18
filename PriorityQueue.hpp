
#ifndef P3_PART1_PRIORITYQUEUE_HPP
#define P3_PART1_PRIORITYQUEUE_HPP

#pragma once
#include <string>
#include <vector>
#include <utility>
#include <cstddef>


class PriorityQueue {
public:
    // consume (word,count) pairs
    explicit PriorityQueue(std::vector<std::pair<std::string,std::size_t>> entries = {})
            : entries_(std::move(entries)) {}

    // replace contents
    void set(std::vector<std::pair<std::string,std::size_t>> entries){
        entries_ = std::move(entries);
    }

    // “Build the queue” = sort by (count desc, word asc) deterministically
    void build();

    // access for writing file
    const std::vector<std::pair<std::string,std::size_t>>& entries() const { return entries_; }

private:
    std::vector<std::pair<std::string,std::size_t>> entries_;
};


#endif //P3_PART1_PRIORITYQUEUE_HPP
