const int LRD_PIN = A0; // Pin analógico utilizado para el sensor LRD
const int BOTON_PIN = 13; // Pin digital utilizado para el botón
const int LED_PIN_INICIAL = 3; // Pin del primer LED de la secuencia
const int LED_PIN_FINAL = 7; // Pin del último LED de la secuencia
const int TIEMPO_RETRASO = 200; // Tiempo de retraso en milisegundos para la secuencia de LEDs
bool leerSensor = false; // Variable para indicar si se debe leer el sensor
bool ultimoEstadoBoton = false; // Variable para almacenar el último estado del botón

void setup() {
  Serial.begin(9600);
  pinMode(BOTON_PIN, INPUT_PULLUP); // Se establece el pin del botón como entrada con resistencia pull-up interna
  for (int i = LED_PIN_INICIAL; i <= LED_PIN_FINAL; i++) {
    pinMode(i, OUTPUT); // Se establecen los pines de los LEDs como salidas
  }
}

void loop() {
  // Se lee el estado actual del botón
  bool estadoBoton = digitalRead(BOTON_PIN);

  // Si el estado del botón cambió, se actualiza la variable leerSensor
  if (estadoBoton != ultimoEstadoBoton && estadoBoton == LOW) {
    leerSensor = !leerSensor;
  }

  // Se almacena el estado actual del botón
  ultimoEstadoBoton = estadoBoton;

  // Si la variable leerSensor es true, se lee el valor del sensor LRD y se verifica si la intensidad de luz es menor a 100
  if (leerSensor) {
    int valor = analogRead(LRD_PIN);
    Serial.println(valor);
    if (valor < 100) {
      // Si la intensidad de luz es menor a 100, se encienden los LEDs secuencialmente con un retraso de tiempo
      for (int i = LED_PIN_INICIAL; i <= LED_PIN_FINAL; i++) {
        digitalWrite(i, HIGH);
        delay(TIEMPO_RETRASO);
        digitalWrite(i, LOW);
      }
    }
  }
}