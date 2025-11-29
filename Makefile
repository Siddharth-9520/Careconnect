CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g
LIBS=
TARGET=careconnect

SRCS=main.c input_module.c queue_module.c heap_module.c graph_module.c
OBJS=$(SRCS:.c=.o)
HEADERS=input_module.h queue_module.h heap_module.h graph_module.h

all: $(TARGET)

$(TARGET): $(OBJS)
\t$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
\t@echo "✅ CareConnect COMPILED SUCCESSFULLY!"

%.o: %.c $(HEADERS)
\t$(CC) $(CFLAGS) -c $< -o $@

clean:
\trm -f $(OBJS) $(TARGET)
\t@echo "🧹 Cleaned!"

run: $(TARGET)
\t./$(TARGET)

.PHONY: all clean run