#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		perror("socket:");
		return 1;
	}


	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10080);
	//addr.sin_addr.s_addr = inet_addr("10.168.3.214");
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("bind:");
		return 1;
	}

	socklen_t len = sizeof(addr);
	if (getsockname(sock, (struct sockaddr*)&addr, &len) == -1)
	{
		perror("getsockname:");
		close(sock);
		return 1;
	}
	printf("getsockname sin_port=%d, sin_addr=%s\n", ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(20080);
	addr.sin_addr.s_addr = inet_addr("222.32.1.2");
	if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("connect:");
		return 1;
	}

	if (getpeername(sock, (struct sockaddr*)&addr, &len) == -1)
	{
		perror("getpeername:");
		close(sock);
		return 1;
	}
	printf("getpeername sin_port=%d, sin_addr=%s\n", ntohs(addr.sin_port), inet_ntoa(addr.sin_addr));

	close(sock);
	return 0;
}

