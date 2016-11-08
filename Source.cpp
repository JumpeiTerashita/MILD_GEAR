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

	glBegin(GL_TRIANGLE_FAN);	// 視界（扇形）
	glColor4f(0, 1, 1, 0);
	glVertex3f(enemy[1].position[0], enemy[1].position[1], 0.0);	// GLfloat x, y, z
	for (int i = 0; i <= 3; i++)
	{
		float x = enemy[1].position[0] + 0.25*cosf(M_PI* i / 16 + enemy[1].angleDeg);
		float y = enemy[1].position[1] + 0.25*sinf(M_PI* i / 16 + enemy[1].angleDeg);
		glVertex3f(x, y, 0);
	}
	glEnd();	//ここまで
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

	glutForceJoystickFunc();	//ジョイスティック　判定　取りに行く指示　timerの中＝毎フレームごと


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

	glutPostRedisplay(); //display関数の再呼び出し
	glutTimerFunc(
		16,   // unsigned int ミリ秒
		update,  //呼び出す関数指定
		0		//呼び出す関数の引数指定
	);
}

void stageDisp() {
	glBegin(GL_LINE_STRIP);	// マップデータ 地形
	glColor4f(0, 1, 0, 0);
	glVertex3f(-0.9, -1, 0.0);	// GLfloat x, y, z
	glVertex3f(-0.9, 0.9, 0.0);	// GLfloat x, y, z
	glVertex3f(0.9, 0.9, 0.0);	// GLfloat x, y, z
	glVertex3f(0.9, -0.9, 0.0);	// GLfloat x, y, z
	glVertex3f(-0.75, -0.9, 0.0);
	glVertex3f(-0.75, -1, 0.0);
	glEnd();	//ここまで

	for (int i = 0; i < 4; i++)
	{
		glBegin(GL_LINE_STRIP);	// マップデータ　ブロック（左下）
		glColor4f(block[i].colorStatus[0], block[i].colorStatus[1], block[i].colorStatus[2], block[i].colorStatus[3]);
		glVertex3f(block[i].position[0], block[i].position[1], 0.0);	// GLfloat x, y, z
		glVertex3f(block[i].position[0], block[i].position[1] + block[i].scale, 0.0);
		glVertex3f(block[i].position[0] + block[i].scale, block[i].position[1] + block[i].scale, 0.0);
		glVertex3f(block[i].position[0] + block[i].scale, block[i].position[1], 0.0);
		glVertex3f(block[i].position[0], block[i].position[1], 0.0);
		glEnd();	//ここまで
	}

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);//クリア（色情報） 残像出なくなる
	glLoadIdentity(); //注文・変換等の初期化　（再描画ごとの重ねがけを無効化できる）
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

	glFlush();			//注文したものを持ってくる
}

void JoyStick(unsigned int buttonMask, int x, int y, int z)
{
	input.AnalogX += x - input.AnalogX;
	input.AnalogY += y - input.AnalogY;
	input.LastKey = input.PressedKey;
	glClear(GL_COLOR_BUFFER_BIT);//クリア（色情報）

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
		0,   // unsigned int ミリ秒
		update,  //呼び出す関数指定
		0		//呼び出す関数の引数指定
	);
	glutJoystickFunc(JoyStick, 0); //int pollinterval 0ならすぐ取りに行く

	glutMainLoop();
}


//pressedKey	今押されている	joystick コールバック関数から受け取るボタンマスク。
//releasedKey	今押されていない	pressedKey の補数（NOT）。
//lastKey	1フレーム前に押されていた	pressedKey 更新前のデータ。
//changedKey	1フレーム前から変化のあった	pressedKey と lastKey のビット差（XOR）。
//downKey	今押された	changedKey と pressedKey のビット積（AND）。
//upKey	今離された	changedKey と releasedKey のビット積（AND）。

//MILD GEAR
//マップ作成
//敵作成　行動パターン
//敵　視界判定

