#include "header.h"

// заполнение данных о полетах
void set_rec(void);

void add_rec(void)
{
	printf("\n\tADDING THE RECORD TO THE DATABASE\n\n");
	char base[LEN];

	printf("Fill the records in this format:\n");
	printf("BASE\n");
	printf("Be careful!\n");
	printf("End the input by using EOF\n");

	while (scanf_s("%s", base, LEN) && base[0] != EOF)
	{
		// расширение массива указателей
		if (size == p_amount)
		{
			p_amount += SIZE;
			graph = (struct Plane **)realloc(graph, p_amount * sizeof(struct Plane *));
			memset(&graph[size], 0, SIZE * sizeof(struct Plane *));
		}
		last_plane = graph;
		last_plane += size;
		size++;

		// выделение памяти под полет
		*last_plane = (struct Plane *)malloc(sizeof(struct Plane));
		// запись пункта отправления
		strcpy_s((*last_plane)->base, LEN, base);
		printf("Record \"%s\" was added successfuly\n", base);
		// инициализация содержимого структуры
		(*last_plane)->direct_tab = NULL;
		(*last_plane)->last_direct = NULL;
		(*last_plane)->directs = (*last_plane)->dir_p_amount = 0;
	}
	// заполнение данных о полетах
	set_rec();
	return;
}

// заполнение данных о полетах
void set_rec(void)
{	
	if (!graph)
		return;
	print_graph();

	char base[LEN], dest[LEN];
	float dep, arr;
	char hours[3], mins[3];
	int cost;
	printf("Set the records in this format:\n");
	printf("BASE DESTINATION DEPARTURE_TIME<hours : minutes> ARRIVE_TIME<hours : minutes> COST\n");
	printf("Be careful!\n");
	printf("End the input by using EOF\n");

	while (scanf_s("%s", base, LEN) && base[0] != EOF)
	{
		// ввод данных о полете
		scanf_s("%s", dest, LEN);
		char buf[1];
		scanf_s("%s", hours, 3);
		scanf_s("%s", buf, 1);
		scanf_s("%s", mins, 3);
		// преобразование времени в одину переменную float
		dep = convert_time(hours, mins);
		scanf_s("%s", hours, 3);
		scanf_s("%s", buf, 1);
		scanf_s("%s", mins, 3);
		// преобразование времени в одину переменную float
		arr = convert_time(hours, mins);
		scanf_s("%d", &cost);

		// поиск самолета по пункту отправления
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++)
		{
			if (strcmp((*plane)->base, base) == 0)
			{
				// расширение массива указателей на полеты
				if ((*plane)->directs == (*plane)->dir_p_amount)
				{
					(*plane)->dir_p_amount += SIZE;
					(*plane)->direct_tab = (struct Direct **)realloc((*plane)->direct_tab, (*plane)->dir_p_amount * sizeof(struct Direct *));
					int j = (*plane)->directs;
					memset(&((*plane)->direct_tab[j]), 0, SIZE * sizeof(struct Direct *));
				}
				(*plane)->last_direct = (*plane)->direct_tab;
				(*plane)->last_direct += (*plane)->directs;
				(*plane)->directs++;

				// выделение памяти под полет и заполнение данными
				*((*plane)->last_direct) = (struct Direct *)malloc(sizeof(struct Direct));
				(*((*plane)->last_direct))->cost = cost;
				(*((*plane)->last_direct))->arrive = arr;
				(*((*plane)->last_direct))->depart = dep;
				strcpy_s((*((*plane)->last_direct))->aim, LEN, dest);
				printf("Data of flight \"%s\"-\"%s\" was filled successfuly\n", base, dest);
				break;
			}
		}
		if (plane > last_plane)
			printf("Sorry, no base like \"%s\" was found\n", base);
	}
	return;
}

// конвертирование времени во float
float convert_time(char *hour, char *min)
{
	float hours, mins;
	if ((hours = (float)atof(hour)) > 24.0 || hours < 0.0)
	{
		printf("Error: time convertation, wrong hours, set to 0\n");
		printf("Please, change time data after settings complete\n");
		return 0.0;
	}
	if ((mins = (float)atof(min)) > 60.0 || mins < 0.0)
	{
		printf("Error: time convertation, wrong minutes, set to 0\n");
		printf("Please, change time data after settings complete\n");
		return 0.0;
	}
	else
		mins /= 60.0;
	return (hours + mins);
}

// вывод всего содержимого базы данных
void print_graph(void)
{
	printf("\nDATABASE:\n\n");

	// проверка массива на пустоту
	if (graph)
	{
		// перебор указателей на указатели на самолеты
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++)
		{
			printf("%s:\n", (*plane)->base);
			// проверка массива указателей на полеты на пустоту
			if ((*plane)->direct_tab)
			{
				// перебор указателей на указатели на полеты
				struct Direct **direct;
				for (direct = (*plane)->direct_tab; direct <= (*plane)->last_direct; direct++)
					printf("-) to %s for %d pounds\n", (*direct)->aim, (*direct)->cost);
			}
			printf("\n");
		}
		printf("\n");
	}
	else
		printf("\tDatabase is empty\n\n");
}