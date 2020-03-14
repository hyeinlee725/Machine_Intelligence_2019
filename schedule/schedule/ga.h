
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
#define GA_END			50//���� ��

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] ������ ���� �߻�
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] ������ ���� �߻�

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

#define QUARTERS	4//�б�(4�б�)
#define BASES		4//�ش� ��ġ�� �� ������ 
#define PLANTS		7//��ġ

struct chromosome {
	int genes[GENES];;//����ü(GENES�� 7��-->��ġ�� 7�� �̹Ƿ�)
	int fitness;
};
