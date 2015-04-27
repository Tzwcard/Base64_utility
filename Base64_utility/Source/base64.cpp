#include"..\Include\base64.h"

BASE64::BASE64(void)
{
	init(); 
}

BASE64::~BASE64(void)
{
	;
}

void BASE64::init(void)
{
	base64String = "";
	rawString = "";
	blockSize = 0;

	int i = 0;
	for (i = 0; i < 4; i++) buffer[i] = 0x00;

	for (i = 0; i < 256; i++) cBase64DecodeChars[i] = 99;
	for (i = 0; i < 64; i++) cBase64DecodeChars[cBase64EncodeChars[i]] = i;
	cBase64DecodeChars['='] = 98;
}

void BASE64::encode(char* input, size_t length)
{
	rawString = "";
	base64String = "";

	rawString.insert(rawString.size(), (char*)input, length);

	size_t i = length, j = 0, k = 0;
	while (j < length)
	{
		if (j + 3 <= length) blockSize = 3;
		else blockSize = (length % 3) ;
		for (k = 0; k < blockSize; k++) buffer[k] = input[3 * (j / 3) + k];
		blockBase64Encode();
		base64String.insert(base64String.size(), (char*)buffer, 4);
		j += 3;
	}
}

bool BASE64::decode(char* input, size_t length)
{
	if ((length & 0x3) != 0) return(false);

	base64String = "";
	rawString = "";

	base64String.insert(base64String.size(), (char*)input, length);

	size_t i = 0;
	int k = 0;
	while (i < (length >> 2))
	{
		for (k = 0; k < 4; k++)
			buffer[k] = input[4 * i + k];
		if (validateCharOfB64() == false) return(false);
		blockBase64Decode();
		rawString.insert(rawString.size(), (char*)buffer, blockSize);
		i++;
	}
	return(true);
}

void BASE64::encode(char* inputFilename, char* outputFilename)
{
	;
}
bool BASE64::decode(char* inputFilename, char* outputFilename)
{
	return(true);
}

void BASE64::blockBase64Encode(void)
{
	if (blockSize == 1)
	{
		buffer[3] = '=';
		buffer[2] = '=';
		buffer[1] = cBase64EncodeChars[(buffer[0] & 0x03) << 4];
		buffer[0] = cBase64EncodeChars[buffer[0] >> 2];
	}
	else if (blockSize == 2)
	{
		buffer[3] = '=';
		buffer[2] = cBase64EncodeChars[(buffer[1] & 0x0f) << 2];
		buffer[1] = cBase64EncodeChars[(buffer[0] & 0x03) << 4 | (buffer[1] >> 4)];
		buffer[0] = cBase64EncodeChars[buffer[0] >> 2];
	}
	else {
		buffer[3] = cBase64EncodeChars[buffer[2] & 0x3f];
		buffer[2] = cBase64EncodeChars[(buffer[1] & 0x0f) << 2 | (buffer[2] >> 6)];
		buffer[1] = cBase64EncodeChars[(buffer[0] & 0x03) << 4 | (buffer[1] >> 4)];
		buffer[0] = cBase64EncodeChars[buffer[0] >> 2];	
	}
}

void BASE64::blockBase64Decode(void)
{
	if (buffer[3] == '='&&buffer[2] == '=') 
	{
		buffer[0] = cBase64DecodeChars[buffer[0]] << 2 | ((cBase64DecodeChars[buffer[1]] & 0x30) >> 4);
		blockSize = 1;
	}
	else if (buffer[3] == '=')
	{
		buffer[0] = cBase64DecodeChars[buffer[0]] << 2 | ((cBase64DecodeChars[buffer[1]] & 0x30) >> 4);
		buffer[1] = ((cBase64DecodeChars[buffer[1]] & 0x0f) << 4) | ((cBase64DecodeChars[buffer[2]] & 0x3c) >> 2);
		blockSize = 2;
	}
	else {
		buffer[0] = cBase64DecodeChars[buffer[0]] << 2 | ((cBase64DecodeChars[buffer[1]] & 0x30) >> 4);
		buffer[1] = ((cBase64DecodeChars[buffer[1]] & 0x0f) << 4) | ((cBase64DecodeChars[buffer[2]] & 0x3c) >> 2);
		buffer[2] = (cBase64DecodeChars[buffer[2]] & 0x03) << 6 | cBase64DecodeChars[buffer[3]];
		blockSize = 3;
	}
}

bool BASE64::validateCharOfB64(void)
{
	for (int pos = 0; pos < 4;pos++)
	if ((cBase64DecodeChars[buffer[pos]] == 99) || ((cBase64DecodeChars[buffer[pos]] == 98) && (pos <= 2))) return(false);
	return(true);
}

string BASE64::encodedGetResult(void)
{
	return(base64String);
}

string BASE64::encodedGetRaw(void)
{
	return(decodedGetResult());
}

string BASE64::decodedGetResult(void)
{
	return(rawString);
}

string BASE64::decodedGetRaw(void)
{
	return(encodedGetResult());
}