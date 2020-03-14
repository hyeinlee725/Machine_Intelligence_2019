//노트에 추가로 필기
#pragma once

#include "stdafx.h"
#include "ga.h"

#define MAX_MUTATION	10
#define MAX_CROSSOVER	10

int shcedule_base[PLANTS][BASES][QUARTERS] = {//장치에 몇개가 형성되어 있는지(강의자료 p.28)
	{ { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 1 } },//장치1
	{ { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 0, 1, 1 } },//장치2
	{ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } },//장치3
	{ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } },//장치4
	{ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } },//장치5
	{ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } },//장치6
	{ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } }//장치7
};
int MW_base[PLANTS][BASES][QUARTERS] = {//빠져나가는 것(발전용량)
	{ { 20, 20, 0, 0 }, { 0, 20, 20, 0 }, { 0, 0, 20, 20 } },
	{ { 15, 15, 0, 0 }, { 0, 15, 15, 0 }, { 0, 0, 15, 15 } },
	{ { 35, 0, 0, 0 }, { 0, 35, 0, 0 }, { 0, 0, 35, 0 }, { 0, 0, 0, 35 } },
	{ { 40, 0, 0, 0 }, { 0, 40, 0, 0 }, { 0, 0, 40, 0 }, { 0, 0, 0, 40 } },
	{ { 15, 0, 0, 0 }, { 0, 15, 0, 0 }, { 0, 0, 15, 0 }, { 0, 0, 0, 15 } },
	{ { 15, 0, 0, 0 }, { 0, 15, 0, 0 }, { 0, 0, 15, 0 }, { 0, 0, 0, 15 } },
	{ { 10, 0, 0, 0 }, { 0, 10, 0, 0 }, { 0, 0, 10, 0 }, { 0, 0, 0, 10 } }
};
int base_num[PLANTS] = { 3, 3, 4, 4, 4, 4, 4 };//개수
int tot_MW = 150;
int max_MW[QUARTERS] = { 80, 90, 65, 70 };
int fitness_wheel[POPULATION_SIZE];

struct chromosome pop1[POPULATION_SIZE], pop2[POPULATION_SIZE];
struct chromosome *pop = pop1, *pop_next = pop2;
struct chromosome best;

void init_pop();
void ga_impl();
void evaluate(struct chromosome *f);
int select(int f_sum);
void crossover(chromosome *parent1, chromosome *parent2, chromosome *child1, chromosome *child2);
void mutation();
void mutation(chromosome *pch);
void print_result(int f_sum);
void print_chromosome(chromosome *pch);
bool get_best();
void keep_best();

int generations;
int selected[POPULATION_SIZE];

void copy_genes(int dest[], int src[]) {
	for (int i = 0; i<GENES; i++)
		dest[i] = src[i];
}
void init_pop() {
	int i, idx;

	for (i = 0; i<GENES; i++)
		pop[0].genes[i] = rand() % base_num[i];
	evaluate(pop);

	idx = 1;
	i = 0;
	while (idx<POPULATION_SIZE) {
		copy_genes(pop[idx].genes, pop[i].genes);
		mutation(pop + idx);
		idx++;
		i++;
	}

	//for (int i=0; i<POPULATION_SIZE; i++) 
	//	evaluate(pop+i); 

	best.fitness = 0;
	get_best();
}

void ga_impl() {
	int i, next_i;
	int fitness_sum;
	struct chromosome *pop_temp, *pch1, *pch2, ch1, ch2;

	while (generations++<GA_END) {
		fitness_wheel[0] = pop[0].fitness;
		for (i = 1; i<POPULATION_SIZE; i++)
			fitness_wheel[i] = fitness_wheel[i - 1] + pop[i].fitness;
		fitness_sum = fitness_wheel[POPULATION_SIZE - 1];
		print_result(fitness_sum);

		next_i = 0;
		while (next_i<POPULATION_SIZE - 1) {
			pch1 = pop + select(fitness_sum);
			do {
				pch2 = pop + select(fitness_sum);
			} while (pch1 == pch2);
			if (drand() <= PCROSS) {
				crossover(pch1, pch2, &ch1, &ch2);
				if (ch1.fitness>0)
					pop_next[next_i++] = ch1;
				if (ch2.fitness>0)
					pop_next[next_i++] = ch2;
			}
			else {
				pop_next[next_i++] = *pch1;
				pop_next[next_i++] = *pch2;
			}
		}
		if (next_i<POPULATION_SIZE)
			pop_next[next_i] = pop[next_i];

		SWAP(pop, pop_next, pop_temp);

		mutation();

		if (get_best())
			keep_best();
	}

	print_result(fitness_sum);
	print_chromosome(&best);
}

bool get_best() {
	bool flag = TRUE;
	for (int i = 0; i<POPULATION_SIZE; i++) {
		if (best.fitness<pop[i].fitness) {
			best = pop[i];
			flag = FALSE;
		}
	}
	return flag;
}
void keep_best() {
	int point = rand() % POPULATION_SIZE;
	pop[point] = best;
}
void evaluate(chromosome *pch) {
	int values[4];
	int i, j, idx;

	for (i = 0; i<QUARTERS; i++) {
		values[i] = 0;
		for (j = 0; j<PLANTS; j++) {
			idx = pch->genes[j];
			values[i] += MW_base[j][idx][i];
		}
		values[i] = tot_MW - values[i] - max_MW[i];
	}
	if (values[0]<0)
		pch->fitness = 0;
	else
		pch->fitness = values[0];
	for (i = 1; pch->fitness>0 && i<QUARTERS; i++) {
		if (values[i]<0)
			pch->fitness = 0;
		else if (values[i]<pch->fitness)
			pch->fitness = values[i];
	}
}
void print_result(int f_sum) {
	int f_fitness;

	printf("generation: %d, fitness avg: %.1f\n", generations, (double)f_sum / POPULATION_SIZE);
	f_fitness = 0;
	for (int i = 0; i<POPULATION_SIZE; i++) {
		if (f_fitness<pop[i].fitness) {
			f_fitness = pop[i].fitness;
		}
	}
	printf("max fitness: %d\n", f_fitness);
}

void print_chromosome(chromosome *pch) {
	for (int i = 0; i<PLANTS; i++)
		printf("장치%d ", i + 1);
	printf("\n");
	for (int i = 0; i<PLANTS; i++) {
		for (int j = 0; j<QUARTERS; j++)
			printf("%d", shcedule_base[i][best.genes[i]][j]);
		printf("  ");
	}
	printf("\n");
}
void mutation(chromosome *pch) {
	int iter = 0, point;
	do {
		point = rand() % GENES;
		pch->genes[point] = rand() % base_num[point];
		evaluate(pch);
	} while (pch->fitness <= 0 && ++iter<MAX_MUTATION);
}
void mutation() {
	chromosome ch;
	for (int i = 0; i<POPULATION_SIZE; i++) {
		if (drand() <= PMUT) {
			ch = pop[i];
			mutation(pop + i);
			if (pop[i].fitness <= 0)
				pop[i] = ch;
		}
	}
}

void crossover(chromosome *parent1, chromosome *parent2, chromosome *child1, chromosome *child2) {
	int iter = 0, point;

	do {
		copy_genes(child1->genes, parent1->genes);
		copy_genes(child2->genes, parent2->genes);
		point = random(1, GENES);
		for (int i = point; i<GENES; i++) {
			child1->genes[i] = parent2->genes[i];
			child2->genes[i] = parent1->genes[i];
		}
		evaluate(child1);
		evaluate(child2);
	} while ((child1->fitness <= 0 || child2->fitness <= 0) && ++iter<MAX_CROSSOVER);
}

int select(int f_sum) {
	int i;
	double r;

	r = drand() * f_sum;
	for (i = 0; i<POPULATION_SIZE - 1; i++) {
		if (r <= fitness_wheel[i])
			return i;
	}
	return POPULATION_SIZE - 1;
}
