#include <HCSR04.h>

//Definindo os pinos echo e trig
#define trig 32
#define echo 33

UltraSonicDistanceSensor distanceSensor(32, 33);

//Pinos para o motor 1
#define velm1 12
#define m1a 14
#define m1b 13
#define tmp 5000


//Pinos para o motor 2
#define velm2 27
#define m2a 15
#define m2b 2

//Pino para o sensor Infravermelho
#define PinoSensor 18

/*Velocidade PWM*/
int vel = 180;



void ControleHorario(int vel, int polo1, int polo2,int PWM);

void ControleAntiHorario(int vel, int polo1, int polo2,int PWM);

void PararMotor(int polo1, int polo2,int PWM);

/* Em desenvolvimento
//declarando as tasks
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;
*/

void setup() {
  
  Serial.begin(9600);

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

  /*EM DESENVOLVIMENTO -- CRIAÇÃO DE TAREFASÃ MULTICORE --
   
  //Tarefa 1 vai rodar no Core 0, com prioridade 1
  xTaskCreatePinnedToCore(
    ControleHorario,
    "ControleHorario",
    5000,
    NULL,
    1,
    NULL
    taskCoreZero);
  
  //Tarefa 2 vai rodar no Core 0, com prioridade 1
  xTaskCreatePinnedToCore(
    ControleAntiHorario,
    "ControleAntiHorario",
    5000,
    NULL,
    1,
    NULL
    taskCoreZero);
  
   //Tarefa 3 vai rodar no Core 1, com prioridade 2
  xTaskCreatePinnedToCore(
    SensorInfra,
    "SensorInfra",
    5000,
    NULL,
    2,
    NULL
    taskCoreOne);*/
}


void loop() {

  // Convertendo distancia em Cm para mm
  long distanciaCm = distanceSensor.measureDistanceCm();
  long distanciaMm = distanciaCm * 10;
  
  //Serial.println(digitalRead(PinoSensor));
  if(digitalRead(PinoSensor) == 0){
    //delay(50);
   
    ControleHorario(vel,m1a,m1b,velm1);
    ControleHorario(vel,m2a,m2b,velm2);
    Serial.println(0);
    Serial.flush();
    }else
    {
      Serial.println(1);
      Serial.flush();
      PararMotor(m1a,m1b,velm1);
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
