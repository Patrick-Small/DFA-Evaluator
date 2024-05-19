/*
Patrick Small
CS_441 Computer Systems Architecture
01/28/2024
*/

/*
With assistance from:
	https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm
	https://www.geeksforgeeks.org/std-find-in-cpp/
	https://cplusplus.com/forum/beginner/265292/
*/

/*
In order to run this file with a specific file, do:
Project -> Properties -> Debugging -> Command Arguments
*/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <array>

using namespace std;

int main(int argc, char* argv[])
{
	//Declarations
	string temp;
	int state_cnt = 0; //# of states
	int start = 0; //Starting location
	vector <int> final; //The accept states
	vector <char> alpha; //Alphabet

	//Open the file
	ifstream DFA(argv[1]);

	if (!DFA)
	{
		cerr << "Error: File cannot be opened" << endl;
	}

	//Initialize state_cnt
	getline(DFA, temp);
	state_cnt = stoi(temp);
	//cout << state_cnt << endl; //Testing

	//Initialize start
	getline(DFA, temp);
	start = stoi(temp);
	//cout << start << endl; //Testing

	//Initialize final
	if (getline(DFA, temp))
	{
		//Iterate through each character in the string
		for (char c : temp)
		{
			//Convert each character to a string and then to an integer
			if (isdigit(c))
			{
				final.push_back((int)c - 48);
			}
		}
	}

	/* Testing
	for (auto i : final)
	{
		cout << i << endl;
	}
	*/

	//Initialize alpha
	if (getline(DFA, temp))
	{
		for (char& c : temp)
		{
			alpha.push_back(c);
		}
	}

	/* Testing
	for (auto i : alpha)
	{
		cout << i << endl;
	}
	*/

	//Declare a memory block
	int** trans = new int* [state_cnt + 1];

	for (int i = 0; i < state_cnt + 1; i++) {
		trans[i] = new int[alpha.size()];
	}

	//Declaration for initializing array
	int value;

	//Failed state for state 0
	for (int i = 0; i < alpha.size(); i++)
	{
		trans[0][i] = 0;
	}

	//Initialize trans array
	for (int w = 0; w < state_cnt; w++)
	{
		for (int l = 0; l < alpha.size(); l++)
		{
			DFA >> value;
			trans[w + 1][l] = value;
		}
	}

	/* Testing 
	for (int w = 0; w < state_cnt + 1; w++)
	{
		for (int l = 0; l < alpha.size(); l++)
		{
			cout << trans[w][l] << endl;
		}
	}
	*/

	//Buffer
	getline(DFA, temp);

	//This will terminate when it reaches the end of the file
	while (getline(DFA, temp))
	{
		//Starting location
		int cur = start;

		//cout << temp << endl; //Testing

		//char array with +1 for null terminator
		char* S = new char[temp.length() + 1];

		//Fill the char array with the string values
		for (int i = 0; i < temp.length(); i++) 
		{
			S[i] = temp[i];
		}

		//Add the null terminator
		S[temp.length()] = '\0';

		//While the S pointer is not at the end and while the current state is not in a fail state
		while (*S != '\0' && cur != 0)
		{
			//cout << cur << endl; //Testing

			//Calculations
			cur = trans[cur][find(alpha.begin(), alpha.end(), *S) - alpha.begin()];

			++S;

		}

		//Good if the current state isn't 0 AND is a final state
		if (cur != 0 && (find(final.begin(), final.end(), cur)) != final.end())
		{

			//If the data is not empty
			if (temp.length() >= 1)
			{
				cout << "good " << temp << endl;
			}

			//Empty data
			else
			{
				cout << "good <empty>" << endl;
			}

		}

		//Bad data
		else
		{
			cout << "bad  " << temp << endl;
		}

	}

	//Exit
	return 0;
}