#pragma once

#include "GameManager.h"

class Bullet
{
public:
	Bullet();
	~Bullet();
	float _speed;
	bool _is_active;
	float shotAngle;
	OBJECT bullet;
	void draw();
	void move();
	void bulletColision();
};

extern float shotAngleDeg;
extern Bullet* newbullet;


