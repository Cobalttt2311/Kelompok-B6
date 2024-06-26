# Proyek 2 - Pengembangan Aplikasi Berbasis Library

Enkripsi AES dan LSB

## Daftar Isi
  * [Informasi Umum](#informasi-umum)
  * [Teknologi](#teknologi)
  * [Petunjuk Instalasi](#petunjuk-instalasi)
  * [Struktur/Hirarki Program](#strukturhirarki-program)
  * [Algoritma Advanced Encryption Standard(AES)](#algoritma-advanced-encryption-standard-aes)
  * [Fitur Aplikasi](#fitur-aplikasi)
  * [Linked List](#linked-list)
  * [About Us](#about-us)
  * [Sumber](#sumber-referensi)

## Informasi Umum

Disini kami mencoba mengembangkan sebuah program keamanan melalui teknik kriptografi dan steganografi. Sistem keamanan ini dikembangkan sebagai syarat untuk memenuhi tugas Proyek 2. Kami menggabungkan Advanced Encryption Standard (AES) untuk mengenkripsi data dan metode Least Significant Bit (LSB) untuk menyembunyikan data dalam gambar.

### PENGERTIAN AES
Advanced Encryption Standard (AES) merupakan algoritma cryptographic yang dapat digunkan untuk mengamakan data. Algoritma AES adalah blok chipertext simetrik yang dapat mengenkripsi (encipher) dan dekripsi (decipher) informasi. Enkripsi merubah data yang tidak dapat lagi dibaca disebut ciphertext; sebaliknya dekripsi adalah merubah ciphertext data menjadi bentuk semula yang kita kenal sebagai plaintext. Algoritma AES is mengunkan kunci kriptografi 128, 192, dan 256 bits untuk mengenkrip dan dekrip data pada blok 128 bits.

![REPRESENTASI AES](./image/AES.webp)

### PENGERTIAN STEGANOGRAFI
Steganografi adalah ilmu yang melibatkan komunikasi data rahasia dalam sebuah media, misalnya file gambar, audio, dan video. Hal ini didasarkan pada asumsi bahwa jika rahasia mudah terlihat, maka mudah untuk dipecahkan, sehingga tujuan dari LSB di sini adalah untuk menyembunyikan keberadaan data yang disisipkan tanpa mudah diketahui orang lain.

### STEGANOGRAFI GAMBAR LSB
Steganografi LSB adalah teknik steganografi gambar di mana pesan disembunyikan di dalam sebuah gambar dengan mengganti bit paling tidak signifikan (bit paling rendah/belakang) dari setiap piksel dengan bit dari pesan yang akan disembunyikan.
RGB (piksel 3x8-bit, warna asli) dan RGBA (piksel 4x8-bit, warna asli dengan transparansi). Nilai-nilai ini berkisar antara 0-255, (nilai 8-bit).

![REPRESENTASI LSB](./image/LSB.webp)

Representasi Gambar sebagai Piksel RGB
Kita dapat mengubah pesan menjadi nilai desimal dan kemudian menjadi biner, dengan menggunakan Tabel ASCII. Kemudian, kita mengulang nilai piksel satu per satu, setelah mengubahnya menjadi biner, kita mengganti setiap bit yang paling tidak signifikan dengan bit pesan tersebut secara berurutan.

Untuk memecahkan kode gambar yang disandikan, kita cukup membalikkan prosesnya. Kumpulkan dan simpan bit terakhir dari setiap piksel kemudian bagi menjadi kelompok 8 dan ubah kembali ke karakter ASCII untuk mendapatkan pesan yang disembunyikan.

## Teknologi

### Proyek ini dibuat dengan :

- Bahasa Pemrograman : C++
- VSCODE Version : 1.84.2
- Dev-C Version : 4.9.2
- GIT Version : 2.44.0

## Petunjuk Instalasi

1. Download seluruh file yang tersedia di GitHub melalui link https://github.com/Cobalttt2311/Kelompok-B6
2. Download aplikasi compiler bahasa C ( disarankan menggunakan Dev C++ )
3. Buka file Project1.dev
4. Compile & Run Program

## Petunjuk Penggunaan Program
![Menu Program](./image/Menu.png)

Saat program dijalankan, anda akan ditampilkan 5 jenis menu, yaitu sebagai berikut:
1.  Enkripsi Pesan 
2.  Dekripsi Pesan
3.  Sisipkan Pesan ke Gambar
4.  Ekstrak Pesan dari Gambar
5.  Exit.

## Penjelasan Menu
#### 1. Menu Enkripsi
Disini anda akan diminta menginputkan cipher key (bebas, maksimal 16 karakter), dan juga Plain Text(bebas, maksimal 16 karakter), /Plain Text disini adalah pesan yang anda ingin sembunyikan.
Setelah memasukkan semua yang diperlukan, anda akan diberikan :
* Cipher Key (Format Hexa)
* Plain Text (Format Hexa)
* Cipher Text (Format Hexa)

Anda perlu mencatat Cipher Key, dan Cipher Text untuk mendekripsi pesan yang sudah terenkripsi.
Nantinya anda akan diberikan pilihan, apakah anda inigin menyiipkan pesan ke dalam sebuah gambar atau tidak. Jika ya maka akan dilanjutkan proses steganography (LSB) (Dijelaskan pada menu nomor 3), jika tidak maka akan kembali ke menu utama.

#### 2. Menu Dekripsi
Disini anda akan diminta menginputkan Cipher Key yang anda miliki (Format Hexa), dan juga Cipher Text (Format Hexa). Setelah anda memasukkan semua yang diperlukan, anda akan diberikan Decrypted Text (Pesan yng disembunyikan)

   
#### 3. Menu Sisipkan Menu ke Gambar
Disini anda akan diminta menginputkan nama file gambar (gambar polosan yang ingin digunakan) dalam format png, anda wajib memberikan ekstensi .png pada akhir nama file, ex: (nama).png
Program ini dapat mensupport gambar bertype JPG, PNG.
Pastikan nama file sesuai, dan file gambar telah tersedia di direktori program yang kamu jalankan. 
jika tidak, maka program tidak akan memproses, dan akan mengemnbalikan anda ke menu utama.
Selanjutnya setelah gambar berhasil dibuka, anda diminta memasukkan pesan yang ingin disisipkan, batasan pesan yang dimasukkan tergantung ukuran gambar itu sendiri, namun kami membatasi karakter yang dibaca dan dienkripsi sebesar 300 kata (termasuk spasi).
Selanjutnya anda akan diminta untuk memasukkan nama file gambar yang sudah di sisipkan pesan rahasia tadi.
output yang dihasilkan adalah sebuah gambar dengan format .png


#### 4. Menu Ekstrak Pesan dari Gambar
Disini anda akan diminta meninputkan nama file gambar, anda wajib memberikan ekstensi .png pada akhir nama file, ex: (nama).png
Output yang dihasilkan adalah pesan yang disisipkan dalam gambar tersebut.

#### 5. Exit
Disini anda akan keluar dari program


## Struktur/Hirarki Program

1. Diagram Alur Encrypt AES

![Diagram AES](./image/Encrypt_AES.png)

## Algoritma Advanced Encryption Standard (AES)

### Enkripsi Algoritma AES

CreateRoundKey :
Fungsi ini membuat dan mengambil 16 elemen dari expandedKey dan menyalin nya ke dalam block roundkey sesuai urutan dari initial round hingga round 10. Nantinya akan menghasilkan roundkey dari kunci yang diperluas.
Dengan menggunakan fungsi ini, kita dapat membuat round key yang unik untuk setiap ronde enkripsi, yang kemudian digunakan untuk melakukan operasi enkripsi pada blok teks.

AddRoundKey :
Addroundkey adalah proses XOR (eksklusif OR) antara setiap byte dalam blok data dengan kunci putaran (round key) yang telah dikembangkan sebelumnya. 
Addroundkey ini diterapkan pada
1. Initial Round, melakukan proses XOR antara Plaintext, dan Key yang diinput oleh user, sehingga menghasilkan blok baru untuk proses enkripsi
2. Proses Enkripsi dari Round 1 - 10

Sub Byte :
mengambil Nilai bit awal dan bit akhir untuk dijadikan index penunjuk sbox
lalu mensubtitusikan / menukar nilai yang dikirim(state) dengan sbox

ShiftRows :
memanipulasi baris-baris dalam matriks state dengan cara menggeser setiap baris 
ke kiri dengan jumlah posisi yang berbeda-beda.

MixColumn :
Mix Column adalah mengalikan tiap elemen dari blok chiper dengan matriks transformasi.

ExpandKey :
* Menghasilkan kunci yang diperluas
* Menyediakan kunci yang diperlukan untuk putaran Enkripsi
* Menerapkan operasi pembangkit kunci yang melibatkan 3 proses
  1. Rotasi(RotWord), setiap karakter dalam kata kunci dipindahkan ke posisi sebelumnya dalam array, dengan karakter pertama dipindahkan ke posisi terakhir.
  2. Substitusi (SubWord), melakukan substitusi pada setiap karakter dalam kata kunci dengan nilai yang sesuai dari tabel S-Box.
  3. XOR, melakukan XOR karakter dengan tabel Rcon

## Fitur Aplikasi

1. Enkripsi plainteks menggunakan metode AES
2. Dekripsi chiperteks menggunakan metode AES
   Steganografi
3. Menyisipkan sebuah pesan ke dalam gambar menggunakan metode LSB
4. Dekripsi sebuah gambar menjadi sebuah pesan menggunakan metode LSB

## Linked List

### Struktur Linked List
Program ini menggunakan linked list dalam beberapa proses, yaitu: 
1. Pada saat enkripsi, program akan menggunakan linked list untuk menyimpan dan mengelola cipher text untuk dimasukkan ke dalam linked list.
2. Menyisipkan node tipuan, node tipuan ini akan disisipkan ke dalam linked list untuk menambah keamanan data.
3. Mengacak dan memutar data, nilai-nilai dalam linked list akan diacak dan diputar untuk membuat ciphertext lebih sulit ditebak.
Linked list yang kami gunakan dalam program ini berupa Circular Doubly Linked List.

### Implementasi Fungsi-fungsi Linked List

    void insert(address *first, infotype isi)
Fungsi ini digunakan untuk menambahkan node baru ke dalam linked list. Node baru ditambahkan di akhir linked list. Jika linked list kosong, node baru menjadi node pertama dan menunjuk ke dirinya sendiri sebagai next dan prev.

    address nodetipuan(address baru, int n)
Fungsi ini membuat node tipuan dengan nilai dari tabel S-Box yang nilai baris dan kolomnya ditentukan oleh bilangan Fibonacci.

    address nodesebelumpalsu(int fibo, address first)
Fungsi ini mencari node pada posisi node sebelum palsu berdasarkan nilai Fibonacci.

    void sisipkantipuan(address first)
Fungsi ini menyisipkan node tipuan ke dalam linked list pada posisi yang ditentukan oleh nilai Fibonacci.

    void printLL(address first)
Fungsi ini mencetak semua elemen dari linked list mulai dari node pertama hingga kembali ke node pertama. 

    infotype pindahkearray(address *first)
Fungsi ini mengubah linked list kembali menjadi bentuk array.

    void hapustipuan(address first)
Fungsi ini menghapus node tipuan dari linked list pada posisi yang ditentukan oleh nilai Fibonacci.

    void acak(address first)
Fungsi ini menukar nilai node yang indexnya bernilai ganjil dalam linked list dengan nilai node setelahnya.

    void putar(address *first,char key,bool reverse)
Fungsi ini memutar linked list ke kiri atau ke kanan sejumlah langkah yang ditentukan oleh key.

    int fibonaci(int n)
Fungsi ini berfungsi untuk menghitung bilangan Fibonacci ke-n menggunakan pendekatan rekursif. Bilangan Fibonacci adalah deret angka di mana setiap angka adalah jumlah dari dua angka sebelumnya, dimulai dengan 0 dan 1. Namun, dalam fungsi ini, deret dimulai dengan 1 dan 1 karena basisnya adalah 1 untuk n <= 2.

## About Us

Jurusan : Teknik Komputer dan Informatika

Prodi : D3 - Teknik Informatika

Kampus : Politeknik Negeri Bandung

Kelas : 1B - JTK

Kelompok B6 :

    Anggota  :

      1. Alanna Tanisya Anwar (231511034) , alannatnsyaa

      2. Daffa Al Ghifari (231511038) , daffalghi

      3. Erina Dwi Yanti (231511043) , erinadwy

      4. Nalendra Praja Bredtyopati Yudo (231511056) , Cobalt2311

      5. Radja Restu Arsita (231511061) , Radja-Restu-A

    Manajer

      1. Djoko Cahyo Utomo Lieharyani, S.Kom., M.MT. (199312282019031013) , Lieharyani

## Sumber referensi

### Aplikasi ini terinspirasi dari
https://github.com/m3y54m/aes-in-c
https://youtu.be/YpHJPvuCHNA?si=-fCSDrAgCLqRn0DO

### Definisi AES :
https://kelas-ol.esaunggul.ac.id/pluginfile.php/232572/mod_forum/intro/Enkripsi%20Algoritma%20AES%20(Advanced%20Encryption%20Standard)%20PERTEMUAN%20KE%205.pdf?time=1585913179960

### Definisi LSB :
https://medium.com/swlh/lsb-image-steganography-using-python-2bbbee2c69a2
