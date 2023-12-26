LIB_DIR := ../
LIB_ARC := get_next_line.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./a.out

SRCS = gnl_tester.c 

OBJS = $(SRCS:.c=.o)

NAME = gnl_tester.a

.SILENT:

all: exe

exe: $(NAME)
	echo BUFFER_SIZE=42
	$(CC) $(CFLAGS) gnl_tester.c gnl_tester.a -D BUFFER_SIZE=42 && ./a.out
	$(VALGRIND)
	echo BUFFER_SIZE=1000
	$(CC) $(CFLAGS) gnl_tester.c gnl_tester.a -D BUFFER_SIZE=1000 && ./a.out
	$(VALGRIND)
	echo BUFFER_SIZE=1
	$(CC) $(CFLAGS) gnl_tester.c gnl_tester.a -D BUFFER_SIZE=1 && ./a.out
	$(VALGRIND)
	rm a.out
	@$(MAKE) -s -C $(LIB_DIR) fclean

$(NAME): $(LIB_DIR)/$(LIB_ARC) $(OBJS) 
	ar rcs $(NAME) $(OBJS)

$(LIB_DIR)/$(LIB_ARC): 
	@$(MAKE) -s -C $(LIB_DIR) all
	cp $(LIB_DIR)/$(LIB_ARC) $(NAME)
	
 %.o: %.c
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	@$(MAKE) -s -C $(LIB_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -s -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all
