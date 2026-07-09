Firmware
#######

.. contents::
   :local:
   :depth: 2


Visão geral
***********

O código do STM32F401 utiliza FreeRTOS para gerenciar a utilização do MCU pelas tarefas.

Desenvolvimento
***************

Tarefas
=======
`RTDTask <Core/Src/temperature_sensor.c#L48>`_ :
   Utiliza o driver do MAX31865 para pegar as temperatura já convertidas pelo driver e os erros se existirem. Ela salva em uma fila que será consumida pela tarefa do CAN.

`CANTempTask <Core/Src/temperature_sensor.c#L74>`_ :
   Consome os dados da fila e monta o pacote no formato CAN com as temps. e os erros e envia o pacote via SPI.

`CurrentTask <Core/Src/current_sensor.c#L78>`_ :
   Ativa por interrupção, ela filtra os valores do buffer do ADC via um butterworth IIR e salva na fila os dados filtrados para o CAN.

`CANCurrentTask <Core/Src/current_sensor.c#L103>`_ :
   Consome os dados da fila e monta o pacote no formato CAN com o valor RMS e pico e o sentido da corrente e envia o pacote via SPI.

Sequência de funcionamento das tarefas
======
Corrente::

   DMA callback (Half)
      ↓
   CurrentTask
      ↓
   IIRFilter (Half)
      ↓
   DMA callback (Full)
      ↓
   CurrentTask
      ↓
   IIRFilter (Full)
      ↓
   CANCurrentTask wakes up
      ↓
   Calculate RMS and peak
      ↓
   send via CAN

Temperatura::

   TIM3 ISR trigger
      ↓
   RTDTask
      ↓
   Temperatures and faults updated
      ↓
   CANTempTask wakes up
      ↓
   send via CAN

Pinout do Blackpill
======

============ ==========  
Blackpill    Devices 
============ ==========
PA8 	       MAX31865 CS Device 1
PA9 	       MAX31865 CS Device 2
PA10 	       MAX31865 CS Device 3
PB13 	       MAX31865 SCLK
PB14	       MAX31865 MISO
PB15	       MAX31865 MOSI
PB12	       MCP2515 CS
PB13 	       MCP2515 SCLK
PB14	       MCP2515 MISO
PB15	       MCP2515 MOSI
PA0	       ADC Input
============ ==========
