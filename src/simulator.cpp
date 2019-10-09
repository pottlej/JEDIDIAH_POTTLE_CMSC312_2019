/*
 * simulator.cpp
 */
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

#include "memory.cpp"
using namespace std;

// Represents size of memory (4096 MiB in this case) in bits.
long long int storage = (4096 * pow(2, 20)) * 8;
//long long int storage = 131072;

int output()
{
	cout << "storage: " << storage << endl;
	return 0;
}

int num = output();
Memory memory = Memory(storage);

/*
//int to hex
stringstream ss;
int num;
string hexNum;
cin >> num;
stream << hex << num;
hexNum = stream.str();
cout << "hex: " << hexNum << endl;
*/

/*
//hex to int
unsigned int x;
stringstream ss;
ss << hex << "f";
ss >> x;
cout << x;
*/

//ioCycle = rand() % 26 + 25;

/*
int main()
{
	return 0;
}*/
