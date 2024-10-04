#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//Definimos los pines de la pantalla 

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

//Almacena los valores ya transformados en la medida real para mostrarlos en la pantalla
float VCC = 0;
float VCC2 = 0;
float VCC3 = 0;
float VCC4 = 0;

//Almacenamos los valores analogicos de las entradas
float vcc1 = 0.0; //A0
float vcc2 =0.0;  //A1
float vcc3 = 0.0;  //A2
float vcc4 =0.0;   //A3


//Pendiente de la conversion 
float m= 9.6;
float b = -24.0;


void setup()   {
  
 //Definimos los pines como salidas para encender los leds en caso de exceder la tensión
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
 
  // Iniciamos comunicacion serie 
  Serial.begin(9600);

  //inicializamos la pantalla
  display.begin();
  display.setContrast(50);// Constraste
  delay(100);
  display.clearDisplay();   //Limpiamos pantalla
}
void loop()
{
  //Lectura de los pines analogicos
  vcc1 = analogRead(A0);
  vcc2 = analogRead(A1);
  vcc3 = analogRead(A2);
  vcc4 = analogRead(A3);

//Convertimos de a los valores reales 
  VCC =  (vcc1*m*4.9+b*1000)/1000.0;
  VCC2 = (vcc2*m*4.9+b*1000)/1000.0;
  VCC3 = (vcc3*m*4.9+b*1000)/1000.0;
  VCC4 = (vcc4*m*4.9+b*1000)/1000.0;

 // Funcionamiento de la pantalla
  display.clearDisplay();
  display.setTextSize(1);//Letra
  display.setCursor(0,0);//Posicion
  display.print("V1=");//Impresion
  display.println(VCC,1);

 // Encender led en caso de tension mayor a 20v
  if(VCC>20||VCC<-20){
  digitalWrite(9, HIGH);
  delay(60);
  digitalWrite(9, LOW);
  delay(60);
  
  }
   
//se repite lo mismo para las otras 3 entradas
   display.setTextSize(1);
  display.setCursor(0,10);
  display.print("V2=");
  display.println(VCC2,1);
    if(VCC2>20||VCC2<-20){
  digitalWrite(10, HIGH);
  delay(60);
  digitalWrite(10, LOW);
  delay(60);
 
  }

  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("V3=");
  display.println(VCC3,1);
    if(VCC3>20||VCC3<-20){
  digitalWrite(11, HIGH);
  delay(50);
  digitalWrite(11, LOW);
  delay(50);
  
  }

  display.setTextSize(1);
  display.setCursor(0,30);
  display.print("V4=");
  display.println(VCC4,1);
    if(VCC4>20||VCC4<-20){
  digitalWrite(8, HIGH);
  delay(50);
  digitalWrite(8, LOW);
  delay(50);
  
  }

 Serial.print("V1:");
 Serial.println(VCC);
 Serial.print("V2:");
 Serial.println(VCC2);
 Serial.print("V3:");
 Serial.println(VCC3);
 Serial.print("V4:");
 Serial.println(VCC4);

  display.display();
  delay(1); ;  
 
}










