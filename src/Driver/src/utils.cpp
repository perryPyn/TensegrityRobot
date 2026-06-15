#include "utils.h"
#include "servo.h"
#include "console.h"

s16 targetPosition[3] = {0,0,0};

void setup() {
	init();
    initServo();
}

void loop() {
	ecuatConsole();

	setPositions(targetPosition);

	// getPosition(1);
    // getPosition(2);
    // getPosition(3);
}
