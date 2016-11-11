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
#include "Enemy.h"

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
		if (WallDetection_player(player.position) || BlockDetection_player(player.position))
		{
			player.position[0] -= player.speed[0];
		}
	}
	else player.speed[0] = 0;

	if (input.AnalogY > 150 || input.AnalogY < -150)
	{
		player.speed[1] = input.AnalogY / 60000.f;
		player.position[1] -= player.speed[1];
		if (WallDetection_player(player.position) || BlockDetection_player(player.position))
		{
			player.position[1] += player.speed[1];
		}
	}
	else player.speed[1] = 0;

	if (!(player.speed[0] == 0 && player.speed[1] == 0))
	{
		playerAngleRad = atan2f(player.speed[0], -player.speed[1]);
	}

	player.angleRad = playerAngleRad * 180 / M_PI;


	glutPostRedisplay(); //display�֐��̍ČĂяo��
	glutTimerFunc(
		16,   // unsigned int �~���b
		update,  //�Ăяo���֐��w��
		0		//�Ăяo���֐��̈����w��
	);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);//�N���A�i�F���j �c���o�Ȃ��Ȃ�
	glLoadIdentity(); //�����E�ϊ����̏������@�i�ĕ`�悲�Ƃ̏d�˂����𖳌����ł���j
	//KeyDisp();

	stageDisp();
	blockDisp();

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
		glRotatef(player.angleRad, 0, 1, 0);
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

