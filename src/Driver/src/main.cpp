#include "main.h"
#include "utils.h"

int main(void) {

    setup();

    while (1) {
        loop();
        delay(300);
    }

    return 0;
}