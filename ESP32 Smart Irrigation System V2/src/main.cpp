#define BLYNK_TEMPLATE_ID   ""
#define BLYNK_TEMPLATE_NAME "ESP32 SMART IRRIGATION SYSTEM"
#define BLYNK_AUTH_TOKEN    ""

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Credenciais de Wi-Fi
char ssid[] = "Seu SSID da rede";
char pass[] = "Sua senha";

// Definição dos pinos no ESP32 
const int pinoDHT = 22;          // Pino digital do DHT11
const int pinoRele = 4;          // Pino do Módulo Relé (bomba)
const int pinoServo = 21;        // Pino de sinal do Servo Motor
const int pinoNivelAgua = 34;    // Sensor de nível de água (ADC1 - livre do Wi-Fi)
const int pinoBuzzer = 26;       // Pino do Buzzer 

#define DHTTYPE DHT11
DHT dht(pinoDHT, DHTTYPE);
Servo meuServo;

// Variáveis locais para os sensores e atuadores
float temperatura = 0.0;
float umidadeAr = 0.0;
int leituraSolo = 0;         
int nivelAgua = 1;           // 0 = Água Detectada, 1 = Reservatório Vazio
int estadoRele = 0;
int anguloServo = 0;

// Variável para controlar o tempo de envio ao Blynk sem usar delay()
unsigned long ultimoEnvioBlynk = 0;
const long intervaloEnvio = 2000; // 2 segundos

// ==========================================
// FUNÇÕES DE CONTROLE VIA BOTÕES DO BLYNK
// ==========================================

BLYNK_WRITE(V4) {
  estadoRele = param.asInt();
  digitalWrite(pinoRele, estadoRele);
  Serial.print("Blynk V4 (Relé) manual: ");
  Serial.println(estadoRele);

  // ALARME: Se ligar a bomba (estadoRele == 1) e o reservatório estiver vazio (nivelAgua == 1)
  if (estadoRele == 1 && nivelAgua == 1) {
    Serial.println("ALERTA SONORO: Bomba ligada com o reservatório vazio!");
    
    // Alerta sonoro por oscilação manual (preserva o canal PWM do Servo na GPIO 21)
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 50; j++) {
        digitalWrite(pinoBuzzer, HIGH);
        delayMicroseconds(500);
        digitalWrite(pinoBuzzer, LOW);
        delayMicroseconds(500);
      }
      delay(200);
    }
  }
}

BLYNK_WRITE(V5) {
  anguloServo = param.asInt();
  meuServo.write(anguloServo);
  Serial.print("Blynk V5 (Servo) manual: ");
  Serial.println(anguloServo);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configuração da atenuação do ADC para leituras analógicas corretas
  analogSetAttenuation(ADC_11db);

  // Inicializações locais
  dht.begin();
  pinMode(pinoRele, OUTPUT);
  digitalWrite(pinoRele, LOW); // Relé começa desligado
  
  pinMode(pinoBuzzer, OUTPUT);
  digitalWrite(pinoBuzzer, LOW);

  meuServo.attach(pinoServo);
  meuServo.write(0);           

  // Conexão Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Serial.print("A conectar ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");

  // Inicializa o Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();
  
  Serial.println("ESP32 pronto e configurado!");
}

void loop() {
  // Mantém o Blynk ativo e processando os botões manuais
  Blynk.run();

  // Leitura local do sensor de nível de água na GPIO 34 (ADC1)
  int leituraNivelBruta = analogRead(pinoNivelAgua);
  
  // Define o estado com base no limiar
  if (leituraNivelBruta > 200) {
    nivelAgua = 0; // Água Detectada
  } else {
    nivelAgua = 1; // Reservatório Vazio
  }

  unsigned long tempoAtual = millis();

  // Envio periódico de leituras para o Blynk (a cada 2 segundos)
  if (tempoAtual - ultimoEnvioBlynk >= intervaloEnvio) {
    ultimoEnvioBlynk = tempoAtual;

    // Lê o sensor DHT11
    temperatura = dht.readTemperature();
    umidadeAr = dht.readHumidity();

    if (isnan(temperatura) || isnan(umidadeAr)) {
      temperatura = 0.0;
      umidadeAr = 0.0;
    }

    // Exibe no monitor serial para acompanhamento local
    Serial.print("Nível Bruto: "); Serial.print(leituraNivelBruta);
    Serial.print(" | Status Nível: "); Serial.print(nivelAgua == 0 ? "Água OK" : "Vazio");
    Serial.print(" | Temp: "); Serial.print(temperatura);
    Serial.print("C | Umidade Ar: "); Serial.print(umidadeAr);
    Serial.println("%");

    // Envia todos os dados para o Blynk
    Blynk.virtualWrite(V0, leituraSolo);
    Blynk.virtualWrite(V1, nivelAgua);
    Blynk.virtualWrite(V2, temperatura);
    Blynk.virtualWrite(V3, umidadeAr);
    Blynk.virtualWrite(V4, estadoRele);
    Blynk.virtualWrite(V5, anguloServo);
  }
}