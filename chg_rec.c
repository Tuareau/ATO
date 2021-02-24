#include "header.h"
#include "select.h" // find_node()

// change of direction, time, cost of flight
void change(char *, char *, int);
// getting information to change
void get_to_change(int);
// change of the departure point of the aircraft
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
			while (getchar() != '\n');
			printf("\nError: invalid input\n");
			break;
		}
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

	while (scanf_s("%s", base, LEN) && base[0] != EOF)
	{
		scanf_s("%s", dest, LEN);
		if (cond)
			change(base, dest, cond);
		else
			change_base(base, dest);
	}
}

// change of direction, time and cost
// change is selected depending on the option parameter
void change(char *base, char *dest, int option)
{
	char newarr[LEN];
	float newtime_dep, newtime_arr;
	int newcost;
	char hours[3], mins[3];
	char tmp[1];

	enum {DIRECT = 1, TIME, COST};

	// get new data about the flight
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

	// adding data to the database
	int changed = 0;
	if (graph)
	{
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++)
		{
			if (strcmp((*plane)->base, base) == 0)
			{
				if ((*plane)->direct_tab)
				{
					struct Direct **direct;
					for (direct = (*plane)->direct_tab; direct <= (*plane)->last_direct; direct++)
					{
						if (strcmp((*direct)->aim, dest) == 0)
						{
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

// changing the plane of one flight
// if available, transfers the flight to it
// if new, allocates memory for the new one
void change_base(char *base, char *dest)
{
	char newbase[LEN];
	printf("Put a new base for %s-%s flight: ", base, dest);
	scanf_s("%s", newbase, LEN);

	// flag: 1, if a new plane is found in the database
	int found_new = 0;

	if ((strcmp(base, newbase) != 0) && graph)
	{
		struct Plane **old_plane;
		struct Direct **old_aim;

		// search for a changeable path: airplane
		for (old_plane = graph; old_plane <= last_plane; old_plane++)
			if (strcmp((*old_plane)->base, base) == 0)
				break;
		if (old_plane > last_plane) 
		{
			printf("You were mistaken, no old base like this: \"%s\"\n", base);
			return;
		}

		// search for a changeable path: flight
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

		struct Plane **new_plane;
		for (new_plane = graph; new_plane < last_plane; new_plane++)
		{
			if (strcmp((*new_plane)->base, newbase) == 0) {
				found_new = 1;
				break;
			}
		}

		// if a new aircraft is found among the existing ones
		// flight data is transferred to it
		// otherwise, the memory is allocated for the new plane and transferred to the new one
		if (found_new)
		{
			if ((*new_plane)->directs == (*new_plane)->dir_p_amount)
			{
				(*new_plane)->dir_p_amount += SIZE;
				(*new_plane)->direct_tab = (struct Direct **)realloc((*new_plane)->direct_tab, 
					(*new_plane)->dir_p_amount * sizeof(struct Direct *));
				int j = (*new_plane)->directs;
				memset(&((*new_plane)->direct_tab[j]), 0, SIZE * sizeof(struct Direct *));
			}
			(*new_plane)->last_direct = (*new_plane)->direct_tab;
			(*new_plane)->last_direct += (*new_plane)->directs;
			(*new_plane)->directs++;

			struct Direct *new_direct;
			*((*new_plane)->last_direct) = (struct Direct *)malloc(sizeof(struct Direct));
			new_direct = *((*new_plane)->last_direct);
			new_direct->cost = (*old_aim)->cost;
			new_direct->arrive = (*old_aim)->arrive;
			new_direct->depart = (*old_aim)->depart;
			strcpy_s(new_direct->aim, LEN, dest);
			printf("Data of flight \"%s\"-\"%s\" was filled successfuly\n", (*new_plane)->base, dest);
		}
		else
		{
			if (size == p_amount)
			{
				p_amount += SIZE;
				graph = (struct Plane **)realloc(graph, p_amount * sizeof(struct Plane *));
				memset(&graph[size], 0, SIZE * sizeof(struct Plane *));
			}
			last_plane = graph;
			last_plane += size;
			size++;

			*last_plane = (struct Plane *)malloc(sizeof(struct Plane));
			strcpy_s((*last_plane)->base, LEN, newbase);
			printf("Record \"%s\" was added successfuly\n", newbase);
			// îáíóëåíèå êîëè÷åñòâà ïîëåòîâ
			(*last_plane)->directs = (*last_plane)->dir_p_amount = 0;

			(*last_plane)->direct_tab = (struct Direct **)malloc(sizeof(struct Direct *));
			(*last_plane)->last_direct = (*last_plane)->direct_tab;
			(*last_plane)->directs++;
			(*last_plane)->dir_p_amount++;

			struct Direct *new_direct;
			(*last_plane)->direct_tab[0] = (struct Direct *)malloc(sizeof(struct Direct));
			new_direct = (*last_plane)->direct_tab[0];

			new_direct->cost = (*old_aim)->cost;
			new_direct->arrive = (*old_aim)->arrive;
			new_direct->depart = (*old_aim)->depart;
			strcpy_s(new_direct->aim, LEN, dest);
			printf("Data of flight \"%s\"-\"%s\" was filled successfuly\n", (*last_plane)->base, dest);
			
		}

		// deleting an old flight
		if ((*old_plane)->last_direct == (*old_plane)->direct_tab) 
		{
			free(*old_aim);
			*old_aim = NULL;
			(*old_plane)->last_direct = (*old_plane)->direct_tab = NULL;
		}
		else
		{
			free(*old_aim);
			*old_aim = *((*old_plane)->last_direct);
			*((*old_plane)->last_direct) = NULL;
			(*old_plane)->last_direct--;
		}
		(*old_plane)->directs--;
		(*old_plane)->dir_p_amount--;

	}
	else printf("Stop, please: new and old are the same or the database is empty\n");

	return;
}
