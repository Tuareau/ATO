#include "header.h"

void start(char *file_name)
{
	FILE *fp;
	// ���� ���� ���������� � ������� ������
	if (fp = fopen(file_name, "rb"))
	{
		// ��������� � ����� �����
		fseek(fp, 0, SEEK_END);
		// ���� ���� �� ����
		if (ftell(fp))
		{
			rewind(fp);

			// ���� ������ ����� �� �����������
			while (!feof(fp)) 
			{
				// �������������� �������� �� ����� ����� 
				int cur = ftell(fp);  // ������� �������� �����
				fseek(fp, 0, SEEK_END);
				int end = ftell(fp); // ������� ��������� �����
				// ���������, ��������� �� ����� �����
				if ((end - cur) == 0)
					break;
				else fseek(fp, cur, SEEK_SET); // ����������� �� �������

				// �������� ������ � ������� ����������
				if (size == p_amount)
				{
					// ����������� ���-�� ���������� � ���������������� ������
					p_amount += SIZE;
					graph = (struct Plane **)realloc(graph, p_amount * sizeof(struct Plane *));
					memset(&graph[size], 0, SIZE * sizeof(struct Plane *));
				}
				// ��������� �� ��������� ���������
				last_plane = graph;
				last_plane += size;

				// ����������� ���������� ���������
				size++;

				// �������� ������ ��� ���������
				*last_plane = (struct Plane *)malloc(sizeof(struct Plane));
				// ������������� ������ ������
				(*last_plane)->direct_tab = NULL;
				(*last_plane)->last_direct = NULL;
				(*last_plane)->directs = 0;
				(*last_plane)->dir_p_amount = 0;

				// ���������� ����� ����������� ��������
				fread((*last_plane)->base, sizeof((*last_plane)->base), 1, fp);
				// ���������� ������
				int flag = 1;
				while (flag) 
				{
					// ������ �����, ����������� � �������
					// ��� ���������� ������
					fread(&flag, sizeof(int), 1, fp);
					// ���� ���� ������ � ������
					if (flag)
					{	
						// ��������� ������ ��� ������ ���������� �� ������				
						if ((*last_plane)->dir_p_amount == (*last_plane)->directs)
						{
							(*last_plane)->dir_p_amount += SIZE;
							(*last_plane)->direct_tab = (struct Direct **)realloc((*last_plane)->direct_tab, 
								(*last_plane)->dir_p_amount * sizeof(struct Direct *));
							int j = (*last_plane)->directs;
							memset(&((*last_plane)->direct_tab[j]), 0, SIZE * sizeof(struct Direct *));
						}
						// ������������� ��������� �� ��������� ���������
						(*last_plane)->last_direct = (*last_plane)->direct_tab;
						(*last_plane)->last_direct += (*last_plane)->directs;

						// ����������� ���������� ������� ��������
						(*last_plane)->directs++; 
											
						// ��������� ������ ��� ����� � ������ ������
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

	// ������� ����
	int c;
	do {
		printf("\n\tWELCOME TO AIRLINE TICKET OFFICE\n\n");

		printf("List of issues:\n");
		printf("0 - Save and quit\n");
		printf("1 - Pick up the route\n");
		printf("2 - Manage the database\n");
		if (scanf_s("%d", &c) != 1)
		{
			// �������� ������ �����
			while (getchar() != '\n');
			printf("\nError: invalid input\n");
			continue;
		}
		// �������� ������ �����
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