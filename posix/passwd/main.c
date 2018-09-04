#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <shadow.h>
#include <sys/utsname.h>
#include <time.h>

int main(int argc, char* argv[])
{
	struct passwd* pwd = getpwuid(getuid());
	if (!pwd)
	{
		perror("get pwuid error:");
		return 1;
	}

	printf("%s,%s,%u,%u,%s,%s\n",
		pwd->pw_name,
		pwd->pw_passwd,
		pwd->pw_uid,
		pwd->pw_gid,
		pwd->pw_dir,
		pwd->pw_shell
		);

	setpwent();
	while ((pwd = getpwent()) != NULL)
	{
		printf("%-10s,%s,%u,%u,%s,%s\n",
			pwd->pw_name,
			pwd->pw_passwd,
			pwd->pw_uid,
			pwd->pw_gid,
			pwd->pw_dir,
			pwd->pw_shell
			);
	}
	endpwent();
	
	struct spwd* sd;
	setspent();
	while ((sd = getspent()) != NULL)
	{
		printf("%s,%s\n",
			sd->sp_namp,
			sd->sp_pwdp
			);
	}
	endspent();

	struct utsname utsn;
	if (uname(&utsn) == -1)
	{
		perror("uname error:");
		return 1;
	}
	printf("%s,%s,%s,%s,%s\n",
		utsn.sysname,
		utsn.nodename,
		utsn.release,
		utsn.version,
		utsn.machine);
	

	char host[128];
	if (gethostname(host, sizeof(host)) == -1)
	{
		perror("gethostname error:");
		return 1;
	}
	printf("HOST_NAME_MAX=%d, hostname=%s\n", 0, host);

	char timestr[128];
	time_t tm = time(NULL);
	if (strftime(timestr, sizeof(timestr), "time is : %r, %a", localtime(&tm)) == 0)
	{
		perror("strftime error:");
		return 1;
	}
	printf("%s\n", timestr);
	return 0;
}

