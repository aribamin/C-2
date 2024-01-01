#ifndef LAB06_H
#define LAB06_H
#include <stdio.h>

int test_bubble(void (*f)(int n, int arr[n]));
int test_gnome(void (*f)(int n, int arr[n]));
int test_insertion(void (*f)(int n, int arr[n]));
int test_custom(void (*f)(int n, int arr[n]));

void bubble_sort(int n, int arr[n]);
void gnome_sort(int n, int arr[n]);
void insertion_sort(int n, int arr[n]);
void custom_sort(int n, int arr[n]);
#endif
