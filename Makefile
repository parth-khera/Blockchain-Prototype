# Simple Blockchain Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(SRCDIR)/main.c $(SRCDIR)/blockchain.c $(SRCDIR)/sha256.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/blockchain

.PHONY: all clean directories

all: directories $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: all
	./$(TARGET)

.PHONY: test
test: all
	@echo "Running blockchain demo..."
	./$(TARGET)