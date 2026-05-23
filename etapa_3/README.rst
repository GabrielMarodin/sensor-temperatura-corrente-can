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


`Link para os Testes <Testes>`_

Teste da Rede CAN com Dados dos Sensores
================================
Após implementação em código do `sensor de corrente <Testes/Sensor_RTOS/Core/Src/Current_Sensor.c>` 
e dos `sensores de temperatura <Testes/Sensor_RTOS/Core/Src/Temperature_Sensor.c>`, foi implementada 
à partir do `driver do MCP2515 <Testes/Sensor_RTOS/Core/Src/MCP2515_Driver.c>` a transmição dos 
dados dos sensores utilizando o protocolo CAN nos IDS 0x10 e 0x11. O teste foi realizado utilizando um 
`Testes/ESP32devkit/ESP32MCP2515` como nó receptor, com o blackpill STM atuando como 
nó transmissor enviando mensagens.

Segue uma imagem do teste da rede CAN, o osciloscópio mede a tensão diferencial da linha no módulo utilizado.
.. image:: images/can_test.png
   :height: 1600px
   :width: 900 px
   :scale: 30 %

O ESP32 foi configurado para repassar as mensagems que recebe por SPI do MCP2515 para a porta 
serial, e o terminal do computador foi configurado para receber as mensagens. 
Abaixo temos um exemplo de mensagem recebida no terminal:
```
Mensagem CAN Recebida:
ID: 0x10
Data: ################
Mensagem CAN Recebida:
ID: 0x11
Data: ################
```

TODO: Comparativo entre os dados recebidos e esperados


Referências (links/datasheets/livros)
*************************************

- `nRF Connect SDK <https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.4.2/nrf/getting_started/modifying.html#configure-application>`_

- `Código de interface MCP2515 <https://github.com/eziya/STM32_SPI_MCP2515/tree/master>`_


