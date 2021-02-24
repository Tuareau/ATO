#include "header.h"

int size, p_amount;

int main(void)
{
	graph = NULL;
	size = p_amount = 0;
	char fname[] = "ato.dat";
	start(fname);
	print_graph();
	end(fname);
	return 0;
}
