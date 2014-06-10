CFLAGS += -fPIC -Wall -Wextra -O2 -s

NAME=example

LIB = lib$(NAME).so

LDFLAGS += -ldl -shared

all: $(LIB)

$(LIB): $(NAME).c libpreload.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

test: test.c
	$(CC) $^ -o $@

check: test $(LIB)
	LD_PRELOAD=./$(LIB) ./$<

clean:
	-rm -f *.so test
