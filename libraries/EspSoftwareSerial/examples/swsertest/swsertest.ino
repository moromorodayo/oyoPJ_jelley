// On ESP8266:
// At 80MHz runs up 57600ps, and at 160MHz CPU frequency up to 115200bps with only negligible errors.
// Connect pin 12 to 14.

#include <SoftwareSerial.h>

#ifndef D5
#if defined(ESP8266)
#define D5 (14)
#define D6 (12)
#define D7 (13)
#define D8 (15)
#define TX (1)
#elif defined(ESP32)
#define D5 (18)
#define D6 (19)
#define D7 (23)
#define D8 (5)
#define TX (1)
#endif
#endif

#ifdef ESP32
#define BAUD_RATE 57600
#else
#define BAUD_RATE 57600
#endif

SoftwareSerial swSer;

void setup() {
	Serial.begin(115200);
	// Important: the buffer size optimizations here, in particular the isrBufSize (11) that is only sufficiently
	// large to hold a single 8N1 word, are on the basis that any char written to the loopback SoftwareSerial
	// adapter gets read before another write is performed.
	// Block writes with a size greater than 1 would usually fail. Do not copy this into your own project without
	// reading the documentation.
	swSer.begin(BAUD_RATE, SWSERIAL_8N1, D5, D6, false, 95, 11);

	Serial.println(PSTR("\nSoftware serial test started"));

	for (char ch = ' '; ch <= 'z'; ch++) {
		swSer.write(ch);
	}
	swSer.println();
}

void loop() {
	while (swSer.available() > 0) {
		Serial.write(swSer.read());
		yield();
	}
	while (Serial.available() > 0) {
		swSer.write(Serial.read());
		yield();
	}

}
