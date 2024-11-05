#include "LEDTextDisplay.h"

LEDTextDisplay::LEDTextDisplay() {}

void LEDTextDisplay::begin() {
    matrix.addLayer(&scrollingLayer);
    matrix.begin();
    matrix.setBrightness(80); // Adjust brightness level as needed

    scrollingLayer.setMode(wrapForward);
    scrollingLayer.setColor(textColor);
    scrollingLayer.setSpeed(50);         // Adjust scrolling speed as desired
    scrollingLayer.setFont(font6x10);    // Set font; change to desired size or style
    scrollingLayer.setOffsetFromTop((kMatrixHeight / 2) - 5);
}

void LEDTextDisplay::displayText(const String &text) {
    scrollingLayer.stop();            // Stop any previous scrolling
    scrollingLayer.start(text.c_str(), -1);  // Start scrolling the new text, repeat indefinitely
}
