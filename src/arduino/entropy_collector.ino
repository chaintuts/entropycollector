/* This file contains a simple accelerometer entropy logger
 *  
 *  Author: Josh McIntyre
 */
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10
#define CARD 4

// Module-level variables
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
File entropy_log;
const String ENTROPY_LOG_NAME = "entropy.txt";

// Initialize components
void setup()
{
  
  // Set up the LED light
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);

  // Set up the accelerometer
  if (! lis.begin(0x18))
  {
    error(6);
  }

  // Use the most sensitive range - 2G
  lis.setRange(LIS3DH_RANGE_2_G);
  lis.setDataRate(LIS3DH_DATARATE_50_HZ);

  // Set up the SD card logging
  if (! SD.begin(CARD))
  {
    error(2);
  }

  if (SD.exists(ENTROPY_LOG_NAME))
  {
    SD.remove(ENTROPY_LOG_NAME);
  }

  entropy_log = SD.open(ENTROPY_LOG_NAME, FILE_WRITE);
  if (! entropy_log)
  {
    error(4);
  }

  // Turn off the red LED since there is no known error
  digitalWrite(13, HIGH);
}

// The main run loop for the program
void loop()
{
  // Turn on the indicator LED
  digitalWrite(8, HIGH);

  // Read the accelerometer data
  uint16_t acl_data = get_acl_data();

  // Log the data to SD card
  entropy_log.print(acl_data, HEX);
  entropy_log.flush();

  // Turn off the indicator
  delay(100);
  digitalWrite(8, LOW);

  // Wait for a bit
  delay(200);

}

// Get data from the accelerometer as a string
// This will return an integer comprised of bits from the accelerometer x,y,z
uint16_t get_acl_data()
{
  // Read from the accelerometer
  lis.read();

  // The lis.read() operation returns a tuple of "normalized" readings from each axis 
  // between -32768 and 32767 (16 bit signed values)
  // We're using 2G, the most sensitive range to try and get the most random data possible
  // Combine bits from the 3 axes into 1 16 bit entry using a simple xor
  // This does not do anything special cryptographically speaking, 
  // it's just a way to combine the bits of each axis into one reading
  return lis.x ^ lis.y ^ lis.z;

}

// From learn.adafruit.com - a simple error code blink
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}
