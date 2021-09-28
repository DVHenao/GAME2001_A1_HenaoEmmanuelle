#include <iostream>
// #include "UnorderedArray.h"
#include "OrderedArray.h"
//just testing
using namespace std;

int main()
{
	OrderedArray<int> array(2);

	array.push(1);
	array.push(2);
	array.push(3);
	array.push(4); 
	array.push(5);
	array.push(5);


	array[2] = 112;

	array.pop();
	array.remove(2);

	cout << "Ordered array contents: ";

	for (int i = 0; i < array.GetSize(); i++)
	{
		cout << array[i] << " ";
	}

	cout << endl;

	cout << "Search for 23 was found at index: ";
	cout << array.search(23);

	cout << endl << endl;

	return 0;
}