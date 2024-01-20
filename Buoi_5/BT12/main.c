#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// Dinh nghia struct cho thong tin sinh vien
typedef struct {
    char hoTen[50];
    char ngaySinh[20];
    char queQuan[50];
} SinhVien;

SinhVien sinhVien;
int dataReady = 0;
int readReady = 0;

void *thread1_function(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        printf("Nhap thong tin sinh vien:\n");
        printf("Ho ten: ");
        scanf("%s", sinhVien.hoTen);
        printf("Ngay sinh: ");
        scanf("%s", sinhVien.ngaySinh);
        printf("Que quan: ");
        scanf("%s", sinhVien.queQuan);

        dataReady = 1; // Du lieu san sang ghi o Thread2
        readReady = 0; // Du lieu chua san sang doc o Thread3
        pthread_cond_signal(&cond); // Thong bao cho Thread2

        pthread_mutex_unlock(&mutex);

        //Doi 1s de Thread2 ghi
        sleep(2);
    }

    return NULL;
}

void *thread2_function(void *arg) {
    FILE *file = fopen("thongtinsinhvien.txt","a");
    if (file == NULL) {
        perror("Loi khi mo file");
        exit(EXIT_FAILURE);
    }

    while (1) {
        pthread_mutex_lock(&mutex);

        while (!dataReady) {
            pthread_cond_wait(&cond, &mutex);
        }

        // Ghi thong tin
        fprintf(file, "%s %s %s\n", sinhVien.hoTen, sinhVien.ngaySinh, sinhVien.queQuan);
        fflush(file); // Day du lieu vao file ngay lat tuc

        dataReady = 0; // Du lieu da duoc su dung
        readReady = 1; // Du lieu san sang doc
        pthread_mutex_unlock(&mutex);

        // Thong bao san sang doc cho Thread3
        pthread_cond_signal(&cond);

        //Doi 1s de Thread3 doc
        sleep(1);
    }

    fclose(file);
    return NULL;
}

void *thread3_function(void *arg) {
    FILE *file = fopen("thongtinsinhvien.txt", "r");
    if (file == NULL) {
        perror("Loi khi mo file");
        exit(EXIT_FAILURE);
    }

    while (1) {
        pthread_mutex_lock(&mutex);

        // Cho du lieu san sang doc
        while (!readReady) {
            pthread_cond_wait(&cond, &mutex);
        }

        // Doc va in thong tin tu file
        char buffer[100];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("Thong tin sinh vien tu file: %s", buffer);
        }

        dataReady = 0; // Du lieu da duoc su dung
        readReady = 0; // Du lieu da doc xong
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    fclose(file);
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);
    pthread_create(&thread3, NULL, thread3_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
