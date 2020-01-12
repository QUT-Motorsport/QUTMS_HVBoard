/**
 * @file MCP2517.h
 * @author Zoe Goodward
 * @brief Analogue to digital conversion
 * */

#ifndef MCP2517_H_
#define MCP2517_H_

#include "MCP2517_defines.h"

/// Transmit Channels
#define MCP2517_TX_FIFO MCP2517_FIFO_CH1
/// Receive Channels
#define MCP2517_RX_FIFO MCP2517_FIFO_CH2
/// Maximum Message Size
#define MCP2517_MAX_MSG_SIZE 21

typedef enum {
	CAN_RECEIVE_ID_INV = 0x0C000000, /**< CAN Bus Identifier for Inverters 	1100000000000000000000000000 */
	CAN_RECEIVE_ID_AMU = 0x0A000000, /**< CAN Bus Identifier for AMU 		1010000000000000000000000000 */
	CAN_RECEIVE_ID_PDM = 0x09000000, /**< CAN Bus Identifier for PDM 		1001000000000000000000000000 */
	CAN_RECEIVE_ID_SHUTDOWN = 0x08800000, /**< CAN Bus for Shutdown 		1000100000000000000000000000 */
	CAN_RECEIVE_ID_WHEEL = 0x08400000, /**< CAN Bus for Steering Wheel 		1000010000000000000000000000 */
	CAN_RECEIVE_ID_BMS = 0x08200000, /**< CAN Bus for BMS					1000001000000000000000000000 */
	CAN_RECEIVE_ID_HV = 0x08100000, /**< CAN Bus for HV 					1000000100000000000000000000 */
} CAN_RECEIVE_ADDRESS; // When sent from CC to other boards

typedef enum {
	CAN_SEND_ID_INV = 0x04000000, /**< CAN Bus Identifier for Inverters 	0100000000000000000000000000 */
	CAN_SEND_ID_AMU = 0x02000000, /**< CAN Bus Identifier for AMU 		0010000000000000000000000000 */
	CAN_SEND_ID_PDM = 0x01000000, /**< CAN Bus Identifier for PDM 		0001000000000000000000000000 */
	CAN_SEND_ID_SHUTDOWN = 0x0800000, /**< CAN Bus for Shutdown 		0000100000000000000000000000 */
	CAN_SEND_ID_WHEEL = 0x0400000, /**< CAN Bus for Steering Wheel 		0000010000000000000000000000 */
	CAN_SEND_ID_BMS = 0x0200000, /**< CAN Bus for BMS					0000001000000000000000000000 */
	CAN_SEND_ID_HV = 0x0100000, /**< CAN Bus for HV 					0000000100000000000000000000 */
} CAN_SEND_ADDRESS; // When sent from other boards to CC

/**
 * @brief Initialises the chip
 *
 * Must be called before using any other functions of this chip.
 */
void MCP2517_init();

/**
 * @brief Writes a word into a buffer at a given index
 *
 * @param value 32-bit value to be written to the buffer
 * @param buff[] The buffer array to be written to
 * @param index The index to write to
 */
void enterWordInBufferAtIndex (const uint32_t value, uint8_t buff[], const uint8_t index);

/**
 * @brief Reads a word from a buffer at a given index
 *
 * @param buff[] The buffer array to be written to
 * @param index The index to write to
 * @returns The 32-bit balue from the buffer
 */
uint32_t wordFromBufferAtIndex (uint8_t buff[], const uint8_t index);

/**
 * @brief Writes a byte to a given register
 *
 * @param regAddr The address of the register
 * @param value The value to be written to the given register
 */
void MCP2517_writeReg8(const uint16_t regAddr, const uint8_t value);

/**
 * @brief Writes a 32-bit value to a given register
 *
 * @param regAddr The address of the register
 * @param value The value to be written to the given register
 */
void MCP2517_writeReg32(const uint16_t regAddr, const uint32_t value);

/**
 * @brief Reads a byte from a given register
 *
 * @param regAddr The address of the register
 * @returns The value read from the register
 */
uint8_t MCP2517_readReg8(const uint16_t regAddr);

/**
 * @brief Reads a 32-bit value from a given register
 *
 * @param regAddr The address of the register
 * @returns The value read from the register
 */
uint32_t MCP2517_readReg32(const uint16_t regAddr);

/// Asserts the chip select line
void MCP2517_assertCS();

/// Deasserts the chip select line
void MCP2517_deassertCS();

/**
 * @brief Performs a software reset on the chip
 * 
 * If the chip goes into restricted access mode, use this function to reset it.
 */
void MCP2517_reset();

/// Sets the operation mode on the chip
void MCP2517_setMode(MCP2517_OPERATION_MODE opMode);

/// Reads the current operation mode from the chip
uint8_t MCP2517_getMode();

/// Performs a test to check that reading and writing memory is working correctly
void MCP2517_testRAM();

/**
 * @brief Reads the FIFO RX status from the chip
 *
 * @param channel The channel number (0 to 31)
 * @param *flags The RX status flags
 * @returns The value of the status register
 */
uint8_t MCP2517_receiveFifoStatus(MCP2517_FIFO_CHANNEL channel, MCP2517_RX_FIFO_STATUS *flags);

/**
 * @brief Reads the FIFO TX status from the chip
 *
 * @param channel The channel number (0 to 31)
 * @param *flags The TX status flags
 * @returns The value of the status register
 */
uint8_t MCP2517_transmitFifoStatus(MCP2517_FIFO_CHANNEL channel, MCP2517_TX_FIFO_STATUS *flags);

/**
 * @brief Pulls a can packet from the chip
 * 
 * @param *receiveID Pointer to the variable storing the receiveID
 * @param *numDataBytes Pointer to the variable storing the data length of the can packet
 * @param *data Pointer to the array of bytes storing the data
 */
void MCP2517_recieveMessage(CAN_RECEIVE_ADDRESS *receiveID, uint8_t *numDataBytes, uint8_t *data);

void MCP2517_readMsgReceive(CAN_RECEIVE_ADDRESS *receiveID, uint8_t *numDataBytes, uint8_t *data, MCP2517_RX_MSG_OBJ *rxObj);

/**
 * @brief Pulls a can packet from the chip
 * 
 * @param canMessageID The message ID to be used when sending the data
 * @param *numDataBytes Pointer to the variable storing the data length of the can packet
 * @param *messageData Pointer to the array of bytes storing the data to be sent
 */
uint8_t MCP2517_transmitMessage(CAN_SEND_ADDRESS canMessageID, uint8_t numDataBytes, uint8_t *messageData);

void MCP2517_loadMsgTXFifo(MCP2517_TX_MSG_OBJ *txObj, uint8_t *payload, uint8_t numDataBytes);

#endif /* MCP2517_H_ */