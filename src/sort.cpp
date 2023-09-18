#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "sort.h"
#include "file_reading.h"

size_t partition(void *arr, size_t size, size_t left, size_t right,
				 int (*comp)(const void *, size_t, size_t));
void swap(void *arr, size_t left, size_t right, size_t size);

int compare_str(const void *data, size_t first, size_t second)
{
	const struct Line *lines = (const struct Line *) data;

	size_t i = 0;
	for (; lines[first].txt[i] != '\0' && lines[second].txt[i] != '\0'; i++) {
		if (lines[first].txt[i] != lines[second].txt[i])
			break;
	}
	
	return lines[first].txt[i] - lines[second].txt[i];
}

int compare_str_reverse(const void *data, size_t first, size_t second)
{
	const struct Line *lines = (const struct Line *) data;

	size_t i = lines[first].len - 1;
	size_t j = lines[second].len - 1;

	for (; i > 0 && j > 0; i--, j--)
		if (lines[first].txt[i] != lines[second].txt[j])
			return lines[first].txt[i] - lines[second].txt[j];

	return (int)(i - j);
}

int compare_int(const void *data, size_t first, size_t second)
{
	const int *arr = (const int *) data;
	if (arr[first] < arr[second]) return -1;
	if (arr[first] > arr[second]) return 1;
	return 0;
}

size_t partition(void *arr, size_t size, size_t left, size_t right, 
				 int (*comp)(const void *, size_t, size_t))
{
	size_t pivot = (left + --right) / 2;

	while (left < right) {
		int left_to_pivot = (*comp)(arr, left, pivot);
		int right_to_pivot = (*comp)(arr, right, pivot);
		
		if (left_to_pivot >= 0 && right_to_pivot <= 0) {
			if ((*comp)(arr, left, right) == 0) {
				right--;
			}
			else {
				if (pivot == left)
					pivot = right;
				else if (pivot == right)
					pivot = left;
				swap(arr, left, right, size);
			}
		}
		if (left_to_pivot < 0)
			left++;
		if (right_to_pivot > 0)
			right--;
	}

	return left;
}

void qsort(void *arr, size_t size, size_t left, size_t right,
		   int (*comp)(const void *, size_t, size_t))
{
	if (right - left <= 1)
		return;
	size_t mid = partition(arr, size, left, right, comp);

	qsort(arr, size, left, mid, comp);
	qsort(arr, size, mid + 1, right, comp);
}

void swap(void *arr, size_t left, size_t right, size_t size)
{
	char *p = (char*) arr + left * size;
	char *q = (char*) arr + right * size;
	char tmp = '\0';

	for (size_t i = 0; i < size; i++) {
		tmp = p[i];
		p[i] = q[i];
		q[i] = tmp;
	}
}
