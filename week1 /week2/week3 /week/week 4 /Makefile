# Compiler to use
CC = clang

# Compiler flags: 
# -Wall and -Wextra enable all warnings
# -std=c11 uses the 2011 C standard
CFLAGS = -Wall -Wextra -std=c11

# Rule to build the 'filter' executable
# Depends on filter.c, helpers.c, helpers.h, and bmp.h
filter: filter.c helpers.c helpers.h bmp.h
	$(CC) $(CFLAGS) -o filter filter.c helpers.c -lm

# Rule to remove the compiled executable and any generated BMP files
clean:
	rm -f filter *.bmp
