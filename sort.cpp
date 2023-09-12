size_t partition(int *arr, size_t left, size_t right);
void qsort(int *arr, size_t left, size_t right);
void swap(int *arr, size_t left, size_t right);

size_t partition(int *arr, size_t left, size_t right)
{
	int pivot = arr[(left + --right) / 2];

	while (left < right) {
		if (arr[left] >= pivot && arr[right] <= pivot)
			swap(arr, left, right);
		if (arr[left] < pivot)
			left++;
		if (arr[right] > pivot)
			right--;
	}

	return left;
}

void qsort(int *arr, size_t left, size_t right)
{
	if (right - left <= 1)
		return;
	size_t mid = partition(arr, left, right);

	qsort(arr, left, mid);
	qsort(arr, mid + 1, right);
}

void swap(int *arr, size_t left, size_t right)
{
	int tmp = arr[left];
	arr[left] = arr[right];
	arr[right] = tmp;
}
