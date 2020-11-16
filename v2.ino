#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#define SS_PIN 10 //RX slave select
#define RST_PIN 9

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

String card_ID=""; //card UID

//Add as many cards you want 
String Name1="90735241";//first UID card
String Name2="145188254154";//second UID card
String Name3="15353114169";//third UID card
String Name4="13937143185";//fourth UID card
String Name5="Your ID";//
String Name6="Your ID";//

int NumbCard[6];//the number of cards. in my case I have 6 cards.
int j=0;  //incresd by one for every user you add
int statu[6];//the number of cards. in my case I have 6 cards.
int s=0;  //incresd by one for every user you add 
int const RedLed=A0;
int const GreenLed=A1;
int const Buzzer = 8; //buzzer to arduino pin 8
String Log;
String Name;//user name
String Number;//user number
String Dept;//user Department
String Year;//user Year

int n ;//The number of card you want to detect (optional)  
int ID=1;
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,ID,Date,Name,Number,Department,Year-Div,Card ID");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)

  pinMode(A0,OUTPUT);//RedLed
  pinMode(A1,OUTPUT);//GreenLed
  //pinMode(A2,OUTPUT);//Buzzer
  
lcd.begin(20,4);  
lcd.setCursor(4,0);  
lcd.print("Welcome !!!");//Wlecome Message will appear in the beginning. 

  delay(2000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Tap Your Card");
   }
   
void loop() {

  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }

 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID += mfrc522.uid.uidByte[i];
 }
 
 Serial.println(card_ID);//Uncomment this line to scan the card ID and appear it on Serial monitor.
 
       if(card_ID==Name1){
       Name="Amit Pol";//user name
       Number="TUS3S171812" ;//user number
       Dept="COMPS" ;//user Department
       Year="TE-C" ;//user Year
       j=0;//incresd by one for every user you add
       s=0;//++1
      }
      else if(card_ID==Name2){
       Name="Vijay Venu";//user name
       Number="TUS3F171806";//user number
       Dept="COMPS" ;//user Department
       Year="TE-C" ;//user Year
       j=1;//++1
       s=1;//++1
      }
      else if(card_ID==Name3){
       Name="Third employee";//user name
       Number=789101;//user number
       j=2;//++1
       s=2;//++1
      }
      else if(card_ID==Name4){
       Name="Fourth employee";//user name
       Number=789101;//user number
       j=3;//++1
       s=3;//++1
      }
      else if(card_ID==Name5){
       Name="Fiveth employee";//user name
       Number=789101;//user number
       j=4;//++1
       s=4;//++1
      }
      else if(card_ID==Name6){
       Name="Sixth employee";//user name
       Number=789101;//user number
       j=5;//incresd by one for every user you add
       s=5;//++1
      }
      else{
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print("UNAUTHORIZED");
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          tone(Buzzer, 1000); // Send 1KHz sound signal...
          delay(2000);        // ...for 2 sec
          noTone(Buzzer);     // Stop sound...
          lcd.clear();
          lcd.setCursor(3,0);
          lcd.print("Tap Your Card");
          goto cont;//go directly to line 188
     }

      if(NumbCard[j] == 0 && statu[s] == 0){
      statu[s]=1;
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print(Name);
       lcd.setCursor(0,1);
       lcd.print(Number);
       lcd.setCursor(0,2);
       lcd.print(Dept);
       lcd.setCursor(0,3);
       lcd.print(Year);
       digitalWrite(GreenLed,HIGH);
       digitalWrite(RedLed,LOW);
       tone(Buzzer, 5000); // Send 1KHz sound signal...
       delay(500);        // ...for 1 sec
       noTone(Buzzer);     // Stop sound...
       delay(2000);
       lcd.clear();
       lcd.setCursor(3,0);
       lcd.print("Tap Your Card");
       

      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.print(",");
      Serial.print(Dept); //send the Department to excel
      Serial.print(",");
      Serial.print(Year); //send the Year to excel
      Serial.print(",");
      Serial.println(card_ID); //send the card ID to excel
      /*Serial.print(",");
      Serial.print("");
      Serial.print(",");
      Serial.println("TIME");*/
      ID=ID+1;

      }
      /*else if(NumbCard[j] == 0){
      NumbCard[j] = 1;
      
      n++;//(optional)
     // lcd.clear();
     // lcd.setCursor(4,0);
     // lcd.print("Welcome ");
     // lcd.setCursor(0,1);
     // lcd.print(Name);
      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.print(",");
      Serial.print(card_ID); //send the card ID to excel
      Serial.print(",");
      Serial.print("TIME");
      Serial.print(",");
      Serial.println("");
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      ID=ID+1;
      }*/
      else if(statu[s] == 1){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(Name);
     lcd.setCursor(0,1);
     lcd.print("Already Present");
     digitalWrite(GreenLed,HIGH);
     digitalWrite(RedLed,LOW);
     tone(Buzzer, 5000); // Send 1KHz sound signal...
     delay(500);        // ...for 1 sec
     noTone(Buzzer);     // Stop sound...
      }
      delay(1000);
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Tap Your Card");

cont:
delay(2000);
digitalWrite(GreenLed,LOW);
digitalWrite(RedLed,LOW);
card_ID="";
}
    
