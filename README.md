# ADS786x

## Description

C++ library for the ADS7866, ADS7867, ADS7868 devices. Designed for use with Arduino devices.

## Classes

- ADS786x

    This is the base class. Allows you to set resolution on each call. No real advantages to using this class.
	Undertemp and Overtemp is not enabled by default. You must pass it with recieve function to enable.
	

- ADS7866, ADS7867, ADS7868

    The main classes. Declare which ever you're using. This sets resolution and maxValue. Also enables under and over temp, which can be overriden.
	

## Functions
- If it's in [], it's optional. ADS7866:: applies to all ADS786(6,7,8) devices.
- void ADS786x(unsigned int chip_select, [SPISettings(Speed, ByteOrder, Mode)], [SPIClass]);
- void begin() - Sets pinMode and pulls pin high.
- uint16_t ADS786x::recieve(uint8_t resolution (8,10,12), [uint16_t undertemp], [uint16_t overtemp] ) - Calls SPI to get the data from the ADS, sets under and over temp.
- int16_t ADS7866::recieve([uint16_t undertemp], [uint16_t overtemp]) - Calls SPI to get the data from the ADS, sets under and over temp.
- bool isUndertemp() - Returns if undertemp limit has been exceeded. Resets to false upon read.
- bool isOvertemp() - Returns if overtemp limit has been exceeded. Resets to false upon read.


## Members

- int16_t resolution - How many bits of resolution there will be.
- int16_t maxValue - The max value possible with the amount of resolution. maxValue=1<<(resolution-1)-1;	
- int16_t correctionValue - This is added or removed to result prior to under/over temp detection. If below or above max value, it is capped.

## Example

Simple example...

```C++
#include <ADS786x.hpp>
ADS7867 adc = ADS7867(ChipSelect); // Set appropriate chip.
void setup() {
  Serial.begin(9600);
  adc.begin();
};
void loop() {
  Serial.println(adc.receive());
  if(adc.isUndertemp() || adc.isOvertemp())
    Serial.pritln("Temp alarm!");
};
```

Advanced example...

```C++
#include <ADS786x.hpp>
ADS7867 adc = ADS7867(ChipSelect, SPISettings(1000000, MSBFIRST, SPI_MODE3), SPI); // Set appropriate chip. Good if you have multiple SPI ports.
void setup() {
  Serial.begin(9600);
  adc.begin();
};
void loop() {
  Serial.println(adc.receive(10, adc.maxValue-10)); // If returned value is below 10 or above maxValue-10, it will set appropriate alarm.
  if(adc.isUndertemp() || adc.isOvertemp())
    Serial.println("Temp alarm!");
};
```

## License

The Unlicense. Do what ever you want with it. If you make it big, give me a shout out.
