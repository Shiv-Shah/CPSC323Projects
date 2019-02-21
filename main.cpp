#include <iostream>
#include<iomanip>
#include <string>
#include<fstream>


using namespace std;
int main()
{
	string file;
	char values;
	fstream inFile;
	cout << "what file do you want to open" << endl;
	cin >> file;
	inFile.open(file.c_str(), ios:: in | ios::out);

	while (inFile >> values)
	{
		cout << values << endl;
	}
	//cin.get();
	system("pause");

	return 0;
}