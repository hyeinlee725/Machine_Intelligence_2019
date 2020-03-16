
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
//도시 10개(디렉토리에 있는 data_10을 읽어옴)--> 각 도시의 (x,y)좌표 있음
//도시 값을 바꾸면 자동으로 읽어오는 data가 달라짐
#define POPULATION_SIZE	1000 //20
//1000개 이상하면 너무 오래 걸림
#define PCROSS			0.7//0.8 
#define PMUT			0.2 //0.01//돌연변이율이 TSP에서는 중요한 역할-->돌연변이율을 크게해야 좋은 결과 나옴
//population size가 작아서 돌연변이율이 작으면 탈출을 못함
//그래서 0.2로 함
#define GA_END			1000//몇번 실행할 것인가(세대 수)
#define BEST_MAX		30000
//최적해가 발견되고 얼마나 오랬동안 변화가 없는지 확인해서 종료하는 용도

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] 사이의 난수 발생
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] 사이의 난수 발생

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

struct point {//도시가 x,y좌표로 생성되었으므로 포인터 사용
	double x, y;
};
class Chromosome {
public:
	int genes[CITIES];//도시 개수만큼 유전자 존재
	double distance, fitness;//총 거리(출발점 to 출발점), fitness = 1/distance

	Chromosome();// 객체를 만드는 생성자
	~Chromosome(); //객체 소멸자
	void init(int *gp);//초기 해집단 만드는 것
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