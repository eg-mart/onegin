#include <stdio.h>

#include "file_reading.h"
#include "sort.cpp"

int compare_str(const char *str1, const char *str2);

int compare_str(const char *str1, const char *str2)
{
	while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int main()
{
	const char *filename = "onegin.txt";

	struct Text text = {};
	read_text(&text, filename);
	printf("1: %s\n2: %s\n3: %s\n\n", text.lines[0], text.lines[1], text.lines[2]);
	destroy_text(&text);

	const int SIZE = 8;
	int arr[] = {-10, 10, 10, 0, 7, 6, 6, 0};
	qsort(arr, 0, SIZE);

	for (size_t i = 0; i < SIZE; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
