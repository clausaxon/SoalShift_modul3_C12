# SoalShift_modul3_C12

1.Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120

Jawab:

Terdapat 2 fungsi yaitu fungsi factorial dan sort.
Pertama Fungsi faktorial yang digunakan untuk menghitung faktorial dengan cara seperti dibawah ini:

```
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
```
Kedua, fungsi Sort yang digunakan untuk menyusun agar bilangat tersusun secara urut, dengan cara seperti ini:

```
     for(int i=1;i<argc;i++) {
        for(int j=i;j<argc;j++) {
            if(angka[i]>angka[j]) {
                temp=angka[j];
                angka[j]=angka[i];
                angka[i]=temp;
            }
        }
    }
``` 

Lalu, di fungsi main terjadi pemanggilan fungsi factorial dan Sort.
Pertama, melakukan perubahan dari argv menjadi integer:
```
 while (i<argc){
        angka[i]=atoi(argv[i]);
        i++;
    }
```  
Lalu, terjadi pemanggilan fungsi sort:
```
    sort (angka, argc);
```
Terakhir, membaut thread:
```
for(i=1;i<argc;i++) {
        int error;
        error=pthread_create(&(tid[i]),NULL,factorial,(void *)&angka[i]);
        if(error!=0){
                printf("Error!\n");
        }
        pthread_join(tid[i],NULL);
    }
}
```

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
4.Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
	- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
	- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
	- Ketika Mengekstrak file .zip juga harus secara bersama-sama
	- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 	       detik untuk mengekstrak kembali”
	- Wajib Menggunakan Multithreading
	- Boleh menggunakan system
	
Jawab:

Pertama, membuat folder bernama FolderProses1 dan FolderProses2:
```
char tempat1 []= "/home/hayu/Documents/FolderProses1";
char tempat2 []= "/home/hayu/Documents/FolderProses2";

void *buatFolder1(void *arg)
{
                char a[100]= "mkdir ";
                strcat(a, tempat1);
                system(a);
}

void *buatFolder2(void *arg)
{
                char b[100]="mkdir ";
                strcat(b, tempat2);
                system(b);
}
```
Setelah itu, untuk menampilkan 10 list proses maka kita memakai ps -aux | head -10, lalu meembuat fie .zip dan menghapus file .txt:
```
char file1 [] = "/home/hayu/Documents/FolderProses1/SimpanProses1.txt";
char file2 [] = "/home/hayu/Documents/FolderProses2/SimpanProses2.txt";

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
```
Lalu, melakukan unzip:
```
void *unzip1(void *arg)
{
                system("unzip /home/hayu/Documents/FolderProses1/KompresProses1.zip -d /home/hayu/Documents/FolderProses1/");
}

void *unzip2(void *arg)
{
                system("unzip /home/hayu/Documents/FolderProses2/KompresProses2.zip -d /home/hayu/Documents/FolderProses2/");
}
```
Untuk memunculkan tulisan "Menunggu 15 detik untuk mengekstrak kembali":
```
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
```
Didalam fungsi main, membaut thread dan dijoinkan:
```
                pthread_create(&(tid[0]),NULL,&buatFolder1,NULL);
                sleep(1);
                pthread_create(&(tid[1]),NULL,&buatFolder2,NULL);
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
```

