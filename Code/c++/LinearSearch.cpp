#include <iostream>
using namespace std;

int linearSearch(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == target)
            return i;
    }
  
    return -1;
}
  
int main()
{

    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 40;
    int index = linearSearch(arr, n, target);

    if (index != -1)
        cout << "Element found at index " << index;

    else
        cout << "Element not found";
    return 0;

}