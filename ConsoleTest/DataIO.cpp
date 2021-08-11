#include "stdafx.h"
#include <fstream>
#include <vector>
#include <string>

#define _CRT_SECURE_NO_WARNINGS

void CreateEmptyFile(PAGE page)
{
	vector<char> empty(1024, 0);
	string address = (string) Path + to_string(page);
	ofstream ofs(address, ios::binary | ios::out);

	for (int i = 0; i < SectorSize; i++)
	{
		if (!ofs.write(&empty[0], empty.size()))
		{
			cout << "problem writing to file" << endl;
		}
	}
}

void CreateEmptyInput()
{
	vector<char> empty(1024, 0);
	string address = (string)Path + "INPUT";
	ofstream ofs(address, ios::binary | ios::out);

	for (int i = 0; i < InputSectorSize; i++)
	{
		if (!ofs.write(&empty[0], empty.size()))
		{
			cout << "problem writing to file" << endl;
		}
	}
}

void SpecificDataRead()
{
	int selection;
	system("cls");
	cout << "Section : ";
	cin >> selection;
	if (selection < SectorCount && selection >= 0)
	{
		FILE *stream;
		errno_t err;
		string address = (string)Path + "1";
		err = fopen_s(&stream, address.c_str(), "r");
		if (err == 0)
		{
			fseek(stream, NeuronSize*selection, SEEK_SET);
			Neuron data;
			fread(&data.header, sizeof(BYTE), 1, stream); //자료 구조가 바뀌면 수정 필요
			fread(&data.info, sizeof(BYTE), 1, stream);
			fread(&data.threshold, sizeof(BYTE16), 1, stream);
			fread(&data.alpha, sizeof(float), 1, stream);

			cout << getByteString(data) << endl;
			system("Pause");
		}
		else
		{
			cout << "Data Read Error" << endl;
		}
		fclose(stream);
	}
}

void SpecificDataWrite()
{
	int selection;
	string input;
	system("cls");
	cout << "Section : ";
	cin >> selection;
	if (selection < SectorCount && selection >= 0)
	{
		errno_t err;
		FILE *stream = NULL;
		string address = (string)Path + "1";
		err = fopen_s(&stream, address.c_str(), "r+b");
		if (err == 0)
		{
			fseek(stream, NeuronSize * selection, SEEK_SET);
			Neuron data;
			fread(&data.header, sizeof(BYTE), 1, stream); //자료 구조가 바뀌면 수정 필요
			fread(&data.info, sizeof(BYTE), 1, stream);
			fread(&data.threshold, sizeof(BYTE16), 1, stream);
			fread(&data.alpha, sizeof(float), 1, stream);
			cout << getByteString(data) << endl;

			//cin >> input;
			cin.ignore();
			getline(cin, input);
			BYTES c = getByteString(input);
			fseek(stream, NeuronSize * selection, SEEK_SET);
			for (int i = 0; i < NeuronSize; i++)
			{
				fwrite(&c[i], 1, 1, stream);
			}

			system("Pause");
		}
		else
		{
			cout << "Data Read Error" << endl;
		}
		fclose(stream);
	}
}

void AddInput(SECTOR sector, char* info)
{
	errno_t err;
	FILE *stream = NULL;
	string address = (string)Path + "INPUT";
	err = fopen_s(&stream, address.c_str(), "r+b");
	if (err == 0)
	{
		char bytes[NeuronSize];
		fseek(stream, NeuronSize * sector, SEEK_SET);
		for (int i = 0; i < NeuronSize; i++)
		{
			fwrite(&bytes[i], 1, 1, stream);
		}
	}
	else
	{
		cout << "Data Write Error" << endl;
	}
	fclose(stream);
}

void InputTrigger(SECTOR sector)
{

}