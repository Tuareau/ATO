#pragma once
#ifndef _SELECT_H_
#define _SELECT_H_

// ���������� ��������� ��������

// ��� ������ �������
struct Tab {
	int cost; // ��������� ������
	char name[LEN]; // ����� ����������
	char parent[LEN]; // ����� ����������� - ��������
	int parsed; // ������ ��������� ������
};

// ��������� �� ������ ���������� �� ������ �������
struct Tab **table;
// ��������� �� ��������� �� ��������� ������
struct Tab **last_tab;

// �������� �������
void set_table(struct Plane *);

// ������������ ������
void clear_table(void);

// ����� ������ � ���������� ����������, ����� ������, ��������
struct Tab *find_lowest(void);
struct Plane *find_node(char *);
struct Tab *find_tab(char *);

// ����� ����������
void print_result(struct Tab *, struct Plane *, struct Plane *);

// ���������� ������ � ������

// ��� ������ ������
struct Note {
	char name[LEN]; // ����� ����������
	char parent[LEN]; // ����� �����������
	int parsed; // ������ ���������
};

// ��������� �� ������ ���������� �� ������
struct Note **list;
// ��������� �� ��������� �� ��������� ������
struct Note **last_list;

// ���������� ���������� � �������
extern int notes;

// ����� ������
struct Note *find_note(char *);

// ����� ����������
void print_path(struct Note *, struct Plane *);

// ������������ ������
void clear_list(void);

#endif