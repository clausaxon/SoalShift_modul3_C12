# SoalShift_modul3_C12

##1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120

Jawab:

Terdapat 2 fungsi yaitu fungsi factorial() dan sort().
Pertama, fungsi factorial() yang digunakan untuk menghitung faktorial dengan cara seperti dibawah ini:

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
Kedua, fungsi sort() yang digunakan untuk menyusun agar bilangan tersusun secara urut, dengan cara seperti ini:

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

Lalu, di fungsi main() terjadi pemanggilan fungsi factorial() dan sort().
Pertama, melakukan perubahan dari argv menjadi integer:
```
 while (i<argc){
        angka[i]=atoi(argv[i]);
        i++;
    }
```  
Lalu, terjadi pemanggilan fungsi sort():
```
    sort (angka, argc);
```
Terakhir, membuat thread:
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
##2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
a. Terdapat 2 server: server penjual dan server pembeli
b. 1 server hanya bisa terkoneksi dengan 1 client
c. Server penjual dan server pembeli memiliki stok barang yang selalu sama
d Client yang terkoneksi ke server penjual hanya bisa menambah stok
	- Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
e. Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
	- Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
f. Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
	- Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
	- Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
g. Server penjual akan mencetak stok saat ini setiap 5 detik sekali
h. Menggunakan thread, socket, shared memory


Untuk pembuatan 2 client dan 2 server kita bisa mengikuti template pembuatan socket di modul 3 sisop 


Tetapi yang menjadi masalah adalah penggunaan shared memory dalam server dan penambahan thread sesuai yang diinginkan soal dengan adanya timer setiap 5 detik untuk pengeprintan jumlah dan beli.


Koding pembikinan thread

```c 
int *p=value;
    pthread_t tid1;
pthread_create(&tid1, NULL, print, (void*) p);
```

Kodingan berada sebelum shared memory dan berada dalam server2.c


Koding untuk fungsi print yang berada dalam server 2.c

```c
void* print(void* arg){
    while(1){
        int num = *((int *) arg);
        printf("Stok : %d\n", num);
        sleep(5);
    }    
}
```

Kodingan adalah bentuk fungsi sendiri yang akan dijalankan oleh thread dengan ada kondisi sleep selama 5 detik dan berada dalam server2.c



##3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
	a. Terdapat 2 karakter Agmal dan Iraj
	b. Kedua karakter memiliki status yang unik
		- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
		- Iraj memiliki Spirit_Status, di awal program memiliki status 100
		- Terdapat 3 Fitur utama
			- All Status, yaitu menampilkan status kedua sahabat
		  	  Ex: Agmal WakeUp_Status = 75 
      		      		Iraj Spirit_Status = 30
			- “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
			- “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
		- Terdapat Kasus yang unik dimana:
			- Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bis			   dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
			- Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa 			      dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
		- Program akan berhenti jika Salah Satu :
			- WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
			- Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

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
##4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
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
Setelah itu, untuk menampilkan 10 list proses maka kita memakai ps -aux | head -10, lalu membuat fie .zip dan menghapus file .txt:
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
Untuk tulisan "Menunggu 15 detik untuk mengekstrak kembali" diberi sleep(15) dan didalam fungsi main(), membuat thread dan dijoinkan.

##5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
	a. Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
	b. Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 		10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila 		   pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
	c. Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene 		status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. 	     Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
	d. Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 	    setiap 10 detik ketika monster dalam keadaan standby.
	e. Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), 	       dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain 	   memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain 	     maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
	f. Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
		- Pembeli (terintegrasi dengan game)
			- Dapat mengecek stok makanan yang ada di toko.
			- Jika stok ada, pembeli dapat membeli makanan.
	- Penjual (terpisah)
			- Bisa mengecek stok makanan yang ada di toko
			- Penjual dapat menambah stok makanan.
Spesifikasi program:
A. Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
B. Program terdiri dari 3 scene yaitu standby, battle, dan shop.
C. Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan    tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika    sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit.        Contoh :

Standby Mode
Health : [health status]
Hunger : [hunger status]
Hygiene : [hygiene status]
Food left : [your food stock]
Bath will be ready in [cooldown]s
Choices
1. Eat
2. Bath
3. Battle
4. Shop
5. Exit

D. Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode
Monster’s Health : [health status]
Enemy’s Health : [enemy health status]
Choices
1. Attack
2. Run

E. Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

Shop Mode
Shop food stock : [shop food stock]
Your food stock : [your food stock]
Choices
1. Buy
2. Back

F. Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop
Food stock : [shop food stock]
Choices
1. Restock
2. Exit

G. Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))


