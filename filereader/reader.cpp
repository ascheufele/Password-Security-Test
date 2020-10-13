//Alex Scheufele
#include <iostream>
#include <fstream>

using namespace std;

void getLine(ifstream& stream, string& res);

int main(int argc, char* argv)
{
	char* line;
	ifstream file;
	string user_phrase, file_phrase;

	cout << "This program will tell you if your entered phrase is listed in a file of the most commonly used passwords." << endl;
	cout << "This program does not store any phrase entered..." << endl;
	cout << "Enter phrase: ";
	cin >> user_phrase;

	file.open("C:\\Users\\asche\\Downloads\\rockyou.txt", ios::in);
	if (file.fail())
	{
		cout << "file failed to open... exiting" << endl;
		exit(1);
	}
	while (!file.fail())
	{
		getLine(file, file_phrase);
		if (user_phrase == file_phrase)
		{
			cout << user_phrase << " == " << file_phrase << endl;
			cout << "Your phrase is included in the list of most commonly used passwords." << endl;
			file.close();
			exit(1);
		}
		file_phrase = "";
	}

	cout << "Congratulations. Your phrase was not found." << endl << "Program exiting..." << endl;
	file.close();
	return 0;
}

void getLine(ifstream& stream, string& res)
{
	//this function assumes stream is a handle to a valid ifstream
	//and that res is a handle to a valid empty string
	char c = '0';
	while ((c = stream.get()) != '\n' && (!stream.fail()))
	{
		res += c;
	}
}