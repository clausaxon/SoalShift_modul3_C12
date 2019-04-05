#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[50];

//mkdir
char tempat1 []= "/home/hayu/Documents/FolderProses1";
char tempat2 []= "/home/hayu/Documents/FolderProses2";

//backup
char file1 [] = "/home/hayu/Documents/FolderProses1/SimpanProses1.txt";
char file2 [] = "/home/hayu/Documents/FolderProses2/SimpanProses2.txt";

void *buatFile1(void *arg);
void *buatFile2(void *arg);
void *zip1(void *arg);
void *zip2(void *arg);
void *unzip1(void *arg);
void *unzip2(void *arg);
void *tulis(void *arg);

int main(void)
{
                pthread_create(&(tid[0]),NULL,&buatFile1,NULL);
                sleep(1);
                pthread_create(&(tid[1]),NULL,&buatFile2,NULL);
                sleep(1);
                pthread_create(&(tid[2]),NULL,&zip1,NULL);
                sleep(1);
                pthread_create(&(tid[3]),NULL,&zip2,NULL);
                sleep(1);
                pthread_create(&(tid[4]),NULL,&tulis,NULL);
                sleep(15);
                pthread_create(&(tid[5]),NULL,&unzip1,NULL);
                pthread_create(&(tid[6]),NULL,&unzip2,NULL);

                pthread_join(tid[0],NULL);
                pthread_join(tid[1],NULL);
                pthread_join(tid[2],NULL);
                pthread_join(tid[3],NULL);
                pthread_join(tid[4],NULL);
                pthread_join(tid[5],NULL);
                pthread_join(tid[6],NULL);
                exit(0);
                return 0;
}

void *buatFile1(void *arg)
{
                char a[100]= "mkdir ";
                strcat(a, tempat1);
                system(a);
}

void *buatFile2(void *arg)
{
                char b[100]="mkdir ";
                strcat(b, tempat2);
                system(b);
}

void *zip1(void *arg)
{
                char c[100]= "ps -aux | head -10 > ";
                strcat(c, file1);
                system(c);
                system("zip -j /home/hayu/Documents/FolderProses1/KompresProses1.zip /home/hayu/Documents/FolderProses1/SimpanProses1.txt");
                char e[100] = "rm ";
                strcat(e, file1);
                system(e);
}

void *zip2(void *arg)
{
                char d[100]= "ps -aux | head -10 > ";
                strcat(d, file2);
                system(d);
                system("zip -j /home/hayu/Documents/FolderProses2/KompresProses2.zip /home/hayu/Documents/FolderProses2/SimpanProses2.txt");
                char f[100] = "rm ";
                strcat(f, file2);
                system(f);
}

void *unzip1(void *arg)
{
                system("unzip /home/hayu/Documents/FolderProses1/KompresProses1.zip -d /home/hayu/Documents/FolderProses1/");
}

void *unzip2(void *arg)
{
                system("unzip /home/hayu/Documents/FolderProses2/KompresProses2.zip -d /home/hayu/Documents/FolderProses2/");
}

void *tulis(void *arg)
{
                FILE *tulis;
                char file[50] = "tulis.txt";
                tulis = fopen(file,"w");
                fprintf(tulis, "Menunggu 15 detik untuk mengekstrak kembali\n");
                fclose(tulis);
                char cat[50]= "cat ";
                strcat(cat, file);
                system(cat);
                system("rm tulis.txt");
}
