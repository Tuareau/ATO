#include "header.h"
#include "select.h"

// ����� ������ � �����
struct Plane *find_node(char *name)
{
	struct Plane **plane;
	for (plane = graph; plane <= last_plane; plane++)
		if (strcmp((*plane)->base, name) == 0)
			return *plane;
	return NULL;
}

// ����� ���������� ��������� � �������
// -1 ���� ����������� ��� (��� ����������)
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

// ���������� ������ � �������
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

// ����������� ����� ����������
void print_result(struct Tab *tp, struct Plane *depart, struct Plane *arrive)
{
	struct Tab *tabptr;
	// ���� �� ����� �� �������� ��������
	if (strcmp(tp->parent, depart->base) != 0)
	{
		// ��������� � �������� ��������
		tabptr = find_tab(tp->parent);
		// � ��������� �������
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

// ����������� ����� ����������
void print_path(struct Note *np, struct Plane *depart)
{
	struct Note *note;
	// ���� �� ����� �� �������� ��������
	if (strcmp(np->parent, depart->base) != 0)
	{
		// ��������� � �������� ��������
		note = find_note(np->parent);
		// � ��������� �������
		print_path(note, depart);
	}
	printf("- from %s to %s\n", np->parent, np->name);
	return;
}