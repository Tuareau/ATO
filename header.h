#define _CRT_SECURE_NO_WARNINGS // ������ ��� fopen()
#pragma once
#ifndef _ATO_H_
#define _ATO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 40 // ���������� ����� ��������

#define SIZE 5 // ���������� ����������� ���������� � ������

// ��� ������ �����
struct Direct {
	char aim[LEN]; // ��� ������ ����������
	int cost; // ��������� ������
	float depart, arrive; // ����� ����������� � ��������
};

// ��� ������ �������
struct Plane {
	char base[LEN]; // ��� ������ �����������
	struct Direct **direct_tab; // ��������� �� ������ ���������� �� ������
	struct Direct **last_direct; // ��������� �� ��������� �� ��������� �����
	int directs; // ��������� ������� ����������
	int dir_p_amount; // ���������� ���������� � �������
};

// ��������� �� ������ ���������� �� ��������
struct Plane **graph;

// ��������� �� ��������� �� ��������� �������
struct Plane **last_plane;

// ���������� ���������
extern int size;

// ���������� ���������� � �������
extern int p_amount;


// ���������������� ����
void start(char *); // ������� ���� � ��������� �����
void end(char *); // ������ ������ � ���� � ������������ ������

void manage(void); // ���������� ����� ������
void select(void); // ������ ����-

void select_cost(void); // �� ���������
void select_time(void); // �� ������� ��������

void add_rec(void); // ���������� �������
void delete_rec(void); // �������� �������
void delete_all(void); // �������� ���� �������
void change_rec(void); // ��������� ����������

// ����� ����������� ���� ������
void print_graph(void);

// ����������� �������
float convert_time(char *, char *);

#endif