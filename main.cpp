#include <iostream>
#include<iomanip>
#include <string>
#include<fstream>


using namespace std;
int main()
{
	string file;
	string values;
	fstream inFile;
	char temp;
	cout << "what file do you want to open" << endl;
	cin >> file;
	inFile.open(file.c_str(), ios:: in | ios::out);

	while (inFile >> temp >> noskipws)
	{
		cout << temp << endl;
		
	}
	//cin.get();
	system("pause");

	return 0;
}