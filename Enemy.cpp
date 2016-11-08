#define _USE_MATH_DEFINES
#include <math.h>
#include "GameManager.h"
#include "glut.h"
#include "Enemy.h"

OBJECT enemy[] =
{
	{
		{ -0.5f,0,0 },
		{ 1.f / 60,1.f / 60,0 },
		0,
		0.03,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ 0.5f,0,0 },
		{ 0.5f / 60,0.5f / 60,0 },
		0,
		0.03,
		180,
		6,
		{ 0, 1, 0, 1 },
		true
	},
	{
		{ -0.5f,0.5f,0 },
		{ 1.f / 60,1.f / 60,0 },
		0,
		0.03,
		180,
		6,
		{ 0, 0, 1, 1 },
		true
	},
};

void enemyDisp()
{
	enemy[1].angleDeg = atan2f(enemy[1].speed[0], enemy[1].speed[1]) * 180 / M_PI;

	glBegin(GL_TRIANGLE_FAN);	// éãäEÅiêÓå`Åj
	glColor4f(0, 1, 1, 0.5);
	glVertex3f(enemy[1].position[0], enemy[1].position[1], 0.0);	// GLfloat x, y, z
	for (int i = 0; i <= 3; i++)
	{
		float x = enemy[1].position[0] + 0.25*cosf(M_PI* i / 16 + enemy[1].angleDeg);
		float y = enemy[1].position[1] + 0.25*sinf(M_PI* i / 16 + enemy[1].angleDeg);
		glVertex3f(x, y, 0);
	}
	glEnd();	//Ç±Ç±Ç‹Ç≈

	int ballMax = 3;

	for (int i = 0; i < ballMax; i++)
	{

		if (enemy[i]._is_active == true)
		{

			glPushMatrix();
			{
				addVector(enemy[i].position, enemy[i].position, enemy[i].speed);
				glColor4f(enemy[i].colorStatus[0], enemy[i].colorStatus[1], enemy[i].colorStatus[2], enemy[i].colorStatus[3]);
				glTranslatef(enemy[i].position[0], enemy[i].position[1], enemy[i].position[2]);
				glutSolidSphere(enemy[i].radius, enemy[i].slices, enemy[i].stacks);
			}
			glPopMatrix();
		}
	}
}

void collisionDetection()
{
	for (int i = 0; i < 3; i++)
	{
		for (int n = 0; n < 3; n++)
		{
			if (enemy[i].position[n] <= -1 + enemy[i].radius || enemy[i].position[n] >= 1 - enemy[i].radius)
			{
				enemy[i].speed[n] = -enemy[i].speed[n];
			}
		}
	}

	int ballMax = 3;
	for (int first = 0; first < ballMax; first++)
	{
		for (int second = first + 1; second < ballMax; second++)
		{
			if (!enemy[first]._is_active) continue;
			if (!enemy[second]._is_active) continue;
			float x = enemy[first].position[0] - enemy[second].position[0];
			float x2 = powf(x, 2.0);
			float y = enemy[first].position[1] - enemy[second].position[1];
			float y2 = powf(y, 2.0);
			float r2 = powf(enemy[first].radius, 2.0);

			if (r2 * 2 >= (x2 + y2))
			{
				for (int i = 0; i < 3; i++)
				{
					enemy[first].speed[i] = -enemy[first].speed[i];
					enemy[second].speed[i] = -enemy[second].speed[i];
					/*	ball[first].colorStatus[i] = (rand() % 5) *0.1f + 0.5f;
					ball[second].colorStatus[i] = (rand() % 10) *0.1f + 0.5f;*/
				}
			}
		}
	}
}
