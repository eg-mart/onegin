#ifndef SORT
#define SORT

void my_qsort(void *arr, size_t count, size_t size,
		   int (*comp)(const void*, const void*));
int compare_str(const void *first, const void *second);
int compare_str_reverse(const void *first, const void *second);
int compare_int(const void *data, size_t a, size_t b);

#endif
