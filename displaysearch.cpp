//EC Presentation
//Aaron Brunette
//Compiled using g++
//Client file
//C++ adaption of the C program by Yash Varyani

#include <iostream>
#include <vector>
using namespace std;

//Parameters: aSize is the size of the original array. search is the value
// the user wants to search for. searchArray[] is the array that the algorithm
// will search through, it is passed by reference to the function.
//Algorithm: loops through checking 1/3 of the array each pass against fibonacci numbers
int FibSearch(int aSize, int search, int searchArray[])
{
	int fibN;			//used to create a list of fibonacci numbers, hold
	int valid;			//tells if position is a valid spot in the array

	//offset is used to convert the fibonacci position to the array position
	//they are at a difference of 1 so the position 1 in the fibonacci is 
	//position 0 in the array
	int offset = -1;		//end of range from front
	vector <int> fibNums;		//initialize vector to hold fibonacci numbers
	fibNums.push_back(0); fibNums.push_back(1);	//add fibonacci seed values to vector
	
	//creates fibonacci numbers up to the next largest of the size of the search array
	while(fibNums.back() < aSize)
	{
		//F(n) = F(n+1) + F(n+2)
		fibN = fibNums[fibNums.size()-1] + fibNums[fibNums.size()-2];
		fibNums.push_back(fibN);
	}
	
	//checks that the range is still valid, != to the second fibonacci number (1)
	while(fibNums.back() > 1)
	{
		if((offset + fibNums[fibNums.size()-3]) <= aSize-1)
		{
			valid = fibNums[fibNums.size()-3] + offset;
		}
		else 
		{
			valid = aSize-1;
		}

		//checks if range is above or below fib number
		if(searchArray[valid] < search)
		{
			fibNums.pop_back();
			offset = valid;
		}
		else if (searchArray[valid] > search)
		{
			fibNums.pop_back();
			fibNums.pop_back();
		}
		else return valid;
	}
	if(fibNums[fibNums.size()-1] && searchArray[offset+1] == search) return offset+1;
	
	return -1;
}

//Purpose: to call and display 
//Algorithm: calls FibSearch function
int main()
{
	int userSearch;		//the value the user wants to search for
	const int aSize = 10;

	//sorted array to be searched through
	int fibArray[aSize] = { 1, 17, 24, 38, 45, 57, 64, 75, 82, 95 };
	
	//User Interface
	cout << "\nThis program will demonstrate the fibonacci search algorithm.\n";
	cout << "Please enter the number you would like to search for (1-100):\t"; 
	cin >> userSearch;
	while(userSearch > 100 || userSearch < 1) { cout << "\n\nInvalid number. Try again: "; cin >> userSearch; }
	cout << "\n\nRunning fibonacci search...\n\n";

	//calls void FibSearch
	int found = FibSearch(aSize, userSearch, fibArray);

	if (found == -1) {cout << "The value was not found in the array.\n"; }

	else {cout << "The value " << userSearch << " was found at position " << found << endl << endl; }

}
