
#pragma once

#include "stdafx.h"
#include "ga.h"

//이 코드를 이해해야 함!!!!!

struct chromosome pop1[POPULATION_SIZE], pop2[POPULATION_SIZE];//구조체 pop(population이라는 의미)1과 pop2를 만듬
//왜 2개?? 부모가 있으면 자식을 만들어야 하기 때문에 2개 만듬
//선택할 때에도 부모, 자식 2개 필요
struct chromosome *pop = pop1, *pop_next = pop2;
struct chromosome best;//현재까지 나온 해 중에서 가장 좋은 해를 keep하는 것
//이 부분은 생략해도 됨 but, 사라지는 것을 방지하기 위해 best에 keep
//유전자 알고리즘을 잘 설계하면 이부분은 필요없음(항상 최적해에 도달되므로)
//fitness가 가장 높은 것 저장

void init_pop();//해집단 초기화
void ga_impl();
void evaluate(struct chromosome *f);//염색체 f에 대해서 fitness값 구하기(적합도 구하기)
int select(int f_sum);//선택 연산(cdf를 이용하므로 전체 합 필요-->f_sum으로 표현)
void crossover(int i1, int i2);//2개의 염색체(부모 염색체)에 대해서 교차 연산
void mutation();//돌연변이
void print_result(int f_sum);//결과값 print
void set_best();//best를 유지하는 역할

int generations;//세대 수를 의미
int selected[POPULATION_SIZE];

void print_chromosome(int idx) {//초기 염색체를 생성하는 연산(염색체를 print하는 연산)
	int i;
	printf("x%d:", idx);//염색체가 몇번 염색체인지 출력
	for (i = 0; i < GENES; i++)//i는 0부터 GENES보다 작을 때까지 반복(GENES는 ga.h에 정의되어있음)
		printf("%d ", pop[idx].genes[i]);//총 4자리의 idx번 염색체의 숫자를 생성(유전자)
		//예를 들어 idx=0이면 x0번 염색체의 (i+1)자리 숫자를 정하는 코드
	printf("\n");//줄바꿈
}
void print_population() {//전체 해집단(6)개를 print
	int i;

	printf("solution population\n");//solution population 출력
	for (i = 0; i < POPULATION_SIZE; i++)//총 6개의 초기 염색체를 출력(POPULATION_SIZE는 ga.h에 정의되어있음)
		print_chromosome(i);//초기 염색체를 생성하는 연산 실행
}
void copy_genes(int dest[], int src[]) {//src는 source, dest는 destination -->생성한 염색체를 복사
	for (int i = 0; i<GENES; i++)//i는 0부터 GENES보다 작을 때까지 반복(GENES는 ga.h에 정의되어있음)
		dest[i] = src[i];//src배열에 있는 유전자를 dest배열로 복사
}
void init_pop() {//population 초기화 함수
	int i, j;

	for (i = 0; i < POPULATION_SIZE; i++) {//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
		for (j = 0; j < GENES; j++) {//i는 0부터 GENES보다 작을 때까지 반복(GENES는 ga.h에 정의되어있음)
			pop[i].genes[j] = rand() % 2;//0또는 1로 유전자의 수를 결정해서 해당하는 염색체(i)의 해당 자리(j)에 저장
			//rand() % 2 = 0 또는 1
			//6개의 염색체, 4개의 유전자에 대해서...
			//But, 이런식으로 하면 같은 염색체가 나올 확률이 큼-->똑같은 염색체가 나올수록 다양성이 없어짐
			//초기 해집단을 만들 때 같은 염색체가 나오지 않도록 주의해서 만들어야 함
		}
	}
	print_population();//print_population함수를 실행

	for (int i = 0; i<POPULATION_SIZE; i++)//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
		evaluate(pop + i);//각 염색체에 대해서 적합도를 계산

	best.fitness = 0;//가장 최상의 적합도를 0으로 초기화
	set_best();//현재 set에서 염색체의 적합도가 가장 큰 값을 가지고 있게 함
}

void ga_impl() {//ga알고리즘 실행하는 함수
	int i;
	int fitness_sum;//적합도 합(cdf를 구할 때 필요)
	struct chromosome *pop_temp;//2개의 pop을 교환하기 위한 용도

	while (generations++<GA_END) {//GA_END보다 작을 때까지 세대 수 증가하는 동안

		fitness_sum = 0;//fitness_sum을 0으로 초기화(하나도 없으므로 0으로 시작)
		for (i = 0; i<POPULATION_SIZE; i++)//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
			fitness_sum += pop[i].fitness;//fitness_sum은 현재 i번째 염색체의 적합도를 더한 값

		print_result(fitness_sum);//print_result함수에 fitness_sum을 인수로 넣어서 결과를 얻음
		
		for (i = 0; i < POPULATION_SIZE; i++)//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
			selected[i] = select(fitness_sum);//select함수를 이용해서 6개를 전부 선택함
		//선택해서 selected배열에 전부 넣음

		for (i = 0; i<POPULATION_SIZE; i++)//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
			pop_next[i] = pop[selected[i]];//선택 된거에 맞춰서 부모 쪽으로 옮김
		SWAP(pop, pop_next, pop_temp);//pop과 pop_next를 swap

		for (i = 0; i<POPULATION_SIZE; i += 2) {//i는 0부터 POPULATION_SIZE보다 작을 때까지 2씩 더해서 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
			//교차 연산은 2개씩 선택하므로 i += 2
			//부모 2개를 선택하므로!!(필기 참고)
			if (drand() <= PCROSS)//만약 drand()가 교차율보다 작으면
				crossover(i, i + 1);//교차연산 실행(0과 1/2와 3/4와 5-->2개의 교차 연산이 일어남)
				//크면 일어나지 않음
		}

		mutation();//돌연변이

		for (i = 0; i<POPULATION_SIZE; i++)//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
			evaluate(pop + i);//새로운 염색체에 대한 적합도를 계산

		set_best();//현재 set에서 가장 큰 값을 가지고 있게 함
	}

	print_result(fitness_sum);//결과를 출력
}

void set_best() {//현재 set에서 가장 좋은 값을 가지고 있게 함
	for (int i = 0; i<POPULATION_SIZE; i++) {//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
		if (best.fitness<pop[i].fitness) {//만약에 기존에 가지고 있던 최상의 적합도가 현재 i번째에서 계산한 적합도보다 작을 경우
			best = pop[i];//최상의 적합도를 현재 i번째의 적합도로 바꿈
		}//전체 해집단 염색체에서 fitness가 가장 큰 것을 선택
	}
}

void evaluate(chromosome *f) {//적합도를 계산하는 방법
	int w = 1;//w를 1로 초기화
	f->fitness = 0;//구조체 맴버 fitness를 0으로 초기화
	f->x = 0;//구조체 맴버 x를 0으로 초기화
	for (int i = GENES - 1; i >= 0; i--) {//i는 GENES-1부터 0보다 크거나 같을 때까지 반복(감소하면서)
		f->x += f->genes[i] * w;//구조체 맴버 x에 구조체 맴버 genes의 i번째 배열에 w를 곱한 값을 더함
		w *= 2;//2진수를 10진수로 변환하는 것
	}
	f->fitness = 15 * f->x - f->x*f->x;//적합도를 계산(15*x - x^2)
}
void print_result(int f_sum) {//결과를 출력
	int f_x, f_fitness;

	printf("generation: %d, fitness avg: %.1f\n", generations, (double)f_sum / POPULATION_SIZE);
	//세대 수와 적합도 계산한 것을 출력
	f_fitness = 0;//f_fitness를 0으로 초기화
	for (int i = 0; i<POPULATION_SIZE; i++) {//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
		if (f_fitness<pop[i].fitness) {//만약 f_fitness가 현재 i번째 염색체의 적합도보다 작을 경우
			f_x = pop[i].x;//f_x에 현재 i번째 염색체의 x를 대입
			f_fitness = pop[i].fitness;//f_fitness 현재 i번째 염색체의 fitness를 대입
		}
	}
	printf("pop-max : x:%d, f(x):%d\n", f_x, f_fitness);//x와 적합도 출력(x??)
	printf("best-max: x:%d, f(x):%d\n", best.x, best.fitness);//x와 적합도 출력
}

void mutation() {//돌연변이
	for (int i = 0; i<POPULATION_SIZE; i++) {//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
		for (int j = 0; j<GENES; j++) {//j는 0부터 GENES보다 작을 때까지 반복(GENES는 ga.h에 정의되어있음)
			//-->각각의 염색체에 대해서 돌연변이가 일어나야 하므로 4개의 유전자에 대해서 실행
			if (drand() <= PMUT) {//만약에 돌연변이율(PMUT)이 drand()([0.0..1.0] 사이의 난수)보다 크거나 같으면
				if (pop[i].genes[j] == 0)//만약 염색체(i)의 유전자(j)가 0이면
					pop[i].genes[j] = 1;//해당하는 염색체(i)의 유전자(j)에 1 대입
				else//그렇지 않으면
					pop[i].genes[j] = 0;//해당하는 염색체(i)의 유전자(j)에 0 대입
			}
		}
	}
}
void crossover(int i1, int i2) {//교차 연산
	int tmp;
	int point = random(1, GENES);//염색체의 끊어지는 지점을 1부터 3까지 중에 랜덤으로 지정
	//(0은 전체를 바꾸는 것이므로 제외)-->의미가 없음

	for (int i = point; i<GENES; i++)//i는 point부터 GENES보다 작을 때까지 반복
		SWAP(pop[i1].genes[i], pop[i2].genes[i], tmp);//i1의 유전자와 i2의 유전자를 swap
}

int select(int f_sum) {//선택 연산(룰렛 휠 이용)
	int i;
	double r, cdf_sum;//cdf_sum : 전체 합

	r = drand() * f_sum;//전체 %값(전체에서 몇 %인지-->그 부분을 선택)
	//예를 들어 r이 35가 나왔다고 가정하면, x2에 해당됨(ppt 참고)
	cdf_sum = 0.0;//누적분포함수를 0으로 초기화

	for (i = 0; i<POPULATION_SIZE; i++) {//i는 0부터 POPULATION_SIZE보다 작을 때까지 반복(POPULATION_SIZE는 ga.h에 정의되어있음)
		cdf_sum += pop[i].fitness;//cdf_sum에 해당 염색체의 적합도를 더함
		if (r <= cdf_sum)//만약 r이 누적분포함수보다 작거나 같으면
			return i;//선택
		//cdf_sum 값보다 작거나 같으면 그 객체를 선택
		//그렇지 않으면 선택 안됨
	}
	return POPULATION_SIZE - 1;// POPULATION_SIZE - 1을 반환
}
