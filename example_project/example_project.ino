// =====================================================================================
// --- Libriry ---
#include <LiquidCrystal.h>


// =====================================================================================
// --- Hardware Mapping ---
#define db7 7
#define db6 6
#define db5 5
#define db4 4
#define db3 11
#define db2 10
#define db1 9
#define db0 8

#define rs 13
#define en 12

#define menu_bt 19
#define ent_bt 18


// =====================================================================================
// --- Project Constants ---
#define MENU_MAX 5
const int debounce_time = 30;  // time in milliseconds


// =====================================================================================
// --- Function Prototypes ---
void read_bts();
void menu_select();


// =====================================================================================
// --- Global Variables ---
int menu_number = 1;
bool sub_menu = 0;


// =====================================================================================
// --- Inicial config ---
LiquidCrystal lcd(rs, en, db0, db1, db2, db3, db4, db5, db6, db7);
void setup() {
  lcd.begin(16, 2);
  pinMode(menu_bt, INPUT_PULLUP);
  pinMode(ent_bt, INPUT_PULLUP);
  lcd.write('>');
}  //end setup


// =====================================================================================
// --- Loop Infinito ---
void loop() {
  if (!sub_menu) {
    switch (menu_number) {
      case 1:
        lcd.setCursor(1, 0);
        lcd.print("1");
        lcd.setCursor(1, 1);
        lcd.print("2");
        break;
      case 2:
        lcd.setCursor(1, 0);
        lcd.print("2");
        lcd.setCursor(1, 1);
        lcd.print("3");
        break;
      case 3:
        lcd.setCursor(1, 0);
        lcd.print("3");
        lcd.setCursor(1, 1);
        lcd.print("4");
        break;
      case 4:
        lcd.setCursor(1, 0);
        lcd.print("4");
        lcd.setCursor(1, 1);
        lcd.print("5");
        break;
      case 5:
        lcd.setCursor(1, 0);
        lcd.print("5");
        lcd.setCursor(1, 1);
        lcd.print("1");
        break;
    }  //end switch
  }    //end if(!sub_menu)
  read_bts();
}  //end loop


// =====================================================================================
// --- Desenvolvimento das Funções ---
void read_bts() {
  static bool menu_flag = 0, enter_flag = 0;
  static unsigned long menu_bounce = 0, enter_bounce = 0;
  unsigned long current_time = millis();

  if (!digitalRead(menu_bt) && (current_time - menu_bounce > 3)) {
    menu_bounce = current_time;
    menu_flag = 0x01;
  }  //end if(menu pressed)
  if (!digitalRead(ent_bt) && (current_time - enter_bounce > 3)) {
    enter_bounce = current_time;
    enter_flag = 0x01;
  }  //end if(menu pressed)

  if (digitalRead(menu_bt) && menu_flag && (current_time - menu_bounce > debounce_time)) {
    menu_bounce = current_time + 35;
    menu_flag = 0x00;
    menu_number += 1;
    if (menu_number > MENU_MAX) menu_number = 1;
  }  //end if menu
  if (digitalRead(ent_bt) && enter_flag && (current_time - enter_bounce > debounce_time)) {
    enter_bounce = current_time + 35;
    enter_flag = 0x00;
    sub_menu = !sub_menu;
    menu_select();
  }  //end if enter
}  //end read_bts


void menu_select() {
  switch (menu_number) {
    case 1:
      lcd.setCursor(1, 0);
      lcd.print("A");
      lcd.setCursor(1, 1);
      lcd.print(" ");
      break;
    case 2:
      lcd.setCursor(1, 0);
      lcd.print("B");
      lcd.setCursor(1, 1);
      lcd.print(" ");
      break;
    case 3:
      lcd.setCursor(1, 0);
      lcd.print("C");
      lcd.setCursor(1, 1);
      lcd.print(" ");
      break;
    case 4:
      lcd.setCursor(1, 0);
      lcd.print("D");
      lcd.setCursor(1, 1);
      lcd.print(" ");
      break;
    case 5:
      lcd.setCursor(1, 0);
      lcd.print("E");
      lcd.setCursor(1, 1);
      lcd.print(" ");
      break;
  }  //end switch
}  //end menu_select


// =====================================================================================
// --- Final do Programa ---
