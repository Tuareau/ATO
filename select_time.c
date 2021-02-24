#include "header.h"
#include "select.h"

#define PLACE 100

int notes = 0;

void select_time(void)
{
	print_graph();
	printf("\n\tSELECTING THE ROUTE WITH THE LOWEST TIME OF WAITING\n\n");

	// начало и конец маршрута
	char dep[LEN], arr[LEN];
	printf("The city of departure:\n");
	scanf_s("%s", dep, LEN);
	printf("The city of arrival:\n");
	scanf_s("%s", arr, LEN);
	printf("\n");

	if (!graph) {
		printf("What a loss: database is empty\n");
		return;
	}

	// нахождение указателей на последний и начальный пункты
	struct Plane *depart, *arrive;
	if ((depart = find_node(dep)) == NULL)
	{
		printf("Try again later: no city like \"%s\" in the database", dep);
		return;
	}
	if ((arrive = find_node(arr)) == NULL)
	{
		printf("Try again later: no city like \"%s\" in the database", arr);
		return;
	}

	// создание очереди
	char *queue[PLACE];
	for (int q = 0; q < PLACE; q++)
		queue[q] = NULL;
	queue[0] = (char *)malloc(sizeof(char[LEN]));
	strcpy_s(queue[0], LEN, dep);

	// заполнение списка
	struct Plane **plane;
	for (plane = graph; plane <= last_plane; plane++)
	{
		list = (struct Note **)realloc(list, (notes + 1) * sizeof(struct Note *));
		last_list = list;
		last_list += notes;
		notes++;

		*last_list = (struct Note *)malloc(sizeof(struct Note));
		strcpy_s((*last_list)->name, LEN, (*plane)->base);
		(*last_list)->parsed = 0;
		strcpy_s((*last_list)->parent, LEN, "");
	}

	// поиск в ширину
	int found = 0;
	int i;
	// пока очередь не пуста
	for (i = 0; (queue[i] != NULL) && i < PLACE; i++)
	{
		// если конечный пуект найден, останавливаем поиск
		if (found)
			break;
		// проверка на конечный
		if (strcmp(queue[i], arr) == 0)
			found = 1;
		// берем первый узел в очереди
		struct Plane *cur_plane = find_node(queue[i]);

		// перебираем полеты от узла
		struct Direct **direct;
		if (cur_plane->direct_tab)
		{
			for (direct = cur_plane->direct_tab; direct <= cur_plane->last_direct; direct++)
			{
				struct Note *note;
				note = find_note((*direct)->aim);
				if (note) 
				{
					// если полет не обработан
					if (!note->parsed)
					{
						// отмечаем как обработанный и добавляем в очередь
						note->parsed = 1;
						int g, filled = 0;
						for (g = 0; g < PLACE; g++)
						{
							// пропускаем пустые указатели в начале очереди
							// затем пропускаем ненулевые указатели
							// затем добавляем в очередь
							if (filled && queue[g] == NULL) 
							{
								queue[g] = (char *)malloc(sizeof(char[LEN]));
								strcpy_s(queue[g], LEN, (*direct)->aim);
								break;
							}
							if (!filled && queue[g])
								filled = 1;
						}
						// записываем родителя
						strcpy_s(note->parent, LEN, cur_plane->base);
					}
				}
			}
		}
		// удаляем из очереди
		free(queue[i]);
		queue[i] = NULL;
	}

	// вывод пути
	printf("The way from %s to %s:\n", depart->base, arrive->base);
	struct Note *dest = find_note(arrive->base);
	if (!dest || !found)
		printf("Unfortunately, there is no path to \"%s\" from \"%s\"\n", arrive->base, depart->base);
	else
		print_path(dest, depart);
	printf("\n");

	// освобождение списка
	clear_list();
	notes = 0;
	// освобождение очереди
	int j;
	for (j = i; j < PLACE; j++)
	{
		if (queue[j]) 
		{
			free(queue[j]);
			queue[j] = NULL;
		}
		else break;
	}

	return;
}

// поиск записи
struct Note *find_note(char *name)
{
	struct Note **note;
	if (list)
	{
		for (note = list; note <= last_list; note++)
		{
			if (strcmp((*note)->name, name) == 0)
				return *note;
		}
	}
	return NULL;
}

void clear_list(void)
{
	struct Note **note;
	if (list)
	{
		for (note = list; note <= last_list; note++)
			free(*note);
		list = last_list = NULL;
	}
}