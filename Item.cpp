#include "glut.h"
#include "Item.h"
#include "GameManager.h"

/*
typedef struct
{
float position[2];
float colorStatus[4];
float scale;
bool _gotten;
}ITEM;
*/

ITEM XFile[4] =
{
	{
		{-0.5f,0.2f},
		{1,1,0,1},
		{0.05f},
		false
	},
	{
		{ 0.2f,0.2f },
		{ 1,1,0,1 },
		{ 0.05f },
		false
	},
	{
		{ 0.2f,-0.37f },
		{ 1,1,0,1 },
		{ 0.05f },
		false
	},
	{
		{ -0.55f,-0.37f },
		{ 1,1,0,1 },
		{ 0.05f },
		false
	}
};

int ItemCounter = 0;

void XFileDisp()
{

	for (int i = 0; i < 4; i++)
	{
		if (!XFile[i]._gotten)
		{
			glPushMatrix();
			{
				glTranslatef(XFile[i].position[0], XFile[i].position[1], XFile[i].position[2]);
				glColor4f(XFile[i].colorStatus[0], XFile[i].colorStatus[1], XFile[i].colorStatus[2], XFile[i].colorStatus[3]);
				glutSolidCube(XFile[i].scale);
			}
			glPopMatrix();
		}

	}


};

void FileGet(float* position)
{
	for (int i = 0; i < 4; i++)
	{
		if (
			(position[0] - XFile[i].position[0] < 0.05&&-0.05 < position[0] - XFile[i].position[0])
			&& (position[1] - XFile[i].position[1] < 0.05&&-0.05 < position[1] - XFile[i].position[1])
			&& (XFile[i]._gotten == false)
			)
		{
			XFile[i]._gotten = true;
			ItemCounter++;
		}
	}
	if (ItemCounter == 4)
	{
		ClearFlag = true;
	}
	return;
};

void ItemStatusDisp()
{
	glPushMatrix();
	{
		glColor4f(1, 1, 0, 1);
		glRasterPos2f(0.55, -0.97);
		DrawString("X Files ");
		if (ItemCounter == 4) glColor4f(1, 1, 0, 1);
		else  glColor4f(1, 1, 1, 1);
		glRasterPos2f(0.75, -0.97);
		DrawString("=     / 4");
	}
	glPopMatrix();
	glPushMatrix();
	{
		glRasterPos2f(0.81, -0.97);
		switch (ItemCounter)
		{
		case 0:
			DrawString("0");
			break;
		case 1:
			DrawString("1");
			break;
		case 2:
			DrawString("2");
			break;
		case 3:
			DrawString("3");
			break;
		case 4:
			DrawString("4");
			break;
		}
	}
	glPopMatrix();


	if (ClearFlag == true && GameState == SCENE_GAMEPLAY)
	{

		glPushMatrix();
		{
			glColor4f(1, 1, 0, 1);
			glRasterPos2f(-0.15, -0.97);
			DrawString("Do escape");
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-0.826, -0.95, 0);
			glScalef(2.95, 1, 1);
			glColor4f(1, 1, 0, 1);
			glutSolidCube(0.05);
		}
		glPopMatrix();

	}


	return;
}