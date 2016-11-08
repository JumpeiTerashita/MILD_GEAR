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
extern OBJECT player;
extern float playerAngleRad;
extern void addVector(float* _vOut, float* _v0, float* _v1);
extern void DrawString(const char* str);
extern void DrawBits(int bits);
extern void KeyDisp();