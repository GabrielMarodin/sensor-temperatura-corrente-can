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

`RTDTask <core/src/temperature_sensor.c#L45>`_
`CANTempTask <core/src/temperature_sensor.c#L71>`_
`CurrentTask <core/src/current_sensor.c#L83>`_
`CANCurrentTask <core/src/current_sensor.c#L108>`_

Testes
======

Descrição dos testes/validações realizadas.

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



