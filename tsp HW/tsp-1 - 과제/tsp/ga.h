
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

#define CITIES	50 
#define POPULATION_SIZE	1000
#define PCROSS			0.8 
#define PMUT			0.01
#define GA_END			1000

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] ������ ���� �߻�
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] ������ ���� �߻�

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

struct point {
	double x, y;
};
class Chromosome {
public:
	int genes[CITIES];
	double distance, fitness;

	Chromosome();
	~Chromosome();					//�Ҹ���, class�� �̿��� ���� 
	void init(int *gp);
	void evaluate();
	void mutation();
	void crossover(Chromosome *pch);
};

extern double mat[CITIES][CITIES];
extern struct point pos[CITIES];
extern int n_city;
extern Chromosome best;
extern int generations;

extern char str_in[20], str_hist[20], str_out[20];