
#include "bdc.h"
#include <algorithm> // this includes the sort function
#include <iostream>

using namespace std;


string vec_to_string(vector<int> v){


    return "null";
};


vector<int> biggest_divisible_conglomerate(vector<int> input){
    vector<int> SortedInput = input; 
    sort(SortedInput.begin(), SortedInput.end()); //sorts in ascending order,


    return bdc_helper(SortedInput);
};




vector<int> bdc_helper(vector<int> input){

    //base cases
    if(input.size() == 1 || input.size() == 1){
        return input;
    }


    vector<vector<int>> candidates; 
    //itereaters through in descending order because the list is sorted in ascending order. 
    for(int i = input.size() -1; i >= 0; i--){
        // we know that if a>b>c, if b|a and c|b, then c|a

        int start = input.at(i); 
        // vector<int> temp; //(input.begin() + i, input.end()); //makes a subvector 


        vector<int>* temp;
        //iterates throiugh the temp vector (subvector)
        for(int j = i-1; j >= 0; j--){
            if(start % input.at(j) == 0){
                temp = new vector<int>(input.begin() + i, input.end());

                vector<int> R = bdc_helper(*temp);
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

    return candidates.at(idx);
    //still need to implement the dealing with no possivble conglomerates issue (largest or biggest number is valid)

};


void test(){

};

int main(){


    vector<int> test = {28, 22, 7, 2, 8, 14, 24, 56};
    vector<int> BDC = biggest_divisible_conglomerate(test);

    for(int i: BDC){
        cout << i;
    }


    return 0; 
}