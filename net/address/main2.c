#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "argc is less then 2");
		return 1;
	}

	in_addr_t addr = inet_ntoa(argv[1]);
	struct hostent* h = gethostbyaddr(&addr, sizeof(addr), AF_INET);
	if (h)
	{
		printf("hostent\n");
		printf("h_name %s\n", h->h_name);
		for (const char** p = h->h_aliases; *p != NULL; p++)
			printf("h_aliase %s\n", *p);

		printf("h_addrtype %s\n", h->h_addrtype == AF_INET ? "AF_INET" : "not AF_INET");

		for (const char** p = h->h_addr_list; *p != NULL; p++)
		{
			char ip[32] = { 0 };
			inet_ntop(h->h_addrtype, *p, ip, sizeof(ip));
			printf("h_addr %s\n", ip);
		}

	}
	else
	{
		fprintf(stderr, "gethostbyaddr error %s", hstrerror(h_errno));	
	}

	return 0;
}

