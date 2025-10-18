//
// Created by Ali Kooshesh on 9/27/25.
//

#include "Scanner.hpp"

#include <utility>
#include <iostream>
#include <fstream>

#include "utils.hpp"

using std::string;

// Helper: ASCII letter check (per the project spec; no locale or unicode).
static inline bool is_ascii_letter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

// You complete this...
Scanner::Scanner(std::filesystem::path inputPath) : inputPath_(std::move(inputPath)) {}

// Extract a single token from `in`.
// Returns "" if we skipped separators and did not find a letter before EOF.
std::string Scanner::readWord(std::istream& in) {
    string token;

    // c = next character code (lookahead character).
    // It’s an int so it can be any byte 0–255 *or* EOF.
    int c = in.peek();

    // 1) Skip all separators until we reach a letter or EOF.
    while (c != EOF) {
        char ch = static_cast<char>(c);           // ch = current character
        if (is_ascii_letter(ch)) break;           // found start of token
        in.get();                                  // consume the separator
        c = in.peek();                              // refresh c (next character)
    }

    // 2) Build the token: letters with optional INTERNAL apostrophes only.
    while (c != EOF) {
        char ch = static_cast<char>(c);           // ch = current character
        if (is_ascii_letter(ch)) {
            // Normalize to lowercase and consume.
            token.push_back(static_cast<char>(
                                    std::tolower(static_cast<unsigned char>(ch))));
            in.get();                               // consume letter
        } else if (ch == '\'') {
            // Apostrophe: keep it only if it's INTERNAL (surrounded by letters).
            in.get();                               // consume apostrophe
            int nextPeek = in.peek();               // nextPeek = next character code
            if (!token.empty() && nextPeek != EOF &&
                is_ascii_letter(static_cast<char>(nextPeek))) {
                token.push_back('\'');               // keep internal apostrophe
                // Do not consume the next letter here; loop will handle it.
            } else {
                // Apostrophe not internal -> stop this token (don't consume next).
                break;
            }
        } else {
            // Any non-letter ends this token.
            break;
        }
        c = in.peek();                             // refresh c (next character)
    }

    return token;
}

// Tokenize entire input file into `words`.
error_type Scanner::tokenize(std::vector<std::string>& words) {
    std::ifstream in(inputPath_);
    if (!in.is_open()) {
        return UNABLE_TO_OPEN_FILE;                // rely on utils error codes
    }

    words.clear();
    while (true) {
        std::string w = readWord(in);
        if (w.empty()) {
            // If we returned empty and are at EOF, we are done.
            // Otherwise, we likely just skipped separators; keep scanning.
            if (in.peek() == EOF) break;
            continue;
        }
        words.push_back(std::move(w));
        if (in.peek() == EOF) break;               // reached end after last token
    }
    return NO_ERROR;
}
