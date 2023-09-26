#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "sort.h"
#include "file_reading.h"

#define abs(x) ((x) < 0 ? -(x) : (x))

size_t partition(void *arr, size_t count, size_t size, 
				 int (*comp)(const void*, const void*));
void fast_swap(void *f, void *s, size_t size);
bool is_russian_letter(char c);

bool is_russian_letter(char c)
{
	unsigned char d = (unsigned char) c;
	return 0300 <= d;
}

int compare_str(const void *first, const void *second)
{
	const struct Line *first_line = (const struct Line*) first;
	const struct Line *second_line = (const struct Line*) second;

	size_t i = 0;
	size_t j = 0;
	for (; first_line->txt[i] != '\0' && second_line->txt[j] != '\0'; i++, j++) {
		while (first_line->txt[i] != '\0' && !is_russian_letter(first_line->txt[i]))
			i++;

		while (second_line->txt[j] != '\0' && !is_russian_letter(second_line->txt[j]))
			j++;

		if (first_line->txt[i] == '\0' || second_line->txt[j] == '\0')
			break;

		if (tolower(first_line->txt[i]) != tolower(second_line->txt[j]))
			return tolower(first_line->txt[i]) -tolower( second_line->txt[j]);
	}
	
	return (int) (first_line->len - second_line->len);
}

int compare_str_reverse(const void *first, const void *second)
{
	const struct Line *first_line = (const struct Line*) first;
	const struct Line *second_line = (const struct Line*) second;

	size_t i = first_line->len - 1;
	size_t j = second_line->len - 1;

	for (; i > 0 && j > 0; i--, j--) {
		while (i > 0 && !is_russian_letter(first_line->txt[i]))
			i--;

		while (i > 0 && !is_russian_letter(second_line->txt[j]))
			j--;

		if (i <= 0 || j <= 0)
			break;

		if (tolower(first_line->txt[i]) != tolower(second_line->txt[j]))
			return tolower(first_line->txt[i]) - tolower(second_line->txt[j]);
	}

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
				fast_swap((char*) arr + left * size, (char*) arr + right * size, size);
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

void fast_swap(void *first, void *second, size_t size)
{
	char *f = (char*) first;
	char *s = (char*) second;
	char max_aligned = 'b';
	size_t alignment = sizeof(char);
	if (((size_t) f - (size_t) s) % sizeof(short) == 0) {
		max_aligned = 's';
		alignment = sizeof(short);
	}
	if (((size_t) f - (size_t) s) % sizeof(int) == 0) {
		max_aligned = 'i';
		alignment = sizeof(int);
	}
	if (((size_t) f - (size_t) s) % sizeof(long) == 0) {
		max_aligned = 'l';
		alignment = sizeof(long);
	}

	char tmpb = '\0';
	short tmps = 0;
	int tmpi = 0;
	long tmpl = 0;
	while (size > 0 && ((size_t) f) % alignment != 0) {
		tmpb = *f;
		*f = *s;
		*s = tmpb;
		f += sizeof(char);
		s += sizeof(char);
		size -= sizeof(char);
	}

	switch (max_aligned) {
		case 'l':
			while (size >= sizeof(long)) {
				tmpl = *((long*) f);
				*((long*) f) = *((long*) s);
				*((long*) s) = tmpl;
				size -= sizeof(long);
				f += sizeof(long);
				s += sizeof(long);
			}
		case 'i':
			while (size >= sizeof(int)) {
				tmpi = *((int*) f);
				*((int*) f) = *((int*) s);
				*((int*) s) = tmpi;
				size -= sizeof(int);
				f += sizeof(int);
				s += sizeof(int);
			}
		case 's':
			while (size >= sizeof(short)) {
				tmps = *((short*) f);
				*((short*) f) = *((short*) s);
				*((short*) s) = tmps;
				size -= sizeof(short);
				f += sizeof(short);
				s += sizeof(short);
			}
		case 'b':
			while (size >= sizeof(char)) {
				tmpb = *((char*) f);
				*((char*) f) = *((char*) s);
				*((char*) s) = tmpb;
				size -= sizeof(char);
				f += sizeof(char);
				s += sizeof(long);
			}
	}
}
