
#include "bdc.h"
#include <algorithm> // this includes the sort function
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;


string vec_to_string(vector<int> v){

    ostringstream oSS;
    oSS << "[";

    for(int i = 0; i < v.size(); i++){
        if(i < v.size()-1){
            oSS << v.at(i) << ", ";
        }else{
            oSS << v.at(i) << "]";
        }
    }
    return oSS.str();
};


vector<int> biggest_divisible_conglomerate(vector<int> input){
    vector<int> SortedInput = input; 
        sort(SortedInput.begin(), SortedInput.end()); 

    // cout << vec_to_string(SortedInput) << endl; // for debugging

    return bdc_helper(SortedInput);
};





//helper function to return the index of the next division 
int index_finder(vector<int> vec, int start){

    for(int i = start + 1; i < vec.size(); i++){
        if(vec[i] % vec[start] == 0){
            return i;
        }
    }
    return -1;
}


vector<int> bdc_helper(vector<int> input){
    cout << "input: " << vec_to_string(input) << endl << endl << endl;

    //base cases 
    if(input.size() == 1 || input.size() == 0){
        return input; 
    }

    //makes a vector of potential candidates: 
    vector<vector<int>> candidates; 


    for(int i = 0; i < input.size(); i++){
        vector<int> L = {input[i]}; cout << " (left esablished as " << input[i] << " on i = " << i << endl;
        vector<int> R;

        int j = index_finder(input, i); //index of next div, -1 of NA (i + 1 is built into the function)

        if(j==-1){
            R = {}; 
            
        }
        if(j!= -1){
            cout << "recursive call (i = " << i << "): " << endl;
            vector<int> Rin(input.begin() + j, input.end()); 
            R = bdc_helper(Rin); 
        }

        vector<int> combined = L; 
        combined.insert(combined.end(), R.begin(), R.end()); 
        candidates.push_back(combined); 

        cout<< i << ":    " << vec_to_string(L) << "<-------->" << vec_to_string(R) << endl;

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

    // for debugging

    // for(int k = 0; k < candidates.size(); k++){
    //     cout << vec_to_string(candidates[k]) << endl << endl;

    // }


    //returns smallest or emtpy lijst if the vector is 1 or 0
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

    vector<int> test1 = {}; 
    assert(biggest_divisible_conglomerate(test1) == test1); 

    vector<int> test2 = {3,11}; 
    vector<int> result2 = {3}; 

    assert(biggest_divisible_conglomerate(test2) == result2);
};

int main(){


    // vector<int> test = {28, 22, 7, 2, 8, 14, 24, 56};

    vector<int> test = {9, 10, 5, 3, 15, 20};
    vector<int> BDC = biggest_divisible_conglomerate(test); 


    cout << "Answer: " << endl;
    cout << vec_to_string(BDC);

    return 0; 
}