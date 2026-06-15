#include "utils.h"
#include "servo.h"
#include "console.h"

s16 targetPosition[3] = {0,0,0};

void setup() {
	init();
    initSerial();
}

void loop() {
	getConsole();
	setPositions(targetPosition);
}
