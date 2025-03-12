// Producto de ZACETREX TECHNOLOGIES S.A.C
// Este código se hizo con fin de compartirlo con la comunidad y tiene fines educativos
// Encuentre otros codigos en zacetrex.com o comuniquese con nosotros.

int ENA = 3;
int IN1 = 5;
int IN2 = 6;
int IN3 = 7;
int IN4 = 8;
int ENB = 9;
int ECHO = 11;
int TRIG = 12;
long distancia; 
long duracion;
bool Parado=true;

  void setup() {
    Serial.begin (9600);
   pinMode(ENA, OUTPUT);
   pinMode(IN1, OUTPUT);
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);
   pinMode(ENB, OUTPUT);
   pinMode(ECHO, INPUT);
   pinMode(TRIG, OUTPUT);
  }
  
  void loop() {
    
    SensarDistancia();
    Serial.print(distancia);        
    Serial.println("cm"); 
      
    if(distancia <=20 && distancia >=1){
      Serial.println("detectado :D");
      Retroceder();
      delay(500);
      Izquierda();
      delay(500);
      Parado=true;
    }
  
    else {
      if(Parado == true) {
        Impulso();
        delay(400);
        Parado=false;
      }
       Avanzar();
       delay(400);
    }
  }
  void SensarDistancia() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG,LOW);
  
    duracion = pulseIn (ECHO, HIGH);
    distancia = (duracion/2) / 29;
  }

// ENA y ENB se utilizan para controlar la velocidad del motor (PWM)
// Puede modificarlo, el rango es de 0 a 255, donde 255 es la maxima velocidad.
// No todos los motores son exactamente iguales, algunos no se moveran por lo 
// que necesitan aumentar la velocidad, tambien si coloca mucho peso, 
// no se moveran y tendra que aumentar la velocidad

  void Retroceder() {
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    analogWrite(ENA,110);
    analogWrite(ENB,100);
    delay(500);
  }
  
  void Izquierda() {
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    analogWrite(ENA,110);
    analogWrite(ENB,100);
  }

  void Impulso(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  analogWrite(ENB,250);
  analogWrite(ENA,250);
  }
  
  void Avanzar(){
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    analogWrite(ENA,100);
    analogWrite(ENB,100);
  }

// En caso de que el sensor no detecte la distancia y no realice el procedimiento de retroceder y 
// avanzar, verifique que el voltaje que esta recibiendo el sensor sea mayor de 4v

//Procesador ATmega328P(Old Bootloader)
