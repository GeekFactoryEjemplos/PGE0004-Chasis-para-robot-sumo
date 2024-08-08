// Variables que indican los pines para el motor A, por comodidad a la hora de conectar, le vamos a poner los mismos nombres que tiene la placa del L298N
int IN1 = 7;
int IN2 = 6;

// Variables que indican los pines para el motor B, por comodidad a la hora de conectar, le vamos a poner los mismos nombres que tiene la placa del L298N
int IN3 = 5;
int IN4 = 4;

// Pines para el sensor ultrasónico
const int trigPin = 9;
const int echoPin = 8;

// Pines para los sensores TRCT5000
const int sensorIzquierdoPin = 2;
const int sensorDerechoPin = 3;

// Variable para almacenar la distancia medida por el sensor
long duration;
int distance;

void setup() {
  // Los pines que controlan el motor A
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Los pines que controlan el motor B
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Inicializar los pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializar los pines de los sensores TRCT5000
  pinMode(sensorIzquierdoPin, INPUT);
  pinMode(sensorDerechoPin, INPUT);

   Serial.begin(9600); // Iniciar comunicación serial para depuración
}

void loop() {
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  // Leer los sensores TRCT5000
  bool sensorIzquierdo = digitalRead(sensorIzquierdoPin);
  bool sensorDerecho = digitalRead(sensorDerechoPin);

  //si alguno de los sensores detecta un objeto gira el carro 180
  if (sensorIzquierdo == LOW || sensorDerecho == LOW) { // LOW indica detección en TRCT5000
  //motor1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //motor2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //motor1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //motor2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //motor1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //motor2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  }

  if (distance >= 30) { // Si la distancia es mayor o igual a 30 cm
    Adelante();
  } else {
    Girar();
  }
  delay(100); // Retraso para evitar comprobaciones excesivas
}

// Función para medir la distancia usando el HC-SR04
int getDistance() {
  // Limpia el trigPin poniéndolo en LOW:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Activa el sensor poniendo el trigPin en HIGH durante 10 microsegundos:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lee el echoPin. La duración es el tiempo (en microsegundos) que tarda el pulso en regresar:
  duration = pulseIn(echoPin, HIGH);

  // Calcula la distancia:
  distance = duration * 0.034 / 2; // Velocidad de la onda sonora dividida por 2 (ida y vuelta)
  return distance;
}

// Función para ir hacia adelante
void Adelante() {
  // Para controlar el motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Para controlar el motor B
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Función para girar
void Girar() {
  // Para controlar el motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Para controlar el motor B
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Función para parar
void Parar() {
  // Dirección motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  // Dirección motor B
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
