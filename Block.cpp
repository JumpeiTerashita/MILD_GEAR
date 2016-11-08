#include "Block.h"
#include "glut.h"

/*
typedef struct
{
	float position[2];
	float colorStatus[4];
	float scale;
}BLOCK;
*/

BLOCK block[] =
{
	{
		{ -0.75,-0.77 },
		{ 0, 1, 0, 0 },
		0.6
	},
	{
		{ -0.75,0.1 },
		{ 0, 1, 0, 0 },
		0.6
	},
	{
		{ 0.1,0.1 },
		{ 0, 1, 0, 0 },
		0.6
	},
	{
		{ 0.1,-0.77 },
		{ 0, 1, 0, 0 },
		0.6
	},
};

void blockDisp()
{
	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_LINE_STRIP);	// マップデータ　ブロック
		glColor4f(block[i].colorStatus[0], block[i].colorStatus[1], block[i].colorStatus[2], block[i].colorStatus[3]);
		glVertex3f(block[i].position[0], block[i].position[1], 0.0);
		glVertex3f(block[i].position[0], block[i].position[1] + block[i].scale, 0.0);
		glVertex3f(block[i].position[0] + block[i].scale, block[i].position[1] + block[i].scale, 0.0);
		glVertex3f(block[i].position[0] + block[i].scale, block[i].position[1], 0.0);
		glVertex3f(block[i].position[0], block[i].position[1], 0.0);
		glEnd();	//ここまで
	}
}

bool BlockDetection()
{

	{

	}

	return true;
}