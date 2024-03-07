//
// Created by Niko Antoun on 7/29/22.
//

#pragma once
#ifndef PROGRAM_4_SORTIMPLS_H
#define PROGRAM_4_SORTIMPLS_H
#include <vector>
#include <iostream>
#include <string>


using namespace std;

//Helper method to swap two elements

void swapElements(int* elementOne, int* elementTwo)
{
    int temp = *elementOne; //temp int so the swapped value is not lost
    *elementOne = *elementTwo;
    *elementTwo = temp;
}

int minimum(int firstElement, int secondElement)
{
    if(firstElement < secondElement) //if first element is smaller than second
        return firstElement; //first element is smaller
    else //second is less (or if equal, doesn't matter)
        return secondElement; //second element is smaller
}

void BubbleSort(vector<int>& sortList, int first, int length)
{
    for(int i = first; i <= length; i++) //traverse list from start
    {
        for(int j = first; j <= (length-first-1); j++) //second partitions the list as bigger and bigger bubbles
        {
            if(sortList[j] > sortList[j+1]) //if elements are unsorted
                swapElements(&sortList[j], &sortList[j+1]); //invokes swap function
        }
    }
}

void InsertionSort(vector<int>& sortList, int start, int length)
{
    for(int i = 0; i <= length; i++)
    {
        int insert = sortList[i]; //starts at the beginning of list
        int index = i - 1; //index for insert
        while(index >= start && sortList[index] > insert) //while current element is unsorted
        {
            sortList[index + 1] = sortList[index]; //insert
            index--; //move down list
        }
        sortList[index + 1] = insert;
    }
}

//Helper method for MergeSort
void MergeSortHelper(vector<int>& sortList, int start, int center, int end)
{
    int leftIndex = center - start + 1, rightIndex = end - center;
    vector<int> leftList(leftIndex); //partitions first half of the list
    vector<int> rightList(rightIndex); //partitions second half of the list

    for(int i = 0; i < leftIndex; i++) //fill left list
        leftList[i] = sortList[start + i];

    for(int i = 0; i < rightIndex; i++) //fill right list
        rightList[i] = sortList[center + i + 1];

    int left = 0, right = 0, listIndex = start; //tracks lists index
    while(left < leftIndex && right < rightIndex) //sorts the split lists via merged comparison
    {
        if(leftList[left] <= rightList[right])
            sortList[listIndex++] = leftList[left++];
        else
            sortList[listIndex++] = rightList[right++];
    }

    while(left < leftIndex) //merges left list
        sortList[listIndex++] = leftList[left++];

    while(right < rightIndex) //merges right list
        sortList[listIndex++] = rightList[right++];
}

void MergeSort(vector<int>& sortList, int start, int end) //Recursive sort
{
    if(start < end)
    {
        int center = start + (end - start) / 2; //index to track the center of each recursive call
        MergeSort(sortList, start, center); //recursive call for left side of list
        MergeSort(sortList, center + 1, end); //recursive call for right side of list
        MergeSortHelper(sortList, start, center, end); //Partitions appropriately per recursive calL
    }
}

//Helper method for IterativeMergeSort
void IterativeMergeSortHelper(vector<int>& sortList, vector<int> temp, int start, int center, int end)
{
    int listIndex = 0, length = end - start + 1; //tracks sort's position in list and length
    int listStart = start, listEnd = center; //current list's endpoints
    int tempStart = center + 1, tempEnd = end; //temp list's endpoints

    while(listStart <= listEnd && tempStart <= tempEnd) //the first endpoints are less than the second...
    {
        if (sortList[listStart] < sortList[tempStart]) //sorts current elements into temp list
            temp[listIndex] = sortList[listStart++]; //insert current element into temp from current list's position
        else
            temp[listIndex] = sortList[tempStart++]; //insert current element into temp from temp list's position

        listIndex++; //increment current list position each time
    }

    while(listStart <= listEnd) //traverse current list
        temp[listIndex++] = sortList[listStart++]; //sets next temp element from list position in current sorted list

    while(tempStart <= tempEnd) //traverse temp list
        temp[listIndex++] = sortList[tempStart++]; //sets next temp element from temp position in current sorted list

    for(int i = 0; i < length; i++) //now traverse the lists and merge sorted temp into current list
        sortList[start++] = temp[i]; //fill in the current list with sorted temp

}

void IterativeMergeSort(vector<int>& sortList, int start, int end)
{
    vector<int> temp(end); //temp list for helper method
    for (int i = 1; i < end; i = 2 * i) //index where it splits the list in portions
    {
        for (int j = start; j < end; j += 2 * i) //index where it makes sure the list is split appropriately
        {
            int listCenter = min((j + i - 1), end); //minimum value to pass as the center index into helper
            int listEnd = min((j + 2 * i - 1), end); //minimum value to pass as the largest index into helper

            //Helper method similar to MergeSortHelper, but uses temp to sort and fill current list
            IterativeMergeSortHelper(sortList, temp, j, listCenter, listEnd);
        }
    }
}

void QuickSort(vector<int>& sortList, int start, int end)
{
    if(start < end)
    {
        int topElement = sortList[end];
        int listIndex = start - 1;
        for(int i = start; i <= end - 1; i++) //traverse list
        {
            if (sortList[i] <= topElement) //if the element is less than the top
            {
                listIndex++; //increases the list position
                swapElements(&sortList[listIndex], &sortList[i]); //... and invokes swap
            }
        }
        //swap from the current position in list to the top
        swapElements(&sortList[listIndex + 1], &sortList[end]);

        //Recursive QuickSort calls
        QuickSort(sortList, start, listIndex);
        QuickSort(sortList, listIndex + 2, end);
    }
}

void ShellSort(vector<int>& sortList, int start, int end)
{
    int position;
    for(int i = end / 2; i > start; i /= 2) //start in the center, and decrement by half each time
    {
        for(int j = i; j < end + 1; j++) //start from i and increment by each element until the end of list
        {
            int temp = sortList[j];
            for(position = j; position >= i && sortList[position-i] > temp; position -= i) //traverse until j is reached
                sortList[position] = sortList[position - i]; //make switch
            sortList[position] = temp;
        }
    }
}


#endif //PROGRAM_4_SORTIMPLS_H
