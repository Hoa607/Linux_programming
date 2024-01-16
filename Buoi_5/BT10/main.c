#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

int array[ARRAY_SIZE];
long long global_sum = 0;
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

void *calculate_partial_sum(void *arg) {
    long long partial_sum = 0;
    int thread_id = *(int *)arg;

    for (int i = thread_id; i < ARRAY_SIZE; i += NUM_THREADS) {
        partial_sum += array[i];
    }

    // Đồng bộ hóa khi cập nhật global_sum
    pthread_mutex_lock(&sum_mutex);
    global_sum += partial_sum;
    pthread_mutex_unlock(&sum_mutex);

    pthread_exit(NULL);
}

int main() {
    // Khởi tạo biến struct timespec để lưu trữ thời gian
    struct timespec single_start, single_end;
    struct timespec multi_start, multi_end;

    // Khởi tạo mảng
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    // Lấy thời gian bắt đầu
    clock_gettime(CLOCK_MONOTONIC, &single_start);

    // Đoạn mã bạn muốn đo thời gian thực hiện
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        global_sum += i + 1;
    }

    // Lấy thời gian kết thúc
    clock_gettime(CLOCK_MONOTONIC, &single_end);

    // Tính toán thời gian thực hiện theo second & nano_second
    double elapsed_time1 = (single_end.tv_sec - single_start.tv_sec) + 
                          (single_end.tv_nsec - single_start.tv_nsec) / 1e9;

    // In ra thời gian thực hiện
    printf("Thời gian thực hiện Single Thread: %lf giây\n", elapsed_time1);
    // In tổng kết quả
    printf("Global sum of Single Thread: %lld\n", global_sum);

    //Reset value
    global_sum = 0;

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Lấy thời gian bắt đầu
    clock_gettime(CLOCK_MONOTONIC, &multi_start);

    // Tạo các luồng
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, calculate_partial_sum, (void *)&thread_ids[i]);
    }

    // Kết hợp các luồng
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Lấy thời gian kết thúc
    clock_gettime(CLOCK_MONOTONIC, &multi_end);

    // Tính toán thời gian thực hiện theo second & nano_second
    double elapsed_time2 = (multi_end.tv_sec - multi_start.tv_sec) + 
                          (multi_end.tv_nsec - multi_start.tv_nsec) / 1e9;

    // In ra thời gian thực hiện
    printf("Thời gian thực hiện Multi Threads: %lf giây\n", elapsed_time2);

    // In tổng kết quả
    printf("Global sum of Multi Threads: %lld\n", global_sum);

    return 0;
}
