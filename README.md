
# 🌱 ESP32 Smart Irrigation System — Irrigação Automática com Blynk IoT

Sistema de irrigação inteligente baseado em **ESP32** e **Blynk IoT** que monitora a temperatura e a umidade do ar, acompanha o nível do reservatório de água, permite o acionamento remoto da bomba d'água e controla o direcionamento do fluxo por meio de um **servomotor SG90** com ângulo ajustável pelo aplicativo.

---

### 🎥 Demonstração em Funcionamento

https://github.com/user-attachments/assets/b1fc6c77-db47-46b3-87bd-189d4489a277

<p align="center">
  <img src="docs/demonstracao-funcionamento.gif" alt="Demonstração do Sistema de Irrigação no Blynk IoT" width="700">
</p>

### 📷 Montagem Física e Unidade de Controle
Abaixo está o módulo central montado em caixa acrílica transparente, integrando o **ESP32**, sensor **DHT11**, módulo relé, sensor de nível e botão **Touch** frontal[cite: 1]:

<div align="center">
  <img src="docs/caixa-controle-esp32.jpg" alt="Unidade de Controle ESP32 em Caixa Acrílica" width="60%" />
</div>

---

## ⚙️ Funcionalidades Principais

* **Monitoramento Climático em Tempo Real:** Leitura de temperatura (°C) e umidade relativa do ar (%) via sensor **DHT11**, com exibição em gráfico histórico no painel do Blynk.
* **Sensor de Nível do Reservatório:** Monitora a quantidade de água disponível no reservatório para evitar funcionamento a seco e sinalizar necessidade de reposição.
* **Acionamento Remoto da Bomba:** Controle liga/desliga da mini bomba d'água diretamente pelo aplicativo **Blynk IoT** (com opção de acionamento local via botão capacitivo Touch)[cite: 1].
* **Direcionamento Ajustável com Servomotor:** Controle deslizante (*slider*) no app que ajusta o ângulo do micro servo **SG90**, movendo a mangueira para irrigar diferentes pontos da planta.

---

## 🏛️ Visão Geral da Arquitetura

<img width="1600" height="1166" alt="Arquitetura do Sistema IoT" src="https://github.com/user-attachments/assets/43b76b07-189b-4902-85f7-bef4b07a11d5" />

---

## 🛠️ Tecnologias e Hardware
* **Microcontrolador:** ESP32 (ESP-32D)[cite: 1]
* **Sensores:** DHT11 (Temperatura e Umidade do Ar), Sensor de Nível de Água e Módulo Botão Touch (TTP223)[cite: 1]
* **Atuadores:** Mini Bomba d'Água Submersa (acionada via Módulo Relé) e Micro Servomotor SG90
* **Conectividade e Plataforma:** Wi-Fi, Blynk IoT Cloud & App

---
