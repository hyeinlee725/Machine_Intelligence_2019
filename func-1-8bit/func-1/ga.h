
#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define seedval	( (unsigned)time( NULL ) )
#define TRUE	1
#define FALSE	0
#define GENES	8

#define POPULATION_SIZE	100		//해집단 크기, 너무 적으면 다양성을 갖지 못한다.
#define PCROSS			0.7		//교차율
#define PMUT			0.001	//돌연변이율
#define GA_END			100		//세대 발생 횟수(세대수)

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] 사이의 난수 발생
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] 사이의 난수 발생

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

#define start -3
#define finish 3

struct chromosome {	//염색체 구조체의 정의
	int genes[GENES];
	int genes2[GENES];
	double x;
	double y;
	double fitness;	//적합도
};