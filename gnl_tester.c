#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	if (s[index] == '\0')
	{
		return (0);
	}
	else
	{
		while (s[index] != '\0')
		{
			index++;
		}
		return (index);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;
	size_t	s1_len;
	size_t	s2_len;
	int		returnval;

	index = 0;
	returnval = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	while (index < n && (index < s1_len || index < s2_len))
	{
		if ((unsigned char)s1[index] != (unsigned char)s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (returnval);
}


int tester (const char * path, char *str, int testnbr, int linenbr)
{
	int 	rtr;
	char 	*gnl;
	FILE 	*errorLog;
	char	errorBuffer[300];

	rtr = 0;
	gnl = get_next_line(path);
	rtr += ft_strncmp(str, gnl, 25);
	if (rtr != 0)
	{
		errorLog = fopen("error_log.txt", "a");

		if (errorLog == NULL)
    	{
        	printf("Error opening the file %s", errorLog);
        	return 1;
    	}
		printf("Test %d\n", testnbr);
		printf("FAIL\n");
		printf("Check error_log.txt\n");
		fputs(snprintf(errorBuffer, 300, "Line %d\n", linenbr), errorLog);
		fputs(snprintf(errorBuffer, 300, "expected output: %s"), errorLog);
		fputs(snprintf(errorBuffer, 300, "gnl output: %s"),  errorLog);
		fclose(errorLog);
	}
	else
	{
		printf("Test %d\n", testnbr);
		printf("OK\n");
		return(0);
	}
}

int main (void)
{
	int testnbr;
	int linenbr;

	testnbr = 0;
	linenbr = 0;
	printf("------------------\n");
	printf("|     tests x    |\n");
	printf("------------------\n");
	testnbr++;
	linenbr++;
	if(tester("test.txt", "lololol", testnbr, linenbr) == 1)
		return(1);
}
