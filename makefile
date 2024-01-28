CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.

OUTPUT_DIR = dist
SRCS = $(wildcard ./*.c) $(wildcard ./**/*.c) $(wildcard ./**/**/*.c)
OBJS = $(OUTPUT_DIR)/libs.o

TARGET = $(OUTPUT_DIR)/task-manager-app

ifeq ($(OS),Windows_NT)
	# Windows commands
	RM = del /Q
	MKDIR = mkdir
	FIXPATH = $(subst /,\,$1)
	TARGET = $(OUTPUT_DIR)/task-manager-app.exe
else
	# macOS and Linux commands
	RM = rm -rf
	MKDIR = mkdir -p
	FIXPATH = $1
endif

.PHONY: all clean

all: $(OUTPUT_DIR) $(TARGET)

$(OUTPUT_DIR):
	$(MKDIR) $(call FIXPATH, $(OUTPUT_DIR))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $^
	ld -r -o $@ *.o
	$(RM) *.o

clean:
	$(RM) $(call FIXPATH, $(OUTPUT_DIR))
