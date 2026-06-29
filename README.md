# IoT Smart Flood Detection System

## Kelompok 3

1. Elis Hilmal Muhibah Syawalah - 23552011313
2. Muhammad Fahmi Abdul Majiid - 23552011423
3. Challik Ruben - 23552011333

---

## Deskripsi Project

IoT Smart Flood Detection System merupakan sistem deteksi dini banjir berbasis Internet of Things (IoT) yang dirancang untuk memantau kondisi ketinggian air secara real-time menggunakan **sensor ultrasonik**, **water sensor**, dan mikrokontroler **ESP32**.

Sensor ultrasonik digunakan untuk mengukur jarak antara sensor dengan permukaan air, sedangkan water sensor digunakan untuk mendeteksi keberadaan air sebagai pendukung pembacaan kondisi banjir. Sistem ini mampu menampilkan informasi kondisi banjir melalui **LCD**, mengirimkan data ke server menggunakan protokol **MQTT**, serta memberikan peringatan dini menggunakan **LED indikator** dan **buzzer** sesuai tingkat bahaya yang terdeteksi.

Selain itu, sistem juga menggunakan konsep **RTOS (Real-Time Operating System)** untuk membagi proses kerja ESP32 menjadi beberapa task, sehingga pembacaan sensor, tampilan LCD, kontrol LED, buzzer, dan pengiriman data MQTT dapat berjalan lebih teratur.

---

## Tujuan Project

1. Membuat sistem deteksi banjir secara otomatis.
2. Memonitor ketinggian air secara real-time.
3. Menampilkan informasi status banjir secara langsung melalui LCD.
4. Mengirimkan data sensor ke server monitoring menggunakan MQTT.
5. Memberikan peringatan dini ketika air mencapai batas bahaya.
6. Menerapkan konsep RTOS agar sistem berjalan lebih teratur dan responsif.
7. Membantu pengguna mengetahui potensi banjir lebih cepat.

---

## Fitur Utama

### 1. Monitoring Ketinggian Air Otomatis

Sensor ultrasonik digunakan untuk mengukur jarak permukaan air secara otomatis. Semakin kecil jarak yang terbaca, maka semakin tinggi permukaan air mendekati sensor.

### 2. Water Sensor Detection

Water sensor digunakan untuk mendeteksi keberadaan air sebagai data tambahan agar sistem dapat mengetahui apakah area sensor sudah terkena air atau belum.

### 3. LCD Real-Time Display

LCD digunakan untuk menampilkan nilai sensor dan status kondisi banjir secara langsung, sehingga pengguna dapat melihat informasi tanpa membuka dashboard monitoring.

### 4. Real-Time Data Transmission dengan MQTT

Data sensor dikirim secara real-time menggunakan protokol MQTT melalui jaringan WiFi. Data yang dikirim dapat berupa nilai sensor ultrasonik, nilai water sensor, dan status kondisi banjir.

### 5. RTOS Task Management

Sistem menggunakan konsep RTOS untuk membagi proses kerja ESP32 menjadi beberapa task. Dengan RTOS, proses pembacaan sensor, tampilan LCD, kontrol LED dan buzzer, serta pengiriman data MQTT dapat berjalan lebih teratur.

### 6. Smart Alarm System

Buzzer akan aktif dengan pola alarm yang berbeda sesuai tingkat bahaya banjir.

### 7. LED Status Indicator

LED digunakan sebagai indikator visual untuk menunjukkan status kondisi air. Sistem menggunakan 3 LED, yaitu hijau, kuning, dan merah.

### 8. IoT Monitoring

Data dapat dipantau melalui dashboard monitoring seperti MQTT Explorer atau platform IoT lainnya.

---

## Komponen Project

| No | Komponen                          | 
| -- | --------------------------------- | 
| 1  | ESP32 DevKit                      | 
| 2  | Sensor Ultrasonik HC-SR04         | 
| 3  | Water Sensor / Water Level Sensor | 
| 4  | LCD 16×2 I2C                      | 
| 5  | LED Hijau                         | 
| 6  | LED Kuning                        | 
| 7  | LED Merah                         | 
| 8  | Active Buzzer                     | 
| 9  | Kabel Jumper                      | 
| 10 | BreadBoard                        | 
| 11 | Resistor 220 ohm                  | 

---

## Cara Kerja Sistem

1. Sensor ultrasonik mengukur jarak antara sensor dengan permukaan air.
2. Water sensor mendeteksi keberadaan air sebagai pendukung pembacaan kondisi.
3. ESP32 membaca dan memproses data dari kedua sensor.
4. RTOS membagi proses sistem menjadi beberapa task.
5. Sistem menentukan status kondisi banjir berdasarkan nilai sensor.
6. LCD menampilkan nilai sensor dan status kondisi secara langsung.
7. LED indikator menyala sesuai tingkat bahaya.
8. Buzzer memberikan alarm sesuai kondisi yang terdeteksi.
9. Data dikirim ke MQTT Broker melalui jaringan WiFi.
10. Pengguna dapat memantau data secara real-time melalui dashboard IoT.

---

## Status Kondisi Banjir

| Jarak Permukaan Air | Status  | LED                                             | Buzzer              |
| ------------------- | ------- | ----------------------------------------------- | ------------------- |
| > 18 cm            | Aman    | LED hijau menyala                               | Mati                |
| 12 – 18 cm         | Waspada | LED kuning menyala                              | Bunyi lambat        |
| 6 – 12 cm          | Siaga   | LED merah menyala                               | Bunyi sedang        |
| ≤ 6 cm             | Darurat | LED hijau, kuning, dan merah menyala bergantian | Bunyi terus-menerus |

**Keterangan:**
Semakin kecil jarak yang terbaca oleh sensor ultrasonik, maka semakin tinggi permukaan air mendekati sensor. Water sensor digunakan sebagai pendukung untuk memastikan adanya air pada area deteksi.

---

## Penjelasan Sistem

Sensor ultrasonik bekerja dengan mengirimkan gelombang suara dan menerima pantulannya dari permukaan air. Dari hasil pantulan tersebut, ESP32 dapat menghitung jarak antara sensor dengan permukaan air.

Water sensor digunakan untuk mendeteksi keberadaan air melalui perubahan nilai analog. Ketika sensor terkena air, nilai pembacaan akan berubah dan dapat digunakan sebagai data tambahan dalam menentukan kondisi banjir.

Berdasarkan hasil pembacaan sensor, sistem mengelompokkan kondisi banjir menjadi empat tingkat, yaitu:

* **Aman**, ketika permukaan air masih rendah.
* **Waspada**, ketika air mulai meningkat.
* **Siaga**, ketika ketinggian air sudah berpotensi menimbulkan banjir.
* **Darurat**, ketika air mencapai batas kritis dan memerlukan tindakan segera.

LCD akan menampilkan informasi status dan nilai sensor secara langsung. LED digunakan sebagai indikator visual, sedangkan buzzer digunakan sebagai alarm peringatan. Data sensor juga dikirim melalui MQTT agar dapat dipantau secara real-time melalui dashboard IoT.

---

## MQTT dan RTOS

Sistem IoT Smart Flood Detection menggunakan **MQTT** sebagai protokol komunikasi untuk mengirimkan data sensor dari ESP32 ke dashboard monitoring secara real-time. MQTT digunakan karena ringan, cepat, dan cocok untuk perangkat IoT seperti ESP32.

Data yang dikirim melalui MQTT meliputi:

1. Nilai jarak dari sensor ultrasonik.
2. Nilai pembacaan water sensor.
3. Status kondisi banjir.
4. Informasi kondisi LED dan buzzer.

Selain MQTT, sistem juga menggunakan konsep **RTOS (Real-Time Operating System)**. RTOS digunakan untuk membagi proses kerja ESP32 menjadi beberapa task agar sistem dapat berjalan lebih teratur dan responsif.

Pembagian task pada sistem ini meliputi:

1. Task membaca sensor ultrasonik.
2. Task membaca water sensor.
3. Task menampilkan data ke LCD.
4. Task mengontrol LED dan buzzer.
5. Task mengirim data ke MQTT Broker.

Dengan adanya RTOS, beberapa proses pada sistem dapat berjalan secara bersamaan secara terjadwal. Hal ini membuat sistem lebih stabil, karena pembacaan sensor, tampilan LCD, alarm, dan pengiriman data MQTT dapat dikelola dengan lebih baik.

---

## Konsep Project

Project ini mengusung konsep **Smart Environment** dengan memanfaatkan teknologi Internet of Things (IoT) untuk mitigasi bencana banjir.

1. Menerapkan konsep Internet of Things pada sistem deteksi dini banjir.
2. Menggunakan sensor ultrasonik untuk mengukur jarak permukaan air.
3. Menggunakan water sensor untuk mendeteksi keberadaan air.
4. ESP32 berfungsi sebagai pusat pemrosesan data sensor.
5. Menampilkan informasi kondisi banjir secara langsung melalui LCD.
6. Mengirimkan data sensor secara real-time menggunakan protokol MQTT melalui WiFi.
7. MQTT Broker digunakan sebagai media komunikasi antara perangkat IoT dan sistem monitoring.
8. RTOS digunakan untuk membagi proses kerja sistem menjadi beberapa task.
9. LED indikator memberikan informasi visual mengenai tingkat bahaya banjir.
10. Buzzer berfungsi sebagai alarm peringatan dini.
11. Sistem memiliki empat tingkat status, yaitu Aman, Waspada, Siaga, dan Darurat.
12. Dashboard monitoring memungkinkan pengguna memantau kondisi banjir dari jarak jauh.
13. Sistem dapat dikembangkan lebih lanjut dengan fitur notifikasi otomatis, penyimpanan data cloud, integrasi aplikasi mobile, security data, serta analisis data historis.

---

## Model Struktur Rangkaian dan Penjelasan Sistem

![Rangkaian](Assets/image.png)

Dalam simulasi pada website WOKWI, bentuk struktur rangkaian sistem dibuat menggunakan ESP32 sebagai pusat kendali, sensor ultrasonik untuk mengukur jarak permukaan air, serta water sensor sebagai pendeteksi keberadaan air.

Sistem ini menggunakan protokol **MQTT** sebagai media komunikasi antara ESP32 dan server monitoring. Data yang dikirim melalui MQTT berupa nilai sensor ultrasonik, nilai water sensor, dan status kondisi banjir.

Selain itu, sistem juga menggunakan konsep **RTOS** untuk membagi proses kerja ESP32 menjadi beberapa task. Dengan RTOS, proses pembacaan sensor, tampilan LCD, kontrol LED dan buzzer, serta pengiriman data MQTT dapat berjalan lebih terjadwal dan responsif.

Pada sistem ini, digunakan 3 LED sebagai indikator kondisi banjir, yaitu:

* LED hijau untuk kondisi **Aman**.
* LED kuning untuk kondisi **Waspada**.
* LED merah untuk kondisi **Siaga**.
* Pada kondisi **Darurat**, LED hijau, kuning, dan merah akan menyala secara bergantian sebagai tanda bahaya tertinggi.

Selain LED, buzzer juga digunakan sebagai alarm peringatan dini. Semakin berbahaya kondisi air, maka pola bunyi buzzer akan semakin cepat hingga menyala terus-menerus pada kondisi darurat.

---

## Kesimpulan

IoT Smart Flood Detection System merupakan sistem deteksi dini banjir berbasis ESP32 yang memanfaatkan sensor ultrasonik dan water sensor untuk memantau kondisi air secara real-time. Sistem ini dilengkapi dengan LCD, LED indikator, buzzer, MQTT, dan RTOS sehingga dapat memberikan informasi kondisi banjir secara langsung, mengirimkan data ke dashboard monitoring, serta mengatur proses kerja sistem dengan lebih terstruktur.

Dengan adanya sistem ini, pengguna dapat mengetahui potensi banjir lebih cepat dan melakukan tindakan pencegahan sebelum kondisi menjadi lebih berbahaya.

---

## Dokumetasi 

## 🎥 Kerja Kelompok

| Kerja Kelompok 1 | Kerja Kelompok 2 | Kerja Kelompok 3 |
|:----------------:|:----------------:|:----------------:|
| <img src="Assets/kerkom1.gif" width="350"> | <img src="Assets/kerkom2.gif" width="350"> | <img src="Assets/kerkom3.gif" width="350"> |

### 🎥 Finish Project

### 🎥 Website
