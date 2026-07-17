#include <Arduino.h>
#include <Sipeed_OV2640.h>
#include <Sipeed_ST7789.h>

// put function declarations here:
//int myFunction(int, int);

#include <Arduino.h>

// making the screen and camera objects
Sipeed_ST7789 lcd(320, 240, SPI0_CH0, DUAL_SPI);
Sipeed_OV2640 camera(FRAMESIZE_QVGA, PIXFORMAT_RGB565);

void setup() {
    Serial.begin(115200);

    // screen init
    if (!lcd.begin(15000000, COLOR_RED)) {
        Serial.println("LCD initialization failed!");
        while (1);
    }
    lcd.setRotation(3); // orientation

    // camera test
    if (!camera.begin()) {
        Serial.println("Camera initialization failed!");
        lcd.drawString(10, 10, "Camera Error!", COLOR_RED);
        while (1);
    }
    
    // camera orientation fixing
    camera.setHflip(1); 
    camera.setVflip(1);

    Serial.println("Camera and LCD successfully initialized.");
}

void loop() { // ai section
    // Grab a frame pointer from the camera sensor
    uint8_t *frameBuffer = camera.getImgBuffer();

    if (frameBuffer != NULL) {
        // Draw the camera raw pixel buffer directly onto the screen
        lcd.drawImage(0, 0, camera.width(), camera.height(), (uint16_t *)frameBuffer);
    } else {
        Serial.println("Failed to capture image frame.");
    }
}

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }