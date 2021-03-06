#include <iostream>
//#include "UnorderedArray.h"
#include "OrderedArray.h"
//just testing
using namespace std;

int main()
{
	bool dup;

	OrderedArray<int> array(2);

	cout << "would you like to allow duplicate data?\n press 1 for yes, press 0 for no\n";
	cin >> dup;
	if (dup == 1)
		array.SetDuplicate(1);
	else
		array.SetDuplicate(0);


	array.push(1);
	array.push(4);
	array.push(3);
	array.push(9); 
	array.push(6);
	array.push(5);
	array.push(7);
	array.push(8);
	array.push(2);
	array.push(5);
	array.push(8);

	array.remove(3);
	array.pop();


	cout << "Ordered array contents: ";

	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << array[i] << " ";
	}

	cout << endl;

	cout << "Search for 8 was found at index: ";
	cout << array.search(8);

	cout << endl << endl;

	return 0;
}