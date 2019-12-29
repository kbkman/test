#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_arr(int* arr, size_t len)
{
	char buf[128] = { 0 };
	for (size_t i = 0; i < len; i++)
	{
		char tmp[16] = { 0 };
		sprintf(tmp, "%d", arr[i]);
		strcat(buf, tmp);
		strcat(buf, " ");
	}
	printf("%s\n", buf);
}

static void _quick_start_partition(int* arr, size_t start, size_t end)
{
	int pivot_val = arr[end];
	size_t s = start;
	size_t e = end;

	while (s < e)
	{
		while (s < e && arr[s] <= pivot_val)
			s++;
		arr[e] = arr[s];

		while (s < e && arr[e] >= pivot_val)
			e--;
		arr[s] = arr[e];
	}
	arr[s] = pivot_val;
	print_arr(arr + start, end - start + 1);

	if (start + 1 < s)
		_quick_start_partition(arr, start, s - 1);

	if (end > s + 1)
		_quick_start_partition(arr, s + 1, end);
}

static void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

static void _quick_start_partition2(int* arr, size_t start, size_t end)
{
	int pivot_val = arr[end];
	size_t pivot = end;
	size_t s = start;

	for (size_t i = start; i < end; i++)
	{
		if (arr[i] < pivot_val)
		{
			swap(arr + i, arr + s);
			s++;
		}
	}

	swap(arr + s, arr + pivot);
	print_arr(arr + start, end - start + 1);

	if (start + 1 < s)
		_quick_start_partition2(arr, start, s - 1);

	if (end > s + 1)
		_quick_start_partition2(arr, s + 1, end);
}

void quick_sort(int* arr, size_t len)
{
	_quick_start_partition(arr, 0, len - 1);
	//_quick_start_partition2(arr, 0, len - 1);
}

int main(int argc, char* argv[])
{
	//int arr[] = { 9, 10, 13, 4, 5, 1, 8, 6, 7, 30, 5, 2, 0, 11 };
	int arr[] = { 9, 10, 13, 4, 5, 1, 8, 6, 7, 30, 5, 2, 0, 11, 12, 60, 32, 99 };
	size_t arr_len = sizeof(arr) / sizeof(int);
	print_arr(arr, arr_len);

	quick_sort(arr, sizeof(arr) / sizeof(int));
	print_arr(arr, arr_len);

	return 0;
}

