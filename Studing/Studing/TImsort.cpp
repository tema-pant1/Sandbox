#include "DynArray.h"
#include "Stack.h"
#include "Timsort.h"

void timsort(DynamicArray<int>& array)
{
    SetRus();
    if (array.GetSize() <= 1) return;
    int MinRun = GetMinrun(array.GetSize());
    int current_run = 0, size_run = 0;
    stack<std::pair<int, int>> sorted_runs;
    while (current_run < array.GetSize())
    {
        size_run = GetRun(current_run, MinRun, array);
        std::pair<int, int> run = { current_run, size_run };
        sorted_runs.push(run);
        while (balance_stack(sorted_runs, array));
        current_run += size_run;
    }

    while (sorted_runs.GetSize() > 1)
    {
        std::pair<int, int> run1 = sorted_runs.top();
        sorted_runs.pop();
        std::pair<int, int> run2 = sorted_runs.top();
        sorted_runs.pop();
        merge(run2, run1, array);
        std::pair<int, int> merged_run = {
            run2.first,
            run2.second + run1.second
        };
        sorted_runs.push(merged_run);
    }
}

bool balance_stack(stack<std::pair<int, int>>& runs, DynamicArray<int>& array)
{
    if (runs.GetSize() < 3) return false;

    std::pair<int, int> Z = runs.top(); runs.pop();
    std::pair<int, int> Y = runs.top(); runs.pop();
    std::pair<int, int> X = runs.top(); runs.pop();

    bool merged = false;

    if (X.second > Y.second + Z.second) {
        if (Y.second < Z.second) {
            merge(Y, Z, array);
            std::pair<int, int> new_run = { Y.first, Y.second + Z.second };
            runs.push(X);
            runs.push(new_run);
        }
        else {
            merge(X, Y, array);
            std::pair<int, int> new_run = { X.first, X.second + Y.second };
            runs.push(new_run);
            runs.push(Z);
        }
        merged = true;
    }
    else if (Y.second > Z.second) {
        merge(Y, Z, array);
        std::pair<int, int> new_run = { Y.first, Y.second + Z.second };
        runs.push(X);
        runs.push(new_run);
        merged = true;
    }
    else {
        runs.push(X);
        runs.push(Y);
        runs.push(Z);
    }

    return merged;
}

void merge(std::pair<int, int> part1, std::pair<int, int> part2, DynamicArray<int>& array)
{
    int left_begin = part1.first;
    int left_end = part1.first + part1.second;
    int right_begin = part2.first;
    int right_end = part2.first + part2.second;

    if (array[left_end - 1] <= array[right_begin]) {
        return;
    }

    DynamicArray<int> temp;
    for (int i = left_begin; i < left_end; i++) {
        temp.push_back(array[i]);
    }

    int i = left_begin;
    int left_idx = 0;
    int right_idx = right_begin;

    const int GALLOP_MODE = 7;
    int left_gllp_cnt = 0;
    int right_gllp_cnt = 0;

    while (left_idx < temp.GetSize() && right_idx < right_end) {
        if (left_gllp_cnt >= GALLOP_MODE || right_gllp_cnt >= GALLOP_MODE) {
            if (left_gllp_cnt >= GALLOP_MODE) {
                int gllp_cnt = gallop_right(temp, left_idx, array, right_idx, right_end);
                for (int j = 0; j < gllp_cnt; j++) {
                    array[i++] = array[right_idx++];
                }
                left_gllp_cnt = 0;
                right_gllp_cnt = 0;
            }
            else {
                int gllp_cnt = gallop_left(array, right_idx, temp, left_idx, temp.GetSize());
                for (int j = 0; j < gllp_cnt; j++) {
                    array[i++] = temp[left_idx++];
                }
                left_gllp_cnt = 0;
                right_gllp_cnt = 0;
            }
            continue;
        }


        if (temp[left_idx] <= array[right_idx]) {
            array[i++] = temp[left_idx++];
            left_gllp_cnt++;
            right_gllp_cnt = 0;
        }
        else {
            array[i++] = array[right_idx++];
            right_gllp_cnt++;
            left_gllp_cnt = 0;
        }
    }

  
    while (left_idx < temp.GetSize()) {
        array[i++] = temp[left_idx++];
    }
    while (right_idx < right_end) {
        array[i++] = array[right_idx++];
    }
}

int binary_search_range(DynamicArray<int>& array, int start, int end, int value, bool find_insert_pos)
{
    int low = start;
    int high = end;

    while (low < high)
    {
        int mid = low + (high - low) / 2;
        if (find_insert_pos ? (value > array[mid]) : (value >= array[mid]))
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }

    return low;
}


int gallop_right(DynamicArray<int>& left, int left_start,
    DynamicArray<int>& right, int right_start, int right_end)
{
    if (right_start >= right_end) return 0;

    int gallop_bound = 1;
    int last_offset = 0;

    while (right_start + gallop_bound < right_end &&
        left[left_start] > right[right_start + gallop_bound])
    {
        last_offset = gallop_bound;
        gallop_bound = (gallop_bound << 1) + 1;
        if (gallop_bound <= 0) 
        {
            gallop_bound = right_end - right_start;
            break;
        }
    }

    if (gallop_bound > right_end - right_start)
    {
        gallop_bound = right_end - right_start;
    }

    int search_start = right_start + last_offset;
    int search_end = right_start + gallop_bound;
    int insert_pos = binary_search_range(right, search_start, search_end, left[left_start], true);

    return insert_pos - right_start;
}


int gallop_left(DynamicArray<int>& right, int right_start,
    DynamicArray<int>& left, int left_start, int left_end)
{
    if (left_start >= left_end) return 0;

    int gallop_bound = 1;
    int last_offset = 0;

    while (left_start + gallop_bound < left_end &&
        right[right_start] > left[left_start + gallop_bound])  
    {
        last_offset = gallop_bound;
        gallop_bound = (gallop_bound << 1) + 1;
        if (gallop_bound <= 0)
        {
            gallop_bound = left_end - left_start;
            break;
        }
    }

    if (gallop_bound > left_end - left_start)
    {
        gallop_bound = left_end - left_start;
    }

    int search_start = left_start + last_offset;
    int search_end = left_start + gallop_bound;
    int insert_pos = binary_search_range(left, search_start, search_end, right[right_start], false);

    return insert_pos - left_start;
}

int GetMinrun(int size)
{
    int r = 0;
    while (size >= 64)
    {
        r |= size & 1;
        size >>= 1;
    }
    return size + r;
}

void insertion_sort(DynamicArray<int>& array, int begin, int begin_sorted, int end)
{
    if (end > array.GetSize()) end = array.GetSize();

    for (int i = begin_sorted; i < end; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (j >= begin && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int GetRun(int begin, int minrun, DynamicArray<int>& array)
{
    if (begin >= array.GetSize() - 1)
    {
        return array.GetSize() - begin;
    }

    int sorted_size = 1;
    bool increasing = true;

    if (array[begin] > array[begin + 1])
    {
        increasing = false;
    }

    for (int i = begin + 1; i < array.GetSize(); i++)
    {
        if (increasing && array[i] >= array[i - 1])
        {
            sorted_size++;
        }
        else if (!increasing && array[i] <= array[i - 1])
        {
            sorted_size++;
        }
        else
        {
            break;
        }
    }

    if (!increasing)
    {
        for (int i = 0; i < sorted_size / 2; i++)
        {
            array.swap(begin + i, begin + sorted_size - 1 - i);
        }
    }

    if (sorted_size < minrun)
    {
        int actual_end = begin + minrun;
        if (actual_end > array.GetSize())
        {
            actual_end = array.GetSize();
        }
        insertion_sort(array, begin, begin + sorted_size, actual_end);
        return actual_end - begin;
    }

    return sorted_size;
}