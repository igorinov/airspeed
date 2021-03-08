#define I2C_HARDWARE 1
#include <SoftI2CMaster.h>

// 4525DO-DS5AI-001D
byte address = 0x28 << 1;

char digits[] = "0123456789ABCDEF";
byte message[16];
byte data[4];
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
  } while (t - t0 < 40);
  t0 = t;

  if (!i2c_start(address))
    return;
  
  i2c_stop();

  delay(10);

  if (!i2c_start(address | 1))
    return;

  for (k = 0; k < 4; k += 1) {
    data[k] = i2c_read(false);
  }
  i2c_stop();

  int i = 0;
  message[i++] = '*';
  for (k = 0; k < 4; k += 1) {
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