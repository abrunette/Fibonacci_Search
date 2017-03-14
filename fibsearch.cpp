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

	cout << "Program is generating a vector of fibonacci numbers...\n\n" << "_____\n\n";	//explanation

	//creates fibonacci numbers up to the next largest of the size of the search array
	while(fibNums.back() < aSize)
	{
		//F(n) = F(n+1) + F(n+2)
		fibN = fibNums[fibNums.size()-1] + fibNums[fibNums.size()-2];
		fibNums.push_back(fibN);
		cout << fibN << endl;		//explanation
	}
	cout << "_____\n\n";	//explanation
	int invalidSlots = fibNums.back() - aSize;	//explanation
	cout << "The last value in the vector, " << fibNums.back() 
	     << ", is greater than or equal to the size of the seached array, " << aSize << ".\n\n"
	     << "This value can be greater than the size of the array. There are " << invalidSlots <<  " invalid slots in the search area.\n\n";	//explanation

	//****
	cout << "_______________\n\n";

	for(int i = 1; i < fibNums.back()+1; i++) 
	{
		if(i-1 < aSize) 
		{
			cout << "  " << i << "  |  " << searchArray[i-1] << "  |  " << i-1 << endl; 
		}
		else	cout << "  " << i << "  |  " << "INVALID    <----\n";
	}

	cout << "_______________\n\n";
	//****

	//checks that the range is still valid, != to the second fibonacci number (1)
	while(fibNums.back() > 1)
	{
		//explanation
		cout << "Checking if " << offset + fibNums[fibNums.size()-3] << " is a valid position against " << aSize-1 << ".\n\n";

		if((offset + fibNums[fibNums.size()-3]) <= aSize-1)
		{
			valid = fibNums[fibNums.size()-3] + offset;
			cout << "F(n-2), " << valid << ", is a valid position.\n\n";	//explanation
		}
		else 
		{
			valid = aSize-1;
			cout << "F(n-2), " << valid << ", is not a valid position.\n\n";	//explanation
		}
		//explanation
		cout << "Now checking if " << search << " is greater than, less than, or equal to " << searchArray[valid] << ".\n\n";

		//checks if range is above or below fib number
		if(searchArray[valid] < search)
		{
			fibNums.pop_back();
			offset = valid;

			//****
			cout << search << " is greater than " << searchArray[valid] << ".\nEnd range of fibonacci is now " << fibNums.back() << "\n\n";

			cout << "_______________\n\n";

			for(int k = fibNums[fibNums.size()-3]; k < fibNums.back()+1; k++) 
			{
				cout << " " << k << "  |  " << searchArray[k-1] << "  |  " << k-1 << endl; 
			}

			cout << "_______________\n\n";
			//****
		}
		else if (searchArray[valid] > search)
		{
			fibNums.pop_back();
			fibNums.pop_back();
			cout << search << " is less than " << searchArray[valid] << ".\nEnd range of fibonacci is now " << fibNums.back() << "\n\n";

			//****
			cout << "_______________\n\n";

			for(int k = fibNums[fibNums.size()-3]; k < fibNums.back()+1; k++) 
			{
				cout << " " << k << "  |  " << searchArray[k-1] << "  |  " << k-1 << endl; 
			}

			cout << "_______________\n\n";
			//****
		}
		else return valid;
	}
	//explanation
	cout << "Checking " << search << " against value at position 1. (The only fibonacci values left are 0 1 1)\n\n";

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
	
	//****
	cout << "__________________________________________________________________\n\n"
	     << "The fibonacci search algorithm is a method of searching through a \n\n"
	     << "sorted array. It is a divide and conquer method and is similar to\n\n"
	     << "binary search. It was first devised by Jack Kiefer in 1953.\n\n"
	     << "W(n) occurs when the search value is in the lower 2/3 of the array.\n\n"
	     << "Every pass of the loop eliminates 1/3 of the initial 1/3 until the\n\n"
	     << "entirety of the initial 1/3 is checked. Then the higher 1/3 of the\n\n"
             << "initial 2/3 is called and checked. n -> (2/3)n -> (4/9)n -> etc...\n\n"
	     << "B(n) is not the middle as is the case with binary search. It is the\n\n"
	     << "F(n-2). It can be more efficient than binary search if it is accessing\n\n"
	     << "non-uniform memory or the size of the array is larger than the cache\n\n"
	     << "or memory. This can also help with lifetime efficiency because it is\n\n"
	     << "less demanding on the hardware.\n\n";
	//****
}
