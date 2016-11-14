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
#include "BlockGate.h"
#include "Item.h"

void update(int value)
{
	glutForceJoystickFunc();	//ジョイスティック　判定　取りに行く指示　timerの中＝毎フレームごと
	switch (GameState)
	{
	case 0:
		break;
	case 1:
		if (input.DownKey == BUTTON_A)
		{
			newbullet = new Bullet();
		}

		if (input.AnalogX > 150 || input.AnalogX < -150)
		{
			player.speed[0] = input.AnalogX / 60000.f;
			if (!(WallDetection_playerX(player.position) || BlockDetection_playerX(player.position)))
			{
				player.position[0] += player.speed[0];
			}
		}
		else player.speed[0] = 0;

		if (input.AnalogY > 150 || input.AnalogY < -150)
		{
			player.speed[1] = input.AnalogY / 60000.f;
			if (!(WallDetection_playerY(player.position) || BlockDetection_playerY(player.position)))
			{
				player.position[1] -= player.speed[1];
			}
		}
		else player.speed[1] = 0;

		if (!(player.speed[0] == 0 && player.speed[1] == 0))
		{
			playerAngleRad = atan2f(player.speed[0], -player.speed[1]);
		}

		player.angleRad = playerAngleRad * 180 / M_PI;

		FileGet(player.position);

		break;
	}
	

	

	glutPostRedisplay(); //display関数の再呼び出し
	glutTimerFunc(
		16,   // unsigned int ミリ秒
		update,  //呼び出す関数指定
		0		//呼び出す関数の引数指定
	);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);//クリア（色情報） 残像出なくなる
	glLoadIdentity(); //注文・変換等の初期化　（再描画ごとの重ねがけを無効化できる）
	//KeyDisp();

	switch (GameState)
	{
	case 0:
		titleDisp();
		break;
	case 1:
		ItemStatusDisp();
		stageDisp();
		blockDisp();
		GateDisp();
		XFileDisp();

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

		gameClear(player.position);
		break;
	}
	

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

