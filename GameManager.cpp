#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "GameManager.h"
#include "Enemy.h"
#include "Item.h"
#include "glut.h"


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
	{1,1,1,0},
	true
};

void addVector(float* _vOut, float* _v0, float* _v1)
{
	for (int i = 0; i < 3; i++)
	{
		_vOut[i] = _v0[i] + _v1[i];
	}
}

void DrawString_Stroke(const char* str)
{
	while (*str != '\0')
	{

		glutStrokeCharacter(
			GLUT_STROKE_ROMAN,  // void *font
			*str++);               // int character
	}
}

void DrawString(const char* str)
{
	while (*str != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str++);
	}
}

void statusInit()
{
	player =
	{
		{ -0.825f,-0.95f,0 },
		{ 0,0,0 },
		0,
		0.1f,
		180,
		18,
		{ 1,1,1,0 },
		true
	};
	enemy[0] =
	{
		{ -0.75f,-0.17f,0 },
		{ 0 },
		60 *  3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	};
	enemy[1] =
	{
		{ -0.15f,0.1f,0 },
		{ 0 },
		-15 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	};
	enemy[2] =
	{
		{ 0.1f,-0.77f,0 },
		{ 0 },
		-90 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	};
	enemy[3] =
	{
		{ 0.7f,0.1f,0 },
		{ 0 },
		-105 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	};
	enemy[4] =
	{
		{ 0.6f,-0.047f,0 },
		{ 0 },
		165 * 3.14159265358f / 180.f,
		0.02f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	};
	for (int i = 0; i < 4; i++)
	{
		XFile[i]._gotten = false;
	}
	ItemCounter = 0;
	ClearFlag = false;
}

void KeyDisp()
{

	return;
}

int GameState = 0;
float playerAngleRad = 0;
bool ClearFlag = false;

void gameClear()
{
	if (ClearFlag == true && player.position[1] <= -0.9)
	{
		GameState = SCENE_GAMECLEAR;
		glPushMatrix();
		{
			glRasterPos2f(-0.2, -0.05);
			DrawString("GAME CLEAR !");
		}
		glPopMatrix();
		glPushMatrix();
		{
			glColor4f(1, 1, 0, 1);
			glRasterPos2f(-0.25, -0.97);
			DrawString("PRESS ANY KEY");
		}
		glPopMatrix();
	}
	return;
}

void titleDisp()
{

	glPushMatrix();
	{
		glColor4f(1, 1, 1, 1);
		glTranslatef(-0.73f, 0.3f, 0);
		glScalef(0.001f, 0.001f, 0.001f);
		DrawString_Stroke("M I L D  G E A R");
	}
	glPopMatrix();
	glPushMatrix();
	{
		glColor4f(1, 1, 1, 1);
		glRasterPos2f(-0.5, -0.2);
		DrawString("PRESS  ANY  BUTTON  TO  START");
	}
	glPopMatrix();
	//glRasterPos2f(-0.2, -0.05);
	//DrawString("MILD GEAR");
}

void gameOver()
{
	glPushMatrix();
	{
		glColor4f(1, 0, 0, 1);
		glRasterPos2f(-0.2, -0.05);
		DrawString("GAME OVER");
	}
	glPopMatrix();
	glPushMatrix();
	{
		glColor4f(1, 0, 0, 1);
		glRasterPos2f(-0.25, -0.97);
		DrawString("PRESS ANY KEY");
	}
	glPopMatrix();
}
