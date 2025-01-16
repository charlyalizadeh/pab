TARGET=chip
SRCS=src/main.c src/ipv4.c src/source_route.c src/security.c src/option.c
OBJS=$(subst src,obj,$(subst .c,.o,$(SRCS)))
INCLUDES=includes
FLAGS=-Wall -Wextra -Werror -I $(INCLUDES)
CC=gcc

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(FLAGS)

$(OBJS): obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(FLAGS)

build:
	mkdir -p obj

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f obj/*.o

re: fclean all
