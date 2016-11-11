#pragma once

#include "GameManager.h"

extern OBJECT enemy[3];
extern int enemyState[3];
extern void enemyDisp();
extern void collisionDetection();
extern void enemyMove(int enemy_number);
extern bool enemySightColision(int enemy_number);
