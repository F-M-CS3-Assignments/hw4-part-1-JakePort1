
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

    //base cases 
    if(input.size() == 1 || input.size() == 0){
        return input; 
    }


    //makes a vector of potential candidates: 
    vector<vector<int>> candidates; 


    for(int i = 0; i < input.size(); i++){
        vector<int> L = {input[i]};
        vector<int> R;

        int j = index_finder(input, i); //index of next div, -1 of NA 

        if(j==-1){
            R = {}; 
            
        }
        if(j!= -1){
            vector<int> Rin(input.begin() + j, input.end()); 
            R = bdc_helper(Rin); 
        }

        vector<int> combined = L; 
        combined.insert(combined.end(), R.begin(), R.end()); 
        candidates.push_back(combined); 

    }



//old code: 
{
    // //iterates through the differnte starting points of input
    // for(int i = 0; i < input.size(); i++){

    //     vector<int> L = {input[i]}; //creates left side with just one element. 

    //     int j = index_finder(input,i); //finds the index of the next element that is a multiple of i; returns -1 if no such number exists 


    //     if(j != -1){
    //         //creates a sub vector of input from the above index
    //         vector<int> Rin(input.begin() + j, input.end()); 

    //         //using recursion to find a vector of all other multiples satifactory elements in input 
    //         vector<int> R = bdc_helper(Rin); 

    //         //Combines L and R into a vector called combined, then pushes that back to the list of candidates 
    //         vector<int> combined = L; 
    //         combined.insert(combined.end(), R.begin(), R.end());
    //         candidates.push_back(combined); 
    //         cout << vec_to_string(L) << "      " << vec_to_string(R) << "          " << vec_to_string(combined) << endl;
    //     }else{
    //         candidates.push_back(L);
    //     }

    // }




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

    for(int k = 0; k < candidates.size(); k++){
        cout << vec_to_string(candidates[k]) << endl << endl;

    }


    //returns smallest or emtpy lijst if the vector is 1 or 0
    if(currVecSize == 0){
        vector<int> emptyVec = {};
        return emptyVec;
    }
    if(currVecSize == 1){
        vector<int> smallest = {input[0]};
    }

    //otherwise, returns the longest element. 
    return candidates[currIndex];

};


void test(){

    vector<int> unSorted = {5, 3, 2, 4, 1};
    sort(unSorted.begin(), unSorted.end()); 
    vector<int> sorted = {1, 2, 3, 4, 5};

    assert(unSorted == sorted); 





};

int main(){

    test();

    // vector<int> test = {28, 22, 7, 2, 8, 14, 24, 56};

    vector<int> test = {10, 5, 3, 15, 20};
    vector<int> BDC = biggest_divisible_conglomerate(test); 


    cout << "Answer: " << endl;
    cout << vec_to_string(BDC);

    return 0; 
}