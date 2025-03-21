
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
    // sort(SortedInput.begin(), SortedInput.end(), greater<int>()); //sorts in descending order,
        sort(SortedInput.begin(), SortedInput.end()); //sorts in descending order,

    // cout << vec_to_string(SortedInput) << endl; // for debugging

    return bdc_helper(SortedInput);
};




vector<int> bdc_helper(vector<int> input){

    //base cases
    if(input.size() <= 1){  //if less than or equal to one, there are no more possible conglomerates t0 make. 
        return input; //just return input. 
    }

    vector<vector<int>> candidates; //will store all the possible conglomerates here. 

    for(int i = 0; i < input.size(); i++){ //tries all the different starting points. 

        vector<int> L = {input.at(i)}; //left side (one element)
        for(int j = i + 1; j < input.size(); j++){ //iterates thorugh the rest of the vector 
            if(input.at(j) % input.at(i) == 0){ //test to see if i divides j (indexes)

                //Make a subset from j to the end, and use the subset as the rescursive input 
                vector<int> Rin(input.begin() + j , input.end());
                vector<int> R = bdc_helper(Rin);

                //combine L and R 
                vector<int> combined;
                combined.insert(combined.end(), L.begin(), L.end());
                combined.insert(combined.end(), R.begin(), R.end());
                
                //add the combined vector to the list of possivl candidates: 
                candidates.push_back(combined); 
            }
        }
    }

    int d = 0;  //dumy variable to hold the size of the current largest vector 
    int idx = 0; //index of the above vector ^^
    for (int i = 0; i < candidates.size(); i++){ //iterates through candidates 
        if(candidates.at(i).size() > d){ //if a candidates sixze is greater than the current largest candidate size, make that the new index and largest size 
            idx = i;
            d = candidates.at(i).size();
        }
    }
   
    //if there are no conglomerates larger than one (so no conglomerates), return a vector of the smallest element 
    if(candidates.at(idx).size() <= 1){
        vector<int> result = {input.at(0)};
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


    cout << endl << endl;
    for(int i: BDC){
        cout << i << " ";
    }

    return 0; 
}