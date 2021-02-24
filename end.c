#include "header.h"

void end(char *file_name)
{
	// ������ � ����
	FILE *fp;
	// ���� ���� �����
	if (!graph) 
	{
		// ������� ������ ����
		if ((fp = fopen(file_name, "wb")) == NULL)
			printf("\n\tERROR: FILE WAS NOT OPENED\n");
		return;
	}
		
	if (fp = fopen(file_name, "wb"))
	{
		// ���������� ����
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++) 
		{
			// ���������� ��� ����
			fwrite((*plane)->base, sizeof((*plane)->base), 1, fp);

			// ������ �����, ����������, ��� ������� ������
			int flight_flag = 1;
			if ((*plane)->direct_tab) 
			{
				// ���������� ������
				struct Direct **direct;
				for (direct = (*plane)->direct_tab; direct <= (*plane)->last_direct; direct++)
				{
					// ������ ����� � ����
					fwrite(&flight_flag, sizeof(int), 1, fp);
					// ������ �����, �������, ���������
					fwrite((*direct)->aim, sizeof((*direct)->aim), 1, fp);
					fwrite(&((*direct)->depart), sizeof(float), 1, fp);
					fwrite(&((*direct)->arrive), sizeof(float), 1, fp);
					fwrite(&((*direct)->cost), sizeof(int), 1, fp);
				}
			}
			// ������ �����������, ���������� ��������������� ����
			flight_flag = 0;
			fwrite(&flight_flag, sizeof(int), 1, fp);
		}
	}
	else printf("\n\tERROR: FILE WAS NOT OPENED\n");

	// ������������ ������
	if (graph) 
	{
		struct Plane **plane;
		for (plane = graph; plane <= last_plane; plane++)
		{
			if ((*plane)->direct_tab) 
			{
				struct Direct **direct;
				for (direct = (*plane)->direct_tab; direct <= ((*plane)->last_direct); direct++)
					free(*direct);
				(*plane)->direct_tab = (*plane)->last_direct = NULL;
			}
			free(*plane);
		}
	}
	free(graph);
	graph = last_plane = NULL;
}