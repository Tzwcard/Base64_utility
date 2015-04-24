#include"..\Include\base64.h"

BASE64::BASE64(void)
{
	clear(); 
}
BASE64::BASE64(string type, string inputStr)
{
	clear();
	if (stricmp(type.c_str(), "encode") == 0)
		encode(inputStr);
	else if (stricmp(type.c_str(), "decode") == 0)
		decode(inputStr);
}
BASE64::BASE64(string type, string input, string output)
{
	clear();
	if (stricmp(type.c_str(), "encode") == 0)
		encode(input, output);
	else if (stricmp(type.c_str(), "decode") == 0)
		decode(input, output);
}

BASE64::~BASE64(void)
{
	;
}

void BASE64::clear(void)
{
	setInputFilename("");
	setOutputFilename("");
	setInputString("");
	memset(buffer, 0x00, sizeof(buffer));
}

void BASE64::encode(string inputStr)
{
	setInputString(inputStr);
	Base64EncodeString();
}

void BASE64::decode(string inputStr)
{
	setInputString(inputStr);
	Base64DecodeString();
}

void BASE64::encode(string input, string output)
{
	setInputFilename(input);
	setOutputFilename(output);
	Base64EncodeFile();
}
void BASE64::decode(string input, string output)
{
	setInputFilename(input);
	setOutputFilename(output);
	Base64DecodeFile();
}

void BASE64::setInputFilename(string input)
{
	inputFilename = input;
}
void BASE64::setOutputFilename(string input)
{
	outputFilename = input;
}
void BASE64::setInputString(string input)
{
	base64String = input;
}

void BASE64::blockBase64Encode(void)
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
void BASE64::blockBase64Decode(void)
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

void BASE64::Base64EncodeFile(void)
{
	;
}
void BASE64::Base64DecodeFile(void)
{
	;
}
void BASE64::Base64EncodeString(void)
{
	;
}
void BASE64::Base64DecodeString(void)
{
	;
}

bool BASE64::validateCharOfB64(unsigned char input, size_t posOfInput)
{
	;
}