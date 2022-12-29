/*
 * COMP2011 (Fall 2021) Programming Assignment 1
 *
 * Student name: FILL YOUR NAME HERE
 * Student ID: FILL YOUR STUDENT ID NUMBER HERE
 * Student email: FILL YOUR EMAIL HERE
 *
 */

#include <iostream>
#include <limits>
using namespace std;

// Global Constants
// You cannot modify these global constants
// You cannot use your own global variables
const int MAX_ARR_LEN = 16;
const int MAX_ROTATIONS = 1024;
// End of Global Constants

// Helper Functions
// Declare additional helper functions below when necessary
// int myHelperFunction(int argc, char *argv[])

// End of Helper Functions

// Tasks
// Please write your code under the TODO tag
// You cannot change the function declarations

// Task 1
int rotate(int arr[], int arrLen, int k)
{
    // Task 1 TODO

    if (k < 0 || k > arrLen-1) {
        cout << "Error: Index k is out of range." << endl;
        return -1;
    }

    if (k == 1) {
        int temp = arr[0];
        arr[0] = arr[k];
        arr[k] = temp;
        return 0;
    }

    for (int i = 0; i < k/2; i++) {
        int temp = arr[i];
        arr[i] = arr[k-i];
        arr[k-i] = temp;
        if (k-2*i == 3) {
            temp = arr[i+1];
            arr[i+1] = arr[k-i-1];
            arr[k-i-1] = temp;
        }
    }

    return 0;

    // End of Task 1 TODO
}

//Task 2
int swapAndRecord(int arr[], int arrLen, int indexA, int indexB, int rotations[], int &rotationLen)
{
    // Task 2 TODO
    rotationLen = 0;

    const int MAX_ROTATION = 6;

    int tempRotation[MAX_ROTATION];

    if ((indexA < 0 || indexA > arrLen-1) || (indexB < 0 || indexB > arrLen-1)) {
        cout << "Error: Index out of range." << endl;
        return -1;
    }

    if (indexA > indexB) {
        int temp = indexA;
        indexA = indexB;
        indexB = temp;
    }

    if (indexA == indexB) {
        return 0;
    }

    tempRotation[0] = indexA-1;
    tempRotation[1] = indexA;
    tempRotation[2] = indexB;
    tempRotation[3] = indexB-indexA-1;
    tempRotation[4] = indexB-indexA-2;
    tempRotation[5] = indexB-1;

    int j = 0;

    for (int i = 0; i < MAX_ROTATION; i++) {
        if (tempRotation[i] == 0) continue;
        if (j != 0 && tempRotation[i] == rotations[j-1]) {
            rotate(arr, arrLen, tempRotation[i]);
            j--;
            continue;
        }
        if (rotate(arr, arrLen, tempRotation[i]) != -1) {
            rotations[j] = tempRotation[i];
            j++;
        }
    }

    rotationLen = j;

    // autoSwap(arr, arrLen);

    return 0;


    // End of Task 2 TODO
}

//Task 3
void sortAndRecord(int arr[], int arrLen, int rotations[], int &rotationLen)
{
    // Task 3 TODO
    int n = arrLen;
    int max, maxIndex;
    rotationLen = 0;
    while(n > 1) {
        max = 0, maxIndex = 0;
        for (int i = 0; i < n; i++) {
            if (max <= arr[i]) {
                max = arr[i];
                maxIndex = i;
            }
        }
        // MAX is not at the end of the array
        if (maxIndex != n-1) {
            if (maxIndex != 0) {
                rotate(arr, n, maxIndex);
                rotations[rotationLen] = maxIndex;
                rotationLen++;
            }
            rotate(arr, n, n-1);
            rotations[rotationLen] = n-1;
            rotationLen++;
        }
        n--;
    }   

    // End of Task 3 TODO
}

//Task 4
int transformAndRecord(int src[], int tgt[], int arrLen, int rotations[], int &rotationLen)
{
    // Task 4 TODO

    int tgtFlag[arrLen] = {};

    bool hasElement;

    for (int i = 0; i < arrLen; i++) {
        hasElement = false;
        for (int j = 0; j < arrLen; j++) {
            if (tgtFlag[j] == 1) {
                continue;
            }
            if (src[i] == tgt[j]) {
                hasElement = true;
                tgtFlag[j] = 1;
                break;
            }
        }
        if (!hasElement) {
            return -1;
        }
    }

    for (int i = arrLen-1, k = 0; i >= 0; i--, k++) {
        for (int j = 0; j < arrLen; j++) {
            if (src[j] == tgt[i]) {
                if (j != arrLen-k-1) {
                    if (j != 0) {
                        rotate(src, arrLen-k, j);
                        rotations[rotationLen] = j;
                        rotationLen++;
                    }
                    rotate(src, arrLen-k, arrLen-k-1);
                    rotations[rotationLen] = arrLen-k-1;
                    rotationLen++;
                }
            }
        }
    }

    return 0;
    // End of Task 4 TODO
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

int init(int arr[], int arrLen)
{
    char buffer;
    cout << "? Please enter one digit at a time and press return:" << endl;
    for (int i = 0; i < arrLen; i++)
    {
        cin >> buffer;
        if (buffer > '9' || buffer < '0')
        {
            cout << "Error: Illegal digit input." << endl;
            return -1;
        }
        else
        {
            arr[i] = (int)buffer - 48;
        }
    }
    return 0;
}

void printArr(int arr[], int arrLen)
{
    for (int i = 0; i < arrLen; i++)
    {
        cout << arr[i];
        if (i < arrLen - 1)
        {
            cout << ',';
        }
    }
    cout << endl;
}

void runInit(int arr[], int &arrLen)
{
    cout << "##################################################" << endl;
    cout << "# Initializing" << endl;
    cout << endl;

    int initResult = -1;
    while (initResult < 0)
    {
        cout << "? Enter the length of your array:" << endl;
        cin >> arrLen;
        if (arrLen < 1)
        {
            cout << "! Error: Length should be larger than 0." << endl;
            continue;
        }
        else if (arrLen > MAX_ARR_LEN)
        {
            cout << "Error: arrLen of should be less than or equal to " << MAX_ARR_LEN << endl;
            continue;
        }
        cout << "? Enter " << arrLen << " elements of your array." << endl;
        initResult = init(arr, arrLen);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "! Initialization succeeded!" << endl;
    cout << "! Printing the array:" << endl;
    cout << endl;
    printArr(arr, arrLen);
    cout << endl;
}

void runPrint(int arr[], int arrLen)
{
    cout << "##################################################" << endl;
    cout << "# Printing the array" << endl;
    cout << endl;
    printArr(arr, arrLen);
    cout << endl;
}

void runRotate(int arr[], int arrLen)
{
    int k, output;
    cout << "##################################################" << endl;
    cout << "# Rotating the array:" << endl;
    cout << "? Enter the index k:";
    cin >> k;
    output = rotate(arr, arrLen, k);
    if (output < 0)
    {
        cout << "! Error: Rotation failed." << endl;
    }
    else
    {
        cout << "! Rotated." << endl;
        cout << "! Array after rotation:" << endl;
        cout << endl;
        printArr(arr, arrLen);
        cout << endl;
    }
}

void runSwap(int arr[], int arrLen)
{
    int indexA, indexB, rotations[MAX_ROTATIONS], rotationLen, output;
    cout << "##################################################" << endl;
    cout << "# Swapping elements:" << endl;
    cout << "? Enter the 1st index:";
    cin >> indexA;
    cout << "? Enter the 2nd index:";
    cin >> indexB;
    output = swapAndRecord(arr, arrLen, indexA, indexB, rotations, rotationLen);
    if (output < 0)
    {
        cout << "! Error: Swap failed." << endl;
    }
    else
    {
        cout << "! Swapped." << endl;
        cout << "! Array after swap:" << endl;
        cout << endl;
        printArr(arr, arrLen);
        cout << endl;
        cout << "! Rotations:" << endl;
        cout << endl;
        printArr(rotations, rotationLen);
        cout << endl;
    }
}

void runSort(int arr[], int arrLen)
{
    int from, to, rotations[MAX_ROTATIONS], rotationLen, output;
    cout << "##################################################" << endl;
    cout << "# Sorting the array:" << endl;
    sortAndRecord(arr, arrLen, rotations, rotationLen);
    cout << "! Sorted." << endl;
    cout << "! Array after sorting:" << endl;
    cout << endl;
    printArr(arr, arrLen);
    cout << endl;
    cout << "! Rotations:" << endl;
    cout << endl;
    printArr(rotations, rotationLen);
    cout << endl;
}

void runTransform(int arr[], int arrLen)
{
    int from, to, rotations[MAX_ROTATIONS], rotationLen, output;
    cout << "##################################################" << endl;
    cout << "# Transforming src array to the tgt:" << endl;
    int tgt[MAX_ARR_LEN], initResult = -1;
    while (initResult < 0)
    {
        cout << "? Enter " << arrLen << " elements of the tgt array." << endl;
        initResult = init(tgt, arrLen);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "! The target array:" << endl;
    cout << endl;
    printArr(tgt, arrLen);
    cout << endl;
    output = transformAndRecord(arr, tgt, arrLen, rotations, rotationLen);
    if (output < 0)
    {
        cout << "! Error: Cannot transform array to target." << endl;
    }
    else
    {
        cout << "! Transformed." << endl;
        cout << "! Array after transformation:" << endl;
        cout << endl;
        printArr(arr, arrLen);
        cout << endl;
        cout << "! Rotations:" << endl;
        cout << endl;
        printArr(rotations, rotationLen);
        cout << endl;
    }
}

void runOption()
{
    int arrLen = 0;
    bool is_initialized = false;
    int src[MAX_ARR_LEN];
    int tgt[MAX_ARR_LEN];
    int option;
    cout << "===========================================" << endl;
    cout << "= Welcome to COMP2011 PA1 1D Rubik's Cube =" << endl;
    cout << "===========================================" << endl;

    while (true)
    {
        if (!is_initialized)
        {
            runInit(src, arrLen);
            is_initialized = true;
        }
        else
        {
            cout << "##################################################" << endl;
            cout << "# Main Menu" << endl;
            cout << endl;
            cout << "1 Initialize" << endl;
            cout << "2 Print" << endl;
            cout << "3 Rotate" << endl;
            cout << "4 Swap" << endl;
            cout << "5 Sort" << endl;
            cout << "6 Transform" << endl;
            cout << "0 Exit" << endl;
            cout << endl;
            cout << "? Please enter an option (0-7): ";
            cin >> option;
            switch (option)
            {
            case 0:
                cout << "! Bye Bye." << endl;
                return;
            case 1:
                runInit(src, arrLen);
                break;
            case 2:
                runPrint(src, arrLen);
                break;
            case 3:
                runRotate(src, arrLen);
                break;
            case 4:
                runSwap(src, arrLen);
                break;
            case 5:
                runSort(src, arrLen);
                break;
            case 6:
                runTransform(src, arrLen);
                break;
            default:
                cout << "Illegal Choice, please try again." << endl;
                break;
            }
            cout << "! Returning to main menu." << endl;
        }
    }
}

int main()
{
    runOption();
    return 0;
}
