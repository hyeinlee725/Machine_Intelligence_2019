
#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>


#define seedval	( (unsigned)time( NULL ) )
#define TRUE	1
#define FALSE	0

#define CITIES	50 //20 //10
//���� 10��(���丮�� �ִ� data_10�� �о��)--> �� ������ (x,y)��ǥ ����
//���� ���� �ٲٸ� �ڵ����� �о���� data�� �޶���
#define POPULATION_SIZE	1000 //20
//1000�� �̻��ϸ� �ʹ� ���� �ɸ�
#define PCROSS			0.7//0.8 
#define PMUT			0.2 //0.01//������������ TSP������ �߿��� ����-->������������ ũ���ؾ� ���� ��� ����
//population size�� �۾Ƽ� ������������ ������ Ż���� ����
//�׷��� 0.2�� ��
#define GA_END			1000//��� ������ ���ΰ�(���� ��)
#define BEST_MAX		30000
//�����ذ� �߰ߵǰ� �󸶳� �������� ��ȭ�� ������ Ȯ���ؼ� �����ϴ� �뵵

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] ������ ���� �߻�
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] ������ ���� �߻�

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

struct point {//���ð� x,y��ǥ�� �����Ǿ����Ƿ� ������ ���
	double x, y;
};
class Chromosome {
public:
	int genes[CITIES];//���� ������ŭ ������ ����
	double distance, fitness;//�� �Ÿ�(����� to �����), fitness = 1/distance

	Chromosome();// ��ü�� ����� ������
	~Chromosome(); //��ü �Ҹ���
	void init(int *gp);//�ʱ� ������ ����� ��
	void evaluate();
	void mutation_inv();
	void mutation_ex();
	void crossover(Chromosome *pch);
};

extern double mat[CITIES][CITIES];
extern struct point pos[CITIES];
extern Chromosome best;
extern int generations;

extern char str_in[20], str_hist[20], str_out[20];