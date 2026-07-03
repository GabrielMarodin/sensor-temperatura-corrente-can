/*
 * MCP2515_driver.c
 *
 *  Created on: May 9, 2026
 *      Author: chris
 */
#include "MCP2515_driver.h"

static void MCP2515_Select(MCP2515_t *dev) {
    HAL_GPIO_WritePin(dev->csPort, dev->csPin, GPIO_PIN_RESET);
}

static void MCP2515_Unselect(MCP2515_t *dev) {
    HAL_GPIO_WritePin(dev->csPort, dev->csPin, GPIO_PIN_SET);
}

void MCP2515_Config(MCP2515_t *dev){

	uint8_t resetInst = MCP2515_RESET;

	// Para um cristal de 16 MHz e saída de 500 kHz
//	uint8_t cnf1 = 0x00;
//	uint8_t cnf2 = 0xD1;
//	uint8_t cnf3 = 0x01;

	// Para um cristal de 8 MHz e saída de 500 kHz
	uint8_t cnf1 = 0x00;
    uint8_t cnf2 = 0x91;
    uint8_t cnf3 = 0x02;

	uint8_t baudR_msg_3[]  = {
			MCP2515_WRITE,
			MCP2515_CNF3,
			cnf3
	};

	uint8_t baudR_msg_2[]  = {
			MCP2515_WRITE,
			MCP2515_CNF2,
			cnf2
	};

	uint8_t baudR_msg_1[]  = {
			MCP2515_WRITE,
			MCP2515_CNF1,
			cnf1
	};

//	uint8_t CANINT_msg[] =  {
//			MCP2515_WRITE,
//			MCP2515_CANINTE,
//			0x1C
//	};

	uint8_t CANCTRL_msg[] = {
			MCP2515_WRITE,
			MCP2515_CANCTRL,
			0x80
	};

	MCP2515_Unselect(dev);


	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, &resetInst, 1, 10);
    MCP2515_Unselect(dev);

    // Aguarda CI reiniciar
    HAL_Delay(10);

	//Modo de configuração
	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, CANCTRL_msg, 3, 10);
    MCP2515_Unselect(dev);

    // Configura o baudRate (500kbps)
	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, baudR_msg_1, 3, 10);
    MCP2515_Unselect(dev);

	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, baudR_msg_2, 3, 10);
    MCP2515_Unselect(dev);

	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, baudR_msg_3, 3, 10);
    MCP2515_Unselect(dev);

    // Habilita INT pin - Retorna status de conclusão da transmissão dos 3 buffers
//	MCP2515_Select(dev);
//    HAL_SPI_Transmit(dev->hspi, CANINT_msg, 3, 1);
//    MCP2515_Unselect(dev);

    // Modo normal habilitado/ habilita clkout para debug
	CANCTRL_msg[2] = 0x04;

	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, CANCTRL_msg, 3, 10);
    MCP2515_Unselect(dev);

    HAL_Delay(1);
}

//uint8_t MCP2515_Read_INT_reg(MCP2515_t *dev){
//	//CANINTF reg read
//	return 0;
//}

void MCP2515_TX(MCP2515_t *dev, uint16_t id, uint8_t dataLength, uint8_t *data_load, uint8_t buffer_n){

	uint8_t TXBnSIDH_addr;
	//uint8_t TXBnSIDL_addr;
	uint8_t TXBnDLC_addr;
	uint8_t TXBnD0_addr;
	uint8_t TXBnCTRL_addr;

	if (buffer_n > 2){
		buffer_n = 2;
	}
	switch (buffer_n)
	{
	case 0:
		TXBnSIDH_addr = MCP2515_TXB0SIDH;
		//TXBnSIDL_addr = MCP2515_TXB0SIDL;
		TXBnDLC_addr  = MCP2515_TXB0DLC;
		TXBnD0_addr   = MCP2515_TXB0D0;
		TXBnCTRL_addr = MCP2515_TXB0CTRL;
		break;
	case 1:
		TXBnSIDH_addr = MCP2515_TXB1SIDH;
		//TXBnSIDL_addr = MCP2515_TXB1SIDL;
		TXBnDLC_addr  = MCP2515_TXB1DLC;
		TXBnD0_addr   = MCP2515_TXB1D0;
		TXBnCTRL_addr = MCP2515_TXB1CTRL;
		break;
	case 2:
		TXBnSIDH_addr = MCP2515_TXB2SIDH;
		//TXBnSIDL_addr = MCP2515_TXB2SIDL;
		TXBnDLC_addr  = MCP2515_TXB2DLC;
		TXBnD0_addr   = MCP2515_TXB2D0;
		TXBnCTRL_addr = MCP2515_TXB2CTRL;
		break;
	default:
	}

	uint8_t id_msg[] = 	{MCP2515_WRITE,
						TXBnSIDH_addr,
						id >> 3,
						(id & 0x07) << 5};

    if (dataLength > 8){
    	dataLength = 8;
    }

    uint8_t dlc_msg[] = {
		MCP2515_WRITE, 
		TXBnDLC_addr, 
		dataLength
	};

    uint8_t load_msg[2 + dataLength];

    load_msg[0] = MCP2515_WRITE;

    load_msg[1] = TXBnD0_addr;

    for (int i = 0; i < dataLength; i++){
    	load_msg[i + 2] = data_load[i];
    }

    uint8_t tx_msg[] = {
		MCP2515_WRITE,
    	TXBnCTRL_addr,
		MCP2515_RTS_TX0
	};

	// Envia identifier para o buffer_n
	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, id_msg, 4, 10);
    MCP2515_Unselect(dev);

	// Define tamanho do pacote de dados para o buffer_n
	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, dlc_msg, 3, 10);
    MCP2515_Unselect(dev);

	// Carrega os dados no buffer escolhido
	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, load_msg, 2 + dataLength, 10);
    MCP2515_Unselect(dev);

    // Requisita envio da mensagem com prioridade "Highest message priority"
	MCP2515_Select(dev);
    HAL_SPI_Transmit(dev->hspi, tx_msg, 3, 10);
    MCP2515_Unselect(dev);

}
