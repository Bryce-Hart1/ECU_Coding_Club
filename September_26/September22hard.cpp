#include<iostream>
#include <random>
#include <unordered_map>
#include<vector>


using namespace std;


std::vector<int> random_numbers(std::size_t n) {
    int min = 100;
    int max = 99999;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(min, max);

    std::vector<int> result(n);
    for (std::size_t i = 0; i < n; ++i) {
        result[i] = dist(rng);
    }
    return result;
}


void printTime(const std::string_view& message, const std::size_t& time){
    cout << message << time << endl;
}



struct customerTransaction{
    string first_name;
    string last_name;
    int transaction;
};





struct Match {
    bool found = false;
    int i = -1;
    int j = -1;
};





// Same first+last name, AND amounts add up to target. O(n^2): every
// transaction checked against every other transaction.
Match find_customer_pair_brute(const std::vector<customerTransaction>& txns, int target) {
    const int n = static_cast<int>(txns.size()); //cast to int from std::size_t
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            //see if the firstname matches the last name.
            bool same_customer = (txns[i].first_name == txns[j].first_name && txns[i].last_name == txns[j].last_name);

            
            if (same_customer && txns[i].transaction + txns[j].transaction == target) {
                return {true, i, j};
            }
        }
    }
    return {};
}


// Combine first + last into one string key, per customer remember every
// amount seen so far. O(n): one pass, O(1) average lookup per transaction.
std::string combine_name(const std::string& first, const std::string& last){
    return first + " " + last;
}

Match find_customer_pair_fast(const std::vector<customerTransaction>& txns, int target) {
    std::unordered_map<std::string, std::unordered_map<int, int>> seen_by_customer;

    for (int i = 0; i < static_cast<int>(txns.size()); ++i) {
        const std::string key = combine_name(txns[i].first_name, txns[i].last_name);
        int complement = target - txns[i].transaction;

        auto& seen = seen_by_customer[key];// creates an empty inner map the first time this name appears
        auto it = seen.find(complement);
        if (it != seen.end()) {
            return {true, it->second, i};
        }

        seen[txns[i].transaction] = i;
    }
    return {};
}

