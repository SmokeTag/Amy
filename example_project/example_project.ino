// =====================================================================================
// --- Libriry ---
#include <LiquidCrystal.h>


// =====================================================================================
// --- Hardware Mapping ---
#define db6 6         //LCD
#define db7 7         //LCD
#define db5 5         //LCD
#define db4 4         //LCD
#define db3 11        //LCD
#define db2 10        //LCD
#define db1 9         //LCD
#define db0 8         //LCD
#define rs 13         //LCD
#define en 12         //LCD

#define menu_bt 19    //Push button  [Analogic 5]
#define ent_bt 18     //Push button  [Analogic 4]

#define sensor_temp 0 //Temperature sensor [Analogic 0]

#define led 17        //Led          [Analogic 3]

// =====================================================================================
// --- Project Constants ---
#define MENU_MAX 5             // number of menu itens
const int debounce_time = 30;  // time in milliseconds


// =====================================================================================
// --- Function Prototypes ---
void  read_bts();
void  menu_select();
float read_temperature();


// =====================================================================================
// --- Global Variables ---
int menu_number = 1;           // number of current menu 
bool sub_menu = 0;             // inside menu_select()
bool update_menu_flag = 1;     // flag for updating the menu

// =====================================================================================
// --- Inicial config ---
LiquidCrystal lcd(rs, en, db0, db1, db2, db3, db4, db5, db6, db7);
void setup() {
  lcd.begin(16, 2);
  pinMode(menu_bt, INPUT_PULLUP);
  pinMode(ent_bt, INPUT_PULLUP);
}  //end setup


// =====================================================================================
// --- Main loop ---
void loop() {
  if (!sub_menu && update_menu_flag) {  //if(not in submenu and update is needed)
    lcd.clear();                   //clear display
    switch (menu_number) {         //access main menu (prints it on LCD)
      case 1:
        lcd.setCursor(0, 0);
        lcd.print(">Read Temp");
        lcd.setCursor(1, 1);
        lcd.print("Play Music");
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print(">Play Music");
        lcd.setCursor(1, 1);
        lcd.print("3");
        break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print(">3");
        lcd.setCursor(1, 1);
        lcd.print("4");
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print(">4");
        lcd.setCursor(1, 1);
        lcd.print("5");
        break;
      case 5:
        lcd.setCursor(0, 0);
        lcd.print(">5");
        lcd.setCursor(1, 1);
        lcd.print("Read Temp");
        break;
    }  //end switch
    update_menu_flag = 0;          //display is update no need to update it again unless a button is pressed
  }    //end if(!sub_menu)
  read_bts();
}  //end loop


// =====================================================================================
// --- Desenvolvimento das Funções ---
void read_bts() {
  static bool menu_flag = 0, enter_flag = 0;                 //flags related to software debounce of buttons
  static unsigned long menu_bounce = 0, enter_bounce = 0;    //time variable also related to software debouncing
  unsigned long current_time = millis();

  //MENU BUTTON
  if (!digitalRead(menu_bt) && (current_time - menu_bounce > 3)) { //if(button is pressed and it's been more than 3ms since last "press")
    menu_bounce = current_time; 
    menu_flag = 0x01;
  }  //end if(menu pressed)
  if (digitalRead(menu_bt) && menu_flag && (current_time - menu_bounce > debounce_time)) { //if(button is reliesed and flag is activated and time since button press > debounce_time)
    menu_bounce = current_time + 35;
    menu_flag = 0x00;
    update_menu_flag = 1;
    if (sub_menu) {
      sub_menu = 0x00;
      return;
    } //end if(submenu)
    menu_number += 1;
    if (menu_number > MENU_MAX) menu_number = 1;
  }  //end if menu

  //ENTER BUTTON
  if (!digitalRead(ent_bt) && (current_time - enter_bounce > 3)) { //if(button is pressed and it's been more than 3ms since last "press")
    enter_bounce = current_time;
    enter_flag = 0x01;
  }  //end if(menu pressed)
  if (digitalRead(ent_bt) && enter_flag && (current_time - enter_bounce > debounce_time)) { //if(button is reliesed and flag is activated and time since button press > debounce_time)
    enter_bounce = current_time + 35;
    enter_flag = 0x00;
    sub_menu = 0x01;
    menu_select();
  }  //end if enter
}  //end read_bts


void menu_select() {
  switch (menu_number) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">TEMP:");
      lcd.print(read_temperature());
      lcd.print("C");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">Playing song:");
      lcd.setCursor(1, 1);
      lcd.print("Imperial March");
      play_music();
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">C");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">D");
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(">E");
      lcd.setCursor(1, 1);
      lcd.print(" ");
      break;
  }  //end switch
}  //end menu_select


float read_temperature() {
  float temperature = analogRead(0);
  temperature = temperature * 0.48828125 - 50;
  return temperature;
} //end read_temperature


// =====================================================================================
// --- Final do Programa ---
