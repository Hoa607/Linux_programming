#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread1, thread2;

// Định nghĩa cấu trúc cho thông tin về con người
typedef struct {
    char hoTen[50];
    int namSinh;
    char sdt[15];
    char queQuan[50];
} Human;

void thread_Handler (void* arg) {
    Human *humanInfo = (Human *)arg;

    if(pthread_equal(pthread_self(), thread1) != 0) {
        printf("This is the Thread_Handler 1!\n");
    }
    else if (pthread_equal(pthread_self(), thread2) != 0) {
         // In thông tin con người
        printf("Thread2 is running.\n");
        printf("Ho ten: %s\n", humanInfo->hoTen);
        printf("Nam sinh: %d\n", humanInfo->namSinh);
        printf("So dien thoai: %s\n", humanInfo->sdt);
        printf("Que quan: %s\n", humanInfo->queQuan);
    }

}

int main(int argc, char **argv)
{

    Human Den_Vau = {.hoTen = "Nguyen Duc Cuong", .namSinh = 1989, .sdt = "0123456789", .queQuan = "Quang Ninh"};

    pthread_create(&thread1,NULL, thread_Handler, NULL);
    pthread_create(&thread2,NULL, thread_Handler, (void*)&Den_Vau);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}