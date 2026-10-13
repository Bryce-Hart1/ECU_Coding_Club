#include <algorithm> 
#include <array>
#include <functional> 
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//prints any container (works for both array and vector)
template <typename Container>
void print(const string& label, const Container& c){
    cout << label << ": ";
    for(int x : c) cout << x << " ";
    cout << "\n";
}

int main(){
    cout << endl << endl;


    std::array<int, 6> dates = {2010, 2015, 2014, 2000, 1999, 1980};
    
    
    vector<int> year_vector{};
    array<int, 4> year_arr{};



    auto date = dates[0];

    year_vector.push_back(date); //push one element
    year_arr.at(0) = date;

    cout << "Total size for Array: " << year_arr.max_size() << "\n";

    cout << "Total size for vector: " << year_vector.capacity() << "\n" << endl;


    //sorting with one element assigned to each container
    cout << "--- std::sort with one element in each ---\n";
    print("Array  before sort", year_arr);
    print("Vector before sort", year_vector);

    sort(year_arr.begin(), year_arr.end());
    sort(year_vector.begin(), year_vector.end());

    print("Array  after sort ", year_arr);     // the unused 0s move to the front
    print("Vector after sort ", year_vector);  // only the 1 real element
    cout << "Array size after sort:  " << year_arr.size() << "\n";
    cout << "Vector size after sort: " << year_vector.size() << "\n\n";


    for(int date : dates){
        year_vector.push_back(date);
    }

    cout << "Total size for vector after adding all dates: " << year_vector.capacity() << "\n";

    //sorting the full vector, ascending then descending
    cout << "\n--- std::sort on the full vector ---\n";
    print("Before sort", year_vector);

    sort(year_vector.begin(), year_vector.end());


    print("Ascending  ", year_vector);

    sort(year_vector.begin(), year_vector.end(), greater<int>());




    print("Descending ", year_vector);

    cout << endl << endl << endl;

    //another example showing the vector change
    year_vector.clear();
    year_vector.shrink_to_fit();
    int current_size;
    for(int i = 0; i < 100'000; i++){
        year_vector.push_back(i); //push back a number
        if(i == 0){
            cout << "Starting size: " << year_vector.capacity() << endl;
            current_size = year_vector.capacity();
        }
        if(current_size != year_vector.capacity()){
            current_size = year_vector.capacity();
            cout << "Size updated! " << ':' << current_size << endl;
        }
        
    }


}