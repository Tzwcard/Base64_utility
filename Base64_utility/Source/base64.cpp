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
	length = 0;
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
		buffer[3] = '=';
		buffer[2] = '=';
		buffer[1] = Base64EncodeChars[(buffer[0] & 0x03) << 4];
		buffer[0] = Base64EncodeChars[buffer[0] >> 2];
	}
	else if (length == 2) {
		buffer[3] = '=';
		buffer[2] = Base64EncodeChars[(buffer[1] & 0x0f) << 2];
		buffer[1] = Base64EncodeChars[(buffer[0] & 0x03) << 4 | (buffer[1] >> 4)];
		buffer[0] = Base64EncodeChars[buffer[0] >> 2];
	}
	else {
		buffer[3] = Base64EncodeChars[buffer[2] & 0x3f];
		buffer[2] = Base64EncodeChars[(buffer[1] & 0x0f) << 2 | (buffer[2] >> 6)];
		buffer[1] = Base64EncodeChars[(buffer[0] & 0x03) << 4 | (buffer[1] >> 4)];
		buffer[0] = Base64EncodeChars[buffer[0] >> 2];	
	}
}

void BASE64::blockBase64Decode(void)
{
	if (buffer[3] == '='&&buffer[2] == '=') {
		buffer[0] = Base64DecodeChars[buffer[0]] << 2 | ((Base64DecodeChars[buffer[1]] & 0x30) >> 4);
		buffer[1] = '0';
		buffer[2] = '0';
		length = 1;
	}
	else if (buffer[2] == '='){
		buffer[0] = Base64DecodeChars[buffer[0]] << 2 | ((Base64DecodeChars[buffer[1]] & 0x30) >> 4);
		buffer[1] = ((Base64DecodeChars[buffer[1]] & 0x0f) << 4) | ((Base64DecodeChars[buffer[2]] & 0x3c) >> 2);
		buffer[2] = '0';
		length = 2;
	}
	else {
		buffer[0] = Base64DecodeChars[buffer[0]] << 2 | ((Base64DecodeChars[buffer[1]] & 0x30) >> 4);
		buffer[1] = ((Base64DecodeChars[buffer[1]] & 0x0f) << 4) | ((Base64DecodeChars[buffer[2]] & 0x3c) >> 2);
		buffer[2] = (Base64DecodeChars[buffer[2]] & 0x03) << 6 | Base64DecodeChars[buffer[3]];
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
