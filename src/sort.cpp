#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "sort.h"
#include "file_reading.h"

size_t partition(void *arr, size_t count, size_t size, 
				 int (*comp)(const void*, const void*));
void swap(void *first, void *second, size_t size);

int compare_str(const void *first, const void *second)
{
	const struct Line *first_line = (const struct Line*) first;
	const struct Line *second_line = (const struct Line*) second;

	size_t i = 0;
	for (; first_line->txt[i] != '\0' && second_line->txt[i] != '\0'; i++) {
		if (first_line->txt[i] != second_line->txt[i])
			return first_line->txt[i] - second_line->txt[i];
	}
	
	return (int) (first_line->len - second_line->len);
}

int compare_str_reverse(const void *first, const void *second)
{
	const struct Line *first_line = (const struct Line*) first;
	const struct Line *second_line = (const struct Line*) second;

	size_t i = first_line->len - 1;
	size_t j = second_line->len - 1;

	for (; i > 0 && j > 0; i--, j--)
		if (first_line->txt[i] != second_line->txt[j])
			return first_line->txt[i] - second_line->txt[j];

	return (int) (first_line->len - second_line->len);
}

int compare_int(const void *data, size_t first, size_t second)
{
	const int *arr = (const int *) data;
	if (arr[first] < arr[second]) return -1;
	if (arr[first] > arr[second]) return 1;
	return 0;
}

size_t partition(void *arr, size_t count, size_t size, 
				 int (*comp)(const void*, const void*))
{
	size_t pivot = (count - 1) / 2;
	size_t left = 0;
	size_t right = count - 1;

	while (left < right) {
		int left_to_pivot = (*comp)((char*) arr + left * size, 
									(char*) arr + pivot * size);
		int right_to_pivot = (*comp)((char *) arr + right *size,
									 (char*) arr + pivot * size);
		
		if (left_to_pivot >= 0 && right_to_pivot <= 0) {
			if ((*comp)((char*) arr + left * size, (char*) arr + right * size) == 0) {
				right--;
			}
			else {
				if (pivot == left)
					pivot = right;
				else if (pivot == right)
					pivot = left;
				swap((char*) arr + left * size, (char*) arr + right * size, size);
			}
		}
		if (left_to_pivot < 0)
			left++;
		if (right_to_pivot > 0)
			right--;
	}

	return left;
}

void my_qsort(void *arr, size_t count, size_t size,
		   int (*comp)(const void*, const void *))
{
	if (count <= 1)
		return;
	size_t mid = partition(arr, count, size, comp);

	my_qsort(arr, mid, size, comp);
	my_qsort((char *) arr + (mid + 1) * size, count - mid - 1, size, comp);
}

void swap(void *first, void *second, size_t size)
{
	char *first_bytes = (char*) first;
	char *second_bytes = (char*) second;
	char tmp = '\0';
	for (size_t i = 0; i < size; i++) {
		tmp = first_bytes[i];
		first_bytes[i] = second_bytes[i];
		second_bytes[i] = tmp;
	}
}
