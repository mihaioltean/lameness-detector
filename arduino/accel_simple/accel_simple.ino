#include <Wire.h>

#define DEVICE (0x53) // Device address as specified in data sheet 

byte _buff[6];

char POWER_CTL = 0x2D;	//Power Control Register
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32;	//X-Axis Data 0
char DATAX1 = 0x33;	//X-Axis Data 1
char DATAY0 = 0x34;	//Y-Axis Data 0
char DATAY1 = 0x35;	//Y-Axis Data 1
char DATAZ0 = 0x36;	//Z-Axis Data 0
char DATAZ1 = 0x37;	//Z-Axis Data 1

#define XL345_OVERRUN              0x01
#define XL345_WATERMARK            0x02
#define XL345_FREEFALL             0x04
#define XL345_INACTIVITY           0x08
#define XL345_ACTIVITY             0x10
#define XL345_DOUBLETAP            0x20
#define XL345_SINGLETAP            0x40
#define XL345_DATAREADY            0x80

#define XL345_INT_SOURCE      0x30

//#define READ_SERIAL

//int max_sensitivity[4] = {282.0, 141.0, 71.0, 35.0};

#define max_g 0

  #ifdef READ_SERIAL
  unsigned long prev_time;
  #endif
//-------------------------------------------------------------------------------------
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output. Make sure you set your Serial Monitor to the same!
  //  Serial.print("init");

  //Put the ADXL345 into +/- 4G range by writing the value 0x01 to the DATA_FORMAT register.
  writeTo(DATA_FORMAT, max_g);
  //Put the ADXL345 into Measurement Mode by writing 0x08 to the POWER_CTL register.
  writeTo(POWER_CTL, 0x08);
  // clear the serial buffer
  #ifdef READ_SERIAL
  int bytes_available = Serial.available();
  if (bytes_available){
    char buff[64];
    Serial.readBytes(buff, bytes_available);
  }
  prev_time = millis();
  #endif
  
}
//-----------------------------------------------------------------------------------------
void loop()
{
  readAccel(); // read the x/y/z tilt
  delay(10); // only read every ... seconds
  
  #ifdef READ_SERIAL
  unsigned long current_time = millis();
  if (current_time -prev_time > 1000){
    prev_time = current_time;
    int bytes_available = Serial.available();
    if (bytes_available){
      // read one byte
      char buff[1];
      Serial.readBytes(buff, 1);
      if ((buff[0] >= 0) && (buff[0] <= 3))
        writeTo(DATA_FORMAT, buff[0]);      
    }
  }
  #endif
  
}
//------------------------------------------------------------------------
void do_pack(char* out, int x, char axis) {
  char r = x % 0x20;
  char c = x / 0x20;

  c <<= 3;
  r <<= 3;
  c |= axis << 1;
  r |= axis << 1;
  r |= 1;


  out[0]=c;
  out[1]=r;
}
//-----------------------------------------------------------------------
bool readAccel() {
  uint8_t howManyBytesToRead = 6;
  byte statusu;
  readFrom(XL345_INT_SOURCE, 1, &statusu);
  if (statusu & XL345_DATAREADY){
    readFrom( DATAX0, howManyBytesToRead, _buff); //read the acceleration data from the ADXL345
    writeTo(XL345_INT_SOURCE, 0);

    // each axis reading comes in 10 bit resolution, ie 2 bytes.  Least Significat Byte first!!
    // thus we are converting both bytes in to one int

    int x = (((int)_buff[1]) << 8) | _buff[0];
    int y = (((int)_buff[3]) << 8) | _buff[2];
    int z = (((int)_buff[5]) << 8) | _buff[4];

//    if ((x >= -max_sensitivity[max_g]) && (x <= max_sensitivity[max_g]) && (y >= -max_sensitivity[max_g]) && (y <= max_sensitivity[max_g]) && (z >= -max_sensitivity[max_g]) && (z <= max_sensitivity[max_g])){ 
      char out[2];
      do_pack(out, x, 1);
      Serial.write(out[0]);
      Serial.write(out[1]);

      do_pack(out, y, 2);
      Serial.write(out[0]);
      Serial.write(out[1]);

      do_pack(out, z, 3);
      Serial.write(out[0]);
      Serial.write(out[1]);
//    }
//    else
    

//    Serial.println("out of range----------------------------");
  }
else
Serial.println("data not ready");
  

}
//----------------------------------------------------------------------------------------------------
void writeTo(byte address, byte val) {
  Wire.beginTransmission(DEVICE); // start transmission to device 
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();         // end transmission
}
//------------------------------------------------------------------------------------------------------
// Reads num bytes starting from address register on device in to _buff array
void readFrom(byte address, int num, byte _buff[]) {
  Wire.beginTransmission(DEVICE); // start transmission to device 
  Wire.write(address);             // sends address to read from
  Wire.endTransmission();         // end transmission

    Wire.beginTransmission(DEVICE); // start transmission to device
  Wire.requestFrom(DEVICE, num);    // request 6 bytes from device

  int i = 0;
  while(Wire.available())         // device may send less than requested (abnormal)
  { 
    _buff[i] = Wire.read();    // receive a byte
    i++;
  }
  Wire.endTransmission();         // end transmission
}
//-------------------------------------------------------------------------------------------------------------

