
#include "bdc.h"
#include <algorithm> // this includes the sort function
#include <iostream>
#include <sstream>

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

    //base case
    if(input.size() <= 1){
        return input;
    }

    vector<vector<int>> candidates; 

    for(int i = 0; i < input.size(); i++){

        vector<int> L = {input[i]}; //creates left side
        int j = index_finder(input,i); //finds the next divisor starting at i

        if(j != -1){

            //creates a subvector and gets the Right side conglomerate by using recursion 
            vector<int> R_side(input.begin() + j, input.end()); 
            vector<int> R = bdc_helper(R_side); 

            //cbombines the left and right side vectors 
            vector<int> combined = L;  
            combined.insert(combined.end(), R.begin(), R.end());

            //adds the combined vector to the list of candidates. 
            candidates.push_back(combined); 

        }

    }


    int d = 0;  //dumy variable to hold the size of the current largest vector 
    int idx = 0; //index of the above vector ^^
    for(int i = 0; i < candidates.size(); i++){ //iterates through candidates 
        if(candidates.at(i).size() > d){ //if a candidates sixze is greater than the current largest candidate size, make that the new index and largest size 
            idx = i;
            d = candidates.at(i).size();
        }
    }
   
    //if there are no conglomerates larger than one (so no conglomerates), return a vector of the smallest element 
    if(candidates.at(idx).size() == 1){
        vector<int> result = {input.at(0)};
        return result;
    }else if(candidates.at(idx).size() == 0){
        vector<int> result = {};
        return result;
    }else{ //else, return the vector thats the longest. 
        return candidates.at(idx);
    }
};


void test(){

};

int main(){


    vector<int> test = {28, 22, 7, 2, 8, 14, 24, 56};
    vector<int> BDC = biggest_divisible_conglomerate(test);




  //  vector<int> test2 = {2,4,6,8,24}; 
   // int j = index_finder(test2,0);
   // vector<int> subset(test2.begin() + j, test2.end()); 

   // cout << "index is: " << j << ". Sub vector is: " << vec_to_string(subset); 







    cout << endl << endl;
    for(int i: BDC){
        cout << i << " ";
    }

    return 0; 
}