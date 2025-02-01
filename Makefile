TARGET=bin/pab

VPATH=src/
SRCS=$(shell find . -name *.c)
OBJS=$(subst src,obj,$(subst .c,.o,$(SRCS)))
INCLUDES=includes
LIBS=-lncursesw
FLAGS=-Wall -Wextra -Werror -I $(INCLUDES) $(LIBS)
DEBUG_FLAGS=$(FLAGS) -g
PROD_FLAGS=$(FLAGS)
CC=gcc


all: $(TARGET)

debug: $(OBJS_DEBUG)
	$(CC) $(SRCS) -o $(TARGET)_debug $(DEBUG_FLAGS)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(PROD_FLAGS)

$(OBJS): obj/%.o: %.c build
	$(CC) -c $< -o $@ $(PROD_FLAGS)

build:
	mkdir -p obj/ipv4
	mkdir -p obj/utils

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f obj/*.o
	rm -f obj/ipv4/*.o
	rm -f obj/utils/*.o

re: fclean all
