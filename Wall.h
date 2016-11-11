#pragma once

typedef struct
{
	float position[2];
	float colorStatus[4];
}WALL;

extern WALL wallPackage_01[6];
extern bool WallDetection_player(float* position);
extern bool WallDetection_bullet(float* position);
extern void stageDisp();
