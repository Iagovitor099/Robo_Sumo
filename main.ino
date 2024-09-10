#define velm1 4
#define m1a 15
#define m1b 2
#define tmp 5000

int vel = 165;

void ControleHorario(int vel, int polo1, int polo2,int PWM);

void ControleAntiHorario(int vel, int polo1, int polo2,int PWM);

void PararMotor(int polo1, int polo2,int PWM);



void setup() {
  //Serial.begin(115200);
  pinMode(velm1, OUTPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);

  analogWrite(velm1, 0);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);

}

void loop() {
  ControleHorario(vel,m1a,m1b,velm1);
  delay(tmp);

  PararMotor(m1a,m1b,velm1);
  delay(100);

  ControleAntiHorario(vel,m1a,m1b,velm1);
  delay(tmp);
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
