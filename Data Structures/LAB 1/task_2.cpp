#include <iostream>
using namespace std;

void merge(int *arr, int low, int high, int mid)
{
	int *tempArr = new int[high - low + 1];
	int tempCtr = 0;

	int leftCtr = low;
	int rightCtr = mid + 1;

	while (leftCtr <= mid || rightCtr <= high)
	{
		if (rightCtr > high)
		{
			tempArr[tempCtr++] = arr[leftCtr++];
			continue;
		}

		if (leftCtr > mid)
		{
			tempArr[tempCtr++] = arr[rightCtr++];
			continue;
		}

		if (arr[leftCtr] < arr[rightCtr])
		{
			tempArr[tempCtr++] = arr[leftCtr++];
		}
		else if (arr[rightCtr] < arr[leftCtr])
		{
			tempArr[tempCtr++] = arr[rightCtr++];
		}
		else
		{
			tempArr[tempCtr++] = arr[rightCtr++];
			tempArr[tempCtr++] = arr[leftCtr++];
		}
	}

	for (int i = low; i <= high; ++i)
	{
		arr[i] = tempArr[i - low];
	}

	delete[] tempArr;
}

void mergeSort(int *arr, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid + 1, high);

		merge(arr, low, high, mid);
	}

	return;
}

void twoSum(int *arr, int size, int target)
{
	mergeSort(arr, 0, size - 1);

	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		if (arr[left] + arr[right] > target)
		{
			right--;
		}
		else if (arr[left] + arr[right] < target)
		{
			left++;
		}
		else
		{
			cout << "Pair found twin: [" << arr[left] << ", " << arr[right] << "]\n";
			return;
		}
	}
	cout << "No pair found twin\n";
	return;
}

int main()
{
	int arr[] = {38, 27, 43, 3, 9, 82, 10};
	int size = sizeof(arr) / sizeof(arr[0]);

	twoSum(arr, size, 30);

	return 0;
}