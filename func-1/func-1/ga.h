
#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define seedval	( (unsigned)time( NULL ) )//seedval-->현재 시간을 가지고 랜덤넘버를 만들 때 사용
//(실행할 때마다 서로 다른 seed넘버를 사용)
#define TRUE	1
#define FALSE	0
#define GENES	4//GENES를 4로 정의(초기 염색체의 자리수 정의-->유전자 수)

#define POPULATION_SIZE	6//POPULATION_SIZE를 6으로 정의(총 몇개의 초기 염색체를 생성할 것인지 정의)
// POPULATION_SIZE가 너무 작으면 다양성이 없고, 너무 많으면 시간이 오래 걸림
#define PCROSS			0.7//교차(연산)율을 0.7로 정의
#define PMUT			0.01//돌연변이율을 0.01로 정의
//PCROSS와 PMUT는 현재 일반적으로 좋은 값이지 여러번 해보면서 안정적으로 나오게 값을 정해야함
#define GA_END			50//20(몇세대를 할 것인지 정의-->세대 수)

#define drand()			((double)rand()/RAND_MAX) //[0.0..1.0] 사이의 난수 발생
#define random(i, n)	(rand()%((n)-(i))+(i))    //[i..n-1] 사이의 난수 발생(n은 포함안됨!!)

#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))//SWAP하는 함수 정의
//x와 y를 swap하는 함수

struct chromosome {//염색체에 대한 구조체
	int genes[GENES];//유전자 배열(현재 4개의 유전자-->4개짜리 배열)
	int x;//genes에 대한 x값-->함수 f(x)에 대입해서 적합도 계산 가능
	int fitness;//x에 대한 f(x), 적합도
};