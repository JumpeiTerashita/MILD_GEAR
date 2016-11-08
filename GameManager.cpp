#include "GameManager.h"

INPUTMANAGER input = { 0 };

/*
typedef struct {
	float position[3];
	float speed[3];
	float angleRad;
	double radius;
	int slices;
	int stacks;
	float colorStatus[4];
	bool _is_active;
}OBJECT;
*/

OBJECT player =
{
	{ -0.825f,-0.95f,0 },
	{ 0,0,0 },
	0,
	0.1f,
	180,
	18,
	{1,1,1,0}
};

OBJECT enemy[] =
{
	{
		{ -0.5f,0,0 },
		{ 1.f / 60,1.f / 60,0 },
		0,
		0.03,
		180,
		6,
		{ 1, 0, 0, 1 },
		true
	},
	{
		{ 0.5f,0,0 },
		{ 0.5f / 60,0.5f / 60,0 },
		0,
		0.03,
		180,
		6,
		{ 0, 1, 0, 1 },
		true
	},
	{
		{ -0.5f,0.5f,0 },
		{ 1.f / 60,1.f / 60,0 },
		0,
		0.03,
		180,
		6,
		{ 0, 0, 1, 1 },
		true
	},
};