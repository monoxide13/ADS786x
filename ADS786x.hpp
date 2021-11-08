
/*  	...SPI Timing...
	Sample Time
		tSU(CSF-FSCLKF) + 2*tC(SCLK)
	Conversion Time
		ADS7866=13*tC(SCLK)μs
		ADS7867=11*tC(SCLK)μs
		ADS7868=9*tC(SCLK)μs;

	tC(SCLK) =					Cycle time μs		Max SPI CLK
		1.2 V < VDD < 1.6 V		100					10kHz
		1.6 V < VDD < 1.8 V		100					10kHz
		1.8 V < VDD < 2.5 V		50					20kHz
		2.5 V < VDD < 3.6 V		6.7					149kHz
*/

#ifndef ADS786x_h
#define ADS786x_h
#pragma once
#include <SPI.h>

class ADS786x {
	public:
	// add explicit
    explicit ADS786x(unsigned int mcs, SPISettings mspiSettings = SPISettings(3400000, MSBFIRST, SPI_MODE3), SPIClass mspi = SPI);
    void begin();
	uint16_t receive(uint8_t resolution, uint16_t undertempValue=0, uint16_t overtempValue=4095);
	bool isUndertemp();
	bool isOvertemp();
	int16_t correctionFactor;
	
	protected:
	bool undertemped;
	bool overtemped;
	
	private:
	const int cs;
	const SPIClass spi;
	const SPISettings spiSettings;
};

class ADS7866 : public ADS786x {
	public:
	explicit ADS7866(unsigned int mcs, SPISettings mspiSettings = SPISettings(3400000, MSBFIRST, SPI_MODE3), SPIClass mspi = SPI);
	uint16_t receive(uint16_t undertempValue = 5, uint16_t overtempValue = 4090);
	const uint8_t resolution = 12;
	const uint16_t maxValue = 4095;
};
class ADS7867 : public ADS786x {
	public:
	explicit ADS7867(unsigned int mcs, SPISettings mspiSettings = SPISettings(3400000, MSBFIRST, SPI_MODE3), SPIClass mspi = SPI);
	uint16_t receive(uint16_t undertempValue = 4, uint16_t overtempValue = 1019);
	const uint8_t resolution = 10;
	const uint16_t maxValue = 1023;
};
class ADS7868 : public ADS786x {
	public:
	explicit ADS7868(unsigned int mcs, SPISettings mspiSettings = SPISettings(3400000, MSBFIRST, SPI_MODE3), SPIClass mspi = SPI);
	uint16_t receive(uint16_t undertempValue = 3, uint16_t overtempValue = 252);
	const uint8_t resolution = 8;
	const uint16_t maxValue = 255;
};

#endif