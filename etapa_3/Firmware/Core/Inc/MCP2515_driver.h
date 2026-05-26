/*
 * MCP2515_driver.h
 *
 *  Created on: May 9, 2026
 *      Author: chris
 */

#ifndef INC_MCP2515_DRIVER_H_
#define INC_MCP2515_DRIVER_H_

#include "main.h"

// Registradores do MCP2515
/* MCP2515 SPI Instruction Set */
#define MCP2515_RESET           0xC0

#define MCP2515_READ            0x03
#define MCP2515_READ_RXB0SIDH   0x90
#define MCP2515_READ_RXB0D0     0x92
#define MCP2515_READ_RXB1SIDH   0x94
#define MCP2515_READ_RXB1D0     0x96

#define MCP2515_WRITE           0x02
#define MCP2515_LOAD_TXB0SIDH   0x40    /* TX0 ID location */
#define MCP2515_LOAD_TXB0D0     0x41    /* TX0 Data location */
#define MCP2515_LOAD_TXB1SIDH   0x42    /* TX1 ID location */
#define MCP2515_LOAD_TXB1D0     0x43    /* TX1 Data location */
#define MCP2515_LOAD_TXB2SIDH   0x44    /* TX2 ID location */
#define MCP2515_LOAD_TXB2D0     0x45    /* TX2 Data location */

#define MCP2515_RTS_TX0         0x81
#define MCP2515_RTS_TX1         0x82
#define MCP2515_RTS_TX2         0x84
#define MCP2515_RTS_ALL         0x87
#define MCP2515_READ_STATUS     0xA0
#define MCP2515_RX_STATUS       0xB0
#define MCP2515_BIT_MOD         0x05

/* MCP25152515 Register Adresses */
#define MCP2515_RXF0SIDH	0x00
#define MCP2515_RXF0SIDL	0x01
#define MCP2515_RXF0EID8	0x02
#define MCP2515_RXF0EID0	0x03
#define MCP2515_RXF1SIDH	0x04
#define MCP2515_RXF1SIDL	0x05
#define MCP2515_RXF1EID8	0x06
#define MCP2515_RXF1EID0	0x07
#define MCP2515_RXF2SIDH	0x08
#define MCP2515_RXF2SIDL	0x09
#define MCP2515_RXF2EID8	0x0A
#define MCP2515_RXF2EID0	0x0B
#define MCP2515_CANSTAT		0x0E
#define MCP2515_CANCTRL		0x0F

#define MCP2515_RXF3SIDH	0x10
#define MCP2515_RXF3SIDL	0x11
#define MCP2515_RXF3EID8	0x12
#define MCP2515_RXF3EID0	0x13
#define MCP2515_RXF4SIDH	0x14
#define MCP2515_RXF4SIDL	0x15
#define MCP2515_RXF4EID8	0x16
#define MCP2515_RXF4EID0	0x17
#define MCP2515_RXF5SIDH	0x18
#define MCP2515_RXF5SIDL	0x19
#define MCP2515_RXF5EID8	0x1A
#define MCP2515_RXF5EID0	0x1B
#define MCP2515_TEC			0x1C
#define MCP2515_REC			0x1D

#define MCP2515_RXM0SIDH	0x20
#define MCP2515_RXM0SIDL	0x21
#define MCP2515_RXM0EID8	0x22
#define MCP2515_RXM0EID0	0x23
#define MCP2515_RXM1SIDH	0x24
#define MCP2515_RXM1SIDL	0x25
#define MCP2515_RXM1EID8	0x26
#define MCP2515_RXM1EID0	0x27
#define MCP2515_CNF3		0x28
#define MCP2515_CNF2		0x29
#define MCP2515_CNF1		0x2A
#define MCP2515_CANINTE		0x2B
#define MCP2515_CANINTF		0x2C
#define MCP2515_EFLG		0x2D

#define MCP2515_TXB0CTRL	0x30
#define MCP2515_TXB1CTRL	0x40
#define MCP2515_TXB2CTRL	0x50
#define MCP2515_RXB0CTRL	0x60
#define MCP2515_RXB0SIDH	0x61
#define MCP2515_RXB1CTRL	0x70
#define MCP2515_RXB1SIDH	0x71

#define MCP2515_TXB0SIDH    0x31
#define MCP2515_TXB0SIDL    0x32
#define MCP2515_TXB1SIDH    0x41
#define MCP2515_TXB1SIDL    0x42
#define MCP2515_TXB2SIDH    0x51
#define MCP2515_TXB2SIDL    0x52

#define MCP2515_TXB0DLC     0x35
#define MCP2515_TXB1DLC     0x45
#define MCP2515_TXB2DLC     0x55

#define MCP2515_TXB0D0      0x36
#define MCP2515_TXB1D0      0x46
#define MCP2515_TXB2D0      0x56

/* Defines for Rx Status */
#define MSG_IN_RXB0             0x01
#define MSG_IN_RXB1             0x02
#define MSG_IN_BOTH_BUFFERS     0x03

/*Define velociadade do barramento CAN */

// Configuração do Controlador MCP2515
typedef struct {
    // Comunicação SPI
    SPI_HandleTypeDef *hspi;    // Ponteiro para o handler do SPI configurado no CubeIDE

    // Pinos de Controle (GPIO)
    GPIO_TypeDef      *csPort;  // Porta do pino CS
    uint16_t           csPin;   // Pino CS

    //GPIO_TypeDef      *intPort; // Porta do pino de Interrupção (CAN_INT_port)
    //uint16_t           intPin;  // Pino de Interrupção (CAN_INT_pin)

    //uint8_t			cnf1;
    //uint8_t			cnf2;
    //uint8_t			cnf3;
} MCP2515_t;

extern MCP2515_t hcan;

void MCP2515_Config(MCP2515_t *dev);

//uint8_t MCP2515_Read_INT_pin(MCP2515_t *dev);

void MCP2515_TX(MCP2515_t *dev, uint16_t id, uint8_t dataLength, uint8_t *data_load, uint8_t buffer_n);

#endif /* INC_MCP2515_DRIVER_H_ */
