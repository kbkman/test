#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	//Write File
	FILE* f = fopen("test_file", "w+");
	if (f)
	{
		if (setvbuf(f, NULL, _IONBF, 0))
		{
			fprintf(stderr, "setvbuf failed\n");
			return 1;
		}

		char data[] = "abcdefg\nccdd";
		int ret = fputs(data, f);
		printf("ret = %d\n", ret);

		ret = fputs("cbd", f);
		printf("ret = %d\n", ret);

		//sleep(5);
		fflush(f);
		fclose(f);
		
	}
	else
	{
		fprintf(stderr, "open file failed\n");
	}

	//Read File
	f = fopen("test_file", "r");
	if (f)
	{
		if (setvbuf(stdout, NULL, _IONBF, 0))
		{
			fprintf(stderr, "setvbuf stdout failed\n");
			return 1;
		}
		
		char data[256] = { 0 };
		while (1)
		{
			if (fgets(data, sizeof(data), f) == NULL)
			{
				fprintf(stderr, "fget return NULL\n");
				return 1;
			}
			printf("read %s", data);
			//fflush(stdout_f);
			/*
			int c;
			if ((c = fgetc(f)) == EOF)
			{
				fprintf(stderr, "fgetc return EOF\n");
				return 1;
			}
			printf("%c", (char)c);
			*/
		}

	}
	else
	{
		fprintf(stderr, "read stdin failed\n");
	}

	return 0;
}

