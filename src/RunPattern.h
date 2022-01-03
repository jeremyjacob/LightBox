#pragma once

class RunPattern {
public:
    enum Pattern {
        OFF,
        RAINBOW,
        BLUE
    };
    static constexpr Pattern DEFAULT_PATTERN = BLUE;
    static Pattern selected_pattern;
public:
    static void tick();
};

