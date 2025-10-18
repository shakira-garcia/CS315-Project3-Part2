Project 3 — Part 2 (Huffman Tree)
Student Information

Name: Shakira Garcia
Student ID: 008218438
Repository Link:https://github.com/shakira-garcia/CS315-Project3-Part2.git

Collaboration & Sources

This project is my own work except for provided starter utilities and places I clearly note outside help.

Starter utilities: utils.hpp/.cpp and Blue script locations were provided.

AI use (ChatGPT): I used ChatGPT to help with make my comments more understandable, to outline the Part 2 structure (Scanner → BST → PriorityQueue), and to explain the explicit constructor choice

Part 2 links I used for concepts/refreshers:

https://www.geeksforgeeks.org/cpp/utility-in-c/

https://www.geeksforgeeks.org/dsa/priority-queue-set-1-introduction/

https://www.geeksforgeeks.org/dsa/binary-search-tree-data-structure/

https://www.geeksforgeeks.org/cpp/use-of-explicit-keyword-in-cpp/

https://www.geeksforgeeks.org/cpp/range-based-loop-c/

https://stackoverflow.com/questions/29859796/c-auto-vs-auto

Implementation Details
Overview

Part 2 extends Part 1 by:

Tokenizing the input file (Scanner) → vector of words (also writes <base>.tokens).

Building a BST of word frequencies (average O(log n) inserts).

Converting the BST to a vector of (word, count) and using a PriorityQueue implemented as vector + sort (no heap yet) to sort by count desc, word asc, then writing <base>.freq.

Printing five BST measures to stdout in the exact order:

BST height: H
BST unique words: U
Total tokens: T
Min frequency: MIN
Max frequency: MAX


Empty input produces empty .tokens/.freq and zeros for all measures.

BST (new in Part 2)

Insert each token; on duplicate, increment its count.

Inorder traversal returns std::vector<std::pair<std::string, size_t>> sorted lexicographically by word.

Measures:

height() — empty tree height defined as 0 (per this assignment).

uniqueCount() — number of distinct words.

minFrequency()/maxFrequency() — 0 if tree empty.

PriorityQueue (vector + sort)

Stores (word, count) entries in a std::vector.

build() sorts deterministically: count desc, then word asc (tie-breaker).

Output: writes one word count per line to input_output/<base>.freq.

Design Notes

bst.toVector() returns word-sorted pairs; PriorityQueue::build() reorders them by frequency for .freq.

I used range-based for loops where appropriate for clarity and safety.

I kept the single-parameter constructor of PriorityQueue explicit to avoid accidental implicit conversions from a plain vector (see Testing note below).

Testing & Status
What works

Program requires exactly one argument: the input .txt (expected under input_output/).

Verifies input_output/ exists, input file is readable, and both output files are writable.

Writes input_output/<base>.tokens and input_output/<base>.freq.

Prints the five BST measures in the exact required format.

Handles empty input (both files empty; all measures 0).

C++ allows implicit conversion from a matching vector to a class with a single-argument constructor. To prevent accidental conversions in calls/assignments and make intent clear, I declared:
- explicit PriorityQueue(std::vector<std::pair<std::string, std::size_t>> entries = {});


Build/Run (local)
g++ -std=c++20 -Wall *.cpp -o huffman_part2
./huffman_part2 input_output/YourInput.txt

Testing on Blue (Part 2)

One-time setup in your project directory:

cp /home/faculty/kooshesh/cs315_fall2025/project3/part2/copy_files.bash .
cp /home/faculty/kooshesh/cs315_fall2025/project3/part2/compile_and_test_project3_part2.bash .


Copy sample inputs:

bash copy_files.bash
# places sample .txt files into input_output/


Compile, run, compare (runs on all files in input_output/):

bash compile_and_test_project3_part2.bash

