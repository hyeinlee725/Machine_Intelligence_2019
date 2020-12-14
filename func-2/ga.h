
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

#define POPULATION_SIZE	120//6//�ʹ� ������ ������ �����ϰ� �ʹ� ũ�� �ð��� �����ɸ�
#define PCROSS			0.7 
#define PMUT			0.001
#define GA_END			50//20

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] ������ ���� �߻�
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] ������ ���� �߻�

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))


struct chromosome {
	int genes_x[GENES], genes_y[GENES];
	double x, y;//����ü 2��
	double fitness;
};

