## Kelompok 3

1. Elis Hilmal Muhibah Syawalah - 23552011313
2. Muhammad Fahmi Abdul Majiid - 23552011423
3. Challik Ruben - 23552011333
---

# IoT Smart Flood Detection System

## Deskripsi Project

IoT Smart Flood Detection System merupakan sistem deteksi dini banjir berbasis Internet of Things (IoT) yang dirancang untuk memantau ketinggian air secara real-time menggunakan **Water Level Depth Detection Sensor** dan mikrokontroler **ESP32**. Sistem ini mampu mendeteksi perubahan tinggi permukaan air, menampilkan informasi kondisi banjir melalui **LCD**, mengirimkan data ke server menggunakan protokol **MQTT**, serta memberikan peringatan dini menggunakan **LED indikator** dan **buzzer** sesuai tingkat bahaya yang terdeteksi.

Dengan adanya sistem ini, pengguna dapat memperoleh informasi kondisi banjir secara cepat dan akurat sehingga dapat melakukan tindakan pencegahan sebelum kondisi menjadi lebih serius.

---

## Tujuan Project

1. Membuat sistem deteksi banjir secara otomatis.
2. Memonitor ketinggian air secara real-time.
3. Menampilkan informasi status banjir secara langsung melalui LCD.
4. Memberikan peringatan dini ketika air mencapai batas bahaya.
5. Menerapkan konsep Internet of Things (IoT) pada sistem keamanan lingkungan.
6. Membantu pengguna mengetahui potensi banjir lebih cepat.

---

## Fitur Utama

### 1. Monitoring Ketinggian Air Otomatis
Water Level Depth Detection Sensor digunakan untuk mendeteksi ketinggian air secara otomatis berdasarkan nilai sensor yang terbaca.

### 2. LCD Real-Time Display
LCD digunakan untuk menampilkan nilai ketinggian air dan status kondisi banjir secara langsung sehingga pengguna dapat melihat informasi tanpa membuka dashboard monitoring.

### 3. Real-Time Data Transmission
Data sensor dikirim secara real-time menggunakan protokol MQTT melalui jaringan WiFi.

### 4. Smart Alarm System
Buzzer akan aktif dengan pola alarm yang berbeda sesuai tingkat bahaya banjir.

### 5. LED Status Indicator
LED digunakan sebagai indikator visual untuk menunjukkan status kondisi air saat ini.

### 6. IoT Monitoring
Data dapat dipantau melalui dashboard monitoring seperti MQTT Explorer atau platform IoT lainnya.

---

## Komponen Project

| No | Komponen | Jumlah |
|----|-----------|---------|
| 1 | ESP32 DevKit | 1 |
| 2 | Water Level Depth Detection Sensor | 1 |
| 3 | LCD 16×2 I2C | 1 |
| 4 | LED Hijau | 1 |
| 5 | LED Kuning | 1 |
| 6 | LED Merah | 1 |
| 7 | LED Hitam | 1 |
| 8 | Active Buzzer | 1 |
| 9 | Kabel Jumper | Secukupnya |

---

## Cara Kerja Sistem

1. Water Level Depth Detection Sensor mendeteksi ketinggian air.
2. ESP32 membaca dan memproses data dari sensor.
3. Sistem menentukan status kondisi banjir berdasarkan nilai sensor.
4. LCD menampilkan nilai sensor dan status kondisi secara langsung.
5. LED indikator menyala sesuai tingkat bahaya.
6. Buzzer memberikan alarm sesuai kondisi yang terdeteksi.
7. Data dikirim ke MQTT Broker melalui jaringan WiFi.
8. Pengguna dapat memantau data secara real-time melalui dashboard IoT.

---

## Status Kondisi Banjir

| Jarak Air | Status | LED | Buzzer |
|--------------|---------|------|----------|
| ≤ 10 cm  | Aman | Hijau | Mati |
| 11 – 50 cm | Waspada | Kuning | Bunyi Lambat |
| 51 – 100 cm  | Siaga | Merah | Bunyi Sedang |
| > 100 cm | Darurat | Hitam | Bunyi Terus-Menerus |

> **Catatan:** Rentang nilai sensor dapat disesuaikan berdasarkan hasil kalibrasi Water Level Depth Detection Sensor yang digunakan.

---

## Penjelasan Sistem

Water Level Depth Detection Sensor bekerja dengan mendeteksi keberadaan dan tingkat ketinggian air melalui perubahan nilai analog yang dihasilkan sensor. Semakin tinggi permukaan air yang mengenai sensor, maka nilai pembacaan sensor akan semakin besar.

Berdasarkan nilai tersebut, sistem mengelompokkan kondisi banjir menjadi empat tingkat, yaitu:

- **Aman**, ketika permukaan air masih rendah.
- **Waspada**, ketika air mulai meningkat.
- **Siaga**, ketika ketinggian air sudah berpotensi menimbulkan banjir.
- **Darurat**, ketika air mencapai batas kritis dan memerlukan tindakan segera.

LCD akan menampilkan informasi status dan nilai sensor secara langsung, sedangkan MQTT digunakan untuk mengirimkan data ke sistem monitoring berbasis IoT.

---

## Konsep Project

Project ini mengusung konsep **Smart Environment** dengan memanfaatkan teknologi Internet of Things (IoT) untuk mitigasi bencana banjir.

1. Menerapkan konsep Internet of Things (IoT) pada sistem deteksi dini banjir.
2. Menggunakan Water Level Depth Detection Sensor untuk mendeteksi ketinggian air.
3. ESP32 berfungsi sebagai pusat pemrosesan data sensor.
4. Menampilkan informasi kondisi banjir secara langsung melalui LCD.
5. Mengirimkan data sensor secara real-time menggunakan protokol MQTT melalui WiFi.
6. MQTT Broker digunakan sebagai media komunikasi antara perangkat IoT dan sistem monitoring.
7. LED indikator memberikan informasi visual mengenai tingkat bahaya banjir.
8. Buzzer berfungsi sebagai alarm peringatan dini.
9. Sistem memiliki empat tingkat status, yaitu Aman, Waspada, Siaga, dan Darurat.
10. Dashboard monitoring memungkinkan pengguna memantau kondisi banjir dari jarak jauh.
11. Mendukung implementasi Smart Environment dan sistem mitigasi bencana berbasis teknologi IoT.
12. Dapat dikembangkan lebih lanjut dengan fitur notifikasi otomatis, penyimpanan data cloud, integrasi aplikasi mobile, serta analisis data historis.

---

## Model Struktur Rangkaian dan Penjelasan Sistem

![Rangkaian](Assets/image.png)

Dalam simulasi pada Website WOKWI bentuk struktur rangkaian sistem akan seperti diatas, dengan menggunakan protokol MQTT sebagai perantara pengirim data ke server.
Dimana pada sistem ini program akan menggunakan sensor ultrasonic untuk mendeteksi volume air, dibantu dengan tambahan RTOS dan security (encrypt & decrypt).
4 Led pada sistem digunakan sebagai tolak ukur keadaan volume air, setiap warna menyesuaikan dengan situasi banjir.

