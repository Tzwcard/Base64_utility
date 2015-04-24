#ifndef BASE64ALGORITHM_H
#define BASE64ALGORITHM_H

#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>

using namespace std;

class BASE64
{
public:
	BASE64(void);
	BASE64(string, string);
	BASE64(string, string, string);

	~BASE64(void);

	void clear(void);
	void encode(string);
	void encode(string, string);
	void decode(string);
	void decode(string, string);


private:
	static const char *Base64EncodeChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	static const char Base64DecodeChars[] = {
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 62/*+*/, 99, 99, 99, 63/***/,
		52/*0*/, 53/*1*/, 54/*2*/, 55/*3*/, 56/*4*/, 57/*5*/, 58/*6*/, 59/*7*/,
		60/*8*/, 61/*9*/, 99, 99, 99, 98/*=*/, 99, 99,
		99, 0/*A*/, 1/*B*/, 2/*C*/, 3/*D*/, 4/*E*/, 5/*F*/, 6/*G*/,
		7/*H*/, 8/*I*/, 9/*J*/, 10/*K*/, 11/*L*/, 12/*M*/, 13/*N*/, 14/*O*/,
		15/*P*/, 16/*Q*/, 17/*R*/, 18/*S*/, 19/*T*/, 20/*U*/, 21/*V*/, 22/*W*/,
		23/*X*/, 24/*Y*/, 25/*Z*/, 99, 99, 99, 99, 99,
		99, 26/*a*/, 27/*b*/, 28/*c*/, 29/*d*/, 30/*e*/, 31/*f*/, 32/*g*/,
		33/*h*/, 34/*i*/, 35/*j*/, 36/*k*/, 37/*l*/, 38/*m*/, 39/*n*/, 40/*o*/,
		41/*p*/, 42/*q*/, 43/*r*/, 44/*s*/, 45/*t*/, 46/*u*/, 47/*v*/, 48/*w*/,
		49/*x*/, 50/*y*/, 51/*z*/, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99
	};

	string base64String = "",
		inputFilename = "",
		outputFilename = "";
	unsigned char buffer[4] = { 0x00, 0x00, 0x00, 0x00 };

	void setInputFilename(string);
	void setOutputFilename(string);
	void setInputString(string);
	
	void blockBase64Encode(void);
	void blockBase64Decode(void);

	void Base64EncodeFile(void);
	void Base64DecodeFile(void);
	void Base64EncodeString(void);
	void Base64DecodeString(void);

	bool validateCharOfB64(unsigned char, size_t);
};





#endif BASE64ALGORITHM_H