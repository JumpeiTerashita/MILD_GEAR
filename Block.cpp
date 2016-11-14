#include "glut.h"
#include "Block.h"
#include "BlockGate.h"
#include "GameManager.h"

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
		{ -0.75f,-0.77f },
		{ 0, 1, 0, 0 },
		0.6f
	},
	{
		{ -0.75f,0.1f },
		{ 0, 1, 0, 0 },
		0.6f
	},
	{
		{ 0.1f,0.1f },
		{ 0, 1, 0, 0 },
		0.6f
	},
	{
		{ 0.1f,-0.77f },
		{ 0, 1, 0, 0 },
		0.6f
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

bool BlockDetection_playerX(float* position)
{
	if (
		(gate[0].EndPosition[1]<position[1] && position[1]<gate[0].StartPosition[1])
		&& (position[0] - gate[0].StartPosition[0]<0.1&&-0.1<position[0] - gate[0].StartPosition[0])
		)
	{
		return false;
	}
	if (
		(gate[3].StartPosition[1]<position[1] && position[1]<gate[3].EndPosition[1])
		&& (position[0] - gate[3].StartPosition[0]<0.1&&-0.1<position[0] - gate[3].StartPosition[0])
		)
	{
		return false;
	}

	for (int i = 0; i < 4; i++)
	{
		if (
			(block[i].position[0]<position[0] + 0.04 && block[i].position[0] + block[i].scale >position[0] - 0.04)
			&& (block[i].position[1]<position[1] + 0.04 && block[i].position[1] + block[i].scale>position[1] - 0.04)
			/*
			(block[i].position[0]<position[0] + 0.04 && block[i].position[0] + block[i].scale >position[0] - 0.04)
			&& (block[i].position[1]<position[1] + 0.04 && block[i].position[1] + block[i].scale>position[1] - 0.04)
			*/
			)
		{
			if (block[i].position[0] > position[0] + player.speed[0] - 0.04 || block[i].position[0] + block[i].scale < position[0] + player.speed[0] + 0.04)
			{
				return true;
			}
		}
		else
		{
			if (
				(block[i].position[0]<position[0]+player.speed[0] + 0.04 && block[i].position[0] + block[i].scale >position[0]+player.speed[0] - 0.04)
				&& (block[i].position[1]<position[1] + 0.04 && block[i].position[1] + block[i].scale>position[1] - 0.04)
				)
			{
				return true;
			}
			
		}

	}
	return false;
}

bool BlockDetection_playerY(float* position)
{
	if (
		(gate[1].StartPosition[0]<position[0] && position[0]<gate[1].EndPosition[0])
		&&(position[1]-gate[1].StartPosition[1]<0.1&&-0.1<position[1] - gate[1].StartPosition[1])
		)
	{
		return false;
	}
	if (
		(gate[2].StartPosition[0] < position[0] && position[0] < gate[2].EndPosition[0])
		&& (position[1] - gate[2].StartPosition[1] < 0.1&&-0.1 < position[1] - gate[2].StartPosition[1])
		)
	{
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		if (
			(block[i].position[0]<position[0] + 0.04 && block[i].position[0] + block[i].scale >position[0] - 0.04)
			&& (block[i].position[1]<position[1] + 0.04 && block[i].position[1] + block[i].scale>position[1] - 0.04)
			/*
			(block[i].position[0]<position[0] + 0.04 && block[i].position[0] + block[i].scale >position[0] - 0.04)
			&& (block[i].position[1]<position[1] + 0.04 && block[i].position[1] + block[i].scale>position[1] - 0.04)
			*/
			)
		{
			if (block[i].position[1] > position[1] - player.speed[1] - 0.04 || block[i].position[1] + block[i].scale < position[1] - player.speed[1] + 0.04)
			{
				return true;
			}
		}
		else
		{
			if (
				(block[i].position[0]<position[0] + 0.04 && block[i].position[0] + block[i].scale >position[0] - 0.04)
				&& (block[i].position[1]<position[1] -player.speed[1] + 0.04 && block[i].position[1] + block[i].scale>position[1]-player.speed[1] - 0.04)
				)
			{
				return true;
			}
		}

	}
	return false;
}

bool BlockDetection_bullet(float* position)
{
	for (int i = 0; i < 4; i++)
	{
		if (
			(block[i].position[0]<position[0] && block[i].position[0] + block[i].scale >position[0])
			&& (block[i].position[1]<position[1] && block[i].position[1] + block[i].scale>position[1])
			)
		{
			return true;
		}
	}
	return false;
}