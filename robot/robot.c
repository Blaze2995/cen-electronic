#include "robot.h"

#include <stdbool.h>

#include "../common/commons.h"
#include "../common/2d/2d.h"
#include "../common/delay/cenDelay.h"

#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/reader.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../device/transmitMode.h"

#include "../drivers/driver.h"
#include "../drivers/driverList.h"

#include "../drivers/motion/motionDriver.h"
#include "../drivers/motion/trajectoryDriver.h"
#include "../drivers/strategy/strategyDriver.h"

#include "../drivers/dispatcher/driverDataDispatcher.h"
#include "../drivers/dispatcher/driverDataDispatcherList.h"

#include "../device/motion/simple/motionDeviceInterface.h"
#include "../robot/match/endMatchDetectorDevice.h"

#include "../main/motorboard/motorBoard32.h"

// ROBOT POSITION
// x / y
static int robotPositionX;
static int robotPositionY;

// orientation in decideg
static int robotAngle;

/** Global variable to know if the robot must stop.*/
static bool robotMustStop = false;

static unsigned int timeAtLastCollision = 0;

static bool robotPositionChanged;

bool isRobotPositionChanged() {
    return robotPositionChanged;
}

void resetRobotPositionChanged() {
    robotPositionChanged = false;
}

void setRobotPositionChanged() {
    robotPositionChanged = true;
}

bool isRobotMustStop() {
    return robotMustStop;
}

int getRobotPositionX() {
    return robotPositionX;
}    

int getRobotPositionY() {
    return robotPositionY;
}    

int getRobotAngle() {
    return robotAngle;
}    

void updateRobotPosition(int x, int y, int angle) {
    robotPositionX = x;
    robotPositionY = y;
    robotAngle = angle;
}

void printRobotPosition(OutputStream* outputStream) {
    appendStringAndDec(outputStream, "\nRobotPositionX=", robotPositionX);
    appendStringAndDec(outputStream, "\nRobotPositionY=", robotPositionY);
    appendStringAndDec(outputStream, "\nRobotAngle=", robotAngle);
    println(outputStream);
}

void setRobotMustStop(bool value) {
    // Comment this if we want that robot doesn't stop on collision
    robotMustStop = value;
}

void stopRobot(void) {
    motionDriverStop();

    // notifyEnd();
    appendString(getWarningOutputStreamLogger(), "Robot stopped");
}

// OBSTACLE

void stopRobotObstacle(void) {
    /*
    unsigned int currentTime = getCurrentTimeInSecond();
    appendString(getWarningOutputStreamLogger(), "Current Time=");
    appendDec(getWarningOutputStreamLogger(), currentTime);
    appendString(getWarningOutputStreamLogger(), " secs\n");

    if (currentTime > timeAtLastCollision + TIME_FOR_OBSTACLE_NEW_NOTIFICATION) {
        timeAtLastCollision = currentTime;
        // TODO : PROBLEM OF STABILITY : motionDriverObstacle();
        motionDriverStop();
        // Notify to the Strategy Board the new position
        sentStrategyRobotPosition(NOTIFY_MOTION_ARG_OBSTACLE, getRobotPositionX(), getRobotPositionY(), getRobotAngle());

        appendString(getWarningOutputStreamLogger(), "Robot stopped(Obstacle)\n");
        printRobotPosition(getWarningOutputStreamLogger());
    } else {
        appendString(getWarningOutputStreamLogger(), "Wait for new notification \n");
    }
    */
}
