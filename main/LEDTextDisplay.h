#ifndef LEDTEXTDISPLAY_H
#define LEDTEXTDISPLAY_H

#define GPIOPINOUT 0
#include <MatrixHardware_ESP32_V0.h>

#include <Arduino.h>
#include <SmartMatrix.h>

#define COLOR_DEPTH 24
const uint16_t kMatrixWidth = 64;             // Adjust for your display's width
const uint16_t kMatrixHeight = 32;            // Adjust for your display's height
const uint8_t kRefreshDepth = 36;
const uint8_t kDmaBufferRows = 4;
const uint8_t kPanelType = SM_PANELTYPE_HUB75_32ROW_MOD16SCAN;
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);

const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

class LEDTextDisplay {
public:
    LEDTextDisplay();
    void begin();
    void displayText(const String &text);

private:
    rgb24 textColor = {255, 255, 255};  // Set default text color
};

#endif
