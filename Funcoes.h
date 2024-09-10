#ifndef Funcoes_H_
#define Funcoes_H_

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

#endif
