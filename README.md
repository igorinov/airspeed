# Airspeed

This project connects a differential pressure sensor to an Android device using an Arduino-compatible board.
It is going to be used in the [Variometer](https://github.com/igorinov/variometer) project to compute total energy.

Default configuration uses hardware i2c support with standard SDA/SCL pins as marked on the Arduino compatible board.

## Pressure sensor

  - [Honeywell ABP2 Series](https://sps.honeywell.com/us/en/products/sensing-and-iot/sensors/pressure-sensors/board-mount-pressure-sensors/basic-abp2-series)
  - [MEAS 4525-DS5A001DP](https://www.te.com/usa-en/product-4525-DS5A001DP.html)
  - [MEAS 5525DSO-DB001DS](https://www.te.com/usa-en/product-5525DSO-DB001DS.html)

## Controller board

  An Arduino-compatible board based on an 8-bit AVR MCU, for example:

  - [Arduino Uno Rev3](https://store.arduino.cc/usa/arduino-uno-rev3)
  - [SparkFun RedBoard](https://www.sparkfun.com/products/13975)
  - [SparkFun Qwiic Pro Micro - USB-C (ATmega32U4)](https://www.sparkfun.com/products/15795)

## Arduino libraries required

  SoftI2CMaster (GPL v3): https://github.com/felias-fogg/SoftI2CMaster
