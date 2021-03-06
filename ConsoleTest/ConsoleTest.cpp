// ConsoleTest.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//
#include "stdafx.h"
#include <thread>

void menu();
void SpecificDataRead();
void SpecificDataWrite();

int main()
{
	CycleThread();


	//menu();
	
	
	int selection;
	do {
		cin >> selection;
		Load(0, selection, 0);
	} while (selection = 5);
	
	
	return 0;
}

void menu()
{
	int selection;
	do {
		system("cls");
		cout << "1. 선택된 데이터 읽기" << endl;
		cout << "2. 선택된 데이터 쓰기" << endl;
		
		cin >> selection;
		switch (selection)
		{
		case 0:
			CreateEmptyFile(0);
			break;
		case 1:
			SpecificDataRead();
			break;
		case 2:
			SpecificDataWrite();
			break;
		case 3:
			break;
		default:
			break;
		}
	} while (selection = 5);
}

void CycleThread() {
	thread([&]
	{
		while (true)
		{
			this_thread::sleep_for(chrono::seconds(RefreshTime));
			UpdateActive(5.0);
			UnloadProcess();
			ShowProcess();
		}
	}).detach();
}

/*
void DataRead()
{
	FILE *stream;
	errno_t err;
	string address = (string)Path + "1";
	err = fopen_s(&stream, address.c_str(), "r");
	if (err == 0)
	{
		Neuron *data = new Neuron[SectorCount];
		for (int i = 0; i<SectorCount; i++)
		{
			fread(&data[i].header, sizeof(BYTE), 1, stream);
			fread(&data[i].info, sizeof(BYTE), 1, stream);
			fread(&data[i].threshold, sizeof(BYTE16), 1, stream);
			fread(&data[i].alpha, sizeof(float), 1, stream);
		}
	}
	else
	{
		cout << "Data Read Error" << endl;
	}
	fclose(stream);
}
*/
