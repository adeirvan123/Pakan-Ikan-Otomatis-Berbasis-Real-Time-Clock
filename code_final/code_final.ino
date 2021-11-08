//RTC
#include <Adafruit_I2CDevice.h>
#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
float suhu;

//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Servo atau Mekanik
#include <Servo.h>
Servo mekanik;

void setup () {
  Serial.begin(9600);

  //LCD
  lcd.begin();

  //Servo
  mekanik.attach(4);//fungsi menampung mekanik ke pin 4
  mekanik.write(0);
    
  //RTC
  if (! rtc.begin()) {
    Serial.println("RTC Tidak Ditemukan");
    Serial.flush();
    abort();
  }

  //Atur Waktu
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop () {
  //RTC
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
  suhu    = rtc.getTemperature();
  Serial.println(String() + hari + ", " + tanggal + "-" + bulan + "-" + tahun);
  Serial.println(String() + jam + ":" + menit + ":" + detik);
  Serial.println(String() + "Suhu: " + suhu + " C");
  Serial.println();

  //LCD
  lcd.setCursor(0,0);
  lcd.print(String() + hari + "," + tanggal + "-" + bulan + "-" + tahun);
  lcd.setCursor(0,1);
  lcd.print("Kel.06");
  lcd.print("  ");
  lcd.print(String() + jam + ":" + menit + ":" + detik);

  

  //kondisi pemberian pakan
  if(jam == 20 & menit == 25 & detik == 50) {
    kasih_pakan(10);
  }
  
  if(jam == 20 & menit == 26 & detik == 20) {
  kasih_pakan(15);
  }
}

void kasih_pakan(int jumlah){
 for(int i=1; i<=jumlah; i++) {
  mekanik.write(180);
  delay(200);
  mekanik.write(0);
  delay(200);
 }

}
