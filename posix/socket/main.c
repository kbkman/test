#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
	in_addr_t addr = inet_addr("192.168.10.1");
	printf("inet_addr=%u\n", addr);

	struct in_addr ina;
	ina.s_addr = addr;
	printf("inet_ntoa=%s\n", inet_ntoa(ina));

	char addr_string[INET_ADDRSTRLEN + 1] = { 0 };
	printf("inet_ntop=%s\n", inet_ntop(AF_INET, &ina, addr_string, sizeof(addr_string)));

	inet_pton(AF_INET, "192.168.10.1", &ina);
	printf("inet_pton=%u\n", ina.s_addr);


	while (1)
	{
		struct hostent* hent = gethostent();
		if (hent)
		{
			printf("gethostent: h_name=%s\n", hent->h_name);
		}
		else
		{
			break;
		}
	}

	while (1)
	{
		struct netent* nent = getnetent();
		if (nent)
		{
			printf("getnetent: n_name=%s\n", nent->n_name);
		}
		else
		{
			break;
		}
	}


	while (1)
	{
		struct protoent* pent = getprotoent();
		if (pent)
		{
			printf("getprotoent: p_name=%s\n", pent->p_name);
		}
		else
		{
			break;
		}
	}

	while (1)
	{
		struct servent* sent = getservent();
		if (sent)
		{
			printf("getservent: s_name=%s, s_proto=%s, s_port=%d\n", sent->s_name, sent->s_proto, ntohs(sent->s_port));
		}
		else
		{
			break;
		}
	}

	return 0;
}

