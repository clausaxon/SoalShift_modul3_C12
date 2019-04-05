# SoalShift_modul3_C12

###NO.3

Untuk no 3 , kita menggunakan sistem multi-threading


Pertama kita bikin variable public yang akan dipakai

```c
pthread_t tid1, tid2, tid3;
int spiritstatus=100;
int wakestatus=0;

int flag=0;
int count1=0;
int count2=0;
int ab=0;
int it=0;
```

Spirit status akan dipakai dalam fungsi iraj dan wakestatus akan dipakai dalam fungsi agmal


Lalu kita bikin 3 fungsi yaitu untuk agmal , siraj dan fungsi status all untuk melihat status skarang


```c
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
```

lalu jika kita lihat di dalam tiap fungsi , terdapat variable yang sama yaitu flag dan sleep


flag digunakan untuk menjadi penanda agar fungsi itu jalan saat yang lain tidak, dan sleep digunakan untuk menghentikan program selama detik yang kita inginkan.


terdapat variable yang berbeda seperti count1, count2 , it , ab yang memiliki peranan masing2 dalam jalannya program.


count1 dan count2 digunakan untuk menghitung berapa kali fungsi dijalankan, karena dalam aturan soal jika salah satu program dijalankan 3 kali maka program yang lainnya akan berhenti.


Lalu terakhir kita bikin threadnya didalam main menggunakan flag dan penyertaan tiap kondisi sesuai soal agar program berjalan dengan benar


```c
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
```


