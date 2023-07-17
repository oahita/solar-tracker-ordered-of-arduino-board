#include <Servo.h>

Servo servomotor_orizontala; //Acesta este servomotorul de pe orizontala
int servo_intrare_unghi_orizontala = 0; //Atribuim acestui microservomotor unghiul de 0 grade.
int servo_limita_superioara_orizontala = 180; //Limita maxima este de 180 grade.
int servo_limita_inferioara_orizontala = 5;   //Limita minima este de 5 grade.

Servo servomotor_verticala; // Acesta este servomotorul de pe verticala.
int servo_intrare_unghi_verticala = 0;//Atribuim acestuia unghiul de 0 grade.
int servo_limita_superioara_verticala = 180;//Limita maxima este de 180 grade.
int servo_limita_inferioara_verticala = 5;//limita minima este de 5 grade.

int ldr_dreapta_sus = 0; //fotorezistorul pentru dreapta sus conectat la pinul analogic A0 
int ldr_stanga_sus = 2; //fotorezistorul pentru stanga sus conectat la pinul analogic  A2 

int ldr_dreapta_jos = 1; //fotorezistorul pentru dreapta jos conectat la pinul analogic A1
int ldr_stanga_jos = 3; //fotorezistorul pentru stanga jos conectat la pinul analogic  A3 


 void setup () 
 {
  Serial.begin(9600);
  servomotor_orizontala.attach(4); //Micro servomotorul pentru orizontala se va conecta la pinul digital cu numarul 4
  servomotor_orizontala.write(0);//Scriem pozitia in care se afla micro servomotorul,pentru miscarea pe orizontala
  
  servomotor_verticala.attach(5); //Micro servomotorul pentru verticala se va conecta la pinul digital cu numarul 5
  servomotor_verticala.write(0);//Scriem pozitia in care se afla micro servomotorul,pentru miscarea pe veticala
  delay(1000); // Delay
 }

void loop()
{
  servo_intrare_unghi_orizontala = servomotor_orizontala.read();
  servo_intrare_unghi_verticala= servomotor_verticala.read();
  
  
  int stanga_sus = analogRead(ldr_stanga_sus); //citim valorile analogice din LDR,pentru stanga-sus
  int dreapta_sus = analogRead(ldr_dreapta_sus); //citim valorile analogice din LDR,pentru dreapta-sus
  int stanga_jos = analogRead(ldr_stanga_jos); //citim valorile analogice din LDR,pentru stanga-jos
  int dreapta_jos = analogRead(ldr_dreapta_jos); //citim valorile analogice din LDR,pentru dreapta-jos
  
  
  int medie_sus = (stanga_sus + dreapta_sus) / 2; //Facem media aritmetica dintre valorile analogice de la stanga-sus si dreapta-sus
  int medie_jos = (stanga_jos + dreapta_jos) / 2; //Facem media aritmetica dintre valorile analogice de la stanga-jos si dreapta-jos
  int medie_stanga = (stanga_sus + stanga_jos) / 2; //Facem media aritmetica dintre valorile analogice de la stanga-sus si stanga-jos
  int medie_dreapta = (dreapta_sus + dreapta_jos) / 2; //Facem media aritmetica dintre valorile analogice de la dreapta-sus si dreapta-jos

  if (medie_sus < medie_jos)
  {
    servomotor_verticala.write(servo_intrare_unghi_verticala -1);
    if (servo_intrare_unghi_verticala > servo_limita_superioara_verticala) 
     { 
      servo_intrare_unghi_verticala = servo_limita_superioara_verticala;
     }
    delay(8);
  }
  else if (medie_jos < medie_sus)
  {
    servomotor_verticala.write( servo_intrare_unghi_verticala +1);
    if (servo_intrare_unghi_verticala < servo_limita_inferioara_verticala )
  {
    servo_intrare_unghi_verticala =servo_limita_inferioara_verticala ;
  }
    delay(8);
  }
  else 
  {
    servomotor_verticala.write(servo_intrare_unghi_verticala);
  }
  
  if (medie_stanga > medie_dreapta)
  {
    servomotor_orizontala.write(servo_intrare_unghi_orizontala -1);
    if (servo_intrare_unghi_orizontala > servo_limita_superioara_orizontala)
    {
    servo_intrare_unghi_orizontala = servo_limita_superioara_orizontala;
    }
    delay(8);
  }
  else if (medie_dreapta > medie_stanga)
  {
    servomotor_orizontala.write(servo_intrare_unghi_orizontala +1);
    if (servo_intrare_unghi_orizontala < servo_limita_inferioara_orizontala)
     {
     servo_intrare_unghi_orizontala = servo_limita_inferioara_orizontala;
     }
    delay(8);
  }
  else 
  {
    servomotor_orizontala.write(servo_intrare_unghi_orizontala); 
  }
  
  
   int valoare_citita_analogica = analogRead(A4); // Citirea valorii analogice de la intrarea A0
  float tensiune_rezultata = (valoare_citita_analogica * 5.0) / 1023.0; /* Conversia valorii citite în voltaj 
  (pentru o placă Arduino cu alimentare la 5V) */

  Serial.print("Tensiune rezultata: ");
  Serial.print(tensiune_rezultata);
  Serial.println("V");

  delay(50); 
}