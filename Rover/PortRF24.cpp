/*
  PortRF24.cpp
  ver. 2022.01
  namik.can@hotmail.com
  descriptions:
  // declaration of RF24 controller pins												Data_Package
  #define joy1_X 			A1 	// joystick_1 x axis (VRx)							byte djoy1_X;
  #define joy1_Y 			A0 	// joystick_1 y axis (VRy)							byte djoy1_Y;
  #define joy1_button A4 	// joystick_1 button										byte djoy1_button;
  #define joy2_X 			A3 	// joystick_2 x axis (VRx)							byte djoy2_X;
  #define joy2_Y 			A2 	// joystick_2 y axis( VRy)							byte djoy2_Y;
  #define joy2_button A5 	// joystick-2 button										byte djoy2_button;
  #define pot_1 			A6 	// potansiyometre_1											byte dpot_1;
  #define pot_2 			A7 	// potansiyometre_2											byte dpot_2;
  #define switch_1 		2 	// switch_1															byte dswitch_1;
  #define switch_2 		3 	// switch_2 														byte dswitch_2;
  #define button_1 		6 	// button_1 														byte dbutton_1;
  #define button_2 		4		// button_2 														byte dbutton_2;
  #define button_3 		5 	// button_3															byte dbutton_3;
  #define button_4 		7 	// button_4 														byte dbutton_4;
  //--------------------------------------------------------
  #define CE 					9 	// NRF24L01 CE pin connection
  #define CSN 				10 	// NRF24L01 CSN pin connection
  #define SCK					13	// Serial Clock (SCLK) pin
  #define MOSI				11	// Master Out Slave In (MOSI) pin
  #define	MISO				12	// Master In Slave Out (MISO) pin
  //#define IRQ 			NC	//
  //--------------------------------------------------------

*/
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
// include these libraries
// #include <stduint8_t const.h>
// #include <avr/uint8_t consterrupt.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <Servo.h>
#include "PortRF24.h"
#include "L298ND.h"
//--------------------------------------------------------
#define CE           9   // NRF24L01 CE pin connection
#define CSN         10  // NRF24L01 CSN pin connection
#define MOSI        11  // Master Out Slave In (MOSI) pin
#define MISO        12  // Master In Slave Out (MISO) pin
#define SCK         13  // Serial Clock (SCLK) pin
//#define IRQ       NC  //
//--------------------------------------------------------
#define pinServo    2  //
//--------------------------------------------------------
//const byte address[6] = "00001";
//unsigned long lastReceiveTime = 0;
//unsigned long currentTime = 0;
//--------------------------------------------------------
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  bool djoy1_button;
  bool djoy2_button;
  bool dswitch_1;
  bool dswitch_2;
  bool dbutton_1;
  bool dbutton_2;
  bool dbutton_3;
  bool dbutton_4;
  byte dpot_1;
  byte dpot_2;
  byte djoy1_X;
  byte djoy1_Y;
  byte djoy2_X;
  byte djoy2_Y;
  //byte pitch;
  //byte roll;
};
//Create a variable with the above structure
Data_Package data;
//--------------------------------------------------------
// declare variables
bool joy1_button;
bool joy2_button;
bool switch_1;
bool switch_2;
bool button_1;
bool button_2;
bool button_3;
bool button_4;
byte pot_1;
byte pot_2;
byte joy1_X;
byte joy1_Y;
byte joy2_X;
byte joy2_Y;



//--------------------------------------------------------
uint8_t servoDegree;
//--------------------------------------------------------
// Declaration classes
RF24 radio(CE, CSN);   	// nRF24L01 (CE, CSN)
L298ND  l298nd;	  	  	//
Servo servoCam;					//

PortRF24::PortRF24() {
  // Constructor
}

PortRF24::~PortRF24() {
  // Destructor
}
//
void PortRF24::initialization() {
  Serial.begin(115200);	//
  resetData();                //
  //pinMode(pinServo, OUTPUT);
  servoCam.attach(pinServo);  //
  servoCam.write(90);         //
  //delay(15);
  // radio communication
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
  // the address of receiver which receive data
  radio.openReadingPipe(0, 0x0000000001);		//
  //radio.setAutoAck(false);					//
  radio.setDataRate(RF24_250KBPS);		//
  //radio.setPALevel(RF24_PA_LOW);		//
  radio.startListening();							// enable the module as receiver
}
//
void PortRF24::resetData() {
  // Set initial default values
  data.djoy1_button = true;
  data.djoy2_button = true;
  data.dswitch_1 = true;
  data.dswitch_2 = true;
  data.dbutton_1 = true;
  data.dbutton_2 = true;
  data.dbutton_3 = true;
  data.dbutton_4 = true;
  data.dpot_1	= 1;
  data.dpot_2 = 1;
  data.djoy1_X = 127;
  data.djoy1_Y = 127;
  data.djoy2_X = 127;
  data.djoy2_Y = 127;
 
}
//
void PortRF24::displayResults() {
  // Check whether there is data to be received
  if (radio.available()) {
    // Read the whole data and store it into the 'data' structure
    radio.read(&data, sizeof(Data_Package));
  }
  // lastReceiveTime = millis(); // At this moment we have received the data
  // Print the data in the Serial Monitor
  Serial.println("-----------------------------------------------");
  Serial.print(" Joy1_button:\t ");  Serial.println(data.djoy1_button);
  Serial.print(" Joy2_button:\t ");  Serial.println(data.djoy2_button);
  Serial.print(" Switch1:\t ");      Serial.println(data.dswitch_1);
  Serial.print(" Switch2:\t ");      Serial.println(data.dswitch_2);
  Serial.print(" Button1:\t ");      Serial.println(data.dbutton_1);
  Serial.print(" Button2:\t ");      Serial.println(data.dbutton_2);
  Serial.print(" Button3:\t ");      Serial.println(data.dbutton_3);
  Serial.print(" Button4:\t ");      Serial.println(data.dbutton_4);
  Serial.print(" Pot1:\t    ");      Serial.println(data.dpot_1);
  Serial.print(" Pot2:\t    ");      Serial.println(data.dpot_2);
  Serial.print(" Joy1_X:\t  ");      Serial.println(data.djoy1_X);
  Serial.print(" Joy1_Y:\t  ");      Serial.println(data.djoy1_Y);
  Serial.print(" Joy2_X:\t  ");      Serial.println(data.djoy2_X);
  Serial.print(" Joy2_Y:\t  ");      Serial.println(data.djoy2_Y);
  Serial.print("-----------------------------------------------");
  //------------------------------------------------------
  delay(1000);
}
//--------------------------------------------------------
// Navigasyon Functions
//--------------------------------------------------------
//
void PortRF24::speedStepX2(uint8_t dstep) {
  if (dstep > 138) {
    dstep = 2 * (dstep - 128);
    l298nd.toLeft(dstep);
  } else if (dstep < 118) {
    dstep = 2 * (127 - dstep);
    l298nd.toRight(dstep);
  } else
    l298nd.fastStop();
}
//
void PortRF24::speedStepY2(uint8_t dstep) {
  if (dstep > 138) {
    dstep = 2 * (dstep - 128);
    l298nd.toForward(dstep);
  } else if (dstep < 118) {
    dstep = 2 * (127 - dstep);
    l298nd.toBackward(dstep);
  } else
    l298nd.fastStop();
}
//
void PortRF24::patrol() {
  // Check whether there is data to be received
  if (radio.available()) {
    // Read the whole data and store it into the 'data' structure
    radio.read(&data, sizeof(Data_Package));
  }
  // lastReceiveTime = millis(); // At this moment we have received the data
  //--- status -------------------------------------------
  joy1_button = data.djoy1_button;
  if (joy1_button == true) {
    joy1_X = data.djoy1_X;
    joy1_X = map(joy1_X, 0, 255, 80, 0);
    servoCam.write(joy1_X);
    delay(70);
  }


  // joy2_button
  // switch_1
  // switch_2
  // button_1
  // button_2
  // button_3
  // button_4
  //--- values -------------------------------------------
  // pot_1
  // pot_2
  //--- movements ----------------------------------------

  //joy1_X = data.djoy1_X-128; servoDegree = map(joy1_X, 0, 255, 0, 180); servoCam.write(servoDegree);
  // joy1_Y
  joy2_button = data.djoy2_button;
  if (joy2_button == true){
      joy2_X = data.djoy2_X; speedStepX2(joy2_X);
  }else{
    joy2_Y = data.djoy2_Y; speedStepY2(joy2_Y);
  }

}




/*attach()

  Bu fonksiyon Servo motorumuzun hangi pinde takılı olduğunu Arduino’muza söylediğimiz fonksiyondur. Mesela myservo.attach(9) kodu ile servo motorumuzun 9. pinde olduğunu Arduino’muza söyleriz. Böylece Servo motorunnun yerini bildirdikten sonra artık işlemlerimizi yapabiliriz.
  write()

  Bu fonksiyon ise servo motorumuzun açılı olarak 0 ile 180 derece arasında döndürmemizi sağlar. Örnek olarak servo.write(45) komutu ile 0 derecede bulunan motorumuz 45 derecelik bir açı alacak şekilde tam hızda döndürmüş oluruz.
  read()

  Servo motorumuz en son döndürdüğümüz açıda durur ve bekler. Bu yüzden servo motorumuzun hangi açıda bulunduğu bulmak için ise servo.read() komutu ile read() fonksiyonumuzu kullanırız. Böylece bu komut bize 0 ile 180 derece arasında bir sayı değeri döndürür. Bu sayı değeri de servo motorumuzun o anki açısıdır.
  attached()

  Servo motorumuzun belirttiğimiz pinde takılı olup olmadığını anlamak için ise servo.attached() komutu ile attached() fonksiyonumuzu kullanarak haberdar olabiliriz. Bu fonksiyonu kullandığımızda eğer Servo motor takılı ise true , değilse false değerini döndürerek bize cevap verir.
*/
