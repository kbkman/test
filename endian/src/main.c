#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	unsigned int i = ':npv';
	char* p = (char*)&i;
	printf("i=%u p=%c%c%c%c\n", i, p[0], p[1], p[2], p[3]);
	

	return 0;
}

