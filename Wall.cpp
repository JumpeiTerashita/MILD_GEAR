#include "Wall.h"
#include "glut.h"

WALL wallPackage_01[6] =
{
	{
		{-0.9f,-1.0f},
		{ 0, 1, 0, 0 }
	},
	{
		{ -0.9f,0.9f },
		{ 0, 1, 0, 0 }
	},
	{
		{ 0.9f,0.9f },
		{ 0, 1, 0, 0 }
	},
	{
		{ 0.9f,-0.9f },
		{ 0, 1, 0, 0 }
	},
	{
		{ -0.75f,-0.9f },
		{ 0, 1, 0, 0 }
	},
	{
		{ -0.75f,-1.0f },
		{ 0, 1, 0, 0 }
	}
};

bool WallDetection_player(float* position)
{
	if (position[0] <= wallPackage_01[0].position[0] + 0.04) return true;
	else if (position[1] >= wallPackage_01[1].position[1] - 0.04) return true;
	else if (position[0] >= wallPackage_01[2].position[0] - 0.04) return true;
	else if ((position[0] <= wallPackage_01[3].position[0] + 0.04&&position[0] >= wallPackage_01[4].position[0] - 0.04) && position[1] <= wallPackage_01[4].position[1] + 0.04) return true;
	else if (position[1] <= -1) return true;
	return false;
}

bool WallDetection_bullet(float* position)
{
	if (position[0] <= wallPackage_01[0].position[0]) return true;
	else if (position[1] >= wallPackage_01[1].position[1]) return true;
	else if (position[0] >= wallPackage_01[2].position[0]) return true;
	else if ((position[0] <= wallPackage_01[3].position[0] &&position[0] >= wallPackage_01[4].position[0]) && position[1] <= wallPackage_01[4].position[1]) return true;
	else if (position[1] <= -1) return true;
	return false;
}

void stageDisp()
{
	glBegin(GL_LINE_STRIP);	// マップデータ 地形
	for (int i = 0; i < 6; i++)
	{
		glColor4f(wallPackage_01[i].colorStatus[0], wallPackage_01[i].colorStatus[1], wallPackage_01[i].colorStatus[2], wallPackage_01[i].colorStatus[3]);
		glVertex3f(wallPackage_01[i].position[0], wallPackage_01[i].position[1], 0.0);	// GLfloat x, y, z
	}
	glEnd();	//ここまで
}