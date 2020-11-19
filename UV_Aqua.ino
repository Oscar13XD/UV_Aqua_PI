#include <SoftwareSerial.h> // libreria que permite establecer pines digitales
                            // para comunicacion serie
#include <Servo.h>
Servo servo1;
int pinServo=2;
int pulMin=500;
int pulMax=2500;

SoftwareSerial Bluetooth(10, 11);   // pin 10 como RX, pin 11 como TX
int ph_pin = A0; // A0 -> Po
char DATO =0;
int m_4 = 623;
int m_7 = 731; //agua

int analisisPH(int medida,int prom);


void setup() {
  Serial.begin(9600);
  Bluetooth.begin(38400);
  servo1.attach(pinServo, pulMin, pulMax);
  servo1.write(180);
  }

void loop() {
  if (Bluetooth.available()){
    DATO = Bluetooth.read();
    if(DATO=='I'){
    Serial.println("LEIDO");
    servo1.write(90);
    float pH=analisisPH(0,0);
    Serial.println(pH); 
    }
    if(DATO=='P'){
      servo1.write(0);
    }
    if(DATO=='N'){
      servo1.write(180);
    }
    if(DATO=='F'){
      servo1.write(180);
    } 
  }
}


int analisisPH(int medida,int prom){
  for(int i=0;i<20;i++){
    medida = analogRead(ph_pin);
    prom = prom + medida;
    delay(50);       
  }
  prom = prom/20;
  Serial.print("Medida: ");
  Serial.print(prom);
  
  float Po = 7 + ((medida - m_7 ) * 3 / ( m_7 - m_4 )); //calibracion
  //Serial.print("\tPH: ");
  //Serial.print(Po, 2);
  //Serial.println("");
  return Po;
}
