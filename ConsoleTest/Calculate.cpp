#include "stdafx.h"
#include <bitset>
#include <vector>
#include <sstream>

vector<string> split(string input, char delimiter);

BIT getBit(BYTE value, int n)
{
	return (value >> (7-n)) & 1;
}

BIT getBit(Neuron value, int n)
{
	char bytes[NeuronSize];
	memcpy(bytes, &value, NeuronSize);
	return (bytes[n/ 8] >> (7 - n % 8)) & 1;
}

void setBit(Neuron &target, int n, BIT value)
{
	char bytes[NeuronSize];
	memcpy(bytes, &target, NeuronSize);
	bytes[n / 8] = ( bytes[n / 8] & ~(1UL << (7- n%8))) | (value << (7- n%8));
	memcpy(&target, &bytes, NeuronSize);
}

unsigned char* getByteString(Neuron source)
{
	char bytes[NeuronSize];
	memcpy(bytes, &source, NeuronSize);

	static unsigned char byte[(sizeof(bytes))*16];
	unsigned char i,j;

	for (i = 0; i < sizeof(bytes); i++) {
		for (j = 0; j < 8; j++)
		{
			byte[(i+1)*9-2-j] = '0' + (bytes[i] & 1);
			bytes[i] >>= 1;
		}
		byte[(i + 1) * 9 - 1] = ' ';
	}
	return byte;
}

unsigned char* getByteString(string source)
{
	char bytes[sizeof(source)];
	memcpy(bytes, &source, sizeof(source));
	static unsigned char byte[NeuronSize];
	unsigned char i, n;

	vector<string> result = split(source, ' ');
	n = (result.size() < 8) ? result.size() : 8;
	for (i = 0; i < n; i++) {
		bitset<8> b(result[i]);
		byte[i] = (b.to_ulong() & 0xFF);
	}
	return byte;
}

vector<string> split(string input, char delimiter) {
	vector<string> answer;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		answer.push_back(temp);
	}

	return answer;
}