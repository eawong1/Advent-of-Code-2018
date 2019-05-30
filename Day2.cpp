#include <iostream>
#include<fstream>
#include <string>
using namespace std;

int checkSums(string filename);
string commonLetters(string filename);

int main()
{
	cout << "Check Sums: " << checkSums("boxIDs.txt") << endl;
	cout << "Common Letter: " << commonLetters("boxIDs.txt");
}

//Day 2 part 1
int checkSums(string filename)
{
	string temp;
	ifstream file;
	file.open(filename);

	int alphabet[26]; //array keeps track of how many letters appear each time
	int twoChar=0; //keeps track of how many times a char appears exactly two times
	int threeChar = 0; //keeps track of how many times a char appears exactly three times

	do
	{
		//two temp variables that keep track of the number of times two or three char times for each line on the file 
		int twoCharTemp = 0; 
		int threeCharTemp = 0;
		if (file.is_open())
		{
			getline(file, temp);
		}
		if (temp.compare("end file") != 0)
		{
			for (int loop = 0; loop < 26; loop++)
			{
				alphabet[loop] = 0;
			}

			for (int i = 0; i < temp.length(); i++)
			{
				char c = temp[i];

				//for loop iterates from the ascii values of 'a' to 'z'
				//this loop checks to see which letter is char c and then increments the array value based on what letter it is
				//so if char c='a' then alphabet[0] would get incremented
				int index = 0;
				for (int j = 97; j <= 122; j++)
				{
					if (c == j)
					{
						alphabet[index]++;
					}
					index++;
				}
			}

			//loops through the alphabet array and checks if any of the letters show up exactly two or three times
			for (int j = 0; j < 26; j++)
			{
				if (alphabet[j] == 2)
				{
					twoCharTemp++;
				}
				if (alphabet[j] == 3)
				{
					threeCharTemp++;
				}
			}

			//if statements the increment the actual variables that keep track of the amount of times a char shows up two or three times
			//so if two chars on the same line show up three times it will only count as one
			if (twoCharTemp >= 1)
			{
				twoChar++;
			}
			if (threeCharTemp >= 1)
			{
				threeChar++;
			}

		} //end of if statement
		
	} while (temp.compare("end file") != 0);

	return twoChar * threeChar;
}

//Day 2 part 2
string commonLetters(string filename)
{
	string temp;
	ifstream file;
	file.open(filename);

	int numOfIDs = 0; //keeps track of how many IDs are in the file 
	int matches=0;  //keeps track of how many char match
	int numOfLetters = 0; //number of letters in an ID
	bool match = false;

	string commonString = ""; //the final string that would be returned 

	//counts the numbers of IDs 
	while (temp.compare("end file") != 0)
	{
		if (file.is_open())
		{
			getline(file, temp);
		}
		numOfIDs++; 
	}
	file.close();
	string *ids=new string[numOfIDs]; //mem allocation for array of IDs

	file.open(filename); //reopens the file so it starts reading from the beginning again 
	//adds each line in the file into the array

	temp = ""; //resets the temp variable
	int f = 0; //index for the ids
	while (temp.compare("end file") != 0)
	{
		if (file.is_open())
		{
			getline(file, temp);
		}
		ids[f] = temp;
		f++;
	}

	numOfLetters = ids[0].length(); //gets the length for each string ID (since all of the IDs are the same length it just gets the first one
	char *commonStrings = new char[numOfLetters];


	for (int i = 0; i < numOfIDs-1; i++) //first for loop selects a value and compares it with everyoen value that comes after it in the list
	{
		for (int j = i+1; j < numOfIDs; j++) //second for loop selects every value after the value selected by the first for loop
		{
			commonString = ""; //resets the string everytime a match isnt found 
			matches = 0; //resets the variable that keeps track of how many char match 
			for (int index = 0; index < numOfLetters; index++) //3rd for loop iterates though the string comparing the two strings char by char
			{
				if (ids[i].at(index) == ids[j].at(index))
				{
					matches++; 
					commonString = commonString + ids[i].at(index); //just conc
				}
				//if the amount of matches is 1 less than the number of letters each string then it is the correct ID
				if (matches == numOfLetters - 1) 
				{
					match = true;
					break;
				}
			}
			if (match) //if statement so it doesnt have to loop through again 
			{
				break;
			}
		}
		if (match) //if statement so it doesnt have ot loop through again 
		{
			break;
		}
	}
	delete[] ids; //deallocates the 'ids' array

	return commonString;
}