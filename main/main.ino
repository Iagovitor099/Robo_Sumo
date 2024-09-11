//Pinos para o motor
#define velm1 4
#define m1a 15
#define m1b 2
#define tmp 5000

//Pino para o sensor Infravermelho
#define PinoSensor 13

/*Velocidade PWM*/
int vel = 255;



void ControleHorario(int vel, int polo1, int polo2,int PWM);

void ControleAntiHorario(int vel, int polo1, int polo2,int PWM);

void PararMotor(int polo1, int polo2,int PWM);

/* Em desenvolvimento
//declarando as tasks
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;
*/

void setup() {
  
  Serial.begin(115200);

  /*Declaraçõo do modo de cada pino*/
  pinMode(velm1, OUTPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(PinoSensor, INPUT);

  //SensorInfra = digitalRead(PinoSensor);
  PararMotor(m1a,m1b,velm1);

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
  
  /*
  ControleHorario(vel,m1a,m1b,velm1);
  delay(tmp);

  PararMotor(m1a,m1b,velm1);
  delay(100);

  ControleAntiHorario(vel,m1a,m1b,velm1);
  delay(tmp);
  */
  
  //Serial.println(digitalRead(PinoSensor));
  if(digitalRead(PinoSensor) == 0){
    delay(50);
    PararMotor(m1a,m1b,velm1);
    Serial.println(0);
    }else
    {
      Serial.println(1);
      //delay(100);
      ControleHorario(vel,m1a,m1b,velm1);
    }
  //delay(200);
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


void PararMotor(int polo1, int polo2,int PWM)
{
  analogWrite(PWM, 0);
  digitalWrite(polo1, LOW);
  digitalWrite(polo2, LOW);
}
