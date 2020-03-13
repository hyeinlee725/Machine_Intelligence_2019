
#pragma once

#include "stdafx.h"
#include "ga.h"
#include <stdio.h>
#include <math.h>

struct chromosome pop1[POPULATION_SIZE], pop2[POPULATION_SIZE];//부모와 자식
struct chromosome *pop = pop1, *pop_next = pop2;
struct chromosome best;

void init_pop();
void ga_impl();
void evaluate(struct chromosome *f);
int select(double f_sum);				//전체 합을 받아옴
void crossover(int i1, int i2);		//2개의 부모 염색체에 대해 cross연산, 2개의 부모를 crossover
void mutation();					//돌연변이
void print_result(double f_sum);
void set_best();

int generations;
int selected[POPULATION_SIZE];

//=========================================================
void print_chromosome(int idx) { //염색체 문자열을 index별로 출력
	int i;
	printf("x%d:", idx);
	for (i = 0; i < GENES; i++)
		printf("%d ", pop[idx].genes[i]);

	printf("\ny%d:", idx);
	for (i = 0; i < GENES; i++)
		printf("%d ", pop[idx].genes2[i]);
	printf("\n");
}
//=========================================================
void print_population() { //염색체 문자열들 출력
	int i;

	printf("solution population\n");
	for (i = 0; i < POPULATION_SIZE; i++)
		print_chromosome(i);
}
//=========================================================
void copy_genes(int dest[], int src[])
{
	for (int i = 0; i < GENES; i++)
		dest[i] = src[i];
}
//=========================================================
void init_pop() {		//population 초기화 함수
	int i, j;

	for (i = 0; i < POPULATION_SIZE; i++) {				//6, 염색체 문자열의 개수
		for (j = 0; j < GENES; j++) {					//4, 염색체 문자열의 길이
			pop[i].genes[j] = rand() % 2;				//random으로 염색체 문자열 생성-->초기에는 같은 엽색체 집단이 나오지 않노록 하는것이 중요함(하지만 이 코드엔 구현되지 않음)(중복이면 나중것을 삭제함.)
			pop[i].genes2[j] = rand() % 2;
		}
	}
	print_population();

	for (int i = 0; i < POPULATION_SIZE; i++)
		evaluate(pop + i);

	best.fitness = 0;
	set_best();
}
//=========================================================
void ga_impl() {
	int i;
	double fitness_sum;
	struct chromosome *pop_temp;

	while (generations++ < GA_END) {					//세대 수만큼 교배

		fitness_sum = 0.0;
		for (i = 0; i < POPULATION_SIZE; i++)
			fitness_sum += pop[i].fitness;	//적합도들을 합함

		print_result(fitness_sum);

		for (i = 0; i < POPULATION_SIZE; i++)			//POPULATION_SIZE(6)개만큼 염색체 선택
			selected[i] = select(fitness_sum);		//룰렛 휠 선택 방법에 따라서 랜덤으로 부모 염색체 선택 

		for (i = 0; i < POPULATION_SIZE; i++)
			pop_next[i] = pop[selected[i]];			//선택된 염색체 복사
		SWAP(pop, pop_next, pop_temp);				//선택된 염색체<-->부모 염색체


		for (i = 0; i < POPULATION_SIZE; i += 2) {	//
			if (drand() <= PCROSS)					//교차가 발생하는 경우
				crossover(i, i + 1);
		}

		mutation();	//돌연변이

		for (i = 0; i < POPULATION_SIZE; i++)			//자식(+1세대) 의 적합도 계산
			evaluate(pop + i);

		set_best();
	}

	print_result(fitness_sum);
}
//=========================================================
void set_best() {	//가장 높은 적합도를 가진 유전자를 저장함
	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (best.fitness < pop[i].fitness) {
			best = pop[i];
		}
	}
}
//=========================================================
void evaluate(chromosome *f) {	//염색체 각각의 적합도 계산
	int w = 1;
	double  numerator = finish - start; //분자
	double denominator = pow(2, GENES) - 1;	//분모
	double makeReal = numerator / denominator;
	//printf("\nmakereal: %f\n", makeReal);

	f->fitness = 0.0;
	f->x = 0.0;
	f->y = 0.0;

	for (int i = GENES - 1; i >= 0; i--) {	//염색체 문자열을 정수로 디코딩
		f->x += f->genes[i] * w;
		f->y += f->genes2[i] * w;
		w *= 2;
	}
	//printf("\ntest: %f %f\n", f->x, f->y);
	f->x = f->x*makeReal + start;
	f->y = f->y*makeReal + start;
	//printf("\ntest2: %f %f\n", f->x, f->y);

	f->fitness = pow((1.0 - (f->x)), 2.0)*exp(-pow((f->x), 2.0) - pow(((f->y) + 1.0), 2.0)) - ((f->x) - pow((f->x), 3.0) - pow((f->y), 3.0))*exp(-pow((f->x), 2.0) - pow((f->y), 2.0));	//염색체 적합도 계산( f(x,y)
	//printf("\n%f %f %f\n", pow(2, 2), exp(2.0),exp(4.0));
	//printf("\nddd: %f\n", f->fitness);
}
//=========================================================
void print_result(double f_sum) {
	//int f_x=0;
	//int f_y = 0;
	//int f_fitness = 0;
	double f_x, f_y, f_fitness;
	printf("\n");
	printf("generation: %d, fitness avg: %.1f\n", generations, (double)f_sum / POPULATION_SIZE);
	f_fitness = 0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (f_fitness < pop[i].fitness) {
			f_x = pop[i].x;
			f_y = pop[i].y;
			f_fitness = pop[i].fitness;
		}
	}
	printf("pop-max : x:%f, y: %f f(x,y):%f\n", f_x, f_y, f_fitness);
	printf("best-max: x:%f, y:%f, f(x,y):%f\n", best.x, best.y, best.fitness);//가장 높은 적합도를 가졌던 X를 출력
}
//=========================================================
void mutation() {								//돌연변이
	for (int i = 0; i < POPULATION_SIZE; i++) {
		for (int j = 0; j < GENES; j++) {
			if (drand() <= PMUT) {				//돌연변이가 발생하는 경우
				if (pop[i].genes[j] == 0)		//0-->1
					pop[i].genes[j] = 1;
				else
					pop[i].genes[j] = 0;		//1-->0

				if (pop[i].genes2[j] == 0)		//0-->1
					pop[i].genes2[j] = 1;
				else
					pop[i].genes2[j] = 0;		//1-->0

			}
		}
	}
}
//=========================================================
void crossover(int i1, int i2) {	//교차
	int tmp;
	int point = random(1, GENES);	//부모 염색체들이 끊어지는 지점을 임의로 선택

	for (int i = point; i < GENES; i++)
	{
		SWAP(pop[i1].genes[i], pop[i2].genes[i], tmp);	//교차 발생
		SWAP(pop[i1].genes2[i], pop[i2].genes2[i], tmp);	//교차 발생
	}


}
//=========================================================
int select(double f_sum) {	//룰렛 휠 선택
	int i;
	double r, cdf_sum;

	r = drand() * f_sum;	//짝을 지을 염색체를 선택하기 위해 난수 생성
	cdf_sum = 0.0;

	for (i = 0; i < POPULATION_SIZE; i++) {		//
		cdf_sum += pop[i].fitness;				//염색체는 적합도에 비례하여 공간을 차지함
		if (r <= cdf_sum)						//r(난수)가 Xi번 염색체에 할당된 구간에 속하면
			return i;							//i를 반환
	}
	return POPULATION_SIZE - 1;
}
