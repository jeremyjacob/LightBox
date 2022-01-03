#include "Off.h"
#include "Panel.h"

void Off::run() {
    digitalWrite(5, 0);
}