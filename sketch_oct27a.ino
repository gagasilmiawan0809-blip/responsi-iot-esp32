#include <WiFi.h>

// ==========================================
// KONFIGURASI WIFI (Sesuaikan dengan Hotspot Anda)
// ==========================================
const char* ssid     = "POCO X7 Pro";
const char* password = "12345678";

// ==========================================
// DEFINISI PIN SENSOR & AKTUATOR
// ==========================================
const int PIN_LDR = 32; // Digital Input - Sensor Cahaya
const int PIN_PIR = 33; // Digital Input - Sensor Gerak
const int PIN_LED = 27; // Digital Output - LED Indikator

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_LED, OUTPUT);

  // Proses Koneksi ke WiFi
  Serial.println("\n==========================================");
  Serial.print("Menghubungkan ke WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nBERHASIL TERHUBUNG KE WIFI!");
  Serial.print("IP Address ESP32: ");
  Serial.println(WiFi.localIP());
  Serial.println("==========================================\n");
}

void loop() {
  // 1. Pembacaan Status Sensor
  int statusLDR = digitalRead(PIN_LDR); // 1 = Gelap, 0 = Terang
  int statusPIR = digitalRead(PIN_PIR); // 1 = Ada Gerakan, 0 = Tidak Ada

  // 2. Logika Sistem: Jika Gelap DAN Ada Orang, Nyalakan LED
  String statusSistem = "STANDBY (Lampu Mati)";

  if (statusLDR == HIGH && statusPIR == HIGH) {
    statusSistem = "OTOMATIS: LAMPU NYALA (Gelap + Ada Orang)";
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }

  // 3. Tampilkan Hasil Pembacaan Sensor ke Serial Monitor
  Serial.println("=== MONITORING IOT 2 SENSOR ===");
  Serial.print("Status WiFi   : Terhubung\n");
  Serial.print("1. LDR (Cahaya) : "); Serial.println(statusLDR == HIGH ? "Gelap (1)" : "Terang (0)");
  Serial.print("2. PIR (Gerak)  : "); Serial.println(statusPIR == HIGH ? "Ada Orang (1)" : "Kosong (0)");
  Serial.print(">> STATUS KODE  : "); Serial.println(statusSistem);
  Serial.println("===============================\n");

  delay(2000); // Jeda 2 detik antar pembacaan
}