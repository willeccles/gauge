#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "oled.h"
#include "obd.h"
#include "logo.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define LOGO_X (((SCREEN_WIDTH - LOGO_WIDTH) / 2) + (LOGO_PADDING / 2))
#define LOGO_Y ((SCREEN_HEIGHT - LOGO_HEIGHT) / 2)

#define OLED_RESET 9

#define FONTSZ 1

// get the y cursor position for row n (starting at 0)
#define ROW(n) ((n) * FONTSZ * 8)

#define RALIGN(len) (1 + SCREEN_WIDTH - ((FONTSZ * 6) * (len)))
#define CALIGN(len) (1 + (SCREEN_WIDTH / 2) - ((FONTSZ * 6) * (len) / 2))

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET,
        1000000UL, 1000000UL);

void OLED::init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (1);
    }

    display.clearDisplay();
    display.display();

    display.setTextSize(FONTSZ);
    display.setTextColor(WHITE);
    display.setTextWrap(false);
    display.cp437(true);
}

void OLED::dim(bool dim) {
    display.dim(dim);
}

void OLED::displayLogo() {
    display.clearDisplay();

    display.drawBitmap(LOGO_X, LOGO_Y, logo, LOGO_WIDTH, LOGO_HEIGHT, WHITE);

    display.display();
}

void OLED::displayLogo(const char* status) {
    display.clearDisplay();

    if (status != nullptr) {
        display.setCursor(CALIGN(strlen(status)), 48);
        display.print(status);
    }

    display.drawBitmap(LOGO_X, LOGO_Y, logo, LOGO_WIDTH, LOGO_HEIGHT, WHITE);

    display.display();
}

void OLED::update(OBD::VehicleData& data) {
    display.clearDisplay();

    // title
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0, ROW(0));
    display.print("                           ");
    display.setCursor(CALIGN(9), ROW(0));
    display.print("Live Data");
    display.setTextColor(WHITE, BLACK);

    // boost
    display.setCursor(0, ROW(1));
    display.print("Vac/Boost: ");
    display.print(data.boost); // TODO: second param = number of decimal places
    display.setCursor(RALIGN(3), ROW(1));
    display.print("PSI");

    // coolant temp
    display.setCursor(0, ROW(2));
    display.print("Temp: ");
    display.print(data.temp);
    display.setCursor(RALIGN(1), ROW(2));
    display.print('C');

    // max speed
    display.setCursor(0, ROW(3));
    display.print("Top Spd: ");
    display.print(data.maxspeedmph);
    display.setCursor(RALIGN(3), ROW(3));
    display.print("MPH");

    display.display();
}
