#define _USE_MATH_DEFINES
#include <math.h>
#include "glut.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Block.h"
#include "Wall.h"

Bullet::Bullet() :shotAngle(player.angleRad - 90), _speed(0.05f), _is_active(true), bullet({ 0 })
{
	for (int i = 0; i < 3; i++)
	{
		bullet.position[i] = player.position[i];
	}
	bullet.radius = 0.01;
	bullet.slices = 180;
	bullet.stacks = 6;
	bullet.colorStatus[0] = 1;
	bullet.colorStatus[1] = 1;
}

Bullet::~Bullet()
{
}

void Bullet::draw()
{
	glPushMatrix();
	{
		glTranslatef(bullet.position[0], bullet.position[1], bullet.position[2]);
		glColor4f(bullet.colorStatus[0], bullet.colorStatus[1], bullet.colorStatus[2], bullet.colorStatus[3]);
		glutSolidSphere(bullet.radius, bullet.slices, bullet.stacks);
	}
	glPopMatrix();


}

void Bullet::move()
{
	bullet.position[0] += _speed*cosf(shotAngle*M_PI / 180);
	bullet.position[1] -= _speed*sinf(shotAngle*M_PI / 180);
	if (bullet.position[1] > 1 || bullet.position[1] < -1 || bullet.position[0]>1 || bullet.position[0] < -1)
	{
		_is_active = false;
	}
	else if (WallDetection_bullet(bullet.position) || BlockDetection_bullet(bullet.position))
	{
		_is_active = false;
	}
	return;
}

void Bullet::bulletColision()
{

	for (int i = 0; i < 3; i++)
	{
		if (enemy[i]._is_active == true)
		{
			float x = bullet.position[0] - enemy[i].position[0];
			float x2 = powf(x, 2.0);
			float y = bullet.position[1] - enemy[i].position[1];
			float y2 = powf(y, 2.0);
			float r2 = powf((bullet.radius + enemy[i].radius), 2.0);
			if (r2 > (x2 + y2))
			{
				_is_active = false;
				enemy[i]._is_active = false;
			}
		}
	}

	return;
}

Bullet* newbullet = nullptr;