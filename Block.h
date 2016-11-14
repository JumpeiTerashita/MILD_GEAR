#pragma once

typedef struct
{
	float position[2];
	float colorStatus[4];
	float scale;
}BLOCK;

extern BLOCK block[4];
extern void blockDisp();
extern bool BlockDetection_playerX(float* position);
extern bool BlockDetection_playerY(float* position);
extern bool BlockDetection_bullet(float* position);