#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "GameManager.h"
#include "glut.h"
#include "Enemy.h"

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

enum
{
	ENEMY_CAMERA_01,
	ENEMY_CAMERA_02,
	ENEMY_CAMERA_03,
	ENEMY_CAMERA_04,
	ENEMY_SOLDIER_01,
	ENEMY_SOLDIER_02,
	ENEMY_SOLDIER_03
};

OBJECT enemy[7] =
{
	{
		{ -0.75f,-0.17f,0 },
		{ 0,0,0 },
		60 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ -0.15f,0.1f,0 },
		{ 0,0,0 },
		15 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ -0.5f,0.5f,0 },
		{ 0,0,0 },
		0 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ -0.5f,0.5f,0 },
		{ 0,0,0 },
		0 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ -0.5f,0.5f,0 },
		{ 0,0,0 },
		0 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ -0.5f,0.5f,0 },
		{ 0,0,0 },
		0 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ -0.5f,0.5f,0 },
		{ 0,0,0 },
		0 * 3.14159265358f / 180.f,
		0.01f,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
};

int enemyState[7] = { 0 };

void enemyDisp()
{
	const int enemyMax = 7;

	//視界表示
	for (int n = 0; n < enemyMax; n++)
	{
		if (enemy[n]._is_active == true)
		{
			//printf("\r%f\n", enemy[1].angleDeg);
			glBegin(GL_TRIANGLE_FAN);	// 視界（扇形）
			if (enemySightColision(n))
			{
				glColor4f(1, 0, 0, 0.5);
			}
			else glColor4f(0, 1, 1, 0.5);
			glVertex3f(enemy[n].position[0], enemy[n].position[1], 0.0);	// GLfloat x, y, z
			for (int i = 0; i <= 3; i++)
			{
				float x = enemy[n].position[0] + 0.25*cosf(M_PI* i / 16 + enemy[n].angleRad);
				float y = enemy[n].position[1] + 0.25*sinf(M_PI* i / 16 + enemy[n].angleRad);
				glVertex3f(x, y, 0);
			}
			glEnd();	//ここまで
		}

	}





	for (int i = 0; i < enemyMax; i++)
	{

		if (enemy[i]._is_active == true)
		{
			if (GameState != SCENE_GAMEOVER&&GameState != SCENE_GAMECLEAR)
			{
				enemyMove(i);
				addVector(enemy[i].position, enemy[i].position, enemy[i].speed);
			}
			glPushMatrix();
			{
				glColor4f(enemy[i].colorStatus[0], enemy[i].colorStatus[1], enemy[i].colorStatus[2], enemy[i].colorStatus[3]);
				glTranslatef(enemy[i].position[0], enemy[i].position[1], enemy[i].position[2]);
				glutSolidSphere(enemy[i].radius, enemy[i].slices, enemy[i].stacks);
			}
			glPopMatrix();
		}
	}


}

void enemyMove(int enemy_number)
{
	float enemyAngleDeg = enemy[enemy_number].angleRad * 180 / M_PI;

	if (enemySightColision(enemy_number))
	{
		GameState = SCENE_GAMEOVER;
	}

	switch (enemy_number)
	{
	case ENEMY_CAMERA_01:
		switch (enemyState[enemy_number])
		{
		case 0:
			enemyAngleDeg += 0.25f;
			if (enemyAngleDeg >= 165) enemyState[enemy_number] = 1;
			break;
		case 1:
			enemyAngleDeg -= 0.25f;
			if (enemyAngleDeg <= 60) enemyState[enemy_number] = 0;
			break;
		}
		enemy[enemy_number].angleRad = enemyAngleDeg*M_PI / 180;
		break;
	case ENEMY_CAMERA_02:
		switch (enemyState[enemy_number])
		{
		case 0:
			enemyAngleDeg -= 0.25f;
			if (enemyAngleDeg <= -105) enemyState[enemy_number] = 1;
			break;
		case 1:
			enemyAngleDeg += 0.25f;
			if (enemyAngleDeg >= -15) enemyState[enemy_number] = 0;
			break;
		}
		enemy[enemy_number].angleRad = enemyAngleDeg*M_PI / 180;
		break;
	case ENEMY_CAMERA_03:
		switch (enemyState[enemy_number])
		{
		case 0:
			enemyAngleDeg += 0.2f;
			if (enemyAngleDeg >= -30) enemyState[enemy_number] = 1;
			break;
		case 1:
			enemyAngleDeg -= 0.2f;
			if (enemyAngleDeg <= -90) enemyState[enemy_number] = 0;
			break;
		}
		enemy[enemy_number].angleRad = enemyAngleDeg*M_PI / 180;
		break;
	case ENEMY_CAMERA_04:
		switch (enemyState[enemy_number])
		{
		case 0:
			enemyAngleDeg += 0.18f;
			if (enemyAngleDeg >= -15) enemyState[enemy_number] = 1;
			break;
		case 1:
			enemyAngleDeg -= 0.18f;
			if (enemyAngleDeg <= -105) enemyState[enemy_number] = 0;
			break;
		}
		enemy[enemy_number].angleRad = enemyAngleDeg*M_PI / 180;
		break;
	case ENEMY_SOLDIER_01:
		switch (enemyState[enemy_number])
		{
		case 0:
			enemy[enemy_number].speed[0] = -0.0015f;
			if (enemy[enemy_number].position[0] <= -0.74f)
			{
				enemy[enemy_number].speed[0] = 0;
				enemyState[enemy_number] = 1;
			}
			break;
		case 1:
			enemyAngleDeg /= 1.01f;
			if (enemyAngleDeg <= 70) enemyState[enemy_number] = 2;
			break;
		case 2:
			enemyAngleDeg *= 1.01f;
			if (enemyAngleDeg >= 255) enemyState[enemy_number] = 3;
			break;
		case 3:
			enemyAngleDeg -= 5.03f;
			if (enemyAngleDeg <= -15) enemyState[enemy_number] = 4;
			break;
		case 4:
			enemy[enemy_number].speed[0] = 0.0015f;
			if (enemy[enemy_number].position[0] >= 0.78f)
			{
				enemy[enemy_number].speed[0] = 0;
				enemyState[enemy_number] = 5;
			}
			break;
		case 5:
			enemyAngleDeg -= 1.01f;
			if (enemyAngleDeg <= -115) enemyState[enemy_number] = 6;
			break;
		case 6:
			enemyAngleDeg += 1.01f;
			if (enemyAngleDeg >= 75) enemyState[enemy_number] = 7;
			break;
		case 7:
			enemyAngleDeg -= 5.11f;
			if (enemyAngleDeg <= -195)
			{
				enemyState[enemy_number] = 0;
				enemyAngleDeg = 165;
			}
			break;
		}
		enemy[enemy_number].angleRad = enemyAngleDeg*M_PI / 180;
		break;
	default:
		enemy[enemy_number].angleRad = atan2f(enemy[enemy_number].speed[0], enemy[enemy_number].speed[1]) * 180 / M_PI;
		break;
	}




}

bool enemySightColision(int enemy_number)
{
	float upEndPos[2] /*点A*/, downEndPos[2] /*点B*/, enemyPos[2] /*点C*/, playerPos[2] /*点P*/;

	upEndPos[0] = enemy[enemy_number].position[0] + 0.25*cosf(enemy[enemy_number].angleRad);
	upEndPos[1] = enemy[enemy_number].position[1] + 0.25*sinf(enemy[enemy_number].angleRad);
	downEndPos[0] = enemy[enemy_number].position[0] + 0.25*cosf(M_PI * 3 / 16 + enemy[enemy_number].angleRad);
	downEndPos[1] = enemy[enemy_number].position[1] + 0.25*sinf(M_PI * 3 / 16 + enemy[enemy_number].angleRad);
	enemyPos[0] = enemy[enemy_number].position[0];
	enemyPos[1] = enemy[enemy_number].position[1];
	playerPos[0] = player.position[0];
	playerPos[1] = player.position[1];

	float VectorAB[2], VectorBC[2], VectorCA[2], VectorAP[2], VectorBP[2], VectorCP[2];

	VectorAB[0] = downEndPos[0] - upEndPos[0];
	VectorAB[1] = downEndPos[1] - upEndPos[1];
	VectorBC[0] = enemyPos[0] - downEndPos[0];
	VectorBC[1] = enemyPos[1] - downEndPos[1];
	VectorCA[0] = upEndPos[0] - enemyPos[0];
	VectorCA[1] = upEndPos[1] - enemyPos[1];
	VectorAP[0] = playerPos[0] - upEndPos[0];
	VectorAP[1] = playerPos[1] - upEndPos[1];
	VectorBP[0] = playerPos[0] - downEndPos[0];
	VectorBP[1] = playerPos[1] - downEndPos[1];
	VectorCP[0] = playerPos[0] - enemyPos[0];
	VectorCP[1] = playerPos[1] - enemyPos[1];

	//外積　c1,c2,c3
	float c1 = VectorAB[0] * VectorBP[1] - VectorAB[1] * VectorBP[0];
	float c2 = VectorBC[0] * VectorCP[1] - VectorBC[1] * VectorCP[0];
	float c3 = VectorCA[0] * VectorAP[1] - VectorCA[1] * VectorAP[0];

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0))
	{
		//三角形内部に点がある
		return true;
	}
	return false;
}


