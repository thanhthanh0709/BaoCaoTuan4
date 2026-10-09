#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace std::chrono;


int partition(vector<int>& arr, int left, int right) {
    int randomIndex = left + rand() % (right - left + 1);
    swap(arr[randomIndex], arr[right]);

    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int left, int right) {
    while (left < right) {
        int partitionIndex = partition(arr, left, right);

        if (partitionIndex - left < right - partitionIndex) {
            quickSortHelper(arr, left, partitionIndex - 1);
            left = partitionIndex + 1;
        } else {
            quickSortHelper(arr, partitionIndex + 1, right);
            right = partitionIndex - 1;
        }
    }
}

void quickSort(vector<int>& arr) {
    if (!arr.empty()) quickSortHelper(arr, 0, (int)arr.size() - 1);
}

void merge(vector<int>& arr, int left, int mid, int right, vector<int>& temp) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int p = left; p <= right; p++) arr[p] = temp[p];
}

void mergeSortHelper(vector<int>& arr, int left, int right, vector<int>& temp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, temp);
        mergeSortHelper(arr, mid + 1, right, temp);
        merge(arr, left, mid, right, temp);
    }
}

void mergeSort(vector<int>& arr) {
    if (arr.size() <= 1) return;
    vector<int> temp(arr.size());
    mergeSortHelper(arr, 0, (int)arr.size() - 1, temp);
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}


void cppStdSort(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}


template <typename Func>
double doThoiGian(Func sortFunc, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

int main() {
    const int N = 1000000;

    cout << left << setw(6)  << "Lan"
         << setw(26) << "Dac tinh du lieu"
         << setw(16) << "std::sort"
         << setw(16) << "QuickSort"
         << setw(16) << "MergeSort"
         << setw(16) << "HeapSort" << endl;
    cout << string(90, '-') << endl;

    for (int lan = 1; lan <= 10; lan++) {
        vector<int> goc(N);
        string moTa = "";

        if (lan == 1) {
            moTa = "Tang dan (Sorted)";
            for (int i = 0; i < N; i++) goc[i] = i;
        } else if (lan == 2) {
            moTa = "Giam dan (Reversed)";
            for (int i = 0; i < N; i++) goc[i] = N - i;
        } else {
            moTa = "Ngau nhien (Seed " + to_string(lan - 2) + ")";
            mt19937 rng((lan - 2) * 2024 + 13);
            uniform_int_distribution<int> dist(1, 1000000000);
            for (int i = 0; i < N; i++) goc[i] = dist(rng);
        }

        double tStd   = doThoiGian(cppStdSort, goc);
        double tQuick = doThoiGian(quickSort, goc);
        double tMerge = doThoiGian(mergeSort, goc);
        double tHeap  = doThoiGian(heapSort, goc);

        cout << left << setw(6)  << lan
             << setw(26) << moTa
             << fixed << setprecision(2)
             << setw(16) << tStd
             << setw(16) << tQuick
             << setw(16) << tMerge
             << setw(16) << tHeap << endl;
    }

    return 0;
}
