#pragma once

#include "Panel.h"

class AssortedNoise {
public:
    AssortedNoise();
    void run();
    
    uint8_t mode = 1;
    uint8_t cycletime = 6.0;
    bool cycle = true;
private:
    uint16_t noisex = 0;
    uint16_t noisey = 0;
    uint16_t noisez = 0;

// We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// use the z-axis for "time".  speed determines how fast time moves forward.  Try
// 1 for a very slow moving effect, or 60 for something that ends up looking like
// water.
    uint32_t noisespeedx = 1;
    uint32_t noisespeedy = 1;
    uint32_t noisespeedz = 1;

// scale determines how far apart the pixels in our noise matrix are.  Try
// changing these values around to see how it affects the motion of the display.  The
// higher the value of scale, the more "zoomed out" the noise will be.  A value
// of 1 will be so zoomed in, you'll mostly see solid colors.
    uint16_t noisescale = 30; // scale is set dynamically once we've started up

// This is the array that we keep our computed noise values in
    uint8_t noise[WIDTH][WIDTH]{};
    
    uint8_t colorLoop = 0;
    
    CRGBPalette16 blackAndWhiteStripedPalette;
    CRGBPalette16 blackAndBlueStripedPalette;
    
    boolean initialized = false;

private:
    void SetupBlackAndWhiteStripedPalette();
    
    void SetupBlackAndBlueStripedPalette();
    
    void fillnoise8();
    
    void mapNoiseToLEDsUsingPalette(CRGBPalette16 palette, uint8_t hueReduce);
    
    uint16_t drawNoise(CRGBPalette16 palette, uint8_t hueReduce);
    
    uint16_t LavaLampRainbow();
    
    uint16_t LavaLampRainbowStripe();
    
    uint16_t Party();
    
    uint16_t Forest();
    
    uint16_t Cloud();
    
    uint16_t Fire();
    
    uint16_t FireNoise();
    
    uint16_t Lava();
    
    uint16_t Ocean();
    
    uint16_t BlackAndWhite();
    
    uint16_t BlackAndBlue();
    
    uint16_t Temperature();
    
    uint16_t Spectrum();
    
    uint16_t OceanBreeze();
    
    uint16_t DeepSea();
    
    uint16_t Aurora();
    
    uint16_t Shikon();
    
    uint16_t ColorCube();
};

// https://github.com/RMProjectsUK/LEDEffectLampProject/blob/main/Noise.h

// The 16 bit version of our coordinates

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void AssortedNoise::SetupBlackAndWhiteStripedPalette() {
    // 'black out' all 16 palette entries...
    fill_solid(blackAndWhiteStripedPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    blackAndWhiteStripedPalette[0] = CRGB::White;
    blackAndWhiteStripedPalette[4] = CRGB::White;
    blackAndWhiteStripedPalette[8] = CRGB::White;
    blackAndWhiteStripedPalette[12] = CRGB::White;
    
}


// This function sets up a palette of black and blue stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void AssortedNoise::SetupBlackAndBlueStripedPalette() {
    // 'black out' all 16 palette entries...
    fill_solid(blackAndBlueStripedPalette, 16, CRGB::Black);
    
    for (uint8_t i = 0; i < 6; i++) {
        blackAndBlueStripedPalette[i] = CRGB::Blue;
    }
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.


// Fill the x/y array of 8-bit noise values using the inoise8 function.
void AssortedNoise::fillnoise8() {
    
    if (!initialized) {
        initialized = true;
        // Initialize our coordinates to some random values
        noisex = random16();
        noisey = random16();
        noisez = random16();
    }
    
    // If we're runing at a low "speed", some 8-bit artifacts become visible
    // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
    // The amount of data smoothing we're doing depends on "speed".
    uint8_t dataSmoothing = 0;
    uint16_t lowestNoise = noisespeedx < noisespeedy ? noisespeedx : noisespeedy;
    lowestNoise = lowestNoise < noisespeedz ? lowestNoise : noisespeedz;
    if (lowestNoise < 8) {
        dataSmoothing = 200 - (lowestNoise * 4);
    }
    
    for (int i = 0; i < WIDTH; i++) {
        int ioffset = noisescale * i;
        for (int j = 0; j < WIDTH; j++) {
            int joffset = noisescale * j;
            
            uint8_t data = inoise8(noisex + ioffset, noisey + joffset, noisez);
            
            // The range of the inoise8 function is roughly 16-238.
            // These two operations expand those values out to roughly 0..255
            // You can comment them out if you want the raw noise data.
            data = qsub8(data, 16);
            data = qadd8(data, scale8(data, 39));
            
            if (dataSmoothing) {
                uint8_t olddata = noise[i][j];
                uint8_t newdata = scale8(olddata, dataSmoothing) + scale8(data, 256 - dataSmoothing);
                data = newdata;
            }
            
            noise[i][j] = data;
        }
    }
    
    noisex += noisespeedx;
    noisey += noisespeedy;
    noisez += noisespeedz;
}

void AssortedNoise::mapNoiseToLEDsUsingPalette(CRGBPalette16 palette, uint8_t hueReduce = 0) {
    static uint8_t ihue = 0;
    
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            // We use the value at the (i,j) coordinate in the noise
            // array for our brightness, and the flipped value from (j,i)
            // for our pixel's index into the color palette.
            
            uint8_t index = noise[j][i];
            uint8_t bri = noise[i][j];
            
            // if this palette is a 'loop', add a slowly-changing base value
            if (colorLoop) {
                index += ihue;
            }
            
            // brighten up, as the color palette itself often contains the
            // light/dark dynamic range desired
            if (bri > 127) {
                bri = 255;
            } else {
                bri = dim8_raw(bri * 2);
            }
            
            if (hueReduce > 0) {
                if (index < hueReduce) index = 0;
                else index -= hueReduce;
            }
            
            CRGB color = ColorFromPalette(palette, index, bri);
            uint16_t n = XY(i, j);
            
            p_leds[n] = color;
        }
    }
    
    ihue += 1;
}

uint16_t AssortedNoise::drawNoise(CRGBPalette16 palette, uint8_t hueReduce = 0) {
    // generate noise data
    fillnoise8();
    
    // convert the noise data to colors in the LED array
    // using the current palette
    mapNoiseToLEDsUsingPalette(palette, hueReduce);
    
    return 10;
}

//===============================================
uint16_t AssortedNoise::LavaLampRainbow() {
    noisespeedx = 1;
    noisespeedy = 0;
    noisespeedz = 0;
    noisescale = 10;
    colorLoop = 0;
    return drawNoise(RainbowColors_p);
}

//===============================================
uint16_t AssortedNoise::LavaLampRainbowStripe() {
    noisespeedx = 2;
    noisespeedy = 0;
    noisespeedz = 0;
    noisescale = 20;
    colorLoop = 0;
    return drawNoise(RainbowStripeColors_p);
}

//===============================================
uint16_t AssortedNoise::Party() {
    noisespeedx = 1;
    noisespeedy = 0;
    noisespeedz = 0;
    noisescale = 50;
    colorLoop = 0;
    return drawNoise(PartyColors_p);
}

//===============================================
uint16_t AssortedNoise::Forest() {
    noisespeedx = 9;
    noisespeedy = 0;
    noisespeedz = 5;
    noisescale = 70;
    colorLoop = 0;
    return drawNoise(ForestColors_p);
}

//===============================================
uint16_t AssortedNoise::Cloud() {
    noisespeedx = 9;
    noisespeedy = 0;
    noisespeedz = 0;
    noisescale = 30;
    colorLoop = 0;
    return drawNoise(CloudColors_p);
}

//===============================================
uint16_t AssortedNoise::Fire() {
    noisespeedx = 8; // 24;
    noisespeedy = 0;
    noisespeedz = 8;
    noisescale = 50;
    colorLoop = 0;
    return drawNoise(HeatColors_p, 60);
}

//===============================================
uint16_t AssortedNoise::FireNoise() {
    noisespeedx = 8; // 24;
    noisespeedy = 0;
    noisespeedz = 8;
    noisescale = 50;
    colorLoop = 0;
    return drawNoise(HeatColors_p, 60);
}

//===============================================
uint16_t AssortedNoise::Lava() {
    noisespeedx = 2;
    noisespeedy = 0;
    noisespeedz = 2;
    noisescale = 20;
    colorLoop = 0;
    return drawNoise(LavaColors_p);
}

//===============================================
uint16_t AssortedNoise::Ocean() {
    noisespeedx = 9;
    noisespeedy = 0;
    noisespeedz = 0;
    noisescale = 90;
    colorLoop = 0;
    return drawNoise(OceanColors_p);
}

//===============================================
uint16_t AssortedNoise::BlackAndWhite() {
    SetupBlackAndWhiteStripedPalette();
    noisespeedx = 9;
    noisespeedy = 0;
    noisespeedz = 0;
    noisescale = 30;
    colorLoop = 0;
    return drawNoise(blackAndWhiteStripedPalette);
}

//===============================================
uint16_t AssortedNoise::BlackAndBlue() {
    SetupBlackAndBlueStripedPalette();
    noisespeedx = -7;
    noisespeedy = 0;
    noisespeedz = 0;
    noisescale = 30;
    colorLoop = 0;
    return drawNoise(blackAndBlueStripedPalette);
}

//===============================================
uint16_t AssortedNoise::Temperature() {
    noisespeedx = 1;
    noisespeedy = 0;
    noisespeedz = 1;
    noisescale = 25; //20
    colorLoop = 0;
    return drawNoise(temperature_gp);
}

//===============================================
uint16_t AssortedNoise::Spectrum() {
    noisespeedx = 1;
    noisespeedy = 0;
    noisespeedz = 1;
    noisescale = 25; //20
    colorLoop = 0;
    return drawNoise(Stripped_Spectrum_gp);
}

//===============================================
uint16_t AssortedNoise::OceanBreeze() {
    noisespeedx = 1;
    noisespeedy = 0;
    noisespeedz = 1;
    noisescale = 25; //20
    colorLoop = 0;
    return drawNoise(es_ocean_breeze_026_gp);
}

//===============================================
uint16_t AssortedNoise::DeepSea() {
    noisespeedx = 1;
    noisespeedy = 1;
    noisespeedz = 0;
    noisescale = 30; //20
    colorLoop = 0;
    return drawNoise(Deep_Sea_gp);
}

//===============================================
uint16_t AssortedNoise::Aurora() {
    noisespeedx = 0;
    noisespeedy = 1;
    noisespeedz = 0;
    noisescale = 30; //20
    colorLoop = 0;
    return drawNoise(ofaurora_gp);
}

//===============================================
uint16_t AssortedNoise::Shikon() {
    noisespeedx = 1;
    noisespeedy = 1;
    noisespeedz = 0;
    noisescale = 10; //20
    colorLoop = 0;
    return drawNoise(shikon_23_gp);
    return drawNoise(shikon_22_gp);
}

//===============================================
uint16_t AssortedNoise::ColorCube() {
    noisespeedx = 1;
    noisespeedy = 1;
    noisespeedz = 0;
    noisescale = 15; //20
    colorLoop = 0;
    return drawNoise(colorcube_gp);
}


//===============================================

void AssortedNoise::run() {
    uint8_t seconds = millis() / 1000;
    if (seconds % cycletime == 0)
        switch (mode) {
            case 0:LavaLampRainbow();
                break;
            case 1:LavaLampRainbowStripe();
                break;
            case 2:Party();
                break;
            case 3:Forest();
                break;
            case 4:Cloud();
                break;
            case 5:Fire();
                break;
            case 6:FireNoise();
                break;
            case 7:Lava();
                break;
            case 8:Ocean();
                break;
            case 9:BlackAndWhite();
                break;
            case 10:BlackAndBlue();
                break;
            case 11:Temperature();
                break;
            case 12:Spectrum();
                break;
            case 13:OceanBreeze();
                break;
            case 14:DeepSea();
                break;
            case 15:Aurora();
                break;
            case 16:Shikon();
                break;
            case 17:ColorCube();
                break;
        };
}

AssortedNoise::AssortedNoise() {
    State::registerWatch([this](const ArduinoJson6192_70::DynamicJsonDocument &doc) -> void {
        this->cycle = doc["patterns"]["AssortedNoise"]["cycle"];
        if (!this->cycle) this->mode = doc["patterns"]["AssortedNoise"]["mode"];
        this->cycletime = doc["patterns"]["AssortedNoise"]["cycleTime"];
    });
}
