
# 🌱 ESP32 Smart Irrigation System — Irrigação Automática com Blynk IoT

Sistema de irrigação inteligente baseado em **ESP32** e **Blynk IoT** que monitora a temperatura e a umidade do ar, acompanha o nível do reservatório de água, permite o acionamento remoto da bomba d'água e controla o direcionamento do fluxo por meio de um **servomotor SG90** com ângulo ajustável pelo aplicativo.

---

### 🎥 Demonstração em Funcionamento


https://github.com/user-attachments/assets/cba424a5-687f-4929-a77b-b7d0dd43f79b
<p align="center">
  <img src="docs/demonstracao-funcionamento.gif" alt="Demonstração do Sistema de Irrigação no Blynk IoT" width="700">
</p>

### 📷 Montagem Física e Unidade de Controle
Abaixo está o módulo central montado em caixa acrílica transparente, integrando o **ESP32**, sensor **DHT11**, módulo relé, e o sensor de nível

<div align="center">
  src=<img width="1280" height="963" alt="image" src="https://github.com/user-attachments/assets/9d87e8f2-0fe4-40f8-a8cc-1224987d8c7f" />

<img width="1280" height="963" alt="image" src=<img width="1280" height="963" alt="image" src="https://github.com/user-attachments/assets/9d87e8f2-0fe4-40f8-a8cc-1224987d8c7f" />
/>
" alt="Unidade de Controle ESP32 em Caixa Acrílica" width="60%" />
</div>

---

## ⚙️ Funcionalidades Principais

* **Monitoramento Climático em Tempo Real:** Leitura de temperatura (°C) e umidade relativa do ar (%) via sensor **DHT11**, com exibição em gráfico histórico no painel do Blynk.
* **Sensor de Nível do Reservatório:** Monitora a quantidade de água disponível no reservatório para evitar funcionamento a seco e sinalizar necessidade de reposição.
* **Acionamento Remoto da Bomba:** Controle liga/desliga da mini bomba d'água diretamente pelo aplicativo **Blynk IoT** 
* **Direcionamento Ajustável com Servomotor:** Controle deslizante (*slider*) no app que ajusta o ângulo do micro servo **SG90**, movendo a mangueira para irrigar diferentes pontos da planta.

---

## 🛠️ Tecnologias e Hardware
* **Microcontrolador:**(ESP-32D)
* **Sensores:** DHT11 (Temperatura e Umidade do Ar), Sensor de Nível de Água e Módulo Botão Touch 
* **Atuadores:** Mini Bomba d'Água Submersa (acionada via Módulo Relé) e Micro Servomotor SG90
* **Conectividade e Plataforma:** Wi-Fi, Blynk IoT Cloud & App

---
