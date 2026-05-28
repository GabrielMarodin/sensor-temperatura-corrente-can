Testes
#######

.. contents::
   :local:
   :depth: 2


Visão geral
***********

Esse diretório contém os códigos usados durante o teste dos drivers e hardwares.

Testes
======

Foram testados ambos os controladores e transmissores CAN via SPI utilizando o `Blackpill <pi3_CAN_test>`_ como transmissor e o `ESP32 <ESP32devkit/ESP32MCP2515>`_ como receptor de teste.

Também foram testadas as tarefas no FreeRTOS para facilitar a temporização e escalonamento das tarefas de sensoriamento e comunicação.

Imagem de teste do `Transmissor CAN </etapa_3/Testes/CAN_Module/Src>`_ onde foi observado o envio da corrente e o pacote recebido.

.. image:: /etapa_3/images/teste_tx_rx_current.png
   :scale: 100 %

Sequência de funcionamento das tarefas
======
`Corrente <Sensor_RTOS/Core/Src/current_task.c#L21-42>`_ ::

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

`Temperatura <Sensor_RTOS/Core/Src/rtd_task.c#L24-48>`_::

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


