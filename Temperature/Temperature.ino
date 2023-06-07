// =====================================================================================
// --- Libraries ---
#include <LiquidCrystal.h>


// =====================================================================================
// --- Hardware Mapping ---
#define db7 7  // LCD [Digital 7]
#define db6 6  // LCD [Digital 6]
#define db5 5  // LCD [Digital 5]
#define db4 4  // LCD [Digital 4]
#define rs 13  // LCD [Digital 13]
#define en 12  // LCD [Digital 12]

#define sensor_temp 0  // TPM [Analog A0]

// =====================================================================================
// --- Function Prototype ---
float read_temperature();


// =====================================================================================
// --- Initial Setup ---
LiquidCrystal lcd(rs, en, db4, db5, db6, db7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("TMP: ");
}


// =====================================================================================
// --- Main Loop ---
void loop() {
  lcd.setCursor(5, 0);
  lcd.print(read_temperature());
  lcd.print("C");
  delay(750);
}

// =====================================================================================
// --- Function Development ---
float read_temperature() {
  float temperature = analogRead(0);
  temperature = temperature * 0.48828125 - 50;
  return temperature;
} //end read_temperature
