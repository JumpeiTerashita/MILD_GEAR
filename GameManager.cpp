#include <math.h>
#include <stdio.h>
#include "GameManager.h"
#include "glut.h"
#define _USE_MATH_DEFINES

INPUTMANAGER input = { 0 };

/*
typedef struct {
	float position[3];
	float speed[3];
	float angleRad;
	double radius;
	int slices;
	int stacks;
	float colorStatus[4];
	bool _is_active;
}OBJECT;
*/

OBJECT player =
{
	{ -0.825f,-0.95f,0 },
	{ 0,0,0 },
	0,
	0.1f,
	180,
	18,
	{1,1,1,0}
};

void addVector(float* _vOut, float* _v0, float* _v1)
{
	for (int i = 0; i < 3; i++)
	{
		_vOut[i] = _v0[i] + _v1[i];
	}
}

void DrawString(const char* str)
{
	while (*str != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str++);
	}
}

void DrawBits(int bits)
{
	int bitsBox[8] = { 0 };
	int bits_copy = bits;
	for (int i = 0; bits_copy > 0; i++)
	{
		bitsBox[i] = bits_copy % 2;
		bits_copy = bits_copy / 2;

	}
	for (int n = 7; n >= 0; n--)
	{
		switch (bitsBox[n])
		{
		case 0:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
			break;
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
			break;
		}
	}

}

void KeyDisp()
{
	glPushMatrix();
	{
		glRasterPos2f(-1, 0);
		DrawString("PressedKey :");
		DrawBits(input.PressedKey);
		glRasterPos2f(-1, -0.1);
		DrawString("ReleasedKey:");
		DrawBits(input.ReleasedKey);
		glRasterPos2f(-1, -0.2);
		DrawString("LastKey    :");
		DrawBits(input.LastKey);
		glRasterPos2f(-1, -0.3);
		DrawString("ChangedKey :");
		DrawBits(input.ChangedKey);
		glRasterPos2f(-1, -0.4);
		DrawString("UpKey      :");
		DrawBits(input.UpKey);
		glRasterPos2f(-1, -0.5);
		DrawString("DownKey    :");
		DrawBits(input.DownKey);
	}
	glPopMatrix();


	return;
}

int GameState = 1;
float playerAngleRad = 0;
bool ClearFlag = false;

void gameClear(float* position)
{
	if (ClearFlag==true&&position[1]<=-0.9)
	{
		glPushMatrix();
		{
			glRasterPos2f(-0.2, -0.05);
			DrawString("GAME CLEAR !");
		}
		glPopMatrix();
		
	}
	return;
}

void titleDisp()
{
	glRasterPos2f(-0.2, -0.05);
	DrawString("MILD GEAR");
}

