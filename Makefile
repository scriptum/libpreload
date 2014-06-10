CFLAGS += -fPIC -Wall -Wextra -O2 -s

NAME=example

LIB = lib$(NAME).so

LDFLAGS += -ldl -shared

all: $(LIB)

$(LIB): $(NAME).c libpreload.h
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	-rm -f *.so

test:
	LD_PRELOAD=./$(LIB) 
