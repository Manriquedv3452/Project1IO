#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		
		if (!strcmp(argv[1], "-X"))
		{
			printf("ARGUMENT GETED\n");
		}
		else if (strstr(argv[1], "-E") != NULL)
		{
			printf("ARGUMENT 2 GETED\n");
		}
	}
	

	else
	{
		printf("ARGUMENT NOT FOUND OR IS NOT VALID!\n\nTO RUN: './program -X' or './program -E=n'\n\n");
		return 0;
	}

	return 0;
}
