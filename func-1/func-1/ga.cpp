
#pragma once

#include "stdafx.h"
#include "ga.h"

//�� �ڵ带 �����ؾ� ��!!!!!

struct chromosome pop1[POPULATION_SIZE], pop2[POPULATION_SIZE];//����ü pop(population�̶�� �ǹ�)1�� pop2�� ����
//�� 2��?? �θ� ������ �ڽ��� ������ �ϱ� ������ 2�� ����
//������ ������ �θ�, �ڽ� 2�� �ʿ�
struct chromosome *pop = pop1, *pop_next = pop2;
struct chromosome best;//������� ���� �� �߿��� ���� ���� �ظ� keep�ϴ� ��
//�� �κ��� �����ص� �� but, ������� ���� �����ϱ� ���� best�� keep
//������ �˰����� �� �����ϸ� �̺κ��� �ʿ����(�׻� �����ؿ� ���޵ǹǷ�)
//fitness�� ���� ���� �� ����

void init_pop();//������ �ʱ�ȭ
void ga_impl();
void evaluate(struct chromosome *f);//����ü f�� ���ؼ� fitness�� ���ϱ�(���յ� ���ϱ�)
int select(int f_sum);//���� ����(cdf�� �̿��ϹǷ� ��ü �� �ʿ�-->f_sum���� ǥ��)
void crossover(int i1, int i2);//2���� ����ü(�θ� ����ü)�� ���ؼ� ���� ����
void mutation();//��������
void print_result(int f_sum);//����� print
void set_best();//best�� �����ϴ� ����

int generations;//���� ���� �ǹ�
int selected[POPULATION_SIZE];

void print_chromosome(int idx) {//�ʱ� ����ü�� �����ϴ� ����(����ü�� print�ϴ� ����)
	int i;
	printf("x%d:", idx);//����ü�� ��� ����ü���� ���
	for (i = 0; i < GENES; i++)//i�� 0���� GENES���� ���� ������ �ݺ�(GENES�� ga.h�� ���ǵǾ�����)
		printf("%d ", pop[idx].genes[i]);//�� 4�ڸ��� idx�� ����ü�� ���ڸ� ����(������)
		//���� ��� idx=0�̸� x0�� ����ü�� (i+1)�ڸ� ���ڸ� ���ϴ� �ڵ�
	printf("\n");//�ٹٲ�
}
void print_population() {//��ü ������(6)���� print
	int i;

	printf("solution population\n");//solution population ���
	for (i = 0; i < POPULATION_SIZE; i++)//�� 6���� �ʱ� ����ü�� ���(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
		print_chromosome(i);//�ʱ� ����ü�� �����ϴ� ���� ����
}
void copy_genes(int dest[], int src[]) {//src�� source, dest�� destination -->������ ����ü�� ����
	for (int i = 0; i<GENES; i++)//i�� 0���� GENES���� ���� ������ �ݺ�(GENES�� ga.h�� ���ǵǾ�����)
		dest[i] = src[i];//src�迭�� �ִ� �����ڸ� dest�迭�� ����
}
void init_pop() {//population �ʱ�ȭ �Լ�
	int i, j;

	for (i = 0; i < POPULATION_SIZE; i++) {//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
		for (j = 0; j < GENES; j++) {//i�� 0���� GENES���� ���� ������ �ݺ�(GENES�� ga.h�� ���ǵǾ�����)
			pop[i].genes[j] = rand() % 2;//0�Ǵ� 1�� �������� ���� �����ؼ� �ش��ϴ� ����ü(i)�� �ش� �ڸ�(j)�� ����
			//rand() % 2 = 0 �Ǵ� 1
			//6���� ����ü, 4���� �����ڿ� ���ؼ�...
			//But, �̷������� �ϸ� ���� ����ü�� ���� Ȯ���� ŭ-->�Ȱ��� ����ü�� ���ü��� �پ缺�� ������
			//�ʱ� �������� ���� �� ���� ����ü�� ������ �ʵ��� �����ؼ� ������ ��
		}
	}
	print_population();//print_population�Լ��� ����

	for (int i = 0; i<POPULATION_SIZE; i++)//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
		evaluate(pop + i);//�� ����ü�� ���ؼ� ���յ��� ���

	best.fitness = 0;//���� �ֻ��� ���յ��� 0���� �ʱ�ȭ
	set_best();//���� set���� ����ü�� ���յ��� ���� ū ���� ������ �ְ� ��
}

void ga_impl() {//ga�˰��� �����ϴ� �Լ�
	int i;
	int fitness_sum;//���յ� ��(cdf�� ���� �� �ʿ�)
	struct chromosome *pop_temp;//2���� pop�� ��ȯ�ϱ� ���� �뵵

	while (generations++<GA_END) {//GA_END���� ���� ������ ���� �� �����ϴ� ����

		fitness_sum = 0;//fitness_sum�� 0���� �ʱ�ȭ(�ϳ��� �����Ƿ� 0���� ����)
		for (i = 0; i<POPULATION_SIZE; i++)//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
			fitness_sum += pop[i].fitness;//fitness_sum�� ���� i��° ����ü�� ���յ��� ���� ��

		print_result(fitness_sum);//print_result�Լ��� fitness_sum�� �μ��� �־ ����� ����
		
		for (i = 0; i < POPULATION_SIZE; i++)//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
			selected[i] = select(fitness_sum);//select�Լ��� �̿��ؼ� 6���� ���� ������
		//�����ؼ� selected�迭�� ���� ����

		for (i = 0; i<POPULATION_SIZE; i++)//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
			pop_next[i] = pop[selected[i]];//���� �Ȱſ� ���缭 �θ� ������ �ű�
		SWAP(pop, pop_next, pop_temp);//pop�� pop_next�� swap

		for (i = 0; i<POPULATION_SIZE; i += 2) {//i�� 0���� POPULATION_SIZE���� ���� ������ 2�� ���ؼ� �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
			//���� ������ 2���� �����ϹǷ� i += 2
			//�θ� 2���� �����ϹǷ�!!(�ʱ� ����)
			if (drand() <= PCROSS)//���� drand()�� ���������� ������
				crossover(i, i + 1);//�������� ����(0�� 1/2�� 3/4�� 5-->2���� ���� ������ �Ͼ)
				//ũ�� �Ͼ�� ����
		}

		mutation();//��������

		for (i = 0; i<POPULATION_SIZE; i++)//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
			evaluate(pop + i);//���ο� ����ü�� ���� ���յ��� ���

		set_best();//���� set���� ���� ū ���� ������ �ְ� ��
	}

	print_result(fitness_sum);//����� ���
}

void set_best() {//���� set���� ���� ���� ���� ������ �ְ� ��
	for (int i = 0; i<POPULATION_SIZE; i++) {//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
		if (best.fitness<pop[i].fitness) {//���࿡ ������ ������ �ִ� �ֻ��� ���յ��� ���� i��°���� ����� ���յ����� ���� ���
			best = pop[i];//�ֻ��� ���յ��� ���� i��°�� ���յ��� �ٲ�
		}//��ü ������ ����ü���� fitness�� ���� ū ���� ����
	}
}

void evaluate(chromosome *f) {//���յ��� ����ϴ� ���
	int w = 1;//w�� 1�� �ʱ�ȭ
	f->fitness = 0;//����ü �ɹ� fitness�� 0���� �ʱ�ȭ
	f->x = 0;//����ü �ɹ� x�� 0���� �ʱ�ȭ
	for (int i = GENES - 1; i >= 0; i--) {//i�� GENES-1���� 0���� ũ�ų� ���� ������ �ݺ�(�����ϸ鼭)
		f->x += f->genes[i] * w;//����ü �ɹ� x�� ����ü �ɹ� genes�� i��° �迭�� w�� ���� ���� ����
		w *= 2;//2������ 10������ ��ȯ�ϴ� ��
	}
	f->fitness = 15 * f->x - f->x*f->x;//���յ��� ���(15*x - x^2)
}
void print_result(int f_sum) {//����� ���
	int f_x, f_fitness;

	printf("generation: %d, fitness avg: %.1f\n", generations, (double)f_sum / POPULATION_SIZE);
	//���� ���� ���յ� ����� ���� ���
	f_fitness = 0;//f_fitness�� 0���� �ʱ�ȭ
	for (int i = 0; i<POPULATION_SIZE; i++) {//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
		if (f_fitness<pop[i].fitness) {//���� f_fitness�� ���� i��° ����ü�� ���յ����� ���� ���
			f_x = pop[i].x;//f_x�� ���� i��° ����ü�� x�� ����
			f_fitness = pop[i].fitness;//f_fitness ���� i��° ����ü�� fitness�� ����
		}
	}
	printf("pop-max : x:%d, f(x):%d\n", f_x, f_fitness);//x�� ���յ� ���(x??)
	printf("best-max: x:%d, f(x):%d\n", best.x, best.fitness);//x�� ���յ� ���
}

void mutation() {//��������
	for (int i = 0; i<POPULATION_SIZE; i++) {//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
		for (int j = 0; j<GENES; j++) {//j�� 0���� GENES���� ���� ������ �ݺ�(GENES�� ga.h�� ���ǵǾ�����)
			//-->������ ����ü�� ���ؼ� �������̰� �Ͼ�� �ϹǷ� 4���� �����ڿ� ���ؼ� ����
			if (drand() <= PMUT) {//���࿡ ����������(PMUT)�� drand()([0.0..1.0] ������ ����)���� ũ�ų� ������
				if (pop[i].genes[j] == 0)//���� ����ü(i)�� ������(j)�� 0�̸�
					pop[i].genes[j] = 1;//�ش��ϴ� ����ü(i)�� ������(j)�� 1 ����
				else//�׷��� ������
					pop[i].genes[j] = 0;//�ش��ϴ� ����ü(i)�� ������(j)�� 0 ����
			}
		}
	}
}
void crossover(int i1, int i2) {//���� ����
	int tmp;
	int point = random(1, GENES);//����ü�� �������� ������ 1���� 3���� �߿� �������� ����
	//(0�� ��ü�� �ٲٴ� ���̹Ƿ� ����)-->�ǹ̰� ����

	for (int i = point; i<GENES; i++)//i�� point���� GENES���� ���� ������ �ݺ�
		SWAP(pop[i1].genes[i], pop[i2].genes[i], tmp);//i1�� �����ڿ� i2�� �����ڸ� swap
}

int select(int f_sum) {//���� ����(�귿 �� �̿�)
	int i;
	double r, cdf_sum;//cdf_sum : ��ü ��

	r = drand() * f_sum;//��ü %��(��ü���� �� %����-->�� �κ��� ����)
	//���� ��� r�� 35�� ���Դٰ� �����ϸ�, x2�� �ش��(ppt ����)
	cdf_sum = 0.0;//���������Լ��� 0���� �ʱ�ȭ

	for (i = 0; i<POPULATION_SIZE; i++) {//i�� 0���� POPULATION_SIZE���� ���� ������ �ݺ�(POPULATION_SIZE�� ga.h�� ���ǵǾ�����)
		cdf_sum += pop[i].fitness;//cdf_sum�� �ش� ����ü�� ���յ��� ����
		if (r <= cdf_sum)//���� r�� ���������Լ����� �۰ų� ������
			return i;//����
		//cdf_sum ������ �۰ų� ������ �� ��ü�� ����
		//�׷��� ������ ���� �ȵ�
	}
	return POPULATION_SIZE - 1;// POPULATION_SIZE - 1�� ��ȯ
}
