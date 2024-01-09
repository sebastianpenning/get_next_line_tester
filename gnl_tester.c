#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h" 

static size_t	test_strlen(const char *s)
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

static int	test_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;
	size_t	s1_len;
	size_t	s2_len;
	int		returnval;

	index = 0;
	returnval = 0;
	s1_len = test_strlen(s1);
	s2_len = test_strlen(s2);
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
	int		fd;
	char 	*gnl;
	int		error_index;
	FILE 	*errorLog;

	error_index = 0; 
	rtr = 0;
	fd = open(path, O_RDONLY);
	gnl = get_next_line(fd);
	rtr += test_strncmp(str, gnl, test_strlen(str));
	if (rtr != 0)
	{
		errorLog = fopen("logs/error_log.txt", "a");

		if (errorLog == NULL)
    	{
			free(gnl);
        	printf("Error opening the file");
        	return 1;
    	}
		printf("Test %d\n", testnbr);
		printf("FAIL\n");
		printf("Line number: %d\n", linenbr);
		printf("Check error_log.txt\n");
		fprintf(errorLog, "----------------\n");
		fprintf(errorLog, "Test number %d\n", testnbr);
		fprintf(errorLog, "Line %d\n", linenbr);
		while (str[error_index] != '\0')
			fprintf(errorLog, "expected output: %d\n", str[error_index++]);
		error_index = 0;
		fprintf(errorLog, "expected output: %s\n", str);
		while (gnl[error_index]!= '\0')
			fprintf(errorLog, "gnl output: %d\n", gnl[error_index++]);
		fprintf(errorLog, "gnl output: %s\n", gnl);
		fprintf(errorLog, "strncmp difference: %d\n", rtr);
		fclose(errorLog);
		free(gnl);
		return(0);
	}
	printf("Test %d OK\n", testnbr);
	free(gnl);
	return(0);
}

int main (void)
{
	int testnbr;
	int linenbr;

	testnbr = 0;
	linenbr = 0;
	fclose(fopen("logs/error_log.txt", "w"));
	printf("------------------\n");
	printf("|     tests x    |\n");
	printf("------------------\n");
	testnbr++;
	linenbr++;
	if(tester("test_files/test.txt", "lololol\n", testnbr, linenbr) == 1)
		return(0);
	return(1);
}
