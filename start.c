#include "header.h"

void start(char *file_name)
{
	FILE *fp;
	// если файл существует и успешно открыт
	if (fp = fopen(file_name, "rb"))
	{
		// переходим в конец файла
		fseek(fp, 0, SEEK_END);
		// если файл не пуст
		if (ftell(fp))
		{
			rewind(fp);

			// пока чтение файла не закончилось
			while (!feof(fp)) 
			{
				// дополнительная проверка на конец файла 
				int cur = ftell(fp);  // позиция текущего байта
				fseek(fp, 0, SEEK_END);
				int end = ftell(fp); // позиция конечного байта
				// проверяем, достигнут ли конец файла
				if ((end - cur) == 0)
					break;
				else fseek(fp, cur, SEEK_SET); // возвращение на позицию

				// выделяем память в массиве указателей
				if (size == p_amount)
				{
					// увеличиваем кол-во указателей и перераспределяем память
					p_amount += SIZE;
					graph = (struct Plane **)realloc(graph, p_amount * sizeof(struct Plane *));
					memset(&graph[size], 0, SIZE * sizeof(struct Plane *));
				}
				// указываем на последний указатель
				last_plane = graph;
				last_plane += size;

				// увеличиваем количество самолетов
				size++;

				// выделяем память под структуру
				*last_plane = (struct Plane *)malloc(sizeof(struct Plane));
				// инициализация членов данных
				(*last_plane)->direct_tab = NULL;
				(*last_plane)->last_direct = NULL;
				(*last_plane)->directs = 0;
				(*last_plane)->dir_p_amount = 0;

				// записываем пункт отправления самолета
				fread((*last_plane)->base, sizeof((*last_plane)->base), 1, fp);
				// перебираем полеты
				int flag = 1;
				while (flag) 
				{
					// чтение флага, сообщающего о наличии
					// или отсутствии полета
					fread(&flag, sizeof(int), 1, fp);
					// если есть запись о полете
					if (flag)
					{	
						// выделение памяти под массив указателей на полеты				
						if ((*last_plane)->dir_p_amount == (*last_plane)->directs)
						{
							(*last_plane)->dir_p_amount += SIZE;
							(*last_plane)->direct_tab = (struct Direct **)realloc((*last_plane)->direct_tab, 
								(*last_plane)->dir_p_amount * sizeof(struct Direct *));
							int j = (*last_plane)->directs;
							memset(&((*last_plane)->direct_tab[j]), 0, SIZE * sizeof(struct Direct *));
						}
						// устанавливаем указатель на последний указатель
						(*last_plane)->last_direct = (*last_plane)->direct_tab;
						(*last_plane)->last_direct += (*last_plane)->directs;

						// увеличиваем количество полетов самолета
						(*last_plane)->directs++; 
											
						// выделение памяти под полет и чтение данных
						struct Direct *new_direct;
						*((*last_plane)->last_direct) = (struct Direct *)malloc(sizeof(struct Direct));
						new_direct = *((*last_plane)->last_direct);
						fread(new_direct->aim, sizeof(char[LEN]), 1, fp);
						fread(&(new_direct->depart), sizeof(float), 1, fp);
						fread(&(new_direct->arrive), sizeof(float), 1, fp);
						fread(&(new_direct->cost), sizeof(int), 1, fp);
					}
					else break;
				}
			}
		}
	}

	print_graph();

	// главное меню
	int c;
	do {
		printf("\n\tWELCOME TO AIRLINE TICKET OFFICE\n\n");

		printf("List of issues:\n");
		printf("0 - Save and quit\n");
		printf("1 - Pick up the route\n");
		printf("2 - Manage the database\n");
		if (scanf_s("%d", &c) != 1)
		{
			// очищение потока ввода
			while (getchar() != '\n');
			printf("\nError: invalid input\n");
			continue;
		}
		// очищение потока ввода
		while (getchar() != '\n');

		system("cls");
		switch (c) {
		case 0: 
			printf("\n\tSEE YOU SOON\n");
			return;
		case 1: 
			select();
			break;
		case 2:
			manage();
			break;
		default:
			printf("\nWrong choice\n\n");
		}

	} while (c != 0);

	return;
}