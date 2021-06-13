// Honeywell ABP2 series
#define I2C_HARDWARE 1
#include <SoftI2CMaster.h>

#define PERIOD_MS 40

// ABP2DDAN001PD2A3
//              ~
byte address = 0x28 << 1;

char digits[] = "0123456789ABCDEF";
byte message[24];
byte data[8];
long t, t0;

void setup()
{
  Serial.begin(9600);
  i2c_init();
  t0 = millis();
}

void loop()
{
  int k;

  while (!Serial) {
    t0 = millis();
  }
  
  do {
    t = millis();
  } while (t - t0 < PERIOD_MS);
  t0 += PERIOD_MS;

  if (!i2c_start(address))
    return;

  if (!i2c_write(0xAA)) {
    i2c_stop();
    return;
  }

  if (!i2c_write(0x00)) {
    i2c_stop();
    return;
  }

  if (!i2c_write(0x00)) {
    i2c_stop();
    return;
  }
  
  i2c_stop();

  delay(10);

  if (!i2c_start(address | 1))
    return;

  for (k = 0; k < 6; k += 1) {
    data[k] = i2c_read(false);
  }
  data[k++] = i2c_read(true);
  i2c_stop();

  int i = 0;
  message[i++] = '*';
  for (k = 0; k < 7; k += 1) {
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
