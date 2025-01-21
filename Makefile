TARGET=chip

VPATH=src/
SRCS=$(shell find . -name *.c)
OBJS=$(subst src,obj,$(subst .c,.o,$(SRCS)))

INCLUDES=includes
FLAGS=-Wall -Wextra -Werror -lncursesw -I $(INCLUDES)
CC=gcc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(FLAGS)

$(OBJS): obj/%.o: %.c build
	$(CC) -c $< -o $@ $(FLAGS)

build:
	mkdir -p obj/ipv4
	mkdir -p obj/tui
	mkdir -p obj/utils

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f obj/*.o

re: fclean all
