# IF4031-Pengambangan Aplikasi Terdistribusi

Oleh:
- Fajar Nugroho (13515060)
- Fadhil Imam Kurnia (13515146)

Untuk melakukan pengukuran, kami menggunakan PC yang sama untuk mendapatkan angka yang akurat. Spesifikasi PC yang digunakan untuk pengukuran:

| Parameter  | Spesifikasi |
| ------------- | ------------- |
| Memori  | 8 GB 2133 MHz LPDDR3  |
| Processor  | Intel Core i5  2.3Ghz|
| OS  | macOS High Sierra v10.13.6 |

## A. Mengukur Kinerja Web Server
> Carilah / kembangkan tool yang dapat digunakan untuk menngukur kinerja web server apache / nginx untuk mengakses sebuah dokumen html yang berukuran sekitar 500 bytes, dan 20 KB. Cek apakah server tersebut mampu melayani hingga 10.000 concurrent request. Laporkan hasil berapa waktu rata - rata dan berapa memory yang digunakan oleh apache / nginx.

Pada tugas ini kami menggunakan tool [Apache Benchmark v2.4](http://httpd.apache.org/docs/2.4/programs/ab.html) untuk mengukur performa dari server. Sedangkan web server yang diukur kami memilih untuk menggunakana [Apache/2.4.33](http://httpd.apache.org/). Untuk menjalankan pengukuran terlebih dahulu siapkan file berukuran 500B dan 20KB, file tersebut dapat diperoleh dalam direktori [data](https://github.com/fadhilimamk/peladen/tree/master/data). Kemudian nyalakan web server dan jalankan perintah:
```
  ab -n 10000 -kn 10000 http://localhost/500b.html
  ab -n 10000 -kn 10000 http://localhost/20kb.html
```

Didapatkan hasil sebagai berikut:

| Benchmark                         | 500B | 20KB |
| -------------                     | ------------- | ------------- |
| Testing Time (s)                  | 1.121 | 1.162 | 
| Average Request Per Second (rps)  | 8917.72 | 8602.84 |
| Average Request Time (s)          | 0.112 | 0.116 |
| Transfer Rate (KB/s)              | 6806.42 | 170414.88 |
| Memory Usage (KB)                 | 988 | 936 |

## B. Implementasi Event-Based Web Server Sederhana
> Buatlah program kecil web server dengan menggunakan pendekatan event-based server. Program tersebut dapat menerima request file dengan format HTTP request pada port tertentu (konfigurasi).
Program dibuat menggunakan bahasa C/C++, dapat ditulis menggunakan socket, library libev. Boleh menggunakan low-level event-based I/O library yang lain. Lakukaan pengukuran dengan cara yang sama dengan tugas no. 1 di atas.

Untuk mengimplementasikan web server sederhana, kami menggunakan library [libevent](https://libevent.org/). Kode program web server ini dapat dilihat pada repository ini. Untuk mengompilasi kode, gunakan perintah `make`. Atau kita dapat mengompilasi dan menjalankan web server sekaligus dengan perintah `make all`. Secara default, web server akan berjalan pada port `8080`, namun kita dapat mengubahnya melalui konstanta `PORT` pada file `peladen.cpp`.

Kami melakukan benchmarking dengan 10000 requests, menggunakan metode yang sama seperti pengukuran pada Apache sebelumnya. Didapatkan hasil sebagai berikut:

Didapatkan hasil sebagai berikut:

| Benchmark                         | 500B | 20KB |
| -------------                     | ------------- | ------------- |
| Testing Time (s)                  | 1.211 | 1.378 | 
| Average Request Per Second (rps)  | 8259.26 | 7257.83 |
| Average Request Time (s)          | 0.121 | 0.138 |
| Transfer Rate (KB/s)              | 4912.00 | 142541.26 |
| Memory Usage (MB)                 | 1.1 | 0.88 |
