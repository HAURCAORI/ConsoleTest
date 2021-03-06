// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <time.h>

#define SectorSize 512 //512KB
#define SectorCount 65536
#define InputSectorSize 8
#define InputSectorCount 256
#define BUFFER_SIZE 512
#define Path "D:/ProjectN/Data/"
#define NeuronSize sizeof(Neuron)
#define InputNeuronInfoSize 26
#define RefreshTime 1 //sec
#define SuspendTime 1000 //ms
#define MaxLoad 100

typedef unsigned char BYTE;
typedef unsigned char* BYTES;
typedef unsigned short BYTE16;
typedef __int8 BIT;
typedef unsigned short SECTOR;
typedef int PAGE;

using namespace std;

struct Neuron
{
	BYTE header;
	BYTE info;
	BYTE16 threshold;
	float alpha;
};

struct ActiveNeuron
{
	struct Neuron neuron;
	SECTOR sector;
	PAGE page;
	clock_t time_active;
	float sender;
};

struct InputNeuron
{
	struct Neuron neuron;
	char info[InputNeuronInfoSize];
};
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//main
void CycleThread();

//dataio
void CreateEmptyFile(PAGE page);
void CreateEmptyInput();
void SpecificDataRead();
void SpecificDataWrite();

//calculate
BIT getBit(BYTE value, int n);
BIT getBit(Neuron value, int n);
void setBit(Neuron &target, int n, BIT value);
unsigned char* getByteString(Neuron source);
unsigned char* getByteString(string source);

//dataprocess
void Load(PAGE page, SECTOR sector, float sender);
void UnloadProcess();
void Save(ActiveNeuron active);
void ShowProcess();
void UpdateActive(float value);