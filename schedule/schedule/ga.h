
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
#define GENES	7

#define POPULATION_SIZE	20
#define PCROSS			0.7 
#define PMUT			0.01//0.001
#define GA_END			50//세대 수

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] 사이의 난수 발생
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] 사이의 난수 발생

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

#define QUARTERS	4//분기(4분기)
#define BASES		4//해당 장치가 몇 개인지 
#define PLANTS		7//장치

struct chromosome {
	int genes[GENES];;//염색체(GENES는 7개-->장치가 7개 이므로)
	int fitness;
};
