#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <string.h>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

bool _parse(const char* src, char* ip, unsigned short* port)
{
	const char* p = strchr(src, ':');
	if (p)
	{
		strncpy(ip, src, p - src);
		*port = (unsigned short)atoi(++p);
		return true;
	}
	return NULL;
}

bool _hold(std::vector<std::pair<std::string, unsigned short> >& dst)
{
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (!s)
	{
		perror("socket");
		return false;
	}

	char buf[] =  "abcefghijklmnoptrstuvwxyz";
	for (std::vector<std::pair<std::string, unsigned short> >::const_iterator it = dst.begin(); it != dst.end(); ++it)
	{
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(struct sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(it->first.c_str());
		addr.sin_port = htons(it->second);
		if (sendto(s, buf, sizeof(buf), 0, (const struct sockaddr*)&addr, sizeof(addr)) == -1)
		{
			perror("sendto");
			close(s);
			return false;
		}
	}
	close(s);
	return true;
}

int main(int argc, char* argv[])
{
	std::vector<std::pair<std::string, unsigned short> > dst;
	const char* shot_opts = "da:";
	static option long_opts[] =
	{
		{ "address", required_argument, NULL, 'a' },
		{ "help", required_argument, NULL, 'h' },
		{ NULL, 0, NULL, '\0' },
	};
	int opt;
	while ((opt = getopt_long(argc, argv, shot_opts, long_opts, NULL)) > 0)
	{
		switch (opt)
		{
			case 'a':
			{
				char ip[32] = { 0 };
				unsigned short port;
				if (_parse(optarg, ip, &port))
					dst.push_back(std::make_pair(std::string(ip), port));
				else
					fprintf(stderr, "error address : %s", optarg);
			}
			break;

			case 'h':
			default:
				printf("%s -a <address1> -a <address2>\n", argv[0]);
				return 1;
		}

	}

	_hold(dst);
	return 0;
}

