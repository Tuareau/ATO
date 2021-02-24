#include "header.h"
#include "select.h"

void select_cost(void)
{
	print_graph();
	printf("\n\tSEARCHING FOR THE CHEAPEST ROUTE\n\n");

	char dep[LEN], arr[LEN];
	printf("The city of departure:\n");
	scanf_s("%s", dep, LEN);
	printf("The city of arrival:\n");
	scanf_s("%s", arr, LEN);
	printf("\n");

	if (!graph) 
	{
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

	// чертение таблицы
	set_table(depart);

	// алгоритм Дейкстра
	int cost, newcost;
	struct Plane *node;
	// находим наименьший по значению пункт от начального
	struct Tab *m = find_lowest();
	// пока не все элементы обработаны
	while (m)
	{
		// запоминаем цену
		cost = m->cost;
		// находим элемент среди самолетов
		node = find_node(m->name);

		if (node) 
		{
			if (node->direct_tab) 
			{
				// перебираем его полеты
				struct Direct **direct;
				for (direct = node->direct_tab; direct <= node->last_direct; direct++)
				{
					// находим новую цену
					newcost = cost + (*direct)->cost;
					// ищем в таблице пункт назначения
					struct Tab **tab;
					for (tab = table; tab <= last_tab; tab++)
					{
						if (strcmp((*direct)->aim, (*tab)->name) == 0)
							break;
					}

					// если новая цена меньше старой
					if ((*tab)->cost > newcost) 
					{
						// записываем новую цену и родителя
						(*tab)->cost = newcost;
						strcpy_s((*tab)->parent, LEN, node->base);
					}
				}
			}
		}
		// отмечаем узел как обработанный
		m->parsed = 1;
		// находим следующий наимешьший среди необработанных
		m = find_lowest();
	}

	// нахождение точки назначения в таблице
	struct Tab **tab;
	for (tab = table; tab <= last_tab; tab++)
		if (strcmp(arrive->base, (*tab)->name) == 0)
			break;
	printf("The way from %s to %s:\n", depart->base, arrive->base);
	print_result(*tab, depart, arrive);
	printf("\n");

	// освобождение памяти
	clear_table();

	return;
}

// создание таблицы, принимает указатель на точку отправления
void set_table(struct Plane *basic)
{
	last_tab = table = NULL;
	// cnt - счетчик записей в таблице
	int cnt = 0;
	struct Plane **plane;
	// таблица родителей и кратчайшего времени до пунктов
	for (plane = graph; plane <= last_plane; plane++)
	{
		if ((*plane)->direct_tab) 
		{
			struct Direct **direct;
			for (direct = (*plane)->direct_tab; direct <= (*plane)->last_direct; direct++)
			{
				if (strcmp((*direct)->aim, basic->base) != 0)
				{	
					// если уже записан
					if (find_tab((*direct)->aim))
					{
						// если был записан не от родителя
						if (*plane == basic)
						{
							// копируем родителя и цену
							struct Tab *tab;
							tab = find_tab((*direct)->aim);
							tab->cost = (*direct)->cost;
							strcpy_s(tab->parent, LEN, (*plane)->base);
						}
					}
					else
					{
						table = (struct Tab **)realloc(table, (cnt + 1) * sizeof(struct Tab *));
						last_tab = table;
						last_tab += cnt;
						cnt++;

						*last_tab = (struct Tab *)malloc(sizeof(struct Tab));
						strcpy_s((*last_tab)->name, LEN, (*direct)->aim);
						(*last_tab)->parsed = 0;
						// если от начального пункта, то и время записываем, а также родителя
						if (*plane == basic) {
							(*last_tab)->cost = (*direct)->cost;
							strcpy_s((*last_tab)->parent, LEN, (*plane)->base);
						}
						else
						{
							(*last_tab)->cost = INT_MAX;
							strcpy_s((*last_tab)->parent, LEN, "");
						}
					}
				}
			}
		}
	}
	return;
}

// освобождение памяти, отведенной под таблицу
void clear_table(void)
{
	struct Tab **tab;
	if (!table) 
		return;
	for (tab = table; tab <= last_tab; tab++)
		free(*tab);
	free(table);
	table = last_tab = NULL;
	return;
}