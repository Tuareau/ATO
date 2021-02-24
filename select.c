#include "header.h"

void select(void)
{
	int c;
	do {
		printf("\n\tSEARCHING FOR THE ROUTE\n\n");

		printf("List of issues:\n");
		printf("0 - Exit the program\n");
		printf("1 - Return back\n");
		printf("2 - Select by timeouts in the transfers\n");
		printf("3 - Select by summary cost\n");
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
			exit(EXIT_SUCCESS);
		case 1:
			break;
		case 2:
			select_time();
			break;
		case 3:
			select_cost();
			break;
		default:
			printf("\nWrong choice\n\n");
		}

	} while (c != 1);

	return;
}