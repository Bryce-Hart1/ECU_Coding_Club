/**
*   @attention First meeting coding solutions 
*  If you are new to programming, read this! I left this document with as much information as possible so that 
* No matter your experience level, you can try to understand what we did in the meeting. I will include all 3 solutions 
* For the question. Hard questions do not have as many comments.
* @details compile this code with any c++ compiler. You will get the worse case runtimes (not in list)
*/

#include <iostream> //We use this library to display information to the terminal 
#include <vector> //This gives us access to std::vector, which allows us to store a list of items!
#include <unordered_map> //this gives us access to a hashmap for quick lookups, but this comes with a tradeoff of space.
#include "utility/timer.hpp" //This is timer class that I made. I will not explain it in the demo.
#include <random> //allows us to generate random numbers for test


using namespace bstd::system;
using namespace std;

/* This generates random numbers for our tests, dont worry too much about this function*/
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

/* Prints the time it took to do the work you should see ~minute for first approach with 100,000 inputs,
and then the other inputs should be under a second.*/
void printTime(const std::string_view& message, const std::string& time){
    cout << message << time << endl << '\n';
}


/**
* This is the first approach we talked about that iterates through every possible combination.
*/
bool first_approach(const vector<int>& bankAmountsList, const int& target){
    
    for(int number_one : bankAmountsList){ //for every number in the list
        for(int number_two : bankAmountsList){ //for every number in list
            //compare (one + two = three)
            if(number_one + number_two == target){
                return true; //return if we found our target
            }

        }
    }

    return false;
}

// Sort the amounts once, then walk inward from both ends. If the two
// ends add up to too much, move the right pointer in. If they add up
// to too little, move the left pointer in. O(n log n), dominated by the sort
bool second_approach(vector<int>& amounts, int target){


    sort(amounts.begin(), amounts.end()); //start by sorting all numbers
    int left = 0; //left walking pointer
    int right = (amounts.size()-1); //right walking pointer 
    //collapse on list
    // [] [] [] [] [] [] []
    // ^ pinch the list   ^
    // [] [] [] [] [] [] []
    // ^              ^ <-
    // [] [] [] [] [] [] []
    //  -> ^           ^
    while (left < right) {
        int total = amounts[left] + amounts[right];

        if (total == target) {
            return true;
        } else if (total < target) {
            ++left;
        } else {
            --right;
        }
    }
    return false;
}


/* Save each number in the list if we see it, then we can just add. */
bool third_approach(const vector<int>& bankAmountsList, const int& target){
    unordered_map<int, bool> map;

    for(int number : bankAmountsList){
        int difference = (target - number);
        if(map.count(difference) > 0){
            return true;
        }else{
            map.insert({difference, true});
        }
    }
    return false;
}







int main(){
    timeKeeper timer{};

    vector<int> small = random_numbers(10); 
    vector<int> large = random_numbers(100000);


    const int smallTarget = -1;
    const int largeTarget = -1;
    
    timer.reset();


    
    //worst case lookup for our list. Always account for the worst case runtimes for your algorithms.

    timer.start();
    first_approach(small, smallTarget);
    timer.stop();
    printTime("First Approach on 10 inputs: ", timer.timePassedInAuto()); //print how long it took
    timer.reset();

    //what about 10,000,000 inputs?
    timer.start();
    first_approach(large, largeTarget);
    timer.stop();
    printTime("First Approach on 100,000 inputs: ", timer.timePassedInAuto()); //print how long it took

    timer.reset();

    timer.start();
    second_approach(large, largeTarget);
    timer.stop();
    printTime("Second Approach on 100,000 inputs: ", timer.timePassedInAuto());
    timer.reset();
    //but can we do better?

    timer.start();
    third_approach(large, largeTarget);
    timer.stop();
    printTime("Third Approach on 100,000 inputs: ", timer.timePassedInAuto());

    return 0;
}

