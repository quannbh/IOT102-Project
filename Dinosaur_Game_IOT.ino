#include <LiquidCrystal.h>
#define led1 8

LiquidCrystal lcd(12, 11, 5, 4, 7, 6);

const int upButton = 2;
const int downButton = 3;
const int backLight = 13;

int dinosaurPosition = 1;
int upButtonState = 0;
int downButtonState = 0;

int buttonPushCounter = 0;
int buttonState = 0;
int lastbuttonState = 0;

int RS;
byte pointer[8] = {
  B00111,
  B00111,
  B10111,
  B11100,
  B11111,
  B01010,
  B01010,
};

byte die[8] = {
  B00000,
  B00000,
  B10101,
  B10101,
  B10101,
  B01110,
  B00100,
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(0,pointer);
  lcd.createChar(1,die);
  pinMode(led1, OUTPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(backLight, OUTPUT);
  pinMode(upButton, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);      // sử dụng điện trở kéo lên cho chân số 2, ngắt 0
  attachInterrupt(0, power, FALLING); // gọi hàm tatled liên tục khi còn nhấn nút
attachInterrupt(1, game, FALLING);
}
int buttonPushCounter1 = 0;
void power(){
    upButtonState = digitalRead(upButton);
  if (upButtonState != lastbuttonState) {
    if (upButtonState == 1) {
      buttonPushCounter++;
    }
  }
 lastbuttonState = upButtonState;
  if (buttonPushCounter % 2 == 0) {
    digitalWrite(backLight, HIGH);
	buttonPushCounter++;
  } else {
    digitalWrite(backLight, LOW);
    buttonPushCounter++;
   
  }
}


int lastbuttonState1 = 0;
unsigned long buttonTime1;
unsigned long buttonTime2;
void game(){
  downButtonState = digitalRead(downButton);
  if (downButtonState != lastbuttonState1) {
    if (downButtonState == 1) {
      buttonPushCounter1++;
    }
  }
 lastbuttonState1 = downButtonState;
  if (buttonPushCounter1 % 2 == 0) {
    lcd.setCursor(0,0);
    lcd.print(char(0));
    lcd.setCursor(0,1);
    lcd.print(" ");
    buttonTime1 = millis();
	buttonPushCounter1++;
  } else {
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print(char(0));
    buttonTime2 = millis();
    buttonPushCounter1++;
  }
}

int countt=0;
void loop() {
  digitalWrite(led1,HIGH);
  if(buttonPushCounter1==0){
  lcd.setCursor(2, 0);
  lcd.print("Dinosaur Game");
  delay(100);
  } else if (buttonPushCounter1==1) {
    lcd.clear();
    delay(50);
    lcd.setCursor(2,0);
    lcd.print("Press button");
    delay(50);
  } else if(buttonPushCounter1>=2) {
    buttonPushCounter1=0;
    lcd.setCursor(2,0);
    lcd.print("             ");
    delay(100);
	gameset();
  } 
  }


void gameset(){
  bool gaming = true;
  while(true){
    int k;
    for(int i = random(14,28); i >=0; i--){

      if(i>=11){
      lcd.setCursor(i-11,0);
      lcd.print("  ");
      }
      if(i>=12){
      lcd.setCursor(i-12,0);
      lcd.print(char(1));
      }
      if(i>=9){
      lcd.setCursor(i-9,1);
      lcd.print(" ");
      }
      if(i>=10){
      lcd.setCursor(i-10,1);
      lcd.print(char(1));
      }
      
      if(i>=7){
      lcd.setCursor(i-7,0);
      lcd.print(" ");
      }
      if(i>=8){
      lcd.setCursor(i-8,0);
      lcd.print(char(1));
      }
      
      if(i>=5){
      lcd.setCursor(i-5,1);
      lcd.print(" ");
      }
      if(i>=6){
      lcd.setCursor(i-6,1);
      lcd.print(char(1));
      }
      
      if(i>=3){
      lcd.setCursor(i-3,0);
      lcd.print(" ");
      }
      if(i>=4){
      lcd.setCursor(i-4,0);
      lcd.print(char(1));
      }
      
      if(i>=1){
	    lcd.setCursor(i-1,1);
      lcd.print(" ");
      }
      if(i>=2){
      lcd.setCursor(i-2,1);
      lcd.print(char(1));
      }
     
      delay(800);
      
      if(i==13||i==9||i==5){
        unsigned long Timer1= millis();
      }
      if(i==12||i==8||i==4){
      	unsigned long Timer2=millis();
        if(700.0 < Timer2-buttonTime2 && buttonTime2< buttonTime1){
          Serial.print("1");
          gaming = false;
          break;
          buttonPushCounter1=0;
          
        }
      }
      
      if(i==11||i==7||i==3){
        unsigned long Timer3= millis();
      }
      if(i==10||i==6||i==2){
      	unsigned long Timer4=millis();
        if(700.0 < Timer4-buttonTime1 && buttonTime1< buttonTime2){
          gaming = false;
          break;
          buttonPushCounter1=0;
        }
      }
      }
      if(!gaming){
    lcd.clear();
    lcd.setCursor(2,0);
    digitalWrite(led1,HIGH);
    lcd.print("GAME OVER");
    delay(3000);
    digitalWrite(led1,LOW);
    buttonPushCounter1=0;
    break;
  }
      }
  
  }
