#include "RunPattern.h"
#include "patterns/all.h"

RunPattern::Pattern RunPattern::selected_pattern = RunPattern::DEFAULT_PATTERN;

void RunPattern::tick() {
    switch (selected_pattern) {
        case OFF:
            Off::run();
            break;
        case RAINBOW:
            Rainbow::run();
            break;
        case BLUE:
            Blue::run();
            break;
    }
}

