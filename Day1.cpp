#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int calculateFrequency(string filename);
int checkTwice(string filename);

//creating linkedlist 
struct linkedList
{
	int data;
	struct linkedList *next;
} *frequencies = NULL;


int main()
{
	cout << "Total Frequencies: " << calculateFrequency("frequencies.txt") << endl;

	cout << "Frequency reached twice: " << checkTwice("frequencies.txt") << endl;

}


//calculates the total frequency
//Day 1 part 1 challenge
int calculateFrequency(string filename)
{
	string temp; 
	int temp1;  
	int frequency=0;
	ifstream file;
	file.open(filename);

	do
	{
		if (file.is_open())
		{
			getline(file, temp); //reads the line and stores the data into temp string
		}

		//if the file hasn't ended it does this
		if (temp.compare("end file") != 0)
		{
			//removes the '+' in front of the int if it is present
			if (temp.at(0) == '+')
			{
				temp = temp.substr(1, temp.length());
			}

			try
			{
				temp1 = stoi(temp); //converts the temp string into an int and stores the value into temp1
			}
			catch (...)
			{

			}

			frequency = frequency + temp1; //adds temp1 into the total frequency
		}
		

	} while (temp.compare("end file") != 0);
	
	return frequency;
}


//Day 1 part 2 challenge
int checkTwice(string filename)
{
	string temp;

	int temp1;
	int frequency = 0;

	ifstream file;

	bool found = false; 
	int iteration = 0; 
	int twice = 0; //variable that will eventually hold the value of the frequency that appears twice

	while (!found)
	{
		file.open(filename);
		do
		{
			if (file.is_open())
			{
				getline(file, temp); //reads the line and stores the data into temp string
			}

			//if the file hasn't ended it does this
			if (temp.compare("end file") != 0)
			{
				//removes the '+' in front of the int if it is present
				if (temp.at(0) == '+')
				{
					temp = temp.substr(1, temp.length());
				}

				try
				{
					temp1 = stoi(temp); //converts the temp string into an int and stores the value into temp1
				}
				catch (...)
				{

				}

				frequency = frequency + temp1; //adds temp1 into the total frequency

				struct linkedList *tempList = frequencies;
				struct linkedList *node = new linkedList;

				//searches through the linkedlist for any values that are the same as the current frequency 
				while (tempList != NULL)
				{
					if (tempList->data == frequency)
					{
						twice = frequency; //sets twice to the current frequency 
						found = true;
					}
					tempList = tempList->next; //iterates the linkedList
				}
				tempList = frequencies; //resets the linkedList after iterating it 

				//if statement to make sure the first element isnt automatically added into the linkedList
				if (iteration != 0)
				{
					node->data = frequency;
					node->next = tempList;
					tempList = node;

					frequencies = tempList;
				}
				iteration++;
			}

			//once the element is found the loop would get terminated
			if (found)
			{
				break;
			}

		} while (temp.compare("end file") != 0);

		//closes the file 
		file.close();
	}
	
	//returns the duplicate number
	return twice;
}




