/*
 What to work on next: Create a function for input and output file for reUsability purposes.
 Fix: Deleting people then adding more breaks program because of some format with txt file
 Add: Delete all function

 Program: Allows user to create an array of people and choose one from random.

*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

double generateRandomNum(int size);

void getName(string* names, int randNum);

int getLength(string* names);

void deletePerson(string* names, int index, int length);

void loadFromFile(string* names);

int main()
{
	//vars
	int randomNum =0;
	int answer =1;
	int r =0;
	int length =0;
	int dP=0;
	string nameForFile;
	bool repeat = true;
	ifstream inFile;
	ofstream outFile;
	string names[100];

	system("CLS");

	//File manipulation
	loadFromFile(names);

	//calculate length of array
		length = getLength(names);
	//Output what was loaded in
		for(int index = 0; index < length-1; index++)
		{
			cout << "Loaded " << names[index] << " from saved list." << endl;
		}
		cout << endl;
		system("PAUSE");
		system("CLS");


	//Start the Prompt
	do {
		if (answer < 1 || answer > 5)
		{
			cout << "Invalid Input, try again..." << endl;
		}
	cout << "*-" << endl;
	cout << "|" << endl;
	cout << "  What would you like to do?" << endl;
	cout << "  1.) Generate random person." << endl;
	cout << "  2.) Add Name to list" << endl;
	cout << "  3.) Delete Name from list" << endl;
	cout << "  4.) See name selection" << endl;
	cout << "  5.) Close the Program" << endl;
	cout << "                            |" << endl;
	cout << "                           -*" << endl;
	cin >> answer;

	system("CLS");

	//Case based on input
	switch (answer)
	{
		case 1:
			randomNum = generateRandomNum(length);
			cout << endl;
			getName(names, randomNum);
			cout << endl;
			break;
		case 2:
			outFile.open("RandomPersonGen", fstream::app);
			 cout << "What name would you like to enter?" << endl;
			 cin >> nameForFile;
			outFile << nameForFile << endl;
			outFile.close();
			//reload from file
			loadFromFile(names);
				system("CLS");
				cout << endl << " Added: " << names[length-1] << " to the list." << endl << endl;
				//recalculate length of array
				length = getLength(names);
			break;
		case 3:
			system("CLS");
			for(int i =0; i < length-1; i++)
			{
				cout << i+1 << ": " << names[i] << endl;
			}
			cout << " Which person would you like to delete? " << endl;
			cin >> dP;
			deletePerson(names, dP-1, length);
			//make length one less
			length--;
			break;
		case 4:
			for(int i =0; i < length-1; i++)
			{
				cout << i+1 << ": " << names[i] << endl;
			}
			cout << endl;
			break;
		case 5:
			return 0;
			break;
		default:
			cout << "Invalid, see switch " << endl;
			break;
	}


	//Accessing the loop
	cout << "Would you like to rerun to the main menu?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. Quit" << endl;
	cin >> r;
	if (r == 2)
	{
		repeat = false;
	}
	system("CLS");
	}while (repeat == true);



	return 0;
}


//Generates a randomNum from 0 to size
//Parameters: size - used for upper bound
double generateRandomNum(int size)
{
	int randomNum =0;
	srand(time(NULL));
	randomNum = rand() % (size-1);
	cout << "GenerateRandomNum() num: " << randomNum << endl;
	return randomNum;
}

//Finds which name corresponds to the array at the random Number index
void getName(string* names, int randNum)
{
	cout << "Your random number is: " << randNum << endl;
	cout << names[randNum] << endl;;
}

//Gets the length of the specified array
int getLength(string* names)
{
	int i =0;
	int count = 0;
	bool r = true;
	while (r)
	{
		if(names[i] == "")
			r = false;
		count++;
		i++;
	}
	return count;
}

//deletes a person from the array and then overwrites the file with the new array
void deletePerson(string* names, int index, int length)
{
	ifstream inFile;
	ofstream outFile;

	string temp[100];

	loadFromFile(temp);
	//remove person from array
	cout << " You have deleted " << names[index] << " from your list." << endl;
	//move each element
	for(int i =index; i < length; i++)
	{
		temp[i] = temp[i+1];
	}
	temp[length] = "";
	//rewrite file
	outFile.open("RandomPersonGen");
	for(int i=0; i < length-2; i++)
	{
		outFile << temp[i] << endl;
	}
	outFile << temp[length -1];
	outFile.close();
	//update list in running program
	loadFromFile(names);

	//rewrite names
	for (int i =0; i < length; i++)
	{
		names[i] = temp[i];
	}
}

//opens and loads in everything from the  file
void loadFromFile(string* names)
{
	ifstream inFile;
	ofstream outFile;

	//File manipulation
	inFile.open("RandomPersonGen");
	//if file cannot be found
	if(inFile.fail())
	{
		outFile.open("RandomPersonGen");
		//create file.
		outFile << "Bryan" << endl;
		outFile.close();
		cout << "Creating NameFile... please restart." << endl;
		system("PAUSE");
		cout << " Make sure to restart Program! " << endl;
	}
	//Load in from File
		for (int i =0; !inFile.eof(); i++)
		{
			getline(inFile, names[i]);
		}
	inFile.close();
}
