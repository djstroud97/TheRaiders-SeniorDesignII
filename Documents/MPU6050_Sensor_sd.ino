#include <Wire.h>
#include <SPI.h>
#include <SD.h>
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float accAngleX, accAngleY;
float AccErrorX, AccErrorY;
float elapsedTime, currentTime, previousTime;
int c = 0;
int range = 2048; //Based on documentation, this is the value to divide by for +-16g sensitivity
File myFile; //File variable for opening 'datafile.txt'

void setup() {
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission

  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);

  // === SD FileIO Setup Here === //
  //Infinite loop to prevent attempts to writing to file if SD card is unconnected
  if (!SD.begin(10)){
    while(1);
  }

  // Create data file if it doesn't exist
  if(!SD.exists("datafile.txt")){
   myFile = SD.open("datafile.txt", FILE_WRITE);
   myFile.close();
  }
  
  // Call this function if you need to get the IMU error values for your module
  calculate_IMU_error();
  delay(20);
}
void loop() {
  // === Read accelerometer data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / range; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / range; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / range; // Z-axis value
  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)

// === Print values to SD Card === //
  myFile = SD.open("datafile.txt", FILE_WRITE);
  if(myFile){
    myFile.print(AccX);
    myFile.print(" ");
    myFile.print(AccY);
    myFile.print(" ");
    myFile.println(AccZ);
  }
  myFile.close();
}
void calculate_IMU_error() {
  // We can call this function in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / range ;
    AccY = (Wire.read() << 8 | Wire.read()) / range ;
    AccZ = (Wire.read() << 8 | Wire.read()) / range ;
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    c++;
  }
  //Divide the sum by 200 to get the error value
  AccErrorX = AccErrorX / 200;
  AccErrorY = AccErrorY / 200;
  c = 0;
}
