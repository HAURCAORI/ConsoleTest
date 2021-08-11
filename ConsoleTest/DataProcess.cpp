#include "stdafx.h"

const BYTE Active = 0x80;
const BYTE Inactive = 0x00;
const BYTE Type_Input = 0x00;
const BYTE Type_Output = 0x20;
const BYTE Type_Process = 0x40;
const BYTE Type_Transfer = 0x60;

const BYTE Mask_Active = 0x80;
const BYTE Mask_Type = 0x60;

list<ActiveNeuron> list_neuron;


void Load(PAGE page, SECTOR sector, float sender)
{
	Neuron data;

	FILE *stream;
	errno_t err;
	string address = (string)Path + "1";
	err = fopen_s(&stream, address.c_str(), "r");
	if (err == 0)
	{
		fseek(stream, NeuronSize * sector, SEEK_SET);
		fread(&data.header, sizeof(BYTE), 1, stream);
		fread(&data.info, sizeof(BYTE), 1, stream);
		fread(&data.threshold, sizeof(BYTE16), 1, stream);
		fread(&data.alpha, sizeof(float), 1, stream);
	}
	else
	{
		cout << "Data Read Error" << endl;
	}
	fclose(stream);

	ActiveNeuron temp;
	temp.neuron = data;
	temp.page = page;
	temp.sector = sector;
	temp.time_active = clock();

	if ((data.header & Mask_Active) == Active)
	{
		list_neuron.push_back(temp);
		if (temp.neuron.header & Mask_Type == Type_Process)
		{
			
		}
		else if (temp.neuron.header & Mask_Type == Type_Transfer)
		{

		}
	}
	else {
		temp.neuron.header |= Active;
		Save(temp);
	}
}

void LoadInput(SECTOR sector)
{
	Neuron data;
	InputNeuron temp;
	FILE *stream;
	errno_t err;
	string address = (string)Path + "INPUT";
	err = fopen_s(&stream, address.c_str(), "r");
	if (err == 0)
	{
		fseek(stream, NeuronSize * sector, SEEK_SET);
		fread(&data.header, sizeof(BYTE), 1, stream);
		fread(&data.info, sizeof(BYTE), 1, stream);
		fread(&data.threshold, sizeof(BYTE16), 1, stream);
		fread(&data.alpha, sizeof(float), 1, stream);
		fread(&temp.info, InputNeuronInfoSize, 1, stream);
	}
	else
	{
		cout << "Data Read Error" << endl;
	}
	fclose(stream);

	temp.neuron = data;
}

void Save(ActiveNeuron active)
{
	errno_t err;
	FILE *stream = NULL;
	string address = (string)Path + "1";
	err = fopen_s(&stream, address.c_str(), "r+b");
	if (err == 0)
	{
		char bytes[NeuronSize];
		memcpy(bytes, &active.neuron, NeuronSize);
		fseek(stream, NeuronSize * active.sector, SEEK_SET);
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

void UnloadProcess()
{
	list<ActiveNeuron>::iterator iter = list_neuron.begin();
	for (; iter != list_neuron.end(); )
	{
		if (difftime(clock(), iter->time_active) > SuspendTime)
		{
			Save(*iter);
			iter = list_neuron.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void ShowProcess()
{
	list<ActiveNeuron>::iterator iter = list_neuron.begin();
	for (; iter != list_neuron.end(); iter++)
	{
		cout << "½Ã°£ : " << clock() << " / " <<    iter->time_active << endl;
	}
}

void UpdateAlpha(ActiveNeuron active, float value)
{
	active.neuron.alpha = value;
}

void UpdateActive(float value)
{
	list<ActiveNeuron>::iterator iter = list_neuron.begin();
	for (; iter != list_neuron.end(); iter++)
	{
		iter->neuron.alpha = value;
	}
}