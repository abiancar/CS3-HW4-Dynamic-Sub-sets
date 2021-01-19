#include <iostream>
#include <vector>
#include <string> 
#include <algorithm>
using namespace std;


/*
GENERAL ALGORITHM:
1. Take a vector of integers
2. Sort the vector from highest to lowest
3. Starting from leftmost integer, find the index of the nearest number that is evenly divisible 
4. If it is divisible update currVector (container for storing optimal vector given this int)
5. If legal and longest thus far... update maxVector
6. If not, discard at the end of iteration
7. Test:
8. Given a sorted combination of integers, find the smallest in vector, check if all other numbers can divide evenly into smallest number
*/


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
        int firstNum = vector.at(i);
        
        //create the subVector
        
        int numIndex = 1;
        
        //if we find a valid divisible integer in our vector


        //[56,28,24,22...]

        currList.push_back(vector.at(0));
        std::vector<int> subVector = subVec(vector, 0, vector.size());  

        //[28,24,22]          
        while(numIndex != -1){
            //[24,22...]
            subVector = subVec(subVector, numIndex, subVector.size());
            numIndex = divIndex(subVector);  
            currList.push_back(subVector.at(0)); // add the first number to the List
            cout << vector_to_string(currList) << endl;
        }
        if(currList.size() > maximum.size() ){
            maximum = currList;
        }
    }
    return {maximum};
}


int main() {
    vector<int> numbers = {28, 22, 7, 2, 8, 14, 24, 56};
    revSort(numbers); // sort numbers in descending order
    cout << vector_to_string(numbers);
    cout << divIndex(numbers); // print the index of the first number evenly by the vector's largest num
    
    cout << vector_to_string(largest_divisible_pairs(numbers));

    return 0;
}



