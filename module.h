// sensor ToF time of flight, berikut adalah informasi  sensor ToF range 4-4M :
// https://robojax.com/learn/arduino/?vid=robojax_VL53L1X_distance_sensor
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "SparkFun_VL53L1X.h"
#define lid0 cekJarak4M(0)
#define lid1 cekJarak4M(1)
#define lid2 cekJarak4M(2)
#define lid3 cekJarak4M(3)
#define lid4 cekJarak4M(4)
#define lid5 cekJarak4M(5)
#define ir 28
#define pb 30

Adafruit_MPU6050 mpu;
QMC5883LCompass compass;
SFEVL53L1X distanceSensor;

const int MPU = 0x68;  // MPU6050 I2C address

void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

int cekJarak4M(uint8_t lid) {
  TCA9548A(lid);
  distanceSensor.startRanging();  //Write configuration bytes to initiate measurement
  // while (!distanceSensor.checkForDataReady()) delay(1);
  int distance = distanceSensor.getDistance();  //Get the result of the measurement from the sensor
  // distanceSensor.clearInterrupt();
  // distanceSensor.stopRanging();
  int distance1 = kalmanFilter(distance, 1000, 200);  //semakin besar parameter 2 semakin kecil gapnya
                                                      //semakin besar parameter 3 semakin besar nilainya
  // Serial.print(distance);
  // Serial.print(" ");
  // Serial.print(distance1);
  return distance1;
}

void kompasInit() {
  compass.init();
  // compass.setCalibration(-1093, 253, -1612, -417, 411, 815); //lalu
  compass.setCalibration(-248, 375, -975, -315, 387, 550);
  compass.setSmoothing(20, true);
}

int bacaKompas() {
  int degree, degree1;
  // Read compass values
  compass.read();
  // Get Azimuth reading
  degree = compass.getAzimuth();
  if (degree < 0) degree = degree + 360;
  // Serial.print(degree);
  degree1 = kalmanFilter(degree, 25, 30);
  // Serial.print(" ");
  //Serial.print(degree1);
  return degree1;
  // return degree;
}

void setupSensor() {
  while (!Serial) delay(10);  // will pause Zero, Leonardo, etc until serial console opens
  Wire.begin();
  // qmc.init();
  kompasInit();
  pinMode(ir, INPUT);
  pinMode(pb, INPUT_PULLUP);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  TCA9548A(0);
  if (distanceSensor.begin() != 0) Serial.println("Sensor failed to begin. Please check wiring. Freezing...");

  TCA9548A(1);
  if (distanceSensor.begin() != 0) Serial.println("Sensor failed to begin. Please check wiring. Freezing...");

  TCA9548A(2);
  if (distanceSensor.begin() != 0) Serial.println("Sensor failed to begin. Please check wiring. Freezing...");

  TCA9548A(3);
  if (distanceSensor.begin() != 0) Serial.println("Sensor failed to begin. Please check wiring. Freezing...");

  TCA9548A(4);
  if (distanceSensor.begin() != 0) Serial.println("Sensor failed to begin. Please check wiring. Freezing...");

  TCA9548A(5);
  if (distanceSensor.begin() != 0) Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
  Serial.print("halo");

  // if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for (;;)
  //     ;
  // }
}
/*
void cekOled(char teks) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4, 10);
  // Display static text
  display.println(teks);
  display.display();
}
*/
int cekIr() {
  int bacaIr = 0;
  bacaIr = digitalRead(ir);
  Serial.println(bacaIr);
  return bacaIr;
}
/*
int bacaKompas() {
  int x, y, z;
  int degree, degree1;
  qmc.read(&x, &y, &z, &degree);
  // Serial.print(degree);
  degree1 = kalmanFilter(degree, 40, 30);
  // Serial.print(" ");
  //Serial.print(degree1);
  return degree;
  // return degree;
}
*/
int cekMpu() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  int derajatKompas = ((a.acceleration.y * 100) * -1);
  Serial.print(derajatKompas);
  int derajatKompas1 = kalmanFilter(derajatKompas, 100, 20);  //semakin besar parameter 2 semakin kecil gapnya
                                                              //semakin besar parameter 3 semakin besar nilainya
  Serial.print(" ");
  Serial.println(derajatKompas1);
  return derajatKompas1;
}

int cekKompasMpu() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  int derajatKompas = (a.acceleration.x);
  // Serial.print(derajatKompas);
  int derajatKompas1 = kalmanFilter(derajatKompas, 100, 20);  //semakin besar parameter 2 semakin kecil gapnya
                                                              //semakin besar parameter 3 semakin besar nilainya
  Serial.print(" ");
  // Serial.println(derajatKompas1);
  return derajatKompas1;
}