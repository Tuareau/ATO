#include "header.h"

// размер массива указателей на самолеты
// и количество указателей в нем
int size, p_amount;

int main(void)
{
	graph = NULL;
	size = p_amount = 0;
	char fname[] = "ato.dat";
	// чтение файла и начало работы
	start(fname);
	print_graph();
	// запись в файл и освобождение памяти
	end(fname);
	return 0;
}