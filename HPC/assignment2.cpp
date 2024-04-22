#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>
using namespace std;



void bubbleSort(int arr[],int size){
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < size - 1; i ++){
        for(int j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Bubble Sort: " <<chrono::duration_cast<chrono::microseconds>(end - start).count()<< " us" << endl;
}

void parallelBubbleSort(int a[],int n){
    auto start = chrono::high_resolution_clock::now();
    for(int i=0;i<n;i++) {       
    	int first = i % 2;      
	#pragma omp parallel for shared(a,first)
	for(int j=first;j<n-1;j+=2){       
	      if(a[j]>a[j+1]){       
	  	swap(a[j],a[j+1]);
	    }        
	}        
    }
    
    auto end = chrono::high_resolution_clock::now();
    cout << "Parallel Bubble Sort: " <<chrono::duration_cast<chrono::microseconds>(end - start).count()<< " us"  << endl;
}


void merge(int array[],int low, int mid, int high,int size){
    int temp[size];
    int i = low;
    int j = mid + 1;
    int k = 0;
    while((i <= mid) && (j <= high)){
        if(array[i] >= array[j]){
            temp[k] = array[j];
            k++;
            j++;
        }
        else{
            temp[k] = array[i];
            k++;
            i++;
        }
    }
    while(i <= mid){
        temp[k] = array[i];
        k++;
        i++;
    }
    while(j <= high){
        temp[k] = array[j];
        k++;
        j++;
    }
    k = 0;
    for(int i = low;i <= high;i++){
        array[i] = temp[k];
        k++;
    }
}

void merge_sort(int array[],int low,int high,int size){
    if(low < high){
        int mid = (low + high) / 2;
        merge_sort(array,low,mid,size);
        merge_sort(array,mid+1,high,size);
        merge(array,low,mid,high,size);
    }
}

void mergeSortSequential(int arr[],int size){
    auto start = chrono::high_resolution_clock::now();
    merge_sort(arr,0,size-1,size);
    auto end = chrono::high_resolution_clock::now();
    cout << "Merge Sort: " <<chrono::duration_cast<chrono::microseconds>(end - start).count()<< " us"  << endl;
}


void ParallelMergeSort(int arr[],int size){
    
    auto start = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single nowait
    	merge_sort(arr,0,size-1,size);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Parallel Merge Sort: " <<chrono::duration_cast<chrono::microseconds>(end - start).count()<< " us"  << endl;
}




int main(int argc, char const *argv[])
{
    int SIZE;
    int MAX = 1000;
    cout << "Enter size of array: ";
    cin >> SIZE;
    int array[SIZE];
    for(int i = 0 ; i < SIZE; i ++){
        array[i] = rand() % MAX;
    }
    bubbleSort(array,SIZE);
    parallelBubbleSort(array,SIZE);
    mergeSortSequential(array,SIZE);
    ParallelMergeSort(array,SIZE);
    return 0;
}
