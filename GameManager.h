#pragma once

typedef struct 
{
	unsigned char LastKey;
	unsigned char PressedKey;
	unsigned char ReleasedKey;
	unsigned char ChangedKey;
	unsigned char DownKey;
	unsigned char UpKey;
	int AnalogX;
	int AnalogY;
}INPUTMANAGER;

typedef struct 
{
	float position[3];
	float speed[3];
	float angleDeg;
	double radius;
	int slices;
	int stacks;
	float colorStatus[4];
	bool _is_active;
}OBJECT;

extern INPUTMANAGER input;
extern OBJECT player,enemy[3];