# Airspeed

This is an Arduino sketch for connecting 4525DO to a USB serial port.
It is going to be used in the [Variometer](https://github.com/igorinov/variometer) project to compute total energy.

Default configuration uses hardware i2c support with standard SDA/SCL pins as marked on the Arduino board.

## Hardware

  Arduino board based on an 8-bit AVR MCU, for example:
  - [Arduino Uno Rev3](https://store.arduino.cc/usa/arduino-uno-rev3)
  - [SparkFun RedBoard](https://www.sparkfun.com/products/13975)
  - [SparkFun Qwiic Pro Micro - USB-C (ATmega32U4)](https://www.sparkfun.com/products/15795)

  4525DO-DSAI001DP
  Tested with the following boards:
  - [Mateksys ASPD-4525](http://www.mateksys.com/?portfolio=aspd-4525)

## Libraries

  SoftI2CMaster (GPL v3): https://github.com/felias-fogg/SoftI2CMaster
