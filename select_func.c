#include "header.h"
#include "select.h"

// поиск города в графе
struct Plane *find_node(char *name)
{
	struct Plane **plane;
	for (plane = graph; plane <= last_plane; plane++)
		if (strcmp((*plane)->base, name) == 0)
			return *plane;
	return NULL;
}

// поиск наименьшей стоимости в таблице
// -1 если наименьшего нет (все обработаны)
struct Tab *find_lowest(void)
{
	int min = INT_MAX;
	struct Tab **tab, **mintab = NULL;
	for (tab = table; tab <= last_tab; tab++)
	{
		if ((*tab)->cost < min) 
		{
			if (!((*tab)->parsed)) 
			{
				min = (*tab)->cost;
				mintab = tab;
			}
		}
	}
	return (mintab) ? *mintab : NULL;
}

// нахождение записи в таблице
struct Tab *find_tab(char *s)
{
	if (table) 
	{
		struct Tab **tab;
		for (tab = table; tab <= last_tab; tab++)
		{
			if (strcmp((*tab)->name, s) == 0)
				return *tab;
		}
	}
	return NULL;
}

// рекурсивный вывод результата
void print_result(struct Tab *tp, struct Plane *depart, struct Plane *arrive)
{
	struct Tab *tabptr;
	// пока не дошли до главного родителя
	if (strcmp(tp->parent, depart->base) != 0)
	{
		// переходим к родителю текущего
		tabptr = find_tab(tp->parent);
		// и повторяем переход
		print_result(tabptr, depart, arrive);
	}
	if (strcmp(tp->name, arrive->base) != 0)
		printf("- from %s to %s\n", tp->parent, tp->name);
	else 
	{
		printf("- from %s to %s\n", tp->parent, tp->name);
		printf("Summary cost: %d\n\n", tp->cost);
	}
}

// рекурсивный вывод результата
void print_path(struct Note *np, struct Plane *depart)
{
	struct Note *note;
	// пока не дошли до главного родителя
	if (strcmp(np->parent, depart->base) != 0)
	{
		// переходим к родителю текущего
		note = find_note(np->parent);
		// и повторяем переход
		print_path(note, depart);
	}
	printf("- from %s to %s\n", np->parent, np->name);
	return;
}