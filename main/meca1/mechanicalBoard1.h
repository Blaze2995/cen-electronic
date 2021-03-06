#ifndef MECHANICAL_BOARD_1_H
#define MECHANICAL_BOARD_1_H

/** Define the I2C address used by motorBoard. */
#define MECHANICAL_BOARD_1_I2C_ADDRESS     0x52

#define MECA_BOARD_1_INPUT_BUFFER_LENGTH         20
#define MECA_BOARD_1_OUTPUT_BUFFER_LENGTH         20

#define MECA_BOARD_1_DEBUG_INPUT_BUFFER_LENGTH        MECA_BOARD_1_INPUT_BUFFER_LENGTH
#define MECA_BOARD_1_DEBUG_OUTPUT_BUFFER_LENGTH        MECA_BOARD_1_OUTPUT_BUFFER_LENGTH

#define MECA_BOARD_1_I2C_INPUT_BUFFER_LENGTH        MECA_BOARD_1_INPUT_BUFFER_LENGTH
#define MECA_BOARD_1_I2C_OUTPUT_BUFFER_LENGTH        MECA_BOARD_1_OUTPUT_BUFFER_LENGTH

// LOGS
#define MECA_BOARD_1_LOG_HANDLER_LIST_LENGTH   2

// TIMER
#define MECHANICAL_BOARD_1_TIMER_LENGTH        1

// SPECIFIC 2011

#define MECHANICAL_BOARD_1_DEVICE_LENGTH        5

#define PIN_SWITCH_PLIER_OPEN_RIGHT        PORTBbits.RB10

#define PIN_SWITCH_PLIER_OPEN_LEFT        PORTBbits.RB11

#define PIN_SWITCH_PLIER_CLOSE_RIGHT    PORTBbits.RB9

#define PIN_SWITCH_PLIER_CLOSE_LEFT        PORTBbits.RB8


#endif
