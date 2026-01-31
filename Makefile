CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

SRC = \
	src/main.c \
	src/app.c \
	src/terminal/terminal.c \
	src/terminal/signals.c \
	src/render/colors.c \
	src/render/renderer.c \
	src/io/temp_file.c \
	src/text/line_split.c \
	src/text/text_process.c \
	src/typing/typing.c \
	src/stats/stats.c \
	src/utils/time_utils.c \
	src/utils/platform.c

OUT = typing

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

.PHONY: all clean
