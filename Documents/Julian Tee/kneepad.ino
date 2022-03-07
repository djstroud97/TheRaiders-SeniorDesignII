#include <Wire.h>
const int sensor = 0x68;    //0x68 is the I2C address for the MPU6050, this allows the program to know we are using the 6050 out of the MPU series sensors
const int range = 1024; //Based on documentation, this is the value to divide by for +-16g sensitivity
float AccX, AccY, AccZ;     //float variables for Acceleration in X,Y,Z axis
float accAngleX, accAngleY; 
float AccErrorX, AccErrorY; 
float elapsedTime, currentTime, previousTime;
int c = 0;
void setup() {
  Serial.begin(19200);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(sensor);    // starts communication with sensor 
  Wire.write(0x6B);                  // Talk to the register 6B (power register)
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission
  Wire.beginTransmission(sensor);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x18);                  //Set the register bit as 0x18 to select full range (16G) as shown in datasheet
  Wire.endTransmission(true);

  calculate_IMU_error();// run this function first so we can use it to correct our readings
  delay(20);
}
void loop() {
  Wire.beginTransmission(sensor);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  AccX = (Wire.read() << 8 | Wire.read()) / range;
  AccY = (Wire.read() << 8 | Wire.read()) /range; 
  AccZ = (Wire.read() << 8 | Wire.read()) / range; 
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; //Math learned online on how to convert angular acceleration into resultant acceleration in each axis
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; 
 

  // Print the values on the serial monitor
  Serial.print(AccX);
  Serial.print("/");
  Serial.print (AccY);
  Serial.print("/");
  Serial.println(AccZ);
}
void calculate_IMU_error() {
// This function was obtained online in order to combat "drift" from the sensor. It essentially runs the sensor to get data 200 times and calculates the error and drift to implements it in the main loop to 
//ensure accurate readings and measurements
  while (c < 200) {
    Wire.beginTransmission(sensor);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(sensor, 6, true);
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
  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);

}
