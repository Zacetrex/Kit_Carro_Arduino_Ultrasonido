// ---------------------------
// Definición de pines del L298N
// ---------------------------
int ENA = 3;   // Pin PWM para controlar la velocidad del motor A (izquierdo)
int IN1 = 5;   // Dirección del motor A
int IN2 = 6;   // Dirección del motor A
int IN3 = 7;   // Dirección del motor B (derecho)
int IN4 = 8;   // Dirección del motor B (derecho)
int ENB = 9;   // Pin PWM para controlar la velocidad del motor B

// ---------------------------
// Pines del sensor ultrasónico HC-SR04
// ---------------------------
int ECHO = 11;  // Recibe el eco (tiempo que tarda el sonido en volver)
int TRIG = 12;  // Envia el pulso ultrasónico

// ---------------------------
// Variables para la medición de distancia
// ---------------------------
long distancia; 
long duracion;

// Esta variable se usa para saber si el carro está parado inicialmente
bool Parado = true;



// =====================================================
// ================ CONFIGURACIÓN INICIAL ===============
// =====================================================
void setup() {
  Serial.begin(9600);    // Inicia el monitor serial a 9600 baudios

  // Definimos todos los pines que controlan motores como salida
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Pines del sensor ultrasónico
  pinMode(ECHO, INPUT);   // ECHO siempre va como entrada
  pinMode(TRIG, OUTPUT);  // TRIG siempre va como salida
}



// =====================================================
// ======================= LOOP ========================
// =====================================================
void loop() {

  // Llamamos a la función que mide la distancia
  SensarDistancia();

  // Mostramos la distancia en el monitor serial
  Serial.print(distancia);
  Serial.println("cm"); 
  
  // Si hay un obstáculo a 20 cm o menos…
  if (distancia <= 20 && distancia >= 1) {
    Serial.println("Obstáculo detectado :D");

    // El carro retrocede para alejarse
    Retroceder();
    delay(500);

    // Luego gira a la izquierda
    Izquierda();
    delay(500);

    // Indicamos que el carro ha cambiado de estado
    Parado = true;
  }
  else {
    // Si recién evitó un obstáculo, da un pequeño impulso antes de avanzar
    if (Parado == true) {
      Impulso();
      delay(400);
      Parado = false;
    }

    // Si no hay obstáculos, avanza
    Avanzar();
    delay(400);
  }
}



// =====================================================
// ============= FUNCIÓN PARA MEDIR DISTANCIA =========
// =====================================================
void SensarDistancia() {

  // Enviamos un pulso corto de 10 microsegundos
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  // Medimos el tiempo que tarda en regresar el eco
  duracion = pulseIn(ECHO, HIGH);

  // Convertimos el tiempo en distancia en cm
  distancia = (duracion / 2) / 29;
}



// =====================================================
// ======= FUNCIONES DE MOVIMIENTO DEL ROBOT ===========
// =====================================================

// ENA y ENB controlan la VELOCIDAD del motor mediante PWM
// 0 = apagado, 255 = máxima velocidad
// Si tu carro no se mueve, sube los valores



// ---------------------
// Retroceder
// ---------------------
void Retroceder() {
  // Ambos motores giran en sentido inverso
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

  // Velocidad moderada hacia atrás
  analogWrite(ENA, 110);
  analogWrite(ENB, 100);

  delay(500);  // Retrocede por medio segundo
}



// ---------------------
// Girar a la izquierda
// ---------------------
void Izquierda() {
  // Motor izquierdo retrocede, motor derecho avanza
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);

  analogWrite(ENA, 110);
  analogWrite(ENB, 100);
}
// Producto de ZACETREX TECHNOLOGIES S.A.C
// Este código se hizo con fin de compartirlo con la comunidad y tiene fines educativos
// Más códigos en zacetrex.com

// ---------------------
// Impulso inicial
// ---------------------
void Impulso() {
  // Ambos motores hacia adelante a alta velocidad
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 

  analogWrite(ENB, 250);
  analogWrite(ENA, 250);
}



// ---------------------
// Avanzar normal
// ---------------------
void Avanzar() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);

  // Velocidad baja y estable
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}



// =====================================================
// NOTAS IMPORTANTES PARA PRINCIPIANTES
// =====================================================

// Si el sensor no detecta distancia correctamente,
// revise el voltaje: debe estar entre 4.5V y 5V.

// Procesador: ATmega328P (Old Bootloader)
