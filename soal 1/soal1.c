#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void *factorial(void *a);
void sort(int angka[], int argc);

int main(int argc, char* argv[]) {
    pthread_t tid[argc];
    int temp;
    int angka[1000];
    int i;

    while (i<argc){
        angka[i]=atoi(argv[i]);
        i++;
    }

    sort (angka, argc);

    for(i=1;i<argc;i++) {
        int error;
        error=pthread_create(&(tid[i]),NULL,factorial,(void *)&angka[i]);
        if(error!=0){
                printf("Error!\n");
        }
        pthread_join(tid[i],NULL);
    }
}

void *factorial(void *a){
    int angka=*((int*)a);
    unsigned long long fac=1;
    int i=angka;

    if(i < 0){
        printf("Error! Factorial of a negative number doesn't exist.");
    }

    else
    {
        while (i>0){
            fac*=i;
            i--;
        }
    }
    printf("%d! = %llu\n", angka,fac);
}

void sort(int angka[], int argc)
{
    int temp;
    for(int i=1;i<argc;i++) {
        for(int j=i;j<argc;j++) {
            if(angka[i]>angka[j]) {
                temp=angka[j];
                angka[j]=angka[i];
                angka[i]=temp;
            }
        }
    }
}
