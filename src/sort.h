void qsort(void *arr, size_t size, size_t left, size_t right,
		   int (*comp)(const void *, size_t, size_t));
int compare_str(const void *str, size_t a, size_t b);
int compare_str_reverse(const void *data, size_t a, size_t b);
int compare_int(const void *data, size_t a, size_t b);
