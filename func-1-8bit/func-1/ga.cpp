
#pragma once

#include "stdafx.h"
#include "ga.h"
#include <stdio.h>
#include <math.h>

struct chromosome pop1[POPULATION_SIZE], pop2[POPULATION_SIZE];//�θ�� �ڽ�
struct chromosome *pop = pop1, *pop_next = pop2;
struct chromosome best;

void init_pop();
void ga_impl();
void evaluate(struct chromosome *f);
int select(double f_sum);				//��ü ���� �޾ƿ�
void crossover(int i1, int i2);		//2���� �θ� ����ü�� ���� cross����, 2���� �θ� crossover
void mutation();					//��������
void print_result(double f_sum);
void set_best();

int generations;
int selected[POPULATION_SIZE];

//=========================================================
void print_chromosome(int idx) { //����ü ���ڿ��� index���� ���
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
void print_population() { //����ü ���ڿ��� ���
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
void init_pop() {		//population �ʱ�ȭ �Լ�
	int i, j;

	for (i = 0; i < POPULATION_SIZE; i++) {				//6, ����ü ���ڿ��� ����
		for (j = 0; j < GENES; j++) {					//4, ����ü ���ڿ��� ����
			pop[i].genes[j] = rand() % 2;				//random���� ����ü ���ڿ� ����-->�ʱ⿡�� ���� ����ü ������ ������ �ʳ�� �ϴ°��� �߿���(������ �� �ڵ忣 �������� ����)(�ߺ��̸� ���߰��� ������.)
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

	while (generations++ < GA_END) {					//���� ����ŭ ����

		fitness_sum = 0.0;
		for (i = 0; i < POPULATION_SIZE; i++)
			fitness_sum += pop[i].fitness;	//���յ����� ����

		print_result(fitness_sum);

		for (i = 0; i < POPULATION_SIZE; i++)			//POPULATION_SIZE(6)����ŭ ����ü ����
			selected[i] = select(fitness_sum);		//�귿 �� ���� ����� ���� �������� �θ� ����ü ���� 

		for (i = 0; i < POPULATION_SIZE; i++)
			pop_next[i] = pop[selected[i]];			//���õ� ����ü ����
		SWAP(pop, pop_next, pop_temp);				//���õ� ����ü<-->�θ� ����ü


		for (i = 0; i < POPULATION_SIZE; i += 2) {	//
			if (drand() <= PCROSS)					//������ �߻��ϴ� ���
				crossover(i, i + 1);
		}

		mutation();	//��������

		for (i = 0; i < POPULATION_SIZE; i++)			//�ڽ�(+1����) �� ���յ� ���
			evaluate(pop + i);

		set_best();
	}

	print_result(fitness_sum);
}
//=========================================================
void set_best() {	//���� ���� ���յ��� ���� �����ڸ� ������
	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (best.fitness < pop[i].fitness) {
			best = pop[i];
		}
	}
}
//=========================================================
void evaluate(chromosome *f) {	//����ü ������ ���յ� ���
	int w = 1;
	double  numerator = finish - start; //����
	double denominator = pow(2, GENES) - 1;	//�и�
	double makeReal = numerator / denominator;
	//printf("\nmakereal: %f\n", makeReal);

	f->fitness = 0.0;
	f->x = 0.0;
	f->y = 0.0;

	for (int i = GENES - 1; i >= 0; i--) {	//����ü ���ڿ��� ������ ���ڵ�
		f->x += f->genes[i] * w;
		f->y += f->genes2[i] * w;
		w *= 2;
	}
	//printf("\ntest: %f %f\n", f->x, f->y);
	f->x = f->x*makeReal + start;
	f->y = f->y*makeReal + start;
	//printf("\ntest2: %f %f\n", f->x, f->y);

	f->fitness = pow((1.0 - (f->x)), 2.0)*exp(-pow((f->x), 2.0) - pow(((f->y) + 1.0), 2.0)) - ((f->x) - pow((f->x), 3.0) - pow((f->y), 3.0))*exp(-pow((f->x), 2.0) - pow((f->y), 2.0));	//����ü ���յ� ���( f(x,y)
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
	printf("best-max: x:%f, y:%f, f(x,y):%f\n", best.x, best.y, best.fitness);//���� ���� ���յ��� ������ X�� ���
}
//=========================================================
void mutation() {								//��������
	for (int i = 0; i < POPULATION_SIZE; i++) {
		for (int j = 0; j < GENES; j++) {
			if (drand() <= PMUT) {				//�������̰� �߻��ϴ� ���
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
void crossover(int i1, int i2) {	//����
	int tmp;
	int point = random(1, GENES);	//�θ� ����ü���� �������� ������ ���Ƿ� ����

	for (int i = point; i < GENES; i++)
	{
		SWAP(pop[i1].genes[i], pop[i2].genes[i], tmp);	//���� �߻�
		SWAP(pop[i1].genes2[i], pop[i2].genes2[i], tmp);	//���� �߻�
	}


}
//=========================================================
int select(double f_sum) {	//�귿 �� ����
	int i;
	double r, cdf_sum;

	r = drand() * f_sum;	//¦�� ���� ����ü�� �����ϱ� ���� ���� ����
	cdf_sum = 0.0;

	for (i = 0; i < POPULATION_SIZE; i++) {		//
		cdf_sum += pop[i].fitness;				//����ü�� ���յ��� ����Ͽ� ������ ������
		if (r <= cdf_sum)						//r(����)�� Xi�� ����ü�� �Ҵ�� ������ ���ϸ�
			return i;							//i�� ��ȯ
	}
	return POPULATION_SIZE - 1;
}
