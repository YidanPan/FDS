#include <stdio.h>
#include <time.h>

#define MAX_N 10010

// ================= 1. 四个核心算法 =================

// 1. 迭代二分搜索
int binary_search_iterative(int a[], int left, int right, int x) {
    while (left <= right) {
        int mid = (left + right) / 2;
        if (x == a[mid]) return mid;
        else if (x > a[mid]) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// 2. 递归二分搜索
int binary_search_recursive(int a[], int left, int right, int x) {
    if (left > right) return -1;
    int mid = (left + right) / 2;
    if (x == a[mid]) return mid;
    else if (x < a[mid]) return binary_search_recursive(a, left, mid - 1, x);
    else return binary_search_recursive(a, mid + 1, right, x);
}

// 3. 迭代顺序搜索
int sequential_search_iterative(int a[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (x == a[i]) return i;
    }
    return -1;
}

// 4. 递归顺序搜索
int sequential_search_recursive(int a[], int n, int index, int x) {
    if (index >= n) return -1;
    if (x == a[index]) return index;
    return sequential_search_recursive(a, n, index + 1, x);
}

// ================= 2. 测试与计时框架 =================

void run_test(int algo_type, int a[], int n, int k, const char* algo_name) {
    clock_t start, stop;
    double total_time, duration;
    
    start = clock(); // 记录开始时间
    
    // 执行 K 次循环
    for (int i = 0; i < k; i++) {
        if (algo_type == 1) binary_search_iterative(a, 0, n - 1, n);
        else if (algo_type == 2) binary_search_recursive(a, 0, n - 1, n);
        else if (algo_type == 3) sequential_search_iterative(a, n, n);
        else if (algo_type == 4) sequential_search_recursive(a, n, 0, n);
    }
    
    stop = clock(); // 记录结束时间
    
    clock_t ticks = stop - start;
    // 注意：题目图片中给的是 CLK_TCK，但现代 C 语言标准库通常使用 CLOCKS_PER_SEC
    total_time = ((double)ticks) / CLOCKS_PER_SEC; 
    duration = total_time / k;
    
    // 打印格式化结果，方便你直接填表
    printf("N = %-5d | K = %-8d | Ticks = %-5ld | Total(s) = %-8.4f | Duration(s) = %e\n", 
           n, k, ticks, total_time, duration);
}

int main() {
    // 题目要求的 8 个 N 值
    int n_values[] = {100, 500, 1000, 2000, 4000, 6000, 8000, 10000};
    int num_sizes = 8;
    int a[MAX_N];

    // 算法名称
    const char* names[] = {
        "1. Binary Search (Iterative)", 
        "2. Binary Search (Recursive)", 
        "3. Sequential Search (Iterative)", 
        "4. Sequential Search (Recursive)"
    };

    printf("================ PERFORMANCE TESTING START ================\n\n");

    for (int algo = 1; algo <= 4; algo++) {
        printf(">>> Testing Algorithm: %s <<<\n", names[algo-1]);
        
        for (int i = 0; i < num_sizes; i++) {
            int n = n_values[i];
            int k;
            
            // 初始化最坏情况的数组
            for (int j = 0; j < n; j++) {
                a[j] = j;
            }
            
            // 动态调整 K 值：二分搜索极快，需要巨大的 K；顺序搜索较慢，K 需要随着 N 变大而减小
            if (algo == 1 || algo == 2) {
                k = 5000000; // 二分搜索 K 固定为 500 万次
            } else {
                // 顺序搜索：N 越大，K 越小，防止跑太久
                if (n <= 1000) k = 1000000;
                else if (n <= 4000) k = 100000;
                else k = 50000; 
            }
            
            run_test(algo, a, n, k, names[algo-1]);
        }
        printf("\n");
    }

    printf("================ PERFORMANCE TESTING END ================\n");
    return 0;
}