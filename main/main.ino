#include <HCSR04.h>

//Definindo os pinos echo e trig
#define trig 32
#define echo 33

UltraSonicDistanceSensor distanceSensor(32, 33);


//Pinos para o motor 1
#define velm1 12 //pino de controle motor 1
#define m1a 14
#define m1b 13
#define tmp 5000


//Pinos para o motor 2
#define velm2 27 //pino de controle motor 2
#define m2a 15
#define m2b 2

//Pino para o sensor Infravermelho
#define PinoSensor 18


const int canalPWM = 0; //canal PWM na esp vai de 0 a 15
const int freq = 5000; // Frequência de 5kHz
const int resolution = 8; // ((2^8) -1) = 255

int vel = 254;


//--------------Funções-------------//

void ControleHorario(int vel, int polo1, int polo2,int PWM);

void ControleAntiHorario(int vel, int polo1, int polo2,int PWM);

void PararMotor(int polo1, int polo2,int PWM);


void setup() {
  
  Serial.begin(115200);
  ledcAttachChannel(velm1, freq, resolution, canalPWM);
  
  /*Pinos motor 1*/
  pinMode(velm1, OUTPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);

  
  //Pinos motor2 
  pinMode(velm2, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);

  /*Pino sensor Infravermelho */
  pinMode(PinoSensor, INPUT);

  //SensorInfra = digitalRead(PinoSensor);
  PararMotor(m1a,m1b,velm1);
  PararMotor(m2a,m2b,velm2);

}


void loop() {

  // Convertendo distancia em Cm para mm
  long distanciaCm = distanceSensor.measureDistanceCm();
  long distanciaMm = distanciaCm * 10;
  
  //Serial.println(digitalRead(PinoSensor));
  if(digitalRead(PinoSensor) == 0){
    //delay(50);
    
    ControleHorarioPWM(canalPWM, m1a,m1b);
    
    //ControleHorario(vel,m1a,m1b,canalPWM);
    ControleHorario(vel,m2a,m2b,velm2);
    Serial.println(0);
    Serial.flush();
    }else
    {
      Serial.println(1);
      Serial.flush();
      
      PararMotorPWM(canalPWM,m1a,m1b);
      PararMotor(m2a,m2b,velm2);
      //delay(1000);
      
    }
}

void ControleHorario(int vel, int polo1, int polo2,int PWM)
{
  analogWrite(PWM, vel);
  digitalWrite(polo1, HIGH);
  digitalWrite(polo2, LOW);
}

void ControleAntiHorario(int vel, int polo1, int polo2,int PWM)
{
  analogWrite(PWM, vel);
  digitalWrite(polo1, LOW);
  digitalWrite(polo2, HIGH);
}


void PararMotor(int polo1, int polo2, int PWM) {
  analogWrite(PWM, 0);
  digitalWrite(polo1, HIGH);
  digitalWrite(polo2, HIGH);
}

void ControleHorarioPWM(int canalPWM, int polo1, int polo2)
{   
    
    ledcWriteChannel(canalPWM, 254);
    digitalWrite(polo1, HIGH);
    digitalWrite(polo2, LOW);
}


void PararMotorPWM(int canalPWM, int polo1, int polo2)
{
    ledcWriteChannel(canalPWM, 254);
    digitalWrite(polo1, HIGH);
    digitalWrite(polo2, HIGH);
}
