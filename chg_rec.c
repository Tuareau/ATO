#include "header.h"
#include "select.h" // для find_node()

// изменение направления, времени, стоимости полета
void change(char *, char *, int);
// получение информации для изменения
void get_to_change(int);
// изменение пункта отправления самолета
void change_base(char *, char *);

void change_rec(void)
{
	enum {BASE, DIRECT, TIME, COST};
	int c;
	do {
		printf("\n\tEDITING THE RECORD FROM THE DATABASE\n\n");

		printf("List of issues:\n");
		printf("0 - Quit without saving\n");
		printf("1 - Cancel editing\n");
		printf("2 - Change base\n");
		printf("3 - Change destination\n");
		printf("4 - Change time\n");
		printf("5 - Change cost\n");
		if (scanf_s("%d", &c) != 1)
		{
			// очищение потока ввода
			while (getchar() != '\n');
			printf("\nError: invalid input\n");
			break;
		}
		// очищение потока ввода
		while (getchar() != '\n');

		system("cls");
		switch (c) {
		case 0:
			exit(EXIT_SUCCESS);
		case 1:
			break;
		case 2:
			get_to_change(BASE);
			break;
		case 3:
			get_to_change(DIRECT);
			break;
		case 4:
			get_to_change(TIME);
			break;
		case 5:
			get_to_change(COST);
			break;
		default:
			printf("\nWrong choice\n\n");
		}

	} while (c != 1);
	return;
}

void get_to_change(int cond)
{
	print_graph();
	printf("\n\tCHANGING FLIGHT INFORMATION\n\n");
	char base[LEN], dest[LEN];
	printf("Set the records in this format:\n");
	printf("BASE DESTINATION\n");
	printf("Be careful!\n");
	printf("End the input by using EOF\n");

	// ввод пункта отправления изменяемого полета
	while (scanf_s("%s", base, LEN) && base[0] != EOF)
	{
		// ввод пункта назначения
		scanf_s("%s", dest, LEN);
		// вызов функции в зависимости от условия изменения
		if (cond)
			change(base, dest, cond);
		else
			change_base(base, dest);
	}
}

// изменение направления, времени и стоимости
// изменение выбирается в зависимости от параметра option
void change(char *base, char *dest, int option)
{
	char newarr[LEN];
	float newtime_dep, newtime_arr;
	int newcost;
	char hours[3], mins[3];
	char tmp[1];

	enum {DIRECT = 1, TIME, COST};
	// получение новых данных о полете
	switch (option)
	{
	case DIRECT:
		printf("Put a new destination for %s-%s flight: ", base, dest);
		scanf_s("%s", newarr, LEN);
		break;
	case TIME:
		printf("Put a new time for %s-%s flight in DEPARTURE_TIME<hours : minutes> ARRIVE_TIME<hours : minutes> format: ", base, dest);
		printf("Be careful!\n");
		scanf_s("%s", hours, 3);
		scanf_s("%s", tmp, 1);
		scanf_s("%s", mins, 3);
		newtime_dep = convert_time(hours, mins);
		scanf_s("%s", hours, 3);
		scanf_s("%s", tmp, 1);
		scanf_s("%s", mins, 3);
		newtime_arr = convert_time(hours, mins);
		break;
	case COST:
		printf("Put a new cost for %s-%s flight: ", base, dest);
		scanf_s("%d", &newcost);
		break;
	}

	// внесение данных в базу
	int changed = 0;
	if (graph)
	{
		// поиск самолета
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++)
		{
			if (strcmp((*plane)->base, base) == 0)
			{
				if ((*plane)->direct_tab)
				{
					// поиск полета
					struct Direct **direct;
					for (direct = (*plane)->direct_tab; direct <= (*plane)->last_direct; direct++)
					{
						if (strcmp((*direct)->aim, dest) == 0)
						{
							// изменение данных
							switch (option)
							{
							case DIRECT:
								strcpy_s((*direct)->aim, LEN, newarr);
								break;
							case TIME:
								(*direct)->depart = newtime_dep;
								(*direct)->arrive = newtime_arr;
								break;
							case COST:
								(*direct)->cost = newcost;
								break;
							}
							printf("Information was changed succesfully\n");
							changed = 1;
							break;
						}
							
					}
					// прерывание поиска самолета при успешном изменении
					if (changed) 
						break;
					if (direct > (*plane)->last_direct)
						printf("Sorry, but there is no \"%s\"-\"%s\" flight in the database\n\n", base, dest);

				}
			}
		}
		if (plane > last_plane)
			printf("Sorry, no \"%s\" in the database\n\n", base);
	}
	else printf("Please, add records; database is empty, nothing to change\n");

	return;
}

// изменение самолета одного авиарейса
// если имеется, переносит полет к нему
// если новый, то выделяет память под новый
void change_base(char *base, char *dest)
{
	char newbase[LEN];
	printf("Put a new base for %s-%s flight: ", base, dest);
	scanf_s("%s", newbase, LEN);

	// флаг: 1, если новый самолет найден в базе
	int found_new = 0;
	// если не одинаковые имена (изменение нужно)
	if ((strcmp(base, newbase) != 0) && graph)
	{
		struct Plane **old_plane;
		struct Direct **old_aim;

		// поиск изменяемого пути: самолет
		for (old_plane = graph; old_plane <= last_plane; old_plane++)
			if (strcmp((*old_plane)->base, base) == 0)
				break;
		if (old_plane > last_plane) 
		{
			printf("You were mistaken, no old base like this: \"%s\"\n", base);
			return;
		}
		// поиск изменяемого пути: полет
		if ((*old_plane)->direct_tab)
		{
			for (old_aim = (*old_plane)->direct_tab; old_aim <= (*old_plane)->last_direct; old_aim++)
				if (strcmp((*old_aim)->aim, dest) == 0)
					break;
			if (old_aim > (*old_plane)->last_direct)
			{
				printf("You were mistaken, no old destination like this: \"%s\"\n", dest);
				return;
			}
		}
		else 
		{
			printf("You should know: no flights from \"%s\"\n", base);
			return;
		}

		// поиск измененного самолета в базе
		struct Plane **new_plane;
		for (new_plane = graph; new_plane < last_plane; new_plane++)
		{
			if (strcmp((*new_plane)->base, newbase) == 0) {
				found_new = 1;
				break;
			}
		}

		// если новый самолет найден среди имеющихся
		// данные полета переносятся к нему
		// иначе выделяется память под новый самолет и переносится к новому
		if (found_new)
		{
			// расширение массива указателей на полеты
			if ((*new_plane)->directs == (*new_plane)->dir_p_amount)
			{
				(*new_plane)->dir_p_amount += SIZE;
				(*new_plane)->direct_tab = (struct Direct **)realloc((*new_plane)->direct_tab, 
					(*new_plane)->dir_p_amount * sizeof(struct Direct *));
				int j = (*new_plane)->directs; // для сокращения записи
				memset(&((*new_plane)->direct_tab[j]), 0, SIZE * sizeof(struct Direct *));
			}
			(*new_plane)->last_direct = (*new_plane)->direct_tab;
			(*new_plane)->last_direct += (*new_plane)->directs;
			(*new_plane)->directs++;

			// выделение памяти под полет
			struct Direct *new_direct;
			*((*new_plane)->last_direct) = (struct Direct *)malloc(sizeof(struct Direct));
			// указатель на полет
			new_direct = *((*new_plane)->last_direct);
			// копирование данных
			new_direct->cost = (*old_aim)->cost;
			new_direct->arrive = (*old_aim)->arrive;
			new_direct->depart = (*old_aim)->depart;
			strcpy_s(new_direct->aim, LEN, dest);
			printf("Data of flight \"%s\"-\"%s\" was filled successfuly\n", (*new_plane)->base, dest);
		}
		else
		{
			// расширение массива указателей на самолеты
			if (size == p_amount)
			{
				p_amount += SIZE;
				graph = (struct Plane **)realloc(graph, p_amount * sizeof(struct Plane *));
				memset(&graph[size], 0, SIZE * sizeof(struct Plane *));
			}
			last_plane = graph;
			last_plane += size;
			size++;

			// выделение памяти под самолет
			*last_plane = (struct Plane *)malloc(sizeof(struct Plane));
			strcpy_s((*last_plane)->base, LEN, newbase);
			printf("Record \"%s\" was added successfuly\n", newbase);
			// обнуление количества полетов
			(*last_plane)->directs = (*last_plane)->dir_p_amount = 0;

			// выделение памяти под указатель на полет, обязательно являющийся первым
			(*last_plane)->direct_tab = (struct Direct **)malloc(sizeof(struct Direct *));
			(*last_plane)->last_direct = (*last_plane)->direct_tab;
			(*last_plane)->directs++;
			(*last_plane)->dir_p_amount++;

			// выделение памяти под полет
			struct Direct *new_direct;
			(*last_plane)->direct_tab[0] = (struct Direct *)malloc(sizeof(struct Direct));
			new_direct = (*last_plane)->direct_tab[0];

			// копирование данных полета
			new_direct->cost = (*old_aim)->cost;
			new_direct->arrive = (*old_aim)->arrive;
			new_direct->depart = (*old_aim)->depart;
			strcpy_s(new_direct->aim, LEN, dest);
			printf("Data of flight \"%s\"-\"%s\" was filled successfuly\n", (*last_plane)->base, dest);
			
		}

		// удаление старого полета
		// если был единственный полет
		if ((*old_plane)->last_direct == (*old_plane)->direct_tab) 
		{
			free(*old_aim);
			*old_aim = NULL;
			(*old_plane)->last_direct = (*old_plane)->direct_tab = NULL;
		}
		else
		{
			// освобождение памяти старого полета
			free(*old_aim);
			*old_aim = *((*old_plane)->last_direct);
			*((*old_plane)->last_direct) = NULL;
			// уменьшение указателя на последний
			(*old_plane)->last_direct--;
		}
		// уменьшение числа полетов старого самолета
		(*old_plane)->directs--;
		// уменьшение числа указатедей в массиве в старом самолете
		(*old_plane)->dir_p_amount--;

	}
	else printf("Stop, please: new and old are the same or the database is empty\n");

	return;
}