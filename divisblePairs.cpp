#include <iostream>
#include <vector>
#include <string> 
#include <algorithm> // outsourcing the sort algorithm
#include <assert.h>
using namespace std;

void checkList(vector<int> vector){
    
if((vector.size() == 1) && (vector.at(0) < 1)){
    cout << "ERROR: Invalid number in vector" << endl;
    exit(0);
}
    
    for(size_t i = 0; i< vector.size()-1; i++){
        
        if(vector.at(i) == vector.at(i+1)){
            cout << "ERROR: Repeated number in vector ";
            exit(1);
        }
        if(vector.at(i) < 1){
            cout << "ERROR: Invalid number in vector";
            exit(2);
        }
    }
}

vector<int> revSort(vector<int> &vector){
    std::sort(vector.begin(), vector.end());
    std::reverse(vector.begin(), vector.end());
    return vector;
}

// returns specified subVector of a given vector
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

// given a vector, returns the index of the first number that is evenly divisible by the target number
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

// adds values of one vector to another
vector<int> addVec(vector<int> one, vector<int> two){
    for(size_t i = 0; i < two.size(); i++){
        one.push_back(two.at(i));
    }
    return one;
}

vector<int> largest_divisible_pairs(vector<int> vector){
    std::vector<int>maximum;
    
    revSort(vector); // sort numbers in descending order

    // create sublist of everything except first number
    // get the index of the first number in sublist that can be evenly divided
    // add first number to curr list
    // recursively call on the first matching index
    // when finished, check if the finalCurrList is the greatest one thus far
    
    if(vector.size() == 0){
        return {};
    }

    if(vector.size() == 1){
        checkList(vector);
        return {subVec(vector,0,1)};
    }
    
    checkList(vector);
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

void test(){
    //divIndex
    cout << "Testing auxiliary method divIndex(): " << endl;
    vector<int> numbers = {1,2,3,4,5,6};
    revSort(numbers); // always deals with sorted list
    assert (divIndex(numbers) == 3);
    // we are not anticipating any lists of size 0 and 1, we check
    // for this in the primary function :)

    numbers = {1,125,123,5,2,15,124,23,25,31,52,3,51};
    revSort(numbers);
    assert (divIndex(numbers) == 6);

    cout << "divIndex() TEST PASSED! " << endl;

    // Testing largest_divisible_pairs
    cout << "Testing largest_divisible_pairs()" << endl;

    numbers = {3,6,9,12,15,18,21,24,48,49};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[48,24,12,6,3]");

    numbers = {1,2,4,8,3,27};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[8,4,2,1]");

    numbers = {1,2,3,5,7,11,13,17,19,23,29};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[29,1]");

    numbers = {1,2,3,5,7,11,13,17,19,23,29,33,99};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[99,33,11,1]");

    numbers = {1,2,3,4,5,7,8,11,13,16,17,19,23,29,33,99};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[16,8,4,2,1]");

    numbers = {};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[]");

    numbers = {1};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[1]");

    numbers = {9};
    assert (vector_to_string(largest_divisible_pairs(numbers)) == "[9]");
    cout << "largest_divisible_pairs() test passed" << endl;

    cout << "PASSED ALL TESTS!" << endl;
}

int main() {
    test();
    vector<int> numbers = {-1};
    cout << "Input: " << vector_to_string(numbers) << endl;
    cout << "Answer: " <<vector_to_string(largest_divisible_pairs(numbers)) << endl;

    return 0;
}



