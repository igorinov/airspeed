// MS5525DSO (TE Connectivity)


#define I2C_HARDWARE 1
#include <SoftI2CMaster.h>

#define PERIOD_MS 40

// CSB is connected to VDD: address = 0xEC;
// CSB is connected to GND: address = 0xEE;
byte address = 0xEC;

char digits[] = "0123456789ABCDEF";
byte data[16];
byte message[64];
long t, t0;

void setup()
{
  Serial.begin(9600);
  i2c_init();
}

void read_prom()
{
  int n = 0;
  int i, k;

  //
  // Read PROM
  //

  for (k = 0; k < 16; k += 2) {
    if (!i2c_start(address))
      return;

    // Read PROM word [k]
    if (!i2c_write(0xA0 | k))
      return;

    i2c_stop();

    if (!i2c_start(address | 1))
      return;

    data[n++] = i2c_read(false);
    data[n++] = i2c_read(true);

    i2c_stop();
  }

  Serial.write("PROM");

  i = 0;
  for (k = 0; k < n; k += 1) {
    if (!(k & 1)) {
      message[i++] = ' ';
    }
    byte d = data[k];
    byte dh = (d & 0xF0) >> 4;
    byte dl = d & 0x0F;
    message[i++] = digits[dh];
    message[i++] = digits[dl];
  }
  message[i++] = '\r';
  message[i++] = '\n';
  Serial.write(message, i);
}

byte prom_sent = 0;

void loop()
{
  int n = 0;
  int k;

  while (!Serial) {
    t0 = millis();
    prom_sent = 0;
  }

  if (!prom_sent) {
    read_prom();
    prom_sent = 1;
    delay(125);
  }
  
  do {
    t = millis();
  } while (t - t0 < PERIOD_MS);
  t0 += PERIOD_MS;

  //
  // Read differential pressure
  //

  if (!i2c_start(address))
    return;

  // I²C Command to initiate a pressure conversion (OSR=4096, typ=D1)
  if (!i2c_write(0x48))
    return;
  
  i2c_stop();

  delay(10);

  if (!i2c_start(address))
    return;

  // I²C ADC read sequence
  if (!i2c_write(0x00))
    return;
  
  i2c_stop();

  delay(1);

  if (!i2c_start(address | 1))
    return;

  data[n++] = i2c_read(false);
  data[n++] = i2c_read(false);
  data[n++] = i2c_read(true);
  i2c_stop();

  //
  // Read temperature
  //

  if (!i2c_start(address))
    return;

  // I²C Command to initiate a temperature conversion (OSR=4096, typ=D2)
  if (!i2c_write(0x58))
    return;
  
  i2c_stop();

  delay(10);

  if (!i2c_start(address))
    return;

  // I²C ADC read sequence
  if (!i2c_write(0x00))
    return;

  i2c_stop();

  delay(1);

  if (!i2c_start(address | 1))
    return;

  data[n++] = i2c_read(false);
  data[n++] = i2c_read(false);
  data[n++] = i2c_read(true);
  i2c_stop();

  int i = 0;
  message[i++] = '*';
  for (k = 0; k < n; k += 1) {
    byte d = data[k];
    byte dh = (d & 0xF0) >> 4;
    byte dl = d & 0x0F;
    message[i++] = digits[dh];
    message[i++] = digits[dl];
  }
  message[i++] = '\r';
  message[i++] = '\n';
  Serial.write(message, i);
}
