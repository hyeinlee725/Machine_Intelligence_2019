// func-1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//
#pragma once

#include "stdafx.h"
#include "ga.h"

void init_pop();//������ �ʱ�ȭ
void ga_impl();//ga�˰��� ����

int _tmain(int argc, _TCHAR* argv[])//_tmain �Լ�
{
	clock_t t_start, t_end;;//ó�� �ð�, �� �ð�
	double duration;//��� �ð�

	srand(seedval);

	init_pop();//������ �ʱ�ȭ
	t_start = clock();//�ð� ���� ����
	ga_impl();//�˰��� ����
	t_end = clock();//�ð� ���� ����
	duration = (double)(t_end - t_start) / CLOCKS_PER_SEC;//���� �˰����� �����ϴµ� �ɸ� �ð��� ���
	//CLOCKS_PER_SEC�� �������� clock������ �ʷ� �ٲ�(stdlib.h�� ���ǵǾ� ����)
	printf("����ð�: %f\n", duration);//���� �˰����� �����ϴµ� �ɸ� �ð��� ���

	return 0;
}
