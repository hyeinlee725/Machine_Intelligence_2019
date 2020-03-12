// func-1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#pragma once

#include "stdafx.h"
#include "ga.h"

void init_pop();//해집단 초기화
void ga_impl();//ga알고리즘 수행

int _tmain(int argc, _TCHAR* argv[])//_tmain 함수
{
	clock_t t_start, t_end;;//처음 시간, 끝 시간
	double duration;//경과 시간

	srand(seedval);

	init_pop();//해집단 초기화
	t_start = clock();//시간 측정 시작
	ga_impl();//알고리즘 실행
	t_end = clock();//시간 측정 종료
	duration = (double)(t_end - t_start) / CLOCKS_PER_SEC;//유전 알고리즘을 실행하는데 걸린 시간을 계산
	//CLOCKS_PER_SEC를 나눔으로 clock단위를 초로 바꿈(stdlib.h에 정의되어 있음)
	printf("경과시간: %f\n", duration);//유전 알고리즘을 실행하는데 걸린 시간을 출력

	return 0;
}
