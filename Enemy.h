#pragma once

#include "GameManager.h"

extern OBJECT enemy[7];
extern int enemyState[7];
extern void enemyDisp();
extern void enemyMove(int enemy_number);
extern bool enemySightColision(int enemy_number);
