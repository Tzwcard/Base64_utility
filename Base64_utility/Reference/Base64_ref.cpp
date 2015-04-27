/*
A Base64 File Encoder/Decoder
*/

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

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

/*
Decode Validate:
If not in "Base64EncodeChars[]" or a early EQUAL char, shown an error.
*/

void validateB64Char(unsigned char t, int pos) { if ((Base64DecodeChars[t] == 99) || ((Base64DecodeChars[t] == 98) && (pos <= 2))) { cout << "INVALID INPUT!!!"; exit(3); } }

/*
Decode:
00ABCDEF 00GHIJKL 00MNOPQR 00STUVWX -> ABCDEFGH IJKLMNOP QRSTUVWX (3)
00ABCDEF 00GHIJKL 00MNOP00 ( EQUAL) -> ABCDEFGH IJKLMNOP          (2)
00ABCDEF 00GH0000 ( EQUAL) ( EQUAL) -> ABCDEFGH                   (1)
If 3rd encoded char is EQUAL then skip the 4th char.
*/

void blockBase64Decode(unsigned char &a, unsigned char &b, unsigned char &c, unsigned char i, unsigned char j, unsigned char k, unsigned char l, int &length)
{
	if (k == '='&&l == '=') {
		a = Base64DecodeChars[i] << 2 | ((Base64DecodeChars[j] & 0x30) >> 4);
		b = '0';
		c = '0';
		length = 1;
	}
	else if (l == '='){
		a = Base64DecodeChars[i] << 2 | ((Base64DecodeChars[j] & 0x30) >> 4);
		b = ((Base64DecodeChars[j] & 0x0f) << 4) | ((Base64DecodeChars[k] & 0x3c) >> 2);
		c = '0';
		length = 2;
	}
	else {
		a = Base64DecodeChars[i] << 2 | ((Base64DecodeChars[j] & 0x30) >> 4);
		b = ((Base64DecodeChars[j] & 0x0f) << 4) | ((Base64DecodeChars[k] & 0x3c) >> 2);
		c = (Base64DecodeChars[k] & 0x03) << 6 | Base64DecodeChars[l];
		length = 3;
	}
}

/*
Encode:
ABCDEFGH IJKLMNOP QRSTUVWX -> 00ABCDEF 00GHIJKL 00MNOPQR 00STUVWX (3)
ABCDEFGH IJKLMNOP          -> 00ABCDEF 00GHIJKL 00MNOP00 ( EQUAL) (2)
ABCDEFGH                   -> 00ABCDEF 00GH0000 ( EQUAL) ( EQUAL) (1)
*/

void blockBase64Encode(unsigned char a, unsigned char b, unsigned char c, unsigned char &i, unsigned char &j, unsigned char &k, unsigned char &l, int length)
{
	if (length == 1) {
		i = Base64EncodeChars[a >> 2];
		j = Base64EncodeChars[(a & 0x03) << 4];
		k = '=';
		l = '=';
	}
	else if (length == 2) {
		i = Base64EncodeChars[a >> 2];
		j = Base64EncodeChars[(a & 0x03) << 4 | (b >> 4)];
		k = Base64EncodeChars[(b & 0x0f) << 2];
		l = '=';
	}
	else {
		i = Base64EncodeChars[a >> 2];
		j = Base64EncodeChars[(a & 0x03) << 4 | (b >> 4)];
		k = Base64EncodeChars[(b & 0x0f) << 2 | (c >> 6)];
		l = Base64EncodeChars[c & 0x3f];
	}
}

/*
File encoder:
Read n byte and encode these byte and write it to file immidiately until eof. (n<=3)
*/

void Base64EncodeFile(char *fileInput, char *fileOutput)
{
	fstream in, out;
	int length = 0;
	unsigned char rChar[3], pChar[4];
	bool stateRead = true;
	char t[1];
	in.open(fileInput, ios::in | ios::binary);
	out.open(fileOutput, ios::out | ios::trunc | ios::binary);
	if (!in) { cout << "FILE READ ERROR!!!"; exit(4); }

	while (stateRead)
	{
		while (stateRead&&length != 3){
			in.read(t, sizeof(t));
			if (!in.eof()) {
				length++;
				rChar[length - 1] = t[0];
			}
			else stateRead = false;
		}
		if (length != 0){
			blockBase64Encode(rChar[0], rChar[1], rChar[2], pChar[0], pChar[1], pChar[2], pChar[3], length);
			out.write((char*)pChar, 4);
			length = 0;
		}
	}
	out.clear(); out.close();
	in.clear(); in.close();
}

/*
File decoder:
Read per 4 bytes and save into a vector.
Pop an error while it's not size mod 4 or invaild data.
If eof and no error, decode data and write to file.
*/

void Base64DecodeFile(char *fileInput, char *fileOutput)
{
	fstream in, out;
	int length = 0, a = 0, i = 0;
	unsigned char rChar[3], pChar[4];
	bool stateRead = true;
	char t[1];
	in.open(fileInput, ios::in | ios::binary);
	if (!in) { cout << "FILE READ ERROR!!!"; exit(5); }
	vector<unsigned char> file;

	while (stateRead)
	{
		while (stateRead&&length != 4){
			in.read(t, sizeof(t));
			if (!in.eof()) {
				length++;
				validateB64Char(t[0], length);
				file.push_back(t[0]);
			}
			else stateRead = false;
		}
		if (length == 4){ length = 0; }
		else if (length != 0) validateB64Char(length, 1);
	}
	out.open(fileOutput, ios::out | ios::trunc | ios::binary);
	for (i = 0; i<file.size();)
	{
		pChar[0] = file[i]; pChar[1] = file[i + 1]; pChar[2] = file[i + 2]; pChar[3] = file[i + 3];
		blockBase64Decode(rChar[0], rChar[1], rChar[2], pChar[0], pChar[1], pChar[2], pChar[3], length);
		out.write((char *)rChar, length);
		i += 4;
	}
	out.clear(); out.close();
	in.clear(); in.close();
}

int main(int argc, char **argv)
{
	if (argc != 4) { cout << "usage: Base64 <e|d> <input> <output>"; exit(1); }
	if (argv[1][0] == 'd') Base64DecodeFile(argv[2], argv[3]);
	else if (argv[1][0] == 'e') Base64EncodeFile(argv[2], argv[3]);
	else { cout << "PARAM ERROR!"; exit(2); }
	return(0);
}