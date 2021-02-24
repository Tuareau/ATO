#include "header.h"

// удаление всей информации узла графа
void delete_plane(void);
// удаление информации о полете
void delete_flight(void);

void delete_rec(void)
{
	int c;
	do {
		printf("\n\tDELETING THE RECORD FROM THE DATABASE\n\n");

		printf("List of issues:\n");
		printf("0 - Quit without saving\n");
		printf("1 - Cancel deleting and save\n");
		printf("2 - Delete the record of plane\n");
		printf("3 - Delete flight information\n");
		printf("4 - Delete all information\n");
		if (scanf_s("%d", &c) == EOF)
			break;
		system("cls");
		switch (c) {
		case 0:
			exit(EXIT_SUCCESS);
		case 1:
			break;
		case 2:
			delete_plane();
			break;
		case 3:
			delete_flight();
			break;
		case 4:
			delete_all();
			break;
		default:
			printf("Wrong choice\n\n");
		}

	} while (c != 1);
	return;
}

void delete_plane(void)
{
	print_graph();
	printf("\n\tDELETING PLANES INFORMATION\n\n");
	char base[LEN];

	if (!graph) 
	{
		printf("We found emptiness: database has no records yet, nothing to delete\n");
		return;
	}

	printf("Fill the records needed to be deleted in this format:\n");
	printf("BASE\n");
	printf("Be careful!\n");
	printf("End the input by using EOF\n");
	while (scanf_s("%s", base, LEN) && base[0] != EOF)
	{
		int deleted = 0;
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++)
		{
			// поиск узла графа
			if (strcmp((*plane)->base, base) == 0)
			{
				if ((*plane)->direct_tab)
				{
					struct Direct **direct;
					for (direct = (*plane)->direct_tab; direct <= (*plane)->last_direct; direct++)
						free(*direct);
					(*plane)->direct_tab = (*plane)->last_direct = NULL;
				}

				// удаление узла
				// если единственный самолет в базе
				if (last_plane == graph) 
				{
					free(*plane);
					last_plane = graph = NULL;
				}
				else
				{
					free(*plane);
					*plane = *last_plane;
					*last_plane = NULL;
					last_plane--;
				}
				size--;
				p_amount--;
				printf("Record \"%s\" was deleted successfuly\n", base);
				deleted = 1;
				break;
			}			
		}
		if (!deleted)
			printf("Are you sure? There is no \"%s\" in the database\n\n", base);
	}
	return;
}

void delete_flight(void)
{
	print_graph();
	printf("\n\tDELETING FLIGHT INFORMATION\n\n");
	char base[LEN], dest[LEN];

	if (!graph) 
	{
		printf("We found emptiness: database has no records yet, nothing to delete\n");
		return;
	}

	printf("Set the records in this format:\n");
	printf("BASE DESTINATION\n");
	printf("Be careful!\n");
	printf("End the input by using EOF\n");

	int deleted;
	while (scanf_s("%s", base, LEN) && base[0] != EOF)
	{
		scanf_s("%s", dest, LEN);
		deleted = 0;
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
							// удаляем старый полет
							// если был единственный полет
							if ((*plane)->last_direct == (*plane)->direct_tab) 
							{
								free(*direct);
								(*plane)->last_direct = (*plane)->direct_tab = NULL;
							}
							else
							{
								// освобождаем память от старого полета
								free(*direct);
								*direct = *((*plane)->last_direct);
								*((*plane)->last_direct) = NULL;
								// уменьшаем указатель на последний
								(*plane)->last_direct--;
								// освобождаем память под указатель на перенесенный последний
							}
							// уменьшаем число полетов в старом узле
							(*plane)->directs--;
							(*plane)->dir_p_amount--;
							printf("Flight \"%s\"-\"%s\" was deleted successfuly\n\n", base, dest);
							deleted = 1;
							break;
						}
					}
					if (!deleted)
						printf("Time wasted: no flight \"%s\"-\"%s\" in the database\n\n", base, dest);
				}
				else
					printf("Sad pilots: no flights from \"%s\" in the database\n\n", base);

				break;
			}
		}
		if (plane > last_plane)
			printf("Brake: no \"%s\" in the database\n\n", base);
	}
	return;
}

// удаление всей информации
void delete_all(void)
{
	printf("\n\tDELETING ALL INFORMATION\n\n");

	if (graph)
	{
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++)
		{
			if ((*plane)->direct_tab)
			{
				struct Direct **direct;
				for (direct = (*plane)->direct_tab; direct <= (*plane)->last_direct; direct++)
					free(*direct);
				(*plane)->direct_tab = (*plane)->last_direct = NULL;				
			}
			free(*plane);
		}
		graph = last_plane = NULL;
		size = 0;
		printf("All information was deleted successfuly\n");
	}
	else
		printf("Wow, we have nothing to do: database is empty, nothing to delete\n");
}