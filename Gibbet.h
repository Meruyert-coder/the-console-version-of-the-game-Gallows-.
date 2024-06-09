#pragma once

#include <iostream>
#include <unordered_set>
#include <fstream>
#include <chrono>
#include <string>
#include <random>
#include <vector>

using namespace std;

class Gibbet {
private:
    ifstream file;
    string word;
    unordered_set<char> guess;
    chrono::steady_clock::time_point startTime;
    chrono::steady_clock::time_point endTime;

    static const vector<string> v;

    string decrypt(const string& input) const;

public:
    Gibbet();
    explicit Gibbet(const string& f_);
    ~Gibbet();

    void Play();
    void displayStatistics() const;
    void displayHangman(int countT) const;
};
