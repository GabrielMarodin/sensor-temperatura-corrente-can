Etapa 2
#######

.. contents::
   :local:
   :depth: 2


Visão geral
***********

A etapa 2 abordará os testes dos sensores de temperatura e corrente em placas de desenvolvimento e a definição da arquitetura do protoloco CAN que será implementado no sistema embarcado referênte ao projeto em questão.


Desenvolvimento
***************

Apresentar o desenvolvimento da etapa contendo detalhes de implementação (se houver) de hardware e software. Adicionar pesqusisas realizadas bem como testes realizados.


Testes
======

**Aquisição de Temperatura com o MAX 31865**

Descrição dos testes/validações realizadas.

**Medição de Corrente com LA 205-S**

Descrição dos testes/validações realizadas.


Arquitetura do Protocolo CAN
============================

O microcontolador STM32f401 (blackpill) não possui o perírico CAN nativo, logo, se faz necessário uma interface controladora que torna possível a implementação do protocolo sem gerar custos adicionais a CPU do microcontrolador.
A interface do microcontrolador com a rede CAN será feita por intermédio de dois circuitos integrados:

+ MCP2515 -> Controlador CAN
+ TJA1050 -> Transceptor CAN

A implemetação física pode ser observada pelo diagrama a seguir:

.. image:: images/CAN_physical.png
   :height: 104 px
   :width: 493 px
   :scale: 100 %
   
O protocolo CAN a ser impletamentado pertence a versão 2.0A, conhecido também como "standard CAN".
Seu dataframe pode ser observado na imagem abaixo:

.. image:: images/CAN_dataframe.png
   :height: 234 px
   :width: 1190 px
   :scale: 45 %
   
Para o projeto em questão é necessário que o microcontrolador somente envie mensagens.

Para implementar a arquitura utilizando o controlador CAN MCP2515 é necessário, através do barramento SPI:

+ Configurar o *baud rate* (registradores CNF[1:3])
+ Habilitar feedback de envio (registrador CANINTE) -> permite debug
+ Escolher modo de operação (Normal, sleep, loopback...) (registrador CANCTRL)


+ Configurar o *identifier* de 11 bits (registradores TXBnSIDH e TXBnSIDL)
+ Escolher o tamanho do pacote de dados (0 a 8 bytes) (registrador TXBnDLC)
+ Carregar dados (registradores TXBnD[0:7])
+ Escolher o buffer que será transmitido (registrador TXRTSCTRL)
+ Requisitar envio do buffer (registrador TXBnCTRL)

O nó da rede CAN em questão possuirá 2 *identifiers*:

+ Id zzz contendo as aquisições de temperatura.
+ Id xxx contendo as medições de corrente.

As mesagens serão divididas da seguinte forma:

	**Id zzz**

	+ Frequencia de envio = 20 Hz
	+ Total bytes = 4
	+ bits[31:30] -> informa status da aquisição ou erro nos sensores
	+ bits[29:20] -> Temperatura das baterias em °C
	+ bits[19:10] -> Temperatura dos controladores de carga em °C
	+ bits[9:0]   -> Temperatura do motor em °C
	
	**Id xxx**

	+ Frequencia de envio = 100 Hz
	+ Total bytes = 4
	+ bits[31:25] -> informa status da aquisição ou erro nos sensores
	+ bit[24]     -> informa sentido predominante da corrente (1 para positivo)
	+ bits[23:12] -> Corrente RMS em mA
	+ bit[11]     -> Sentido da corrente de pico (1 para positivo)
	+ bits[10:00] -> Corrente de pico em mA

Referências (links/datasheets/livros)
*************************************

- `MCP2515 documentação <https://www.microchip.com/en-us/product/mcp2515>`_

- `Zênite Solar GitHub <https://github.com/ZeniteSolar>`_


