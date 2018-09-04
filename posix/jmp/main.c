#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

jmp_buf jb;

void foo(void)
{
	printf("run foo\n");
	longjmp(jb, 0);
	printf("run foo end\n");
}

void do_somthing(void)
{
	printf("run do_somthing\n");
	foo();
	printf("run do_somthing end\n");
}

int main(int argc, char* argv[])
{
	int i = setjmp(jb);
	printf("i=%d\n", i);
	if (i)
	{
		perror("setjmp");
		return 1;
	}

	do_somthing();
	printf("end\n");
	return 0;
}

