#include <iostream>
#include <vector>
#include <string> 
#include <algorithm> // outsourcing the sort algorithm
#include <assert.h>
using namespace std;

// simple check of user Inputs [no repeated #, no negative ints, no zeros]
void checkList(vector<int> vector){   
if((vector.size() == 1) && (vector.at(0) < 1)){
    cout << "ERROR: Invalid number in vector" << endl;
    exit(1);
}
    for(size_t i = 0; i< vector.size()-1; i++){
        
        if(vector.at(i) == vector.at(i+1)){
            cout << "ERROR: Repeated number in vector ";
            exit(2);
        }
        if(vector.at(i) < 1){
            cout << "ERROR: Invalid number in vector";
            exit(3);
        }
    }
}

//Sorts given vector in descending order
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

// used for debugging and printing
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
    
    // if there is an empty vector, there is no possible divisible number!
    if(vector.size() == 0){
        return -1;
    }

    //find largest number, we are going to see what is the first valid denominator
    int largest = vector.at(0);

    //If the largest number % smallest = 0, it is divisible, return its index!
    for(size_t i = 1; i < vector.size(); i++){
        int curr = vector.at(i);
        if (largest % curr == 0){
            return i;
        }
    }
    return -1;
}
/*  
GENERAL ALGORITHM: 
1)  create sublist of everything except first number
2)  get the index of the first number in sublist that can be evenly divided
3)  If a valid number was found, add the first number to curr list
4)  recursively call on the matching index
5)  If one was not found, end the current iteration (stop adding to currList)
6)  At every iteration, this will create a vector of valid integers (all divisible by each other)
7)  when finished with each iteration, check if given CurrList is the greatest one thus far, if so, set maximum to this list
*/

vector<int> largest_divisible_pairs(vector<int> vector){
    std::vector<int>maximum;
    
    revSort(vector); 
    // sort numbers in descending order to make use of divisive properties
    // if numbers are sorted, we can iterate through all numbers in the sorted vector
    // knowing that the first number at each iteration represents the largest number

    
    // basic check of edge case, empty list
    if(vector.size() == 0){
        return {};
    }

    // basic check of edge case, single number, simply return the number
    if(vector.size() == 1){
        checkList(vector);
        return {subVec(vector,0,1)};
    }
    
    checkList(vector); // check if the given vector is valid first

    for(size_t i = 0; i< vector.size(); i++){        
        int numIndex = 1; // set to one so that we can enter coming while loop
        
        std::vector<int> currList; // stores list of valid number combinations of each iteration 
        std::vector<int> subVector = subVec(vector, i, vector.size()); // creates for recursive call of divIndex() using previous answers

        // if we have not yet found all the valid values featuring the first number of this iteration
        // keep looking for the rest!
        while(numIndex != -1){
            currList.push_back(subVector.at(0));                       // if we have not reached the end of this iteration's list, add first number
            numIndex = divIndex(subVector);                            // find the index of the next number of the list
            subVector = subVec(subVector, numIndex, subVector.size()); // recursively call divIndex() on the next iteration
        }
        if(currList.size() > maximum.size() ){
            maximum = currList;   // update maximum to currList if this is the greatest thus far
        }
        currList.clear(); // clear currList for use in next iteration
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
    test(); // test function
    
    // sample output
    vector<int> numbers = {28, 22, 7, 2, 8, 14, 24, 56};
    cout << "Input: " << vector_to_string(numbers) << endl;
    cout << "Answer: " <<vector_to_string(largest_divisible_pairs(numbers)) << endl;

    return 0;
}



