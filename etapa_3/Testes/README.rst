Etapa 3
#######

.. contents::
   :local:
   :depth: 2


Visão geral
***********

Esse diretório contém os códigos usados durante o teste dos drivers e hardwares.


Testes
======

Foram testados ambos os controladores e transmissores CAN via SPI utilizando o blackpill como transmissor e o ESP32 como receptor de teste.

Também foram testadas as tarefas no FreeRTOS para facilitar a temporização e escalonamento das tarefas de sensoriamento e comunicação.

Sequência de funcionamento das tarefas
======
Corrente::

   DMA callback (Half/Full)
      ↓
   CurrentTask
      ↓
   Treated buffer ready
      ↓
   CANCurrentTask wakes up
      ↓
   Calculate RMS
      ↓
   send via CAN

Temperatura::

   TIM3 ISR trigger
      ↓
   RTDTask
      ↓
   Temperatures updated
      ↓
   CANTempTask wakes up
      ↓
   send via CAN

Pinout do ESP32
======
============ ==========  
MCP2515 Pin  ESP32 Pin 
============ ==========
VCC 	       5V
GND 	       GND
CS 	       IO5
SO 	       IO19
SI 	       IO23
SCK 	       IO13
INT 	       IO4
============ ==========

Referências
*************************************

- `Código de interface MCP2515 <https://github.com/eziya/STM32_SPI_MCP2515/tree/master>`_

- `Tutorial de setup do MCP2515 para o ESP32 <https://how2electronics.com/esp32-can-bus-communication-with-mcp2515-module/>`_

- `Driver do MCP2515 para o ESP32 <https://github.com/autowp/arduino-mcp2515/>`_


