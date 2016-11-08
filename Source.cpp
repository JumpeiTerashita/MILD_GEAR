#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_X 4
#define BUTTON_Y 8
#define BUTTON_L 16
#define BUTTON_R 32
#define BUTTON_SELECT 64
#define BUTTON_START 128

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "glut.h"
#include "GameManager.h"
#include "Bullet.h"
#include "Block.h"
#include "Wall.h"

Bullet* newbullet = nullptr;

float tmpSpeed[2] = { 0 };
float playerAngleRad = 0;

void addVector(float* _vOut, float* _v0, float* _v1)
{
	for (int i = 0; i < 3; i++)
	{
		_vOut[i] = _v0[i] + _v1[i];
	}
}

void enemyDisp()
{
	enemy[1].angleDeg = atan2f(enemy[1].speed[0], enemy[1].speed[1]) * 180 / M_PI;

	glBegin(GL_TRIANGLE_FAN);	// ���E�i��`�j
	glColor4f(0, 1, 1, 0);
	glVertex3f(enemy[1].position[0], enemy[1].position[1], 0.0);	// GLfloat x, y, z
	for (int i = 0; i <= 3; i++)
	{
		float x = enemy[1].position[0] + 0.25*cosf(M_PI* i / 16 + enemy[1].angleDeg);
		float y = enemy[1].position[1] + 0.25*sinf(M_PI* i / 16 + enemy[1].angleDeg);
		glVertex3f(x, y, 0);
	}
	glEnd();	//�����܂�
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

void DrawString(const char* str)
{
	while (*str != '\0')
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str++);
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

bool WallDetection(float* position)
{
	if (position[0] <= wallPackage_01[0].position[0]+0.04) return true;
	else if (position[1] >= wallPackage_01[1].position[1]-0.04) return true;
	else if (position[0] >= wallPackage_01[2].position[0]-0.04) return true;
	else if ((position[0] <= wallPackage_01[3].position[0]+0.04&&position[0] >= wallPackage_01[4].position[0]-0.04) && position[1] <= wallPackage_01[4].position[1]+0.04) return true;
	return false;
}

bool BlockDetection()
{

	{

	}

	return true;
}

void update(int value)
{

	glutForceJoystickFunc();	//�W���C�X�e�B�b�N�@����@���ɍs���w���@timer�̒������t���[������


	if (input.DownKey == BUTTON_A)
	{
		newbullet = new Bullet();
	}

	if (input.AnalogX > 150 || input.AnalogX < -150)
	{
		player.speed[0] = input.AnalogX / 60000.f;
		player.position[0] += player.speed[0];
		if (WallDetection(player.position))
		{
			player.position[0] -= player.speed[0];
		}
	}
	else player.speed[0] = 0;



	if (input.AnalogY > 150 || input.AnalogY < -150)
	{
		player.speed[1] = input.AnalogY / 60000.f;
		player.position[1] -= player.speed[1];
		if (WallDetection(player.position))
		{
			player.position[1] += player.speed[1];
		}
	}
	else player.speed[1] = 0;

	if (!(player.speed[0] == 0 && player.speed[1] == 0))
	{
		playerAngleRad = atan2f(player.speed[0], -player.speed[1]);
	}

	player.angleDeg = playerAngleRad * 180 / M_PI;

	tmpSpeed[0] = player.speed[0];
	tmpSpeed[1] = player.speed[1];

	glutPostRedisplay(); //display�֐��̍ČĂяo��
	glutTimerFunc(
		16,   // unsigned int �~���b
		update,  //�Ăяo���֐��w��
		0		//�Ăяo���֐��̈����w��
	);
}

void stageDisp() {
	glBegin(GL_LINE_STRIP);	// �}�b�v�f�[�^ �n�`
	glColor4f(0, 1, 0, 0);
	glVertex3f(-0.9, -1, 0.0);	// GLfloat x, y, z
	glVertex3f(-0.9, 0.9, 0.0);	// GLfloat x, y, z
	glVertex3f(0.9, 0.9, 0.0);	// GLfloat x, y, z
	glVertex3f(0.9, -0.9, 0.0);	// GLfloat x, y, z
	glVertex3f(-0.75, -0.9, 0.0);
	glVertex3f(-0.75, -1, 0.0);
	glEnd();	//�����܂�

	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_LINE_STRIP);	// �}�b�v�f�[�^�@�u���b�N�i�����j
		glColor4f(block[i].colorStatus[0], block[i].colorStatus[1], block[i].colorStatus[2], block[i].colorStatus[3]);
		glVertex3f(block[i].position[0], block[i].position[1], 0.0);	// GLfloat x, y, z
		glVertex3f(block[i].position[0], block[i].position[1] + block[i].scale, 0.0);
		glVertex3f(block[i].position[0] + block[i].scale, block[i].position[1] + block[i].scale, 0.0);
		glVertex3f(block[i].position[0] + block[i].scale, block[i].position[1], 0.0);
		glVertex3f(block[i].position[0], block[i].position[1], 0.0);
		glEnd();	//�����܂�
	}

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);//�N���A�i�F���j �c���o�Ȃ��Ȃ�
	glLoadIdentity(); //�����E�ϊ����̏������@�i�ĕ`�悲�Ƃ̏d�˂����𖳌����ł���j
	//KeyDisp();

	stageDisp();

	if (!(newbullet == nullptr))
	{
		newbullet->move();
		newbullet->bulletColision();
		if (newbullet->_is_active == false)
		{
			newbullet = nullptr;
			delete newbullet;
		}
	}
	enemyDisp();
	collisionDetection();

	if (!(newbullet == nullptr))
	{
		newbullet->draw();
	}

	glPushMatrix();
	{

		glTranslatef(player.position[0], player.position[1], player.position[2]);
		glRotatef(-90, 1, 0, 0);
		glRotatef(player.angleDeg, 0, 1, 0);
		glColor4f(player.colorStatus[0], player.colorStatus[1], player.colorStatus[2], player.colorStatus[3]);
		//glutSolidSphere(player.radius, player.slices, player.stacks);
		glutSolidCone(0.020, 0.050, player.slices, player.stacks);
	}
	glPopMatrix();

	glFlush();			//�����������̂������Ă���
}

void JoyStick(unsigned int buttonMask, int x, int y, int z)
{
	input.AnalogX += x - input.AnalogX;
	input.AnalogY += y - input.AnalogY;
	input.LastKey = input.PressedKey;
	glClear(GL_COLOR_BUFFER_BIT);//�N���A�i�F���j

	printf("joystick buttonMask:%d x:%d y:%d z:%d\n", buttonMask, x, y, z);
	input.PressedKey = buttonMask;
	input.ReleasedKey = ~buttonMask;
	input.ChangedKey = (input.PressedKey ^ input.LastKey);
	input.UpKey = (input.ChangedKey & input.ReleasedKey);
	input.DownKey = (input.ChangedKey & input.PressedKey);
}



int main(int argc, char *argv[])
{

	glutInit(
		&argc, // int*
		argv //char**
	);
	glutInitWindowSize(
		640,  // int width
		640);// int height
	glutCreateWindow("MILD_GEAR");
	glutDisplayFunc(display);
	glutTimerFunc(
		0,   // unsigned int �~���b
		update,  //�Ăяo���֐��w��
		0		//�Ăяo���֐��̈����w��
	);
	glutJoystickFunc(JoyStick, 0); //int pollinterval 0�Ȃ炷�����ɍs��

	glutMainLoop();
}


//pressedKey	��������Ă���	joystick �R�[���o�b�N�֐�����󂯎��{�^���}�X�N�B
//releasedKey	��������Ă��Ȃ�	pressedKey �̕␔�iNOT�j�B
//lastKey	1�t���[���O�ɉ�����Ă���	pressedKey �X�V�O�̃f�[�^�B
//changedKey	1�t���[���O����ω��̂�����	pressedKey �� lastKey �̃r�b�g���iXOR�j�B
//downKey	�������ꂽ	changedKey �� pressedKey �̃r�b�g�ρiAND�j�B
//upKey	�������ꂽ	changedKey �� releasedKey �̃r�b�g�ρiAND�j�B

//MILD GEAR
//�}�b�v�쐬
//�G�쐬�@�s���p�^�[��
//�G�@���E����

