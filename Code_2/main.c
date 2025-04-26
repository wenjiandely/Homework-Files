/*
 ******************************************************************************
 * @file    main.c
 * @author  [Your Name/ID]
 * @version V1.0
 * @date    2025年4月26日
 * @brief   Comprehensive Experiment 2: Application of Loop Structures and Array Sorting
 ******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h> // For fabs in ratio comparison if needed, and for bar chart scaling

#define MAX_RAND_NUM 20
#define MAX_RAND_VAL 50
#define BAR_CHAR_ARRAY_SIZE (MAX_RAND_VAL + 1) // For Part 1 bar chart buffer
#define NUM_COUNTRIES 49
#define MAX_COUNTRY_NAME_LEN 12 // Max length including null terminator
#define MAX_BAR_LEN 40.0        // Max stars for Part 2 bar charts

// --- Helper Functions ---

// Function to print an integer and its corresponding bar chart (Part 1)
void printIntWithBar(int value) {
    printf("%3d: ", value);
    for (int i = 0; i < value; i++) {
        printf("*");
    }
    printf("\n");
}

// Function to print the array and bars (Part 1)
void printArrayWithBars(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printIntWithBar(arr[i]);
    }
    printf("\n");
}

// Function to wait for user input
void waitForEnter() {
    printf("Press Enter to continue...\n");
    // Clear input buffer before waiting
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar(); // Wait for Enter
}

// --- Sorting Algorithms ---

// Bubble Sort (Descending) for integers
void bubbleSortDesc(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Selection Sort (Ascending) for integers
void selectionSortAsc(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

// --- Part 2 Data Structures and Functions ---

// Structure to hold country data together for easier sorting
typedef struct {
    char name[MAX_COUNTRY_NAME_LEN];
    int import_val;
    int export_val;
    double ie_ratio;
} CountryData;

// Swap two CountryData structures
void swapCountryData(CountryData *a, CountryData *b) {
    CountryData temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort (Descending) for CountryData based on import value
void bubbleSortCountriesByImport(CountryData data[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (data[j].import_val < data[j + 1].import_val) {
                swapCountryData(&data[j], &data[j + 1]);
            }
        }
    }
}

// Selection Sort (Descending) for CountryData based on export value
void selectionSortCountriesByExport(CountryData data[], int n) {
    int i, j, max_idx;
    for (i = 0; i < n - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < n; j++) {
            if (data[j].export_val > data[max_idx].export_val) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swapCountryData(&data[i], &data[max_idx]);
        }
    }
}

// Selection Sort (Descending) for CountryData based on IE ratio
void selectionSortCountriesByRatio(CountryData data[], int n) {
    int i, j, max_idx;
    for (i = 0; i < n - 1; i++) {
        max_idx = i;
        for (j = i + 1; j < n; j++) {
            // Handle potential floating point inaccuracies if needed, but direct comparison is usually fine
            if (data[j].ie_ratio > data[max_idx].ie_ratio) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swapCountryData(&data[i], &data[max_idx]);
        }
    }
}

// Function to print country data table header
void printTableHeader(const char* sortKey) {
    printf("\n--- Sorted by %s (Descending) ---\n", sortKey);
    if (strcmp(sortKey, "Import") == 0) {
        printf("序号  进口额   国家        出口额   进出口交换比率  棒图 (进口额)\n");
    } else if (strcmp(sortKey, "Export") == 0) {
        printf("序号  出口额   国家        进口额   进出口交换比率  棒图 (出口额)\n");
    } else if (strcmp(sortKey, "IE Ratio") == 0) {
        printf("序号  进出口交换比率 国家        进口额   出口额   棒图 (交换比率)\n");
    }
    printf("--------------------------------------------------------------------------------------\n");
}

// Function to print a single row of country data and its bar chart
void printCountryDataRow(int index, const CountryData* data, const char* sortKey, double maxValue) {
    int numStars = 0;
    double valueForBar = 0;

    if (strcmp(sortKey, "Import") == 0) {
        valueForBar = data->import_val;
        printf("%-4d %-10d %-12s %-10d %-15.4f ", index + 1, data->import_val, data->name, data->export_val, data->ie_ratio);
    } else if (strcmp(sortKey, "Export") == 0) {
        valueForBar = data->export_val;
        printf("%-4d %-10d %-12s %-10d %-15.4f ", index + 1, data->export_val, data->name, data->import_val, data->ie_ratio);
    } else if (strcmp(sortKey, "IE Ratio") == 0) {
        valueForBar = data->ie_ratio;
        printf("%-4d %-15.4f %-12s %-10d %-10d ", index + 1, data->ie_ratio, data->name, data->import_val, data->export_val);
    }

    // Calculate and print bar chart
    if (maxValue > 0) { // Avoid division by zero
        numStars = (int)(valueForBar * MAX_BAR_LEN / maxValue);
    }
     if (numStars < 0) numStars = 0; // Ensure non-negative stars

    for (int i = 0; i < numStars; i++) {
        printf("*");
    }
    printf("\n");
}

// Function to find max value for bar chart scaling
double findMaxValue(const CountryData data[], int n, const char* key) {
    double maxVal = 0.0;
    if (n <= 0) return 0.0;

    if (strcmp(key, "Import") == 0) {
        maxVal = data[0].import_val; // Already sorted descending
    } else if (strcmp(key, "Export") == 0) {
         maxVal = data[0].export_val; // Already sorted descending
    } else if (strcmp(key, "IE Ratio") == 0) {
         maxVal = data[0].ie_ratio; // Already sorted descending
    }
     // Ensure maxVal is positive for scaling
    return (maxVal > 0) ? maxVal : 1.0;
}


// --- Main Function ---
int main() {
    // Set console output encoding to support Chinese characters if possible (Windows specific)
    // system("chcp 65001"); // UTF-8
    // system("chcp 936"); // GBK (might be default on Chinese Windows)
    // printf("Console encoding set.\n"); // Optional: Check if command works

    // --- Part 1: Random Integer Sorting and Bar Chart Display ---
    printf("--- Part 1: Random Integer Sorting and Bar Chart ---\n");
    int rArray[MAX_RAND_NUM];
    // char cArray[BAR_CHAR_ARRAY_SIZE]; // Not strictly needed as per implementation choice

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Generate and store random numbers
    printf("Generating %d random integers (1-%d)...\n", MAX_RAND_NUM, MAX_RAND_VAL);
    for (int i = 0; i < MAX_RAND_NUM; i++) {
        rArray[i] = (rand() % MAX_RAND_VAL) + 1;
    }

    // Print initial array and bars
    printf("\nInitial random numbers and bars:\n");
    printArrayWithBars(rArray, MAX_RAND_NUM);

    waitForEnter();

    // Sort descending using Bubble Sort
    printf("\nSorting in descending order (Bubble Sort)...\n");
    bubbleSortDesc(rArray, MAX_RAND_NUM);
    printf("Sorted numbers and bars (Descending):\n");
    printArrayWithBars(rArray, MAX_RAND_NUM);

    waitForEnter();

    // Sort ascending using Selection Sort
    printf("\nSorting in ascending order (Selection Sort)...\n");
    selectionSortAsc(rArray, MAX_RAND_NUM);
    printf("Sorted numbers and bars (Ascending):\n");
    printArrayWithBars(rArray, MAX_RAND_NUM);

    waitForEnter();

    // --- Part 2: China's Import/Export Data Analysis ---
    printf("\n--- Part 2: China Import/Export Data Analysis ---\n");

    // Initialize data directly (as required by instructions)
    // Note: Ensure array sizes match NUM_COUNTRIES = 49
    char country_names[NUM_COUNTRIES][MAX_COUNTRY_NAME_LEN] = {
        "美国", "日本", "韩国", "德国", "越南", "澳大利亚", "马来西亚", "巴西",
        "俄罗斯", "泰国", "印度", "印度尼西亚", "荷兰", "英国", "新加坡", "沙特阿拉伯",
        "墨西哥", "法国", "菲律宾", "加拿大", "意大利", "阿联酋", "智利", "南非",
        "西班牙", "瑞士", "波兰", "比利时", "秘鲁", "伊拉克", "土耳其", "阿曼",
        "巴基斯坦", "尼日利亚", "哈萨克斯坦", "孟加拉国", "新西兰", "安哥拉", "爱尔兰",
        "以色列", "科威特", "捷克", "瑞典", "哥伦比亚", "埃及", "乌克兰", "缅甸",
        "丹麦", "阿根廷"
    };
    int import_values[NUM_COUNTRIES] = {
        17970081, 20550277, 21344326, 11991430, 9231942, 16352908, 9830508, 11000670,
        7960907, 6183263, 2814551, 6392283, 1400494, 2567686, 3881973, 5696861,
        1913928, 3910500, 2476131, 3048978, 3032373, 2857327, 3957795, 3295561,
        1228866, 3788005, 554183, 857188, 2423903, 2665311, 504897, 2859710,
        358448, 303163, 1129056, 104693, 1615598, 2102743, 1762666,
        753454, 1775554, 605328, 987409, 561778, 170358, 977446, 812208,
        697291, 712432
    };
    int export_values[NUM_COUNTRIES] = {
        57607523, 16581426, 14880548, 11517540, 13789507, 6638009, 7865488, 5361123,
        6755117, 6935458, 9750751, 6064749, 10243171, 8702212, 5510346, 3032124,
        6743974, 4593066, 5151026, 5151026, 4362921, 4375166, 2629229, 2111525,
        3612557, 623357, 3657787, 3038163, 1330132, 1068987, 2915179, 356515,
        2424040, 2263626, 1395926, 2409441, 856063, 249142, 532132,
        1529400, 436847, 1510814, 1103495, 1435442, 1826461, 940443, 1052395,
        1087242, 1068798
    };

    CountryData countries[NUM_COUNTRIES];
    double maxVal; // For bar chart scaling

    // Populate the CountryData array and calculate IE ratios
    printf("\nCalculating IE Ratios...\n");
    for (int i = 0; i < NUM_COUNTRIES; i++) {
        strcpy(countries[i].name, country_names[i]);
        countries[i].import_val = import_values[i];
        countries[i].export_val = export_values[i];
        if (countries[i].export_val != 0) {
            countries[i].ie_ratio = (double)countries[i].import_val / countries[i].export_val;
        } else {
            countries[i].ie_ratio = 0.0; // Or handle as infinite/undefined if needed
             printf("Warning: Export value for %s is zero. Ratio set to 0.\n", countries[i].name);
        }
    }

    // 4) Sort by Import (Descending) using Bubble Sort and display
    printf("\nSorting by Import (Descending - Bubble Sort)...\n");
    bubbleSortCountriesByImport(countries, NUM_COUNTRIES);
    printTableHeader("Import");
    maxVal = findMaxValue(countries, NUM_COUNTRIES, "Import");
    for (int i = 0; i < NUM_COUNTRIES; i++) {
        printCountryDataRow(i, &countries[i], "Import", maxVal);
    }

    waitForEnter();

    // 5) Sort by Export (Descending) using Selection Sort and display
    printf("\nSorting by Export (Descending - Selection Sort)...\n");
    selectionSortCountriesByExport(countries, NUM_COUNTRIES);
    printTableHeader("Export");
    maxVal = findMaxValue(countries, NUM_COUNTRIES, "Export");
    for (int i = 0; i < NUM_COUNTRIES; i++) {
        printCountryDataRow(i, &countries[i], "Export", maxVal);
    }

    waitForEnter();

    // 6) Sort by IE Ratio (Descending) using Selection Sort and display
    printf("\nSorting by IE Ratio (Descending - Selection Sort)...\n");
    selectionSortCountriesByRatio(countries, NUM_COUNTRIES);
    printTableHeader("IE Ratio");
    maxVal = findMaxValue(countries, NUM_COUNTRIES, "IE Ratio");
    for (int i = 0; i < NUM_COUNTRIES; i++) {
        printCountryDataRow(i, &countries[i], "IE Ratio", maxVal);
    }

    printf("\n--- Experiment Finished ---\n");

    return 0;
}
