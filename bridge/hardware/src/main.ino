#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"

Adafruit_BluefruitLE_SPI ble(8, 7, 4);

int threshold = 500;

void setup() {
	Serial.begin(115200);
	initBluetooth();
}

void loop() {
	int sensorValue = analogRead(A5);
	if (sensorValue > threshold) {
		ble.print("AT+BLEUARTTX=");
		ble.println(sensorValue);
		delay(200);
	}
}

void initBluetooth() {
	ble.begin(true);
	ble.factoryReset();
	ble.sendCommandCheckOK(F("AT+GAPDEVNAME=Raquette_1"));
	ble.echo(false);
	ble.info();
	ble.verbose(false);
	while (!ble.isConnected()) {
		delay(500);
	}
}
