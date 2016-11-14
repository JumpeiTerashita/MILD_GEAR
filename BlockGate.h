#pragma once

typedef struct
{
	float StartPosition[2];
	float EndPosition[2];
	float colorStatus[4];
	bool _is_open;
}GATE;

extern GATE gate[4];
extern void GateDisp();

