#pragma once

typedef struct
{
	float position[2];
	float colorStatus[4];
	float scale;
}BLOCK;

extern BLOCK block[4];
extern void blockDisp();
extern bool BlockDetection();