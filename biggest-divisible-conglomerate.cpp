// Jacob Port 
// CPS 222
// HW4_part1

#include "bdc.h"
#include <algorithm> // this includes the sort function
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

string vec_to_string(vector<int> v){

    //if vector is empty output []
    if(v.size() == 0){
        return "[ ]";
    }

    ostringstream oSS;
    oSS << "["; //start output here 

    //iterates throug the vector an outputs the element with a comma and space 
    for(int i = 0; i < v.size(); i++){
        if(i < v.size()-1){
            oSS << v.at(i) << ", ";
        }else{
            oSS << v.at(i) << "]"; //end output here 
        }
    }
    return oSS.str(); //return the to string version of oSS
};

vector<int> biggest_divisible_conglomerate(vector<int> input){
    vector<int> SortedInput = input; 
        sort(SortedInput.begin(), SortedInput.end());  //sort in ascending outer 

    return bdc_helper(SortedInput); //call the helper function with the sorted input
};

//helper function to return the index of the next division 
int index_finder(vector<int> vec, int start){

    //iterates through the input from start + 1 to the end, and finds if an element is a multiple of the start element. 
    // then returns that index. Returns -1 if no multiples are found. 
    for(int i = start + 1; i < vec.size(); i++){
        if(vec[i] % vec[start] == 0){
            return i;
        }
    }
    return -1;
}

//Helper function that makes the rescursive logic. 
vector<int> bdc_helper(vector<int> input){

    //base cases if input has no elements or 1 element. 
    if(input.size() == 1 || input.size() == 0){
        return input; 
    }

    //initializes a vector which will store all the candidates: 
    vector<vector<int>> candidates; 

    //Iterates through the input, trying different starting points. 
    for(size_t i = 0; i < input.size(); i++){
        vector<int> L = {input[i]};  //initalizes the "left side" to be the starting element (i)
        vector<int> R; //initalizes the right side vector

        int j = index_finder(input, i); //finds index of next multiple, -1 if NA (i + 1 is built into the function)

        //if no new multiple if found sets the right side to be empty
        if(j==-1){ 
            R = {}; 
            
        }
        //else, creates a subset from the index j to the end of the input. Then calls a recursive function on that subset
        if(j!= -1){
            vector<int> Rin(input.begin() + j, input.end()); 
            R = bdc_helper(Rin); 
        }

        //combines left and right side, but checks to make sure that the elements are multiples of each other: 
        vector<int> combined;
        if (R.size()>0 && R.at(0) % L.at(0) != 0) {
            combined = L;
        }
        else{
            for (size_t i=0; i<L.size();i++){
                combined.push_back(L.at(i));
            }
            for (size_t i=0; i<R.size();i++){
                combined.push_back(R.at(i));
            }
        }
        candidates.push_back(combined);
    }


    //finds the longest vector in candidates. if no vector in longer than one elemnt, it will return the smallest element of input, using 
    // input[0]
    int currVecSize = 0;
    int currIndex = 0;
    for(int i = 0; i < candidates.size(); i++){
        if(candidates[i].size() > currVecSize){
            currVecSize = candidates[i].size();
            currIndex = i;
        }
    }

    //returns smallest or emtpy list if the vector is 1 or 0
    if(currVecSize == 0){
        vector<int> emptyVec = {};
        return emptyVec;
    }
    if(currVecSize == 1){
        vector<int> smallest = {input[0]};
        return smallest;
    }

    //otherwise, returns the longest element. 
    return candidates[currIndex];

};

void test(){

    //tests emtpty vector
    vector<int> test1 = {}; 
    assert(biggest_divisible_conglomerate(test1) == test1); 
    cout <<  "Input: " << vec_to_string(test1) << endl << "Output: " << vec_to_string(biggest_divisible_conglomerate(test1)) << endl << endl;

    //tests if it will return the lowest number if there are no possible conglomerates.
    vector<int> test2 = {3,11, 19,13,17}; 
    vector<int> result2 = {3}; 
    cout <<  "Input: " << vec_to_string(test2) << endl << "Output: " << vec_to_string(biggest_divisible_conglomerate(test2)) << endl << endl;
    assert(biggest_divisible_conglomerate(test2) == result2);

    //test from PDF 
    vector<int> test3 = {28, 22, 7, 2, 8, 14, 24, 56}; 
    vector<int> test3_result = biggest_divisible_conglomerate(test3);
    assert(test3_result.size() == 4); 
    cout <<  "Input: " << vec_to_string(test3) << endl << "Output: " << vec_to_string(test3_result) << endl << endl;


    vector<int> test4 = {10, 5, 3, 15, 20};
    vector<int> test4_result = biggest_divisible_conglomerate(test4); 
    assert(test4_result.size() == 3);
    cout <<  "Input: " << vec_to_string(test4) << endl << "Output: " << vec_to_string(test4_result) << endl << endl;



};

int main(){

    cout << "Starting Testing: " << endl; 
    test();
    cout << "Testing Complete" << endl;


    return 0; 
}