#include"Include\base64.h"
#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	BASE64 test;
	test.encode("TES", 3);
	cout << test.encodedGetResult().c_str() << endl;;

	test.encode("TEST", 4);
	cout << test.encodedGetResult().c_str() << endl;;

	test.encode("TESTT", 5);
	cout << test.encodedGetResult().c_str() << endl;;

	if (test.decode("VEVTVFQ=", 8))	cout << test.decodedGetResult().c_str();
	else cout << "Decode failed.";

	return(0);
}