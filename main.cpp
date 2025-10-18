#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "Scanner.hpp"
#include "utils.hpp"
#include "BST.hpp"
#include "PriorityQueue.hpp"


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileName = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);

    // build the path to the .tokens output file.
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";
    const std::string wordFreqFileName   = dirName + "/" + inputFileBaseName + ".freq"; //added

    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
     if( error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR )
        exitOnError(status, inputFileName);


    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    if (error_type status; (status = canOpenForWriting(wordFreqFileName)) != NO_ERROR)     // added
        exitOnError(status, wordFreqFileName);

    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName); // create a file system path using the output file.

    //fixed bug the auto fileToWords
    // for README.md trying to figure out how to construct Scanner with output
    //.tokens instead of input .txt
    auto fileToWords = Scanner(std::filesystem::path(inputFileName));

    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
	    exitOnError(status, inputFileName);

    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    // 2) BST: build frequencies from tokens
    BST bst;
    bst.buildFromTokens(words);

    // 3) Print BST measures (exact labels/order)
    std::size_t H   = bst.height();
    std::size_t U   = bst.uniqueCount();
    std::size_t T   = words.size();
    std::size_t MIN = bst.minFrequency();
    std::size_t MAX = bst.maxFrequency();

    std::cout << "BST height: "      << H   << "\n";
    std::cout << "BST unique words: " << U   << "\n";
    std::cout << "Total tokens: "     << T   << "\n";
    std::cout << "Min frequency: "    << MIN << "\n";
    std::cout << "Max frequency: "    << MAX << "\n";

    // 4) PriorityQueue: sort by (count desc, word asc), then write .freq
    //order is lexicographic by *word* (because it's an inorder traversal of the BST)
    auto freqVec = bst.toVector();
    PriorityQueue pq(std::move(freqVec));
    pq.build();                                // sort by count desc, word asc

    {
        std::ofstream out(wordFreqFileName);   // overwrite if exists
        if (!out.is_open())
            exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, wordFreqFileName);

        for (const auto &entry : pq.entries()) {
            // entry.first is the *word* (std::string)
            // binding a const reference (&) avoids copying the string
            const std::string &w = entry.first;
            // entry.second is the *count* (std::size_t)
            std::size_t c = entry.second;
            out << w << " " << c << "\n";
            if (!out) {
                std::cerr << "Error: failed while writing to " << wordFreqFileName << "\n";
                return FAILED_TO_WRITE_FILE;
            }
        }
    }

    return 0;
}
