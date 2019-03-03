#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "argc is less then 3");
		return 1;
	}

	struct servent* s = getservbyport(htons((unsigned short)atoi(argv[1])), argv[2]);
	if (s)
	{
		printf("servent\n");
		printf("s_name %s\n", s->s_name);
		for (char** p = s->s_aliases; *p != NULL; p++)
			printf("s_aliase %s\n", *p);

		printf("s_port %u\n", ntohs(s->s_port));


	}
	else
	{
		fprintf(stderr, "getservbyname error %s", hstrerror(h_errno));	
	}

	return 0;
}

