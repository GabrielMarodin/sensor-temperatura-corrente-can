Etapa 4
#######

.. contents::
   :local:
   :depth: 2


Visão geral
***********

A Etapa 4 abordará projeto do layout e montagem da placa de circuito impresso que abriga o sistema embarcado. A partir da montagem da PCB serão verificados os critérios de desempenho definidos na Etapa 3, juntamente a validação do sistema e integridade dos dados no barco.


Desenvolvimento
***************


Layout da PCB
=============

Para a elaboração do *layout* foram priorizados os seguintes aspectos:

+ Alta densidade de componentes, visando aproveitar o espaço limitado;
+ Segmentação da placa em áreas relacionadas à potência (dissipação de calor e emissão de EMI), tratamento de sinais analógicos e trilhas de sinais digitais;
+ Dedicação de um plano de referência exclusivo para o condicionamento do sinal proveniente do sensor de corrente (visando diminuir erros e aumentar a precisão);
+ Priorização de componentes SMD;
+ As regras de desenho devem ser compatíveis com os limites da CNC do LPAE(IFSC);
+ Placa de face dupla, sendo a camada superior majoritariamente um plano de referência sólido.


Observando as condições de manufatura do IFSC, foram priorizados componentes SMD de tamanho mínimo equivalente ao encapsulamento SOIC para os circuitos integrados e 0805 para capacitores e resistores. O projeto desenvolvido no KiCad pode ser visualizado em: `Link para a versão 1 do projeto <https://github.com/GabrielMarodin/sensor-temperatura-corrente-can/tree/main/etapa_3/PCB/Modulo_corrente_temperatura_barco_Zenite>`_ .

No entanto, alguns componentes estavam indisponíveis e adaptações foram necessárias, como pode ser observado na imagem abaixo.

.. image:: images/layoutCompair.png
   :scale: 30 %

O amplificador operacional TLV9004, inicialmente idealizado, foi substituído pelo TLV2376, em um encapsulamento menor, mas plenamente compatível com os requisitos do projeto. A substituição também ocorreu com o filtro ativo anteriormente previsto que foi trocado por um filtro passivo RC passa-baixa. O *layout* adaptado no KiCad pode ser visualizado em: `Link para a versão 2 do projeto <https://github.com/GabrielMarodin/sensor-temperatura-corrente-can/tree/main/etapa_3/PCB/Modulo_corrente_temperatura_barco_Zenite-V02>`_ .


Montagem da PCB
===============

A fabricação da PCB foi realizada no LPAE com o auxílio de seus técnicos e professores para a operação da CNC. O projeto impresso corresponde à `versão 2 <https://github.com/GabrielMarodin/sensor-temperatura-corrente-can/tree/main/etapa_3/PCB/Modulo_corrente_temperatura_barco_Zenite-V02>`_ . No entanto, algumas modificações foram necessárias, como o corte manual das trilhas e pads do amplificador operacional, além da utilização da técnica de *wire up* para integrar o circuito integrado à placa.

A PCB montada pode ser visualizada nas imagens abaixo:

.. image:: images/PCB_V2_Assembled_top.png
   :scale: 30 %
   
.. image:: images/PCB_V2_Assembled_bottom.png
   :scale: 30 %

Nota-se nas imagens que há muitos espaços não ocupados por componentes. Esses espaços correspondem a elementos que não estavam disponíveis no momento da montagem, mas que poderão ser inseridos posteriormente, assim que houver disponibilidade. Observa-se também a presença de diversos fios de cobre nu esmaltado na parte inferior da placa. Esses fios foram utilizados para interconectar as ilhas de GND, uma vez que não foi possível fabricar a placa em dupla face e garantir o plano de referência sólido originalmente previsto.

Validação da Aplicação
======================


Validação do Desempenho
***********************

Sensor Hall
======================

O sensor de efeito Hall lido pelo ADC com offset teve os seguintes resultados:

.. figure:: images/offset.jpeg

A figura mostra o valor real medido do offset no divisor resistivo.

.. figure:: images/F0001TEK.JPG

A figura mostra o valor de tensão com corrente positiva no shunt de 16 Ohms do sensor de corrente.

.. figure:: images/F0000TEK.JPG

A figura mostra o valor de tensão com corrente negativa no shunt de 16 Ohms do sensor de corrente.

.. figure:: images/ADC.png

A figura mostra o valor lido e convertido utilizando a fórmula `previamente exposta na etapa 2 <../etapa_2/README.rst#L55>`_.

Pode-se concluir que há uma variação de 3 mA o que era esperado para a resolução de 10 bits mais as não idealidades propagadas.

Sensor de temperatura
======================

O sensor temperatura lido pelo SPI da breakout board MAX31865 teve os seguintes resultados:

.. figure:: images/temp_ambiente.jpeg

A figura mostra a temperatura ambiente no momento de teste.

.. figure:: images/temp1.jpeg

A figura mostra a temperatura lida e calculada do PT100.

.. figure:: images/temp2.jpeg

A figura mostra a temperatura do PT100 depois de um tempo em contato com a mão.

O ADC do MAX31865 é de 16 bits com 15 bits de RTD a resolução é alta e o maior fator de erro é o valor do resistor de referência, alterar a macro do software do [RREF] para o valor medido com um multímetro na hora 
afeta a exatidão da temperatura dastricamente.

Verificação da Integridade dos Dados
====================================


Referências (links/datasheets/livros)
*************************************

- `Código de interface MCP2515 <https://github.com/eziya/STM32_SPI_MCP2515/tree/master>`_

- `Datasheet do MCP2515 <https://www.microchip.com/en-us/product/mcp2515>`_

- `Datasheet do MAX31865 <https://www.analog.com/media/en/technical-documentation/data-sheets/max31865.pdf>`_

- `Datasheet do TLV2376 <https://www.ti.com/product/TLV2376/part-details/TLV2376IDGKR>`_

- `Datasheet do TJA1050 <https://www.nxp.com/docs/en/data-sheet/TJA1050.pdf>`_

- `Fundamentos da camada física do CAN <https://www.ti.com/lit/an/slla270/slla270.pdf?ts=1783507668427>`_

- `GitHub do Zenite Solar <https://github.com/ZeniteSolar>`_

