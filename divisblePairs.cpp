#include <iostream>
#include <vector>
#include <string> 
#include <algorithm> // outsourcing the sort algorithm
#include <cassert>
using namespace std;

void checkList(vector<int> vector){
    for(size_t i = 0; i< vector.size()-1; i++){
        if(vector.at(i) == vector.at(i+1)){
            cout << "WHY?";
            exit(1);
        }
        if(vector.at(i) < 1){
            cout << "WHY?";
            exit(2);
        }
    }
}

vector<int> revSort(vector<int> &vector){
    std::sort(vector.begin(), vector.end());
    std::reverse(vector.begin(), vector.end());
    return vector;
}


vector<int> subVec(vector<int> vector,unsigned int start,unsigned int end){
    std::vector<int> subVec;
    for(size_t i = start; i < end; i++){
        subVec.push_back(vector.at(i));
    }
    return subVec;
}

// used for debugging, not called in main()
string vector_to_string(vector<int> numList){
    string numString ("[");
    if(numList.size() == 0){
        return "[]";
    }
    for (size_t i = 0; i < numList.size();i++){
        numString += to_string(numList.at(i)); 
        if(i != numList.size()-1){numString += ',';}
    }
    numString += "]";
    return numString;
}

//given a vector, returns the index of the first number that is evenly divisible by the target number
int divIndex(vector<int> vector){
    
    if(vector.size() == 0){
        return -1;
    }

    int largest = vector.at(0);

    for(size_t i = 1; i < vector.size(); i++){
        int curr = vector.at(i);
        if (largest % curr == 0){
            return i;
        }
    }
    return -1;
}

//adds values of one vector to another
vector<int> addVec(vector<int> one, vector<int> two){
    for(size_t i = 0; i < two.size(); i++){
        one.push_back(two.at(i));
    }
    return one;
}

vector<int> largest_divisible_pairs(vector<int> vector){
    std::vector<int>maximum;
    checkList(vector);
    
    revSort(vector); // sort numbers in descending order

    // create sublist of everything except first number
    // get the index of the first number in sublist that can be evenly divided
    // add first number to curr list
    // recursively call on the first matching index
    // when finished, check if the finalCurrList is the greatest one thus far
    
    if(vector.size() == 0){
        return {};
    }

    else if(vector.size() == 1){
        return {subVec(vector,0,1)};
    }
    
    for(size_t i = 0; i< vector.size(); i++){
        
        std::vector<int> currList;
        
        //create the subVector
        
        int numIndex = 1;
        
        //if we find a valid divisible integer in our vector


        //[56,28,24,22...]

        // currList.push_back(vector.at(0));
        std::vector<int> subVector = subVec(vector, i, vector.size());  

        //[28,24,22]          
        while(numIndex != -1){
            //[24,22...]
            currList.push_back(subVector.at(0)); // add the first number to the List
            numIndex = divIndex(subVector);  
            subVector = subVec(subVector, numIndex, subVector.size());
        }
        if(currList.size() > maximum.size() ){
            maximum = currList;
        }
        currList.clear();
    }
    return maximum;
}


int main() {
    vector<int> numbers = {2,3,4,5,6,7,8,16,50};
    
    cout << vector_to_string(largest_divisible_pairs(numbers)) << endl;

    return 0;
}



