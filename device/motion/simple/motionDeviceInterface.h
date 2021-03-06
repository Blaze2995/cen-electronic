#ifndef MOTION_DEVICE_INTERFACE_H
#define MOTION_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

// COMMAND

/** Backward with value in mm. */
#define COMMAND_MOTION_BACKWARD_IN_MM         'b'

/** Cancel all current motion. */
#define COMMAND_MOTION_CANCEL                 'c'

/** Forward with value in mm. */
#define COMMAND_MOTION_FORWARD_IN_MM          'f'

/** Goto with value in coder pulse. */
#define COMMAND_MOTION_GOTO_IN_PULSE          'g'

/** Turn to the left in degree. */
#define COMMAND_MOTION_LEFT_IN_DECI_DEGREE    'l'

/** Turn to the right in degree. */
#define COMMAND_MOTION_RIGHT_IN_DECI_DEGREE   'r'

/** Turn to the left in degree, but without turning right wheel. */
#define COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE '('

/** Turn to the left in degree, but without turning right wheel. */
#define COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE ')'

// PARAMETERS

/** Load default Motion parameters. */
#define COMMAND_MOTION_LOAD_DEFAULT_PARAMETERS 'd'

/** Show in a table the different value of Speed / Acceleration for each kind of move. */
#define COMMAND_MOTION_PARAMETERS_DEBUG        'D'

/** Defines the COMMAND used to get speed / acceleration parameters for different motion type. */
#define COMMAND_GET_MOTION_PARAMETERS          'p'

/** Defines the COMMAND used to set speed / acceleration parameters for different motion type. */
#define COMMAND_SET_MOTION_PARAMETERS          'w'

/** Save the motion parameters to the eeprom. */
#define COMMAND_MOTION_SAVE_TO_EEPROM_PARAMETERS 's'

// CALIBRATION

/** Define the command used to do a square useful for calibration. */
#define COMMAND_SQUARE_CALIBRATION             '@'

// MOTION MODE

/** Indicates that the instruction must be added on a stack and not replace the current instruction. */
#define COMMAND_MOTION_MODE_ADD				   '+'

/** Indicates that the instruction must replace the stack and not be added on stack */
#define COMMAND_MOTION_MODE_REPLACE			   '_'

/** Function to get the motion mode (Add/stacking or replace). */
#define COMMAND_MOTION_MODE_GET				   '?'

// NOTIFICATION

/** Argument for the status of the robot when position reached. */
#define NOTIFY_MOTION_STATUS_REACHED           'r'

/** Argument for the status of the robot when robot failed to reach. */
#define NOTIFY_MOTION_STATUS_FAILED            'e'

/** Argument for the status of the robot when there is an obstacle. */
#define NOTIFY_MOTION_STATUS_OBSTACLE          'o'

/** Argument for the status of the robot when position is in progress. */
#define NOTIFY_MOTION_STATUS_MOVING            'm'

/** Obstacle : stop the current Motion and maintain Position. */
#define COMMAND_MOTION_OBSTACLE                '|'

/**
* Interface for Device
*/
DeviceInterface* getMotionDeviceInterface();

#endif
