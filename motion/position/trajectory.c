#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>

#include "trajectory.h"

#include "../../common/2d/2d.h"

#include "../../common/commons.h"
#include "../../common/math/cenMath.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"


#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../motion/position/coders.h"
#include "../../motion/pid/pid.h"
#include "../../robot/kinematics/robotKinematics.h"

// Position update threshold in mm
// #define UPDATE_THRESHOLD 5.0f
// No Threshold, we compute at the end of a trajectory
#define UPDATE_THRESHOLD 1.0f

// Position on the board in true length
static Position position = {
    {0.0f, 0.0f}, 0.0f, 0.0f};

// Last left coder value
static float lastLeft = 0.0f;
// Last right coder value
static float lastRight = 0.0f;
// Last angle
static float lastAngle = 0.0f;

void initializeTrajectory(void) {
    clearTrajectory();
}


void clearTrajectory(void) {
    setPosition(0, 0, 0);
    lastLeft = 0.0f;
    lastRight = 0.0f;
    lastAngle = 0.0f;
}

void setPosition(float x, float y, float orientation) {
    position.pos.x = x;
    position.pos.y = y;
    position.initialOrientation = orientation - position.orientation + position.initialOrientation;
    position.orientation = orientation;
    lastAngle = 0.0f;
}

Position* getPosition(void) {
    return &position;
}

void debugTrajectoryVariables(char* valueName1, float value1, char* valueName2, float value2) {
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendStringAndDecf(outputStream, valueName1, value1);
    appendStringAndDecf(outputStream, valueName2, value2);
    appendCRLF(outputStream);
}

/**
 * @private
 * Computes and updates the position from the specified
 * values from the coders.
 * @param left the value of the left coder
 * @param right the value of the right coder
 * @return 1 if the position has been updated, 0 otherwise
 */
bool absoluteUpdateFromCoders(signed long left, signed long right, bool useThreshold, bool debug) {
    if (debug) {
        debugTrajectoryVariables("left=", (float) left, ", right=", (float) right);
    }
    RobotKinematics* robotKinematics = getRobotKinematics();
    float leftWheelLengthForOnePulse = getLeftWheelLengthForOnePulse(robotKinematics);
    float rightWheelLengthForOnePulse = getRightWheelLengthForOnePulse(robotKinematics);

    float l = (float) left * leftWheelLengthForOnePulse;
    float r = (float) right * rightWheelLengthForOnePulse;
    if (debug) {
        debugTrajectoryVariables("l=", l, ", r=", r);
    }
    float dl = l - lastLeft;
    float dr = r - lastRight;
    if (debug) {
        debugTrajectoryVariables("dl=", dl, ", dr=", dr);
    }
    if (useThreshold) {
        if (fabsf(dl) <= UPDATE_THRESHOLD && fabsf(dr) <= UPDATE_THRESHOLD) {
            return false;
        }
    }

    // difference des distances parcourues par les roues en m
    float dw = r - l;
    // orientation finale = difference des distances / demi-distance des roues
    float wheelsDistance = robotKinematics->wheelsDistance;
    float orientation = fmodf(dw / wheelsDistance, 2.0f * PI) + lastAngle + position.initialOrientation;
    // angle relatif au dernier mouvement
    // lastAngle is only used when we clear Coders !
    float relativePositionOrientation = position.orientation;
    float angle = orientation - relativePositionOrientation;
    float meanOrientation = (orientation + relativePositionOrientation) / 2.0f;

    if (debug) {
        debugTrajectoryVariables("dw=", dw, ", orien=", orientation);
        debugTrajectoryVariables("angle=", angle, ",meanOrien=", meanOrientation);
    }

    // distance during last move
    float d = (dl + dr) / 2.0f;
    // project distance according the angle
    float k = 1.0f;
    if (angle != 0.0f) {
        float t = angle / 2.0f;
        k = sinf(t) / t;
    }

    float dx = d * k * cosf(meanOrientation);
    float dy = d * k * sinf(meanOrientation);
    if (debug) {
        debugTrajectoryVariables("dx=", dx, ", dy=", dy);
    }

    // update position
    position.pos.x += dx;
    position.pos.y += dy;
    position.orientation = orientation;

    lastLeft = l;
    lastRight = r;

    return true;
}

void updateTrajectory() {
    signed long left = getCoderValue(CODER_LEFT);
    signed long right = getCoderValue(CODER_RIGHT);
    //    curveUpdateFromCoders(left, right);
    absoluteUpdateFromCoders(left, right, true, false);
}

void updateTrajectoryWithNoThreshold() {
    signed long left = getCoderValue(CODER_LEFT);
    signed long right = getCoderValue(CODER_RIGHT);
    // do not use threshold
    absoluteUpdateFromCoders(left, right, false, false);
}

void updateTrajectoryAndClearCoders() {
    updateTrajectoryWithNoThreshold();
    lastAngle = position.orientation - position.initialOrientation;
    clearCoders();
    lastLeft = 0;
    lastRight = 0;
}

// DEBUG


void printDebugPosition(OutputStream* outputStream) {
	#define TRAJECTORY_X_DEC_COLUMN_LENGTH	                12
	#define TRAJECTORY_Y_DEC_COLUMN_LENGTH	                12
	#define TRAJECTORY_X_HEX_COLUMN_LENGTH	                12
	#define TRAJECTORY_Y_HEX_COLUMN_LENGTH	                12
	#define TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH	            16
	#define TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH	        16

	// HEADER
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "x (Dec) mm", TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y (Dec) mm", TRAJECTORY_Y_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "x (Hex) mm", TRAJECTORY_X_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y (Hex) mm", TRAJECTORY_Y_HEX_COLUMN_LENGTH);

	appendStringHeader(outputStream, "angle (deg)", TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "angle init (deg)", TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, 0);
	appendTableHeaderSeparatorLine(outputStream);

	// VALUES
    Position* position = getPosition();
	Point* point = &(position->pos);

	// X / Y
	appendDecfTableData(outputStream, point->x, TRAJECTORY_X_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, point->y, TRAJECTORY_Y_DEC_COLUMN_LENGTH);

	appendHex4TableData(outputStream, (int) point->x, TRAJECTORY_X_HEX_COLUMN_LENGTH);
	appendHex4TableData(outputStream, (int) point->y, TRAJECTORY_Y_HEX_COLUMN_LENGTH);

	// Angle / Last Angle
	appendDecfTableData(outputStream, position->orientation / PI_DIVIDE_180, TRAJECTORY_ANGLE_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, position->initialOrientation / PI_DIVIDE_180, TRAJECTORY_ANGLE_INIT_DEC_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, 0);

	// END OF TABLE
	appendTableHeaderSeparatorLine(outputStream);
}

void printDebugCoderHistory(OutputStream* outputStream) {
	#define TRAJECTORY_LEFT_DEC_COLUMN_LENGTH	            11
	#define TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH	            12
	#define TRAJECTORY_LEFT_HEX_COLUMN_LENGTH	            11
	#define TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH	            12
	#define TRAJECTORY_LAST_LEFT_COLUMN_LENGTH	            17
	#define TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH	            18
	#define TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH	            16
	#define TRAJECTORY_LAST_COLUMN_LENGTH					0

	// HEADER
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);

	appendStringHeader(outputStream, "left (Dec)", TRAJECTORY_LEFT_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "right (Dec)", TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "left (Hex)", TRAJECTORY_LEFT_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "right (Hex)", TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH);

	appendStringHeader(outputStream, "lastLeft (pulse)", TRAJECTORY_LAST_LEFT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "lastRight (pulse)", TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "lastAngle (deg)", TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, TRAJECTORY_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);

	// VALUES
	// Left / Right
	appendDecTableData(outputStream, getCoderValue(CODER_LEFT), TRAJECTORY_LEFT_DEC_COLUMN_LENGTH);
	appendDecTableData(outputStream, getCoderValue(CODER_RIGHT), TRAJECTORY_RIGHT_DEC_COLUMN_LENGTH);

	appendHex4TableData(outputStream, getCoderValue(CODER_LEFT), TRAJECTORY_LEFT_HEX_COLUMN_LENGTH);
	appendHex4TableData(outputStream, getCoderValue(CODER_RIGHT), TRAJECTORY_RIGHT_HEX_COLUMN_LENGTH);

	// Last left / Right / Angle
	appendDecTableData(outputStream, (long) lastLeft, TRAJECTORY_LAST_LEFT_COLUMN_LENGTH);
	appendDecTableData(outputStream, (long) lastRight, TRAJECTORY_LAST_RIGHT_COLUMN_LENGTH);
	appendDecfTableData(outputStream, lastAngle / PI_DIVIDE_180, TRAJECTORY_LAST_ANGLE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, TRAJECTORY_LAST_COLUMN_LENGTH);

	// END OF TABLE
	appendTableHeaderSeparatorLine(outputStream);
}
