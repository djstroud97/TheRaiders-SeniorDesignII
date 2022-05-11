#include <Wire.h>
#include <SPI.h>
#include <SD.h>
const int MPU = 0x68; //0x68 is the I2C address for the MPU6050, this allows the program to know we are using the 6050 out of the MPU series sensors
float AccX, AccY, AccZ;     //float variables for Acceleration in X,Y,Z axis
float accAngleX, accAngleY;
float AccErrorX, AccErrorY;
float elapsedTime, currentTime, previousTime;
int c = 0;
int range = 2048; //Based on documentation, this is the value to divide by for +-16g sensitivity
File myFile; //File variable for opening 'datafile.txt'

void setup() {
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);    // starts communication with sensor 
  Wire.write(0x6B);                  // Talk to the register 6B (power register)
  Wire.write(0x00);                  // reset the sensor
  Wire.endTransmission(true);        //end the transmission
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bit as 0x18 to select full range (16G) as shown in datasheet
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
  // Obtain Accelerometer data
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); //Read data from 6 registers as each axis uses 2 registers
  AccX = (Wire.read() << 8 | Wire.read()) / range; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / range; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / range; // Z-axis value


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
// This function was obtained online in order to combat "drift" from the sensor. It essentially runs the sensor to get data 200 times and calculates the error and drift to implements it in the main loop to 
//ensure accurate readings and measurements
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
