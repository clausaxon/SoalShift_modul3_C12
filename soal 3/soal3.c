#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
 
pthread_t tid1, tid2, tid3;
int spiritstatus=100;
int wakestatus=0;

int flag=0;
int count1=0;
int count2=0;
int ab=0;
int it=0;
void* agmalwake(void *arg)
{
   while(1){
    if(flag ==1 ){
    if(count2 == 3){
    printf("Agmal Ayo Bangun disabled 10s\n");
    count2=0;
    ab=1;
    flag=0;
    sleep(10);
    ab=0;
    continue;
    }
    else{ 
    wakestatus+=15;
    count1++;
    printf("Agmal Ayo Bangun!\n");
    if(count1==3){
    flag=2;
    continue;
    }
    }
    flag=0;
    }
   }
    return NULL;
}

void* irajsleep(void *arg)
{
   while(1){
    if(flag == 2){
    if(count1 == 3){
    printf("Iraj Ayo Tidur disabled 10s\n");
    count1=0;
    it=1;
    flag=0;
    sleep(10);
    it=0;
    continue;
    }
    else{
    spiritstatus-=20;
    count2++;
    printf("Iraj Ayo Tidur!\n");
    if(count2==3){ 
    flag=1;
    continue;
    }

   }
    flag=0;
   }
   }
    return NULL;
}

void* statusall(void *arg)
{
   while(1){
    if(flag == 3){
    printf("\nWakeup status: %d\n", wakestatus);
    printf("Spirit status: %d\n", spiritstatus);

   flag=0;
   }
   }
   return NULL;
}
 
int main(void)
{
    int x;

    pthread_create(&(tid1), NULL, agmalwake, NULL);
    pthread_create(&(tid2), NULL, irajsleep, NULL);
    pthread_create(&(tid3), NULL, statusall, NULL);
    
    while(1){
    while(flag != 0){}
    printf("Masukan input : ");
    scanf("%d", &x);

    if(x==1){
    if(ab!=1){
    flag=x;
    }
    }
    else if (x==2){
    if(it!=1){
    flag=x;
    }
    }
    else if(x==3){
    flag=x;
    }
    if(wakestatus>=100){
    printf("\n Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
    break;
    }
    else if(spiritstatus<0){
    printf("\n Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
    break;
    }
    }
    return 0;
}
