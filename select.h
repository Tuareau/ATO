#pragma once
#ifndef _SELECT_H_
#define _SELECT_H_

// реализация алгоритма Дейкстра

// тип данных таблица
struct Tab {
	int cost; // стоимость полета
	char name[LEN]; // пункт назначения
	char parent[LEN]; // пункт отправления - родитель
	int parsed; // статус обработки полета
};

// указатель на массив указателей на записи таблицы
struct Tab **table;
// указатель на указатель на последнюю запись
struct Tab **last_tab;

// чертение таблицы
void set_table(struct Plane *);

// освобождение памяти
void clear_table(void);

// поиск записи с наименьшей стоимостью, поиск записи, самолета
struct Tab *find_lowest(void);
struct Plane *find_node(char *);
struct Tab *find_tab(char *);

// вывод результата
void print_result(struct Tab *, struct Plane *, struct Plane *);

// реализация поиска в ширину

// тип данных запись
struct Note {
	char name[LEN]; // пункт назначения
	char parent[LEN]; // пункт отправления
	int parsed; // статус обработки
};

// указатель на массив указателей на записи
struct Note **list;
// указатель на указатель на последнюю запись
struct Note **last_list;

// количество указателей в массиве
extern int notes;

// поиск записи
struct Note *find_note(char *);

// вывод результата
void print_path(struct Note *, struct Plane *);

// освобождение памяти
void clear_list(void);

#endif