#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#include "controlSystem.h"
#include "module.h"
#include "bodyKinematics.h"
#include "kaki.h"
#include "algorithm.h"`
#include "komponen.h"
#include "prog.h"
#include "prog_kanan.h"
bool bag = 0;  //set robot pada bagian 0 = kiri dan 1 = kanan#include <Wire.h>

int j, k, l, m, n, o, p;
char keyInput;

void bacaLidar() {
  // Serial.println(bacaKompas());
  Serial.print("lid0 : ");
  Serial.print(lid0);
  Serial.print("   lid1 : ");
  Serial.print(lid1);
  Serial.print("   lid2 : ");
  Serial.print(lid2);
  Serial.print("   lid3 : ");
  Serial.print(lid3);
  Serial.print("   lid4 : ");
  Serial.print(lid4);
  Serial.print("   lid5 : ");
  Serial.println(lid5);
}

void tungguTombolStartDanPrintNilaiSensor() {
  while (digitalRead(pb) == 1) {
   // bacaLidar();
    // Zoff = -115;
    // posisiAwal = 68;
    // lebarLangkah = 25;    //25
    // tinggiLangkah = 115;  //115
    // Yoff = -20;
    // roll_x(-6);
    // servo_naik_tangga();
     passData(0);
    // followDindingKanan(14, 15);
  }
}

void setup() {
  Serial.begin(9600);
  //setupSensor();
  setupKaki();
  setupBody();
  servo_park_home();
  // servo_ambil_korban_0();
  passData(0);
}

void loop() {
  Serial.println(digitalRead(pb));
  
  /*
  //passData(1);
  if (Serial.available() > 0) {
    keyInput = Serial.read();
    Serial.print("keyInput : ");
    Serial.println(keyInput);
    switch (keyInput) {
      case 'a':  //kiri
        input = 2;
        break;
      case 'd':  //kanan
        input = 4;
        break;
      case 'e':  //pivot kanan
        input = 6;
        break; 
      case 'w':  //maju
        input = 1;
        break;
      case 's':  //mundur
        input = 3;
        break; 
      case 'q':  //pivot kiri
        input = 5;
        break;
      case ' ':
        input = 50;
        break;
      }
    passData(input);
  }
   */
  tungguTombolStartDanPrintNilaiSensor();
 // passData(1);
  /*if (bag == 0) {
    menujuKorban1();
    ambilKorban1();
    menujuSz1();
    taruhKorban1();
    menujuKorban2();
    ambilKorban2();
    menujuSz2();
    taruhKorban2();
    menujuKorban3();
    ambilKorban3();
    menujuKorban4();
    ambilKorban4();
    menujuSz3();
    menujuTangga();
    naikTangga();
    menujuSz4();
    taruhKorban4();
    menujuKorban5();
    ambilKorban5();
    menujuSz5();
    taruhKorban5();
  } else {
    menujuKorban1_1();
    ambilKorban1_1();
    menujuSz1_1();
    taruhKorban1_1();
    menujuKorban2_1();
    ambilKorban2_1();
    menujuSz2_1();
    taruhKorban2_1();
    menujuKorban3_1();
    ambilKorban3_1();
    menujuKorban4_1();
    ambilKorban4_1();
    menujuSz3_1();
    menujuTangga_1();
    naikTangga_1();
    menujuSz4_1();
    taruhKorban4_1();
    menujuKorban5_1();
    ambilKorban5_1();
    menujuSz5_1();
    taruhKorban5_1();*/
  }
  // while (1) {
  //   passData(50);
  //   servo_park_home();
  //   Serial.println("sudah");
  // }*/
