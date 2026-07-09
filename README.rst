Monitoramento de temperatura e corrente via CAN do barco solar
#####################################################################

.. contents::
   :local:
   :depth: 2



Requisitos
**********

Este projeto foi implementado com os seguintes módulos/softwares/hardwares:
 | Sensor de temperatura PT100 com 3 fios.    
 | Sensor de corrente de efeito Hall LEM LA 205-S.  
 | MCP2515 (Controlador CAN);
 | TJA1050 (Transceptor CAN);  
 | Linguagem de programação C.  
 | Microcontrolador STM32F401 com SPI, ADC e regulador de 5V para 3V3.  


Visão geral
***********

Esse projeto faz parta do barco solar Zênite Solar.

.. figure:: /images/pcb_3dmodel.png
   :alt: Modelo 3D da placa de circuito impresso
   :align: center
   :name: 3D model of PCB.

É um sistema microcontrolado embarcado ao barco que possui capacidade de ler temperaturas em pontos estratégicos do barco e a corrente do motor.

O microcontrolador lê e trata os dados e empacota em um frame CAN para transmitir, através a implementação do controlador e transmissor CAN, para a saída do conector RJ45.

O desenvolvimento foi divido em quatro etapas:

- Etapa 1 (02/04/2026): Pesquisa, planejamento e outline do projeto.
- Etapa 2 (30/04/2026): Teste dos módulos e desenvolvimento de protótipo.
- Etapa 3 (28/05/2026): Desenvolvimento do produto.
- Etapa 4 (09/07/2026): Implementação e análise de desempenho.


Interface do usuário
********************
LED de respiração:
  Pisca enquanto o RTOS estiver ativo.

Testando
========

Para testar pode ser usado o debugger do microcontrolador para ler as variáveis e registradores ou um analizador de CAN para capturar as mensagens transmitidas.

Montagem
********

O sistema é alimentado e transmite os frames CAN pelo conector RJ45;

O sensor de corretente de efeito hall deve ser conectado no conector de 4 pinos;

O PT100 deve ser conectado no MAX31865 nos conectores de parafuso.

.. figure:: /images/max_3wired.jpg
   :alt: MAX31865 breakout board com 3 fios conectados
   :align: center
   :name: MAX31865 connection

   Modo de conexão de 3 fios do PT100.

   No modo 3 wires 2 fios estão em paralelo e 1 fio tem 100 ohms de resistência a 0 graus celsius em relação aos outros, os fios com resistência muito baixa entre si devem ser conectados em RTD+ e F+, enquanto o terceiro fio deve ser conectado em RTD-.

Referências (Links)
*******************

- `GitHub do Zênite Solar <https://github.com/ZeniteSolar>`_

- `Firmware do Projeto </etapa_4/Firmware>`_

- `Projeto KiCad da PCB </etapa_3/PCB/Modulo_corrente_temperatura_barco_Zenite>`_
