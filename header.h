#define _CRT_SECURE_NO_WARNINGS // только для fopen()
#pragma once
#ifndef _ATO_H_
#define _ATO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 40 // допустимая длина названий

#define SIZE 5 // количество добавляемых указателей в массив

// тип данных полет
struct Direct {
	char aim[LEN]; // имя пункта назначения
	int cost; // стоимость полета
	float depart, arrive; // время отправления и прибытия
};

// тип данных самолет
struct Plane {
	char base[LEN]; // имя пункта отправления
	struct Direct **direct_tab; // указатель на массив указателей на полеты
	struct Direct **last_direct; // указатель на указатель на последний полет
	int directs; // количетво пунктов назначения
	int dir_p_amount; // количество указателей в массиве
};

// указатель на массив указателей на самолеты
struct Plane **graph;

// указатель на указатель на последний самолет
struct Plane **last_plane;

// количество самолетов
extern int size;

// количество указателей в массиве
extern int p_amount;


// пользовательское меню
void start(char *); // главное меню и обработка файла
void end(char *); // запись данных в файл и освобождение памяти

void manage(void); // управление базой данных
void select(void); // подбор пути-

void select_cost(void); // по стоимости
void select_time(void); // по времени ожидания

void add_rec(void); // добавление записей
void delete_rec(void); // удаление записей
void delete_all(void); // удаление всех записей
void change_rec(void); // изменение информации

// вывод содержимого базы данных
void print_graph(void);

// конвертация времени
float convert_time(char *, char *);

#endif