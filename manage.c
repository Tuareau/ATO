#include "header.h"

// меню для редактирования базы данных
void manage(void)
{
	int c;
	do {
		printf("\n\tMANAGMENT OF DATA BASE\n\n");

		printf("List of issues:\n");
		printf("0 - Quit without saving\n");
		printf("1 - Return back\n");
		printf("2 - Add a record\n");
		printf("3 - Change information\n");
		printf("4 - Delete a record\n");
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
			exit(EXIT_SUCCESS);
		case 1:
			break;
		case 2:
			add_rec();
			break;
		case 3:
			change_rec();
			break;
		case 4:
			delete_rec();
			break;
		default:
			printf("\nWrong choice\n\n");
		}

	} while (c != 1);

	return;
}