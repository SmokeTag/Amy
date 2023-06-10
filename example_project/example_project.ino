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

#define menu_bt 19     //Push button  [Analogic 5]
#define enter_bt  18     //Push button  [Analogic 4]
#define up_bt   17     //Push button  [Analogic 3]
#define down_bt 16     //Push button  [Analogic 2]

#define sensor_temp 0 //Temperature sensor [Analogic 0]

#define led 2        //Led

// =====================================================================================
// --- Project Constants ---
#define MENU_MAX 5             // number of menu itens
const int debounce_time = 30;  // time in milliseconds


// =====================================================================================
// --- Function Prototypes ---
void  read_bts();
bool  read_bt_enter();
bool  read_bt_menu();
bool  read_bt_up();
bool  read_bt_down();

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
  pinMode(enter_bt, INPUT_PULLUP);
  pinMode(up_bt, INPUT_PULLUP);
  pinMode(down_bt, INPUT_PULLUP);
  pinMode(led, OUTPUT);
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
        lcd.print("LED on");
        break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print(">LED on");
        lcd.setCursor(1, 1);
        lcd.print("LED off");
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print(">LED off");
        lcd.setCursor(1, 1);
        lcd.print("LED switch");
        break;
      case 5:
        lcd.setCursor(0, 0);
        lcd.print(">LED switch");
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
  if (read_bt_menu())   return;
  if (read_bt_enter ()) return;
  if (read_bt_up())     return;
  if (read_bt_down())   return;

}  //end read_bts

bool read_bt_menu() {
  static bool menu_flag = 0;
  static unsigned long menu_bounce = 0;
  unsigned long current_time = millis();
  //MENU BUTTON
  if (!digitalRead(menu_bt) && (current_time - menu_bounce > 3)) { //if(button is pressed and it's been more than 3ms since last "press")
    menu_bounce = current_time; 
    menu_flag = 0x01;
    return 1;
  }  //end if(menu pressed)
  if (digitalRead(menu_bt) && menu_flag && (current_time - menu_bounce > debounce_time)) { //if(button is reliesed and flag is activated and time since button press > debounce_time)
    menu_bounce = current_time + 35;
    menu_flag = 0x00;
    if (sub_menu) {
      update_menu_flag = 0x01;
      sub_menu = 0x00;
    } //end if(submenu)
    return 1;
  }  //end if menu
  return 0;
}

bool read_bt_enter() {
  static bool enter_flag = 0;
  static unsigned long enter_bounce = 0;
  unsigned long current_time = millis();
  //ENTER BUTTON
  if (!digitalRead(enter_bt) && (current_time - enter_bounce > 3)) { //if(button is pressed and it's been more than 3ms since last "press")
    enter_bounce = current_time; 
    enter_flag = 0x01;
    return 1;
  }  //end if(enter pressed)
  if (digitalRead(enter_bt) && enter_flag && (current_time - enter_bounce > debounce_time)) { //if(button is reliesed and flag is activated and time since button press > debounce_time)
    enter_bounce = current_time + 35;
    enter_flag = 0x00;
    sub_menu = 0x01;
    menu_select();
    return 1;
  }  //end if enter
  return 0;
}

bool read_bt_up() {
  static bool up_flag = 0;
  static unsigned long up_bounce = 0;
  unsigned long current_time = millis();
  //UP BUTTON
  if (!digitalRead(up_bt) && (current_time - up_bounce > 3)) { //if(button is pressed and it's been more than 3ms since last "press")
    up_bounce = current_time;
    up_flag = 0x01;
    return 1;
  }  //end if(up pressed)
  if (digitalRead(up_bt) && up_flag && (current_time - up_bounce > debounce_time)) { //if(button is reliesed and flag is activated and time since button press > debounce_time)
    up_bounce = current_time + 35;
    up_flag = 0x00;
    update_menu_flag = 0x01;
    menu_number--;
    if (menu_number < 1) menu_number = MENU_MAX;
    return 1;
  }  //end if up
  return 0;
}

bool read_bt_down() {
  static bool down_flag = 0;
  static unsigned long down_bounce = 0;
  unsigned long current_time = millis();
  //DOWN BUTTON
  if (!digitalRead(down_bt) && (current_time - down_bounce > 3)) { //if(button is pressed and it's been more than 3ms since last "press")
    down_bounce = current_time;
    down_flag = 0x01;
    return 1;
  }  //end if(down pressed)
  if (digitalRead(down_bt) && down_flag && (current_time - down_bounce > debounce_time)) { //if(button is reliesed and flag is activated and time since button press > debounce_time)
    down_bounce = current_time + 35;
    down_flag = 0x00;
    update_menu_flag = 0x01;
    menu_number += 1;
    if (menu_number > MENU_MAX) menu_number = 1;
    return 1;
  }  //end if down
  return 0;
}


void menu_select() {
  lcd.clear(); 
  switch (menu_number) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print(">TEMP:");
      lcd.print(read_temperature());
      lcd.print("C");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print(">Playing song:");
      lcd.setCursor(1, 1);
      lcd.print("Imperial March");
      play_music();
      lcd.setCursor(0, 0);
      lcd.print(">Song finished:");
      lcd.setCursor(1, 1);
      lcd.print("Imperial March");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print(">LED activated");
      digitalWrite(led, HIGH);
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print(">LED deactivated");
      digitalWrite(led, LOW);
      break;
    case 5:
      PORTD ^= (1<<led);
      if (PIND & (1<<led)) {
        lcd.setCursor(0, 0);
        lcd.print(">LED switch");
        lcd.setCursor(1, 1);
        lcd.print(">LED on");
      }
      else {
        lcd.setCursor(0, 0);
        lcd.print(">LED switch");
        lcd.setCursor(1, 1);
        lcd.print(">LED off");
      }
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
