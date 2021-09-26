#include <iostream>

using namespace std;

int n;

void print(int* a);
int control();
void swap(int& a, int& b);
void bubbleSort(int* arr);
void insertionSort(int* arr);
void selectionSort(int* arr);
void mergeSort(int arr[], int const begin, int const end);
void quickSort(int arr[], int low, int high);

int main()
{ 
	srand(time(NULL)); 
	
	n = control(); 
	int* a = new int[n]; 
	for (int i = 0; i < n; i++) 
		a[i] = rand() % 2001 - 1000;

	cout << "Array before sorting:\n";
	print(a);

	// bubbleSort(a);
	// insertionSort(a);
	// selectionSort(a);
	// mergeSort(a, 0, n - 1);
	quickSort(a, 0, n - 1);

	cout << "Array after sorting:\n";
	print(a); 

	delete[] a; 

	return 0;
}

void print(int* a) 
{
	for (int i = 0; i < n; i++) 
		cout << a[i] << '\t';
	cout << endl;
}

int control()
{
	cout << "Enter size of the array: ";

	while (!(cin >> n) || n == 0)
	{
		cin.clear(); 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Incorrect input! Try again: ";
	}

	return n; 
}

void swap(int& a, int& b) 
{
	int tmp = a; 
	a = b; 
	b = tmp; 
}

////////// BUBBLE SORT //////////
void bubbleSort(int* arr) 
{
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++) 
			if (arr[j] > arr[j + 1]) 
				swap(arr[j], arr[j + 1]); 
}

////////// INSERTION SORT //////////
void insertionSort(int* arr)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

////////// SELECTION SORT //////////
void selectionSort(int* arr)
{
	int i, j, min_idx;

	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		swap(arr[min_idx], arr[i]);
	}
}

////////// MERGE SORT //////////
void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, 
		indexOfSubArrayTwo = 0; 
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
		{
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else
		{
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne)
	{
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo)
	{
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

void mergeSort(int arr[], int const begin, int const end)
{
	if (begin >= end)
		return; 

	auto mid = begin + (end - begin) / 2;
	mergeSort(arr, begin, mid);
	mergeSort(arr, mid + 1, end);
	merge(arr, begin, mid, end);
}

////////// QUICK SORT //////////
int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}