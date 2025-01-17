TARGET=chip

VPATH=src/ src/ipv4
SRCS=$(shell find . -name *.c)
OBJS=$(subst src,obj,$(subst .c,.o,$(SRCS)))

INCLUDES=includes
FLAGS=-Wall -Wextra -Werror -I $(INCLUDES)
CC=gcc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(FLAGS)

$(OBJS): obj/%.o: %.c
	$(CC) -c $< -o $@ $(FLAGS)

build:
	mkdir -p obj/ipv4

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f obj/*.o

re: fclean all
