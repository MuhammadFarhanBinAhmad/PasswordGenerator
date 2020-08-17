#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

bool close_Program;

vector<string> a_Title;
vector<string> a_Password;

void CloseProgram();
void InputCommandCode();

char GenerateCharacter(int v)
{
	char new_Password;
	//Giving random char to password creation
	switch (v)
	{
	case 0:
	{
		new_Password = 'A' + rand() % 26;
		break;
	}
	case 1:
	{
		new_Password = 'a' + rand() % 26;
		break;
	}
	case 2:
	{
		new_Password = '0' + rand() % 10;
		break;
	}
	case 3:
	{
		new_Password = ':' + rand() % 6;
		break;
	}
	default:
	{}
	}
	return new_Password;
}

void PrintPassword(string file_Name)
{
	ifstream IF_Password{ file_Name + ".txt" };
	string content;

	IF_Password.open(file_Name + ".txt");

	for (int i = 0; i < a_Title.size() ; i++)
	{
		cout << a_Title[i] << endl;
		cout << a_Password[i] << endl;
	}
}
void AddPassword(string file_Name)
{
	ifstream IF_Password{ file_Name + ".txt" };
	//add password
	string name_Password;
	string new_Password;
	int length_Password;

	cout << "Input name of password" << endl;
	cin >> name_Password;
	cout << "Input length of password" << endl;
	cin >> length_Password;

	srand(time(0));

	for (int i = 1; i <= length_Password; i++)
	{
		int v = rand() % 4;//give random value from 0-3
		new_Password += GenerateCharacter(v);
	}

	cout << "Do you accept this password" << endl;
	cout << new_Password << endl;
	cout << "0 - no" << endl << "1 - yes" << endl;

	int A;
	cin >> A;
	if (A == 0)
	{
		AddPassword("Password");
	}
	if (A == 1)
	{
		a_Title.push_back("Title: " + name_Password);
		a_Password.push_back(new_Password);
	}
}
void ClearAll(string file_Name)
{
	ofstream OF_Password;
	char b;
	cout << "Are you sure?" << endl << "y/n" << endl;
	cin >> b;
	if (b == 'y')
	{
		//clear all content in the text file
		OF_Password.open(file_Name + ".txt");
		OF_Password.clear();
		//clear out new password
		for (int i = 0; i < a_Title.size(); i++)
		{
			//a_Title[i].clear();
			//a_Password[i].clear();
		}
		cout << "All Password Deleted" << endl;
	}
	if (b == 'n')
	{
	}
}
void EditPassword()
{

}
void DeletePassword()
{
	
	int selecting_Password;
	char state;

	cout << "which pasword you wish to delete" << endl;
	for (int i = 0; i < a_Title.size(); i++)
	{
		cout << i << ". " << a_Title[i] << endl;
	}
	cin >> selecting_Password;
	if (selecting_Password > a_Title.size())
	{
		cout << "Invalid Number" << endl;
		DeletePassword();
	}
	else
	cout << "Are you sure" << endl << "y/n" << endl;
	cin >> state;

	if (state == 'y')
	{
		a_Title[selecting_Password].erase();
		a_Password[selecting_Password].erase();
		/*a_Title[selecting_Password] = '\0';
		a_Password[selecting_Password] = '\0';*/

	}
	if (state == 'n')
	{
		cout << "Deletion Cancel" << endl;
	}
}
void InputCommandCode()
{
	int input_Command;

	cout
		<< "What you wish to do" << endl
		<< "1: PrintPassword" << endl
		<< "2: AddPassword" << endl
		<< "3: ClearAll" << endl
		<< "4: EditPassword" << endl
		<< "5: DeletePassword" << endl
		<< "0: CloseProgram" << endl;

	cin >> input_Command;

	if (input_Command > 6 || input_Command < 0)
	{
		InputCommandCode();
	}
	if (input_Command == 1)
	{
		PrintPassword("Password");
	}
	if (input_Command == 2)
	{
		AddPassword("Password");
	}
	if (input_Command == 3)
	{
		ClearAll("Password");
	}
	if (input_Command == 4)
	{
		ClearAll("Password");
	}
	if (input_Command == 5)
	{
		DeletePassword();
	}
	if (input_Command == 0)
	{
		CloseProgram();
		cout << "hit";
	}
}
void CloseProgram()
{
	int i;
	cout << "close program?" << endl;
	cout << "0 - no"<< endl << "1 - yes" <<  endl;

	cin >> i;

	if (i == 0)
	{
		InputCommandCode();
	}
	if (i == 1)
	{
		ofstream OF_Password;
		ifstream IF_Password{"Password.txt"};

		string new_List_Password;
		string file_contents{ istreambuf_iterator<char>(IF_Password), istreambuf_iterator<char>() };//grab all current password in file

		//input newly created password into string
		for (int i = 0; i < a_Title.size(); i++)
		{
			new_List_Password += a_Title[i] + '\n';
			new_List_Password += a_Password[i] + '\n';
		}
		//set string input all newly created password in text file
		OF_Password.open("Password.txt");
		OF_Password << new_List_Password;
		close_Program = true;
	}
}
void main()
{
	//use to get a line from the text file
	ifstream file("Password.txt");
	string f_Content;

	int i = 0;
	int t = 0;//Title
	int p = 0;//Password

	while (getline(file, f_Content))
	{
		//placing title and password in their respective vectors
		if (i % 2 == 0 || i == 0)
		{
			a_Title.push_back(f_Content);
			t++;
		}
		else
		{
			a_Password.push_back(f_Content);
			p++;
		}
		i++;
	}
	while (!close_Program)
	{
		InputCommandCode();
	}
}

