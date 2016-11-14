#include "glut.h"
#include "BlockGate.h"

/*
	typedef struct
	{
	float StartPosition[2];
	float EndPosition[2];
	float colorStatus[4];
	bool _is_open;
	}GATE;
*/


GATE gate[4] =
{
	{	//����
		{-0.15f,-0.37f},
		{-0.15f,-0.57f},
		{1,0,0,1},
		false
	},
	{	//����
		{-0.55f,0.7f},
		{-0.35f,0.7f},
		{1,0,0,1},
		false
	},
	{	//�E��
		{ 0.3f,-0.77f },
		{ 0.5f,-0.77f },
		{ 1,0,0,1 },
		false
	},
	{	//�E��
		{ 0.7f,0.3f },
		{ 0.7f,0.5f },
		{ 1,0,0,1 },
		false
	}
};

void GateDisp()
{


	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_LINES);	// �}�b�v�f�[�^ ��
		glColor4f(gate[i].colorStatus[0], gate[i].colorStatus[1], gate[i].colorStatus[2], gate[i].colorStatus[3]);
		glVertex3f(gate[i].StartPosition[0], gate[i].StartPosition[1], 0.0);	// GLfloat x, y, z
		glVertex3f(gate[i].EndPosition[0], gate[i].EndPosition[1], 0.0);	// GLfloat x, y, z
		glEnd();	//�����܂�
	}



}

