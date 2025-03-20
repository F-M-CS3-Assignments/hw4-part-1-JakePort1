
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
    sort(SortedInput.begin(), SortedInput.end(), greater<int>()); //sorts in descending order,
    // cout << vec_to_string(SortedInput) << endl; // for debugging

    return bdc_helper(SortedInput);
};




vector<int> bdc_helper(vector<int> input){

    //base cases
    if(input.size() == 1 || input.size() == 0){
        return input;
    }


    vector<vector<int>> candidates; 
    //itereaters through in descending order because the list is sorted in ascending order. 
    for(int i = 0; i < input.size(); i++){
        // we know that if a>b>c, if b|a and c|b, then c|a

        int start = input.at(i);

        for(int j = i ; j < input.size(); j++){                //i + 1 might not be right        
            if(start % input.at(j) == 0){
                vector<int> temp =  vector<int>(input.begin() + j , input.end());


                //for debugging
                // for (size_t i = 0; i < temp->size(); i++) {
                // cout << temp->at(i) << " ";
                // }
                // cout << endl << endl;




                vector<int> R = bdc_helper(temp);
                vector<int> cand = {start};
                cand.insert(cand.end(), R.begin(), R.end()); // combines the two vectors 
                candidates.push_back(cand);
                break;
            }
        }
    }



    //find the largest vector. 
    int d = 0; 
    int idx = 0;
    int size = 0;
    for (int i = 0; i < candidates.size(); i++){
        if(candidates.at(i).size() > d){
            idx = i;
            size = candidates.at(i).size();
        }
    }

    //debugging purposes:
    for(vector<int> v : candidates){
        cout << vec_to_string(v) << endl;
    }
        
        return candidates.at(idx);
    

    //still need to implement the dealing with no possivble conglomerates issue (largest or biggest number is valid)

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