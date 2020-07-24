#include <EEPROM.h>

int jam_off = 0;
int menit_off = 5 ;
int jam_on = 0;
int menit_on = 10;

int jam = 0;
int menit = 0;
int detik = 0;

int wajib_on = 0; // 1 : on | -1 : off

int pin_relay = 13;
int pin_tombol = 12;

// EEPROM ADDR
int jam_addr = 0;
int menit_addr = 1;
int detik_addr = 2;

long end_millis = 1000;

void setup() {
  set_waktu();
  Serial.begin(9600);
  pinMode(pin_relay, OUTPUT);
  pinMode(pin_tombol, INPUT);
  load_data();
}

void loop() {
  cek_millis();
  waktu_sekarang();
  if (wajib_on == 0)  {
    cek_tombol();
  } else if (wajib_on == 1) {
    digitalWrite(pin_relay, LOW);
  }
  
  cek_waktu_on();
}

void set_waktu()  {
  jam = 9;
  menit = 00;
  detik = 45;
  save_data();
}

void cek_waktu_on() {
  if ((jam == 16) && (menit == 30)) {
    wajib_on = 1;
  }
  if ((jam == 7) && (menit == 30)) {
    wajib_on = 1;
  }
}

void cek_waktu_off() {
  if ((jam == 18) && (menit == 00)) {
    wajib_on = 0;
  }
  if ((jam == 8) && (menit == 45)) {
    wajib_on = 0;
  }
}

void cek_tombol() {
  digitalWrite(pin_relay, digitalRead(pin_tombol));
}

void waktu_sekarang()  {
  String text_sekarang = String(jam) + ":" + String(menit) + ":" + String(detik);
  Serial.println(text_sekarang);
  save_data();
} 

void load_data()  {
  jam = EEPROM.read(jam_addr);
  menit = EEPROM.read(menit_addr);
  detik = EEPROM.read(detik_addr);
  waktu_sekarang();
}

void save_data()  {
  EEPROM.write(jam_addr, jam);
  EEPROM.write(menit_addr, menit);
  EEPROM.write(detik_addr, detik);
}

void cek_millis() {
  if (millis() > end_millis)  {
    end_millis += 1000;
    detik += 1;
  }
  if (detik > 59) {
    detik = 0;
    menit += 1;
  }
  if (menit > 59) {
    menit = 0;
    jam += 1;
  }
  if (jam > 23) {
    jam = 0;
  }
}
