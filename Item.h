#pragma once

typedef struct
{
	float position[2];
	float colorStatus[4];
	float scale;
	bool _gotten;
}ITEM;

extern ITEM XFile[4];
extern int ItemCounter;

extern void XFileDisp();
extern void FileGet(float* position);
extern void ItemStatusDisp();