#include <windows.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");

	cout<<"I am created.";
	/*for (i = 0; i < argc; i++)
		cout << "\n " << argv[i];
		cout<<"\n "<<atoi(argv[i]) * 2;*/

	
	int N = 10;//argc;
	long* arr = new long[N];
	char *name;
	name = argv[0];
	for (int i = 1; i < N; i++)
	{
		
		arr[i] = atoi(argv[i]);
		cout << arr[i] << ' ';
	}
	cout << endl << " кратные 4: \n";
	for (int i = 0; i < 10; i++)
	{
		if (!(arr[i] % 4))
			cout << arr[i] << ' ';
		
	}
cout << "\n";
	/*for (; ;) {
		cout << "Input 'e' to exit";
		char ch;
		cin >> ch;
		if (ch == 'e')
			ExitProcess(1);
	}*/

	return 0;
}