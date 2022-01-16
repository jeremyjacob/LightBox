// Auto generated by patterns.py

#pragma once

#include "patterns/Metaballs.h"
#include "patterns/BlockPuzzle.h"
#include "patterns/LostLands.h"
#include "patterns/Pool.h"
#include "patterns/EnergyBalls.h"
#include "patterns/Rainbow.h"
#include "patterns/Ameoba.h"
#include "patterns/Galaxy.h"
#include "patterns/PlasmaWaves.h"
#include "patterns/ExpandingCircles.h"
#include "patterns/Spirits.h"
#include "patterns/IcyNoise.h"
#include "patterns/SmokeCurtains.h"
#include "patterns/Fireplace.h"
#include "patterns/Living.h"
#include "patterns/TheMatrix.h"
#include "patterns/SolidColor.h"
#include "patterns/CrossHatch.h"
#include "patterns/InfinitySign.h"
#include "patterns/AssortedNoise.h"
#include "patterns/Plasm.h"
#include "patterns/Off.h"
#include "patterns/FireRings.h"
#include "patterns/Geometry.h"


class Patterns {
public:
    enum Pattern {INIT, METABALLS, BLOCKPUZZLE, LOSTLANDS, POOL, ENERGYBALLS, RAINBOW, AMEOBA, GALAXY, PLASMAWAVES, EXPANDINGCIRCLES, SPIRITS, ICYNOISE, SMOKECURTAINS, FIREPLACE, LIVING, THEMATRIX, SOLIDCOLOR, CROSSHATCH, INFINITYSIGN, ASSORTEDNOISE, PLASM, OFF, FIRERINGS, GEOMETRY,};
    static Pattern selected_pattern;
public:
    static void tick();

    static void set(Pattern);
};

Patterns::Pattern Patterns::selected_pattern = Patterns::INIT;

Metaballs *metaballs; 
BlockPuzzle *blockpuzzle; 
LostLands *lostlands; 
Pool *pool; 
EnergyBalls *energyballs; 
Rainbow *rainbow; 
Ameoba *ameoba; 
Galaxy *galaxy; 
PlasmaWaves *plasmawaves; 
ExpandingCircles *expandingcircles; 
Spirits *spirits; 
IcyNoise *icynoise; 
SmokeCurtains *smokecurtains; 
Fireplace *fireplace; 
Living *living; 
TheMatrix *thematrix; 
SolidColor *solidcolor; 
CrossHatch *crosshatch; 
InfinitySign *infinitysign; 
AssortedNoise *assortednoise; 
Plasm *plasm; 
Off *off; 
FireRings *firerings; 
Geometry *geometry;


void Patterns::tick() {
//    Serial.println("Tick()");
    switch (selected_pattern) {
        case METABALLS: metaballs->run(); break; 
case BLOCKPUZZLE: blockpuzzle->run(); break; 
case LOSTLANDS: lostlands->run(); break; 
case POOL: pool->run(); break; 
case ENERGYBALLS: energyballs->run(); break; 
case RAINBOW: rainbow->run(); break; 
case AMEOBA: ameoba->run(); break; 
case GALAXY: galaxy->run(); break; 
case PLASMAWAVES: plasmawaves->run(); break; 
case EXPANDINGCIRCLES: expandingcircles->run(); break; 
case SPIRITS: spirits->run(); break; 
case ICYNOISE: icynoise->run(); break; 
case SMOKECURTAINS: smokecurtains->run(); break; 
case FIREPLACE: fireplace->run(); break; 
case LIVING: living->run(); break; 
case THEMATRIX: thematrix->run(); break; 
case SOLIDCOLOR: solidcolor->run(); break; 
case CROSSHATCH: crosshatch->run(); break; 
case INFINITYSIGN: infinitysign->run(); break; 
case ASSORTEDNOISE: assortednoise->run(); break; 
case PLASM: plasm->run(); break; 
case OFF: off->run(); break; 
case FIRERINGS: firerings->run(); break; 
case GEOMETRY: geometry->run(); break;

    }
    
    for (int x = 0; x < WIDTH; ++x) {
        p_leds[XY(x, 15)] = CRGB::Black;
    }
}

void Patterns::set(Patterns::Pattern
                   _pattern) {
    switch (selected_pattern) {
        case METABALLS: delete metaballs; break; 
case BLOCKPUZZLE: delete blockpuzzle; break; 
case LOSTLANDS: delete lostlands; break; 
case POOL: delete pool; break; 
case ENERGYBALLS: delete energyballs; break; 
case RAINBOW: delete rainbow; break; 
case AMEOBA: delete ameoba; break; 
case GALAXY: delete galaxy; break; 
case PLASMAWAVES: delete plasmawaves; break; 
case EXPANDINGCIRCLES: delete expandingcircles; break; 
case SPIRITS: delete spirits; break; 
case ICYNOISE: delete icynoise; break; 
case SMOKECURTAINS: delete smokecurtains; break; 
case FIREPLACE: delete fireplace; break; 
case LIVING: delete living; break; 
case THEMATRIX: delete thematrix; break; 
case SOLIDCOLOR: delete solidcolor; break; 
case CROSSHATCH: delete crosshatch; break; 
case INFINITYSIGN: delete infinitysign; break; 
case ASSORTEDNOISE: delete assortednoise; break; 
case PLASM: delete plasm; break; 
case OFF: delete off; break; 
case FIRERINGS: delete firerings; break; 
case GEOMETRY: delete geometry; break;

    }
    selected_pattern = _pattern;
    switch (selected_pattern) {
        case METABALLS: metaballs = new Metaballs(); break; 
case BLOCKPUZZLE: blockpuzzle = new BlockPuzzle(); break; 
case LOSTLANDS: lostlands = new LostLands(); break; 
case POOL: pool = new Pool(); break; 
case ENERGYBALLS: energyballs = new EnergyBalls(); break; 
case RAINBOW: rainbow = new Rainbow(); break; 
case AMEOBA: ameoba = new Ameoba(); break; 
case GALAXY: galaxy = new Galaxy(); break; 
case PLASMAWAVES: plasmawaves = new PlasmaWaves(); break; 
case EXPANDINGCIRCLES: expandingcircles = new ExpandingCircles(); break; 
case SPIRITS: spirits = new Spirits(); break; 
case ICYNOISE: icynoise = new IcyNoise(); break; 
case SMOKECURTAINS: smokecurtains = new SmokeCurtains(); break; 
case FIREPLACE: fireplace = new Fireplace(); break; 
case LIVING: living = new Living(); break; 
case THEMATRIX: thematrix = new TheMatrix(); break; 
case SOLIDCOLOR: solidcolor = new SolidColor(); break; 
case CROSSHATCH: crosshatch = new CrossHatch(); break; 
case INFINITYSIGN: infinitysign = new InfinitySign(); break; 
case ASSORTEDNOISE: assortednoise = new AssortedNoise(); break; 
case PLASM: plasm = new Plasm(); break; 
case OFF: off = new Off(); break; 
case FIRERINGS: firerings = new FireRings(); break; 
case GEOMETRY: geometry = new Geometry(); break;

    }
}