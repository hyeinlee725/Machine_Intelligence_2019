
#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define seedval	( (unsigned)time( NULL ) )//seedval-->���� �ð��� ������ �����ѹ��� ���� �� ���
//(������ ������ ���� �ٸ� seed�ѹ��� ���)
#define TRUE	1
#define FALSE	0
#define GENES	4//GENES�� 4�� ����(�ʱ� ����ü�� �ڸ��� ����-->������ ��)

#define POPULATION_SIZE	6//POPULATION_SIZE�� 6���� ����(�� ��� �ʱ� ����ü�� ������ ������ ����)
// POPULATION_SIZE�� �ʹ� ������ �پ缺�� ����, �ʹ� ������ �ð��� ���� �ɸ�
#define PCROSS			0.7//����(����)���� 0.7�� ����
#define PMUT			0.01//������������ 0.01�� ����
//PCROSS�� PMUT�� ���� �Ϲ������� ���� ������ ������ �غ��鼭 ���������� ������ ���� ���ؾ���
#define GA_END			50//20(��븦 �� ������ ����-->���� ��)

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] ������ ���� �߻�
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] ������ ���� �߻�(n�� ���Ծȵ�!!)

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))//SWAP�ϴ� �Լ� ����
//x�� y�� swap�ϴ� �Լ�

struct chromosome {//����ü�� ���� ����ü
	int genes[GENES];//������ �迭(���� 4���� ������-->4��¥�� �迭)
	int x;//genes�� ���� x��-->�Լ� f(x)�� �����ؼ� ���յ� ��� ����
	int fitness;//x�� ���� f(x), ���յ�
};