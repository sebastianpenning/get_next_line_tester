CC = cc

CFLAGS = -Wall -Werror -Wextra

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=logs/valgrind-out.txt 

TEST_1 = output/test1.out

.SILENT:

all: 
	mkdir output
	$(CC) $(CFLAGS) gnl_tester.c ../get_next_line.c ../get_next_line_utils.c -D BUFFER_SIZE=42 -o $(TEST_1) 
	-$(VALGRIND) ./$(TEST_1)

clean_logs:
	-rm -f logs/*.txt

clean_output:
	-rm -f output/*.out

clean: clean_logs clean_output

re: clean all
