Import("env")
import os, glob

header = '''// Auto generated by patterns.py

#pragma once

#INCLUDES

enum Pattern {#ENUMS};
class Patterns {
public:
    static Pattern selected_pattern;
public:
    static void tick();

    static void set(Pattern);
};

Pattern Patterns::selected_pattern = Pattern::INIT;

#POINTERS

void Patterns::tick() {
//    Serial.println("Tick()");
    switch (selected_pattern) {
        #RUN_SWITCH
    }
    
    for (int x = 0; x < WIDTH; ++x) {
        p_leds[XY(x, 15)] = CRGB::Black;
    }
}

void Patterns::set(Pattern
                   _pattern) {
    if (selected_pattern == _pattern) return;
    switch (selected_pattern) {
        #DELETE_SWITCH
    }
    selected_pattern = _pattern;
    switch (selected_pattern) {
        #NEW_SWITCH
    }
}'''


def test(node):
    template_include = []
    template_enum = ['INIT,']
    template_pointers = []
    template_switch_run = []
    template_switch_delete = []
    template_switch_new = []

    patterns = []
    files = glob.glob("src/patterns/*.h")
    for filename in sorted(files):
        if filename.startswith("."): continue
        patterns.append(filename.replace(".h", "").split("\\")[-1])

    for pattern in patterns:
        enum = pattern.upper()
        variable = pattern.lower()

        template_include.append(f'#include "patterns/{pattern}.h"')
        template_enum.append(f'{enum},')
        template_pointers.append(f'{pattern} *{variable};')
        template_switch_run.append(f'''case {enum}: {variable}->run(); break;''')
        template_switch_delete.append(f'''case {enum}: delete {variable}; break;''')
        template_switch_new.append(f'''case {enum}: {variable} = new {pattern}(); break;''')

    file = header.replace("#INCLUDES", '\n'.join(template_include) + '\n')
    file = file.replace("#ENUMS", ' '.join(template_enum))
    file = file.replace("#POINTERS", ' \n'.join(template_pointers) + '\n')
    file = file.replace("#RUN_SWITCH", ' \n'.join(template_switch_run) + '\n')
    file = file.replace("#DELETE_SWITCH", ' \n'.join(template_switch_delete) + '\n')
    file = file.replace("#NEW_SWITCH", ' \n'.join(template_switch_new) + '\n')

    with open("src/Patterns.h", "w") as f:
        f.write(file)
    return node


env.AddBuildMiddleware(test, "*/src/main.cpp")
