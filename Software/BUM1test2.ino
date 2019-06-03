// Declaraciones relativas a los servos

#include <Servo.h>
 
Servo ServoD;     // Servo lado derecho
Servo ServoI;     // Servo lado izquierdo
Servo MiniServo;  // MiniServo del medidor
int pos = 90;     // Para almacenar la posición del servo derecho

// Uso de interrupciones para medir 

#define entrada 3        // Entrada asignada a la interrupción
#define medidor 0        // Puerto A/D del medidor de distancias
#define medir 2          // Pin para activar la medición

int distancia = 0;      // Valor obtenido en la conversión A/D
float mm = 0;           // Valor de la medición convertido a mm
int incomingByte;

volatile int cuentas = 0;
volatile int vale = LOW;  // Medición válida
volatile unsigned long ahora = 0;
volatile unsigned long antes = 0;

void setup()
{
  // Asigna pines a los servos
  ServoD.attach(9);        // Asigna el servo derecho al pin 9 (OUTPUT 2 de la TINKERKIT)
  ServoI.attach(10);       // Asigna el servo izquierdo al pin 10 (OUTPUT 1 de la TINKERKIT)
  MiniServo.attach(11);    // Asigna el miniservo al pin 11 (OUTPUT 0 de la TINKERKIT)

  // Inmoviliza servos  
  ServoD.write(92);  
  ServoI.write(95);  
  MiniServo.write(90);    
  
  pinMode(entrada, INPUT);           // Pin de entrada del medidor
  pinMode(medir, OUTPUT);            // Señal de disparo del medidor
  digitalWrite(medir, LOW);          // Inhibe mediciones
  Serial.begin(9600);                // Inicializamos la comunicación serie  
  Serial.println("Inicializado");

}
 
void loop()
{
  // Medición distancia
  
  antes = micros();                   // Instante actual
  pos = 0;                            // Inicializa contador
  digitalWrite(medir, HIGH);          // Activa medidor de distancia
  delay(3);                           // Pulso de más de 2ms de duración para provocar medición


  Serial.println("Iniciado medicion");
  attachInterrupt(1, mide, CHANGE);   // Activa interrupción en pin de entrada (3)  

  do
  {
    vale = digitalRead(3);
    pos += 1;
  }
  while (vale);                       // Espera desaparición detección propio pulso

  Serial.println("Esperando medicion");

  do
  {
    vale = digitalRead(3);
    pos +=1;
  }
  while (!vale);                       // Espera medición

  ahora = micros();                    // Instante recepción eco

  digitalWrite(medir, LOW);           // Detiene medición

  cuentas = ahora - antes;             // Tiempo transcurrido durante la medición en microsegundos
  Serial.print("pos = ");
  Serial.println(pos);
  Serial.print("Distancia... ");
  Serial.print(cuentas);
  Serial.print(" us= ");
  mm = (float)cuentas * (float)0.170;    // Convierte valor del PWM a mm
  Serial.print(mm);
  Serial.println(" milimetros");
  Serial.println(" ");

  detachInterrupt(1);            // Inhabilita interrupción
  
  // Mueve servo derecho adelante, izquierdo atrás y realiza barrido miniservo
  
  for(pos = 90; pos<=180; pos+=10)     
  {                                
    ServoD.write(pos+2);      
    ServoI.write(pos+5);   
    MiniServo.write(pos-45);              
    delay(100);                       
  }
  for(pos = 180; pos>=90; pos-=10)     
  {                                
    ServoD.write(pos+2);              
    ServoI.write(pos+5);   
    MiniServo.write(pos-45);              
    delay(100);                       
  }  

  MiniServo.write(90); // Devuelve el miniservo a la posición central

  delay(5000);                   // Insertamos una espera
}

// Rutina de servicio de la interrupción (No usada)
void mide()
{
  vale = digitalRead(entrada);       // Nivel actual de la entrada que ha provocado la interrupción
  if (vale) {                         // Nivel alto. Medición
    ahora = micros();                // Anota instante actual
  }
  else {
    ahora = antes + 200;                // Nivel bajo. No medición
  }
  vale = HIGH;
}
  

