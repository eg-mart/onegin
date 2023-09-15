#include <stdio.h>
#include <string.h>

#include "file_reading.h"
#include "sort.h"

int main(int argc, char *argv[])
{
	const char *filename = "onegin.txt";

	struct Text text = {};
	if (read_text(&text, filename) < 0)
		return (fputs("Error: unable to read file\n", stderr), 1);

	if (argc < 2 || strcmp(argv[1], "-f") == 0)
		qsort(text.lines, sizeof(Line),  0, text.num_lines, compare_str);
	else if (strcmp(argv[1], "-b") == 0)
		qsort(text.lines, sizeof(Line), 0, text.num_lines, compare_str_reverse);
	else
		return (fputs("Error: wrong arguments\n", stderr), 1);

	for (size_t i = 0; i < text.num_lines; i++)
		printf("%s\n", text.lines[i].txt);
	destroy_text(&text);
}
