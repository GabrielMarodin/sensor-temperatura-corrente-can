Etapa 3
#######

.. contents::
   :local:
   :depth: 2


Visão geral
***********

A etapa 3 ...


Desenvolvimento
***************

Apresentar o desenvolvimento da etapa contendo detalhes de implementação (se houver) de hardware e software. Adicionar pesqusisas realizadas bem como testes realizados.


Testes
======

Descrição dos testes/validações realizadas.

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

(Outras subseções se necessário)
================================


Referências (links/datasheets/livros)
*************************************

- `nRF Connect SDK <https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.4.2/nrf/getting_started/modifying.html#configure-application>`_

- `Código de interface MCP2515 <https://github.com/eziya/STM32_SPI_MCP2515/tree/master>`_


