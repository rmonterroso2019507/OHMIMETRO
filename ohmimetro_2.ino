/*
  Fundacion Kinal
  Centro Educativo Tecnico Kinal
  Electronica
  Grado: Quinto
  Curso: Taller de Electronica Digital
  Alumno: Roberto Antonio Monterroso Aguilar
  Seccion: A
  Carne: 2019507
  Proyecto: Uso de interrupciones de termporizador
*/
//librerias a usar
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Directivas de preprocesador
#define direccion_lcd 0x27 //Direccion del I2C del LCD
#define filas 2
#define columnas 16
#define Res_2 A0//Lectura de entrada

//Variables
int Res_1();

//Constructor
LiquidCrystal_I2C LCD_Roberto(direccion_lcd, columnas, filas); 

  void setup() {
    Serial.begin(9600);
    Serial.print("Ohmimetro de ROB");
    pinMode(Res_2, INPUT);
    LCD_Roberto.init();
    LCD_Roberto.backlight();
}

void loop() {
  LCD_Roberto.setCursor(0,0);
  LCD_Roberto.print("Ohmimetro de ROBERTO :D");
  unsigned long int ohms = Res_1();
  LCD_Roberto.setCursor(0,1);
  LCD_Roberto.print(ohms);
  LCD_Roberto.print(" ohms           ");
}

 int Res_1(){
    int lectura = 0;//Valor de voltaje en el divisor de voltaje
    int Ve = 5;// Voltaje de entrada
    float Vr2 = 0;//Voltaje de R2
    float R1 = 10000;// Valor de la Resistencia 
    float R2 = 0;// valor de la recistencia a encontrar
    float relacion = 0;

     lectura = analogRead(Res_2);
   if(lectura) //Si detecta una resistencia
  {
    relacion = lectura * Ve;   // Opera el valor de la lectura del divisor por el voltaje de alimentacion
    Vr2 = (relacion)/1024.0;  //Convierte la relacion a una escala de 0-1023 RAW para calcular el voltaje
    relacion = (Ve/Vr2) -1;  // La Operacion deja un entero 1 parasito que se elimina con el -1 para obtener el valor real
    R2= (R1 * relacion)-30; //Multiplica la R1 por la relacion para obtener el valor de R2
    LCD_Roberto.println(R2);   //Imprime resultado de la operacion
    return R2;
  } 
  
  else {   
    Serial.println("Conecta una resistencia");//Si no detecta una resistencia
    return 0;
    }
  }
  
