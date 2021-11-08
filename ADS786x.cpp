#include <ADS786x.hpp>

ADS786x::ADS786x(unsigned int mcs, SPISettings mspiSettings, SPIClass mspi) : cs(mcs), spiSettings(mspiSettings), spi(mspi){
	correctionFactor = 0;
	undertemped = false;
	overtemped = false;
};
void ADS786x::begin(){
	pinMode(cs, OUTPUT);
	digitalWrite(cs, HIGH);
};
uint16_t ADS786x::receive(uint8_t resolution, uint16_t undertempValue, uint16_t overtempValue){
	noInterrupts();
	digitalWrite(cs, LOW);
	SPI.beginTransaction(spiSettings);
	// 4 low bits, then data of length resolution.
	uint16_t receivedVal16 = SPI.transfer16(0x0000);
	SPI.endTransaction();
	digitalWrite(cs, HIGH);
	interrupts();
	receivedVal16 >> (13-resolution); // 16 - 4 + 1 - resolution
	if(receivedVal16+correctionFactor>maxValue){
		receivedVal16=maxValue;
		overtemped=true;
	}else if(receivedVal16+correctionFactor<0){
		receivedVal16=0;
		undertemped=true;
	}else if(receivedVal16<undertempValue){
		undertemped=true;
	}else if(receivedVal16>overtempValue){
		overtemped=true;
	}
	return receivedVal16;
};
bool ADS786x::isUndertemp(){
	if(undertemped){
		undertemped=false;
		return true;
	}
	return false;
};

bool ADS786x::isOvertemp(){
	if(overtemped){
		overtemped=false;
		return true;
	}
	return false;
};

ADS7866::ADS7866(unsigned int mcs, SPISettings mspiSettings, SPIClass mspi) : ADS786x(mcs, mspiSettings, mspi){
};
uint16_t ADS7866::receive(uint16_t undertempValue, uint16_t overtempValue){
	return ADS786x::receive(resolution, undertempValue, overtempValue);
};
ADS7867::ADS7867(unsigned int mcs, SPISettings mspiSettings, SPIClass mspi) : ADS786x(mcs, mspiSettings, mspi){
};
uint16_t ADS7867::receive(uint16_t undertempValue, uint16_t overtempValue){
	return ADS786x::receive(resolution, undertempValue, overtempValue);
};
ADS7868::ADS7868(unsigned int mcs, SPISettings mspiSettings, SPIClass mspi) : ADS786x(mcs, mspiSettings, mspi){
};
uint16_t ADS7868::receive(uint16_t undertempValue, uint16_t overtempValue){
	return ADS786x::receive(resolution, undertempValue, overtempValue);
};