COMMON_SRCS=list.c debug.c
SRCS=quidditch_test.c list.c debug.c checkin.c
EXECUTABLES=quidditch_test

CC=gcc
CFLAGS=-g3 -Wall -std=gnu99 -pthread

COMMON_OBJS=$(COMMON_SRCS:.c=.o)
OBJS=$(SRCS:.c=.o)

all: quidditch_test

quidditch_test: $(COMMON_OBJS) quidditch_test.o checkin.o
	$(CC) $(CFLAGS) $(COMMON_OBJS) quidditch_test.o checkin.o -o $@

#$(EXECUTABLES): $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) $@.o -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(EXECUTABLES)
