#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_reading.h"
#include "sort.h"

int main(int argc, const char *argv[])
{
	if (argc < 3) {
		fputs("Error: wrong arguments\n", stderr);
		return 1;
	}

	const char *filename = argv[2];

	struct Text text = {};
	if (read_text(&text, filename) < 0)
		return (fputs("Error: unable to read file\n", stderr), 1);

	if (strcmp(argv[1], "-f") == 0)
		my_qsort(text.lines, text.num_lines, sizeof(Line), compare_str);
	else if (strcmp(argv[1], "-b") == 0)
		qsort(text.lines, text.num_lines, sizeof(Line), compare_str_reverse);
	else if (strcmp(argv[1], "-n") != 0)
		return (fputs("Error: wrong arguments\n", stderr), 1);

	for (size_t i = 0; i < text.num_lines; i++)
		printf("%s\n", text.lines[i].txt);
	destroy_text(&text);
}
