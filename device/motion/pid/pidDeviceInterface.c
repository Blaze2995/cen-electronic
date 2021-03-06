#include <stdbool.h>

#include "pidDeviceInterface.h"

#include "../../../device/device.h"
#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

const char* getPIDDeviceName(void) {
    return "PID";
}

int devicePIDGetInterface(char commandHeader, DeviceInterfaceMode mode, bool fillDeviceArgumentList) {
    if (commandHeader == COMMAND_WRITE_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("setPID", 9, 0);
            setArgumentUnsignedHex2(0, "pidIdx");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "p");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "i");
            setArgumentSeparator(5);
            setArgumentUnsignedHex2(6, "d");
            setArgumentSeparator(7);
            setArgumentUnsignedHex2(8, "mI");
        }
        return commandLengthValueForMode(mode, 14, 0);
    } else if (commandHeader == COMMAND_READ_PID_PARAMETERS) {
        if (fillDeviceArgumentList) {
            setFunction("getPID", 1, 9);
            setArgumentUnsignedHex2(0, "pidIdx");
            setResultUnsignedHex2(0, "pidIdx");
            setResultSeparator(1);
            setResultUnsignedHex2(2, "p");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "i");
            setResultSeparator(5);
            setResultUnsignedHex2(6, "d");
            setResultSeparator(7);
            setResultUnsignedHex2(8, "mI");
        }
        return commandLengthValueForMode(mode, 2, 14);
    } else if (commandHeader == COMMAND_LOAD_PID_DEFAULT_VALUES) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("loadDefaultValues");
        }
        return commandLengthValueForMode(mode, 0, 0);
    } else if (commandHeader == COMMAND_SET_END_DETECTION_PARAMETER) {
        if (fillDeviceArgumentList) {
            setFunction("setEndDetectParam", 9, 0);
            setArgumentUnsignedHex2(0, "absDeltaPositionIntegralFactorThreshold");
            setArgumentSeparator(1);
            setArgumentUnsignedHex2(2, "maxUIntegralFactorThreshold");
            setArgumentSeparator(3);
            setArgumentUnsignedHex2(4, "maxUIntegralConstantThreshold");
            setArgumentSeparator(5);
            setArgumentUnsignedHex2(6, "timeRangeAnalysis");
            setArgumentSeparator(7);
            setArgumentUnsignedHex2(8, "noAnalysisAtStartupTime");
        }
        return commandLengthValueForMode(mode, 14, 0);
    } else if (commandHeader == COMMAND_GET_END_DETECTION_PARAMETER) {
        if (fillDeviceArgumentList) {
            setFunction("getEndDetectParameter", 0, 9);
            setResultUnsignedHex2(0, "absDeltaPositionIntegralFactorThreshold");
            setResultSeparator(1);             
            setResultUnsignedHex2(2, "maxUIntegralFactorThreshold");
            setResultSeparator(3);             
            setResultUnsignedHex2(4, "maxUIntegralConstantThreshold");
            setResultSeparator(5);             
            setResultUnsignedHex2(6, "timeRangeAnalysis");
            setResultSeparator(7);             
            setResultUnsignedHex2(8, "noAnalysisAtStartupTime");
        }
        return commandLengthValueForMode(mode, 0, 14);
    } else if (commandHeader == COMMAND_GET_DEBUG_DATA_PID) {
        if (fillDeviceArgumentList) {
            setFunction("sendDbgDataPid", 1, 19);
            
            setArgumentUnsignedHex2(0, "instructionType");

            setResultUnsignedHex2(0, "instructionType");
            setResultSeparator(1);             
            setResultUnsignedHex4(2, "pidTime");
            setResultSeparator(3);             
            setResultUnsignedHex2(4, "pidType");
            setResultSeparator(5); 
            setResultUnsignedHex6(6, "normalPosition");
            setResultSeparator(7);
            setResultUnsignedHex6(8, "position");
            setResultSeparator(9);
            setResultUnsignedHex4(10, "error");
            setResultSeparator(11);
            setResultUnsignedHex4(12, "u");
            setResultSeparator(13);
            setResultUnsignedHex4(14, "endMotion_integralTime");
            setResultSeparator(15);
            setResultUnsignedHex4(16, "endMotion_absDelPosiInt");
            setResultSeparator(17);
            setResultUnsignedHex4(18, "endMotion_uIntegral");
        }
        return commandLengthValueForMode(mode, 2, 49);
    } else if (commandHeader == COMMAND_GET_MOTION_PARAMETER) {
        if (fillDeviceArgumentList) {    
            setFunction("getMotionParameter", 1, 25);
            
            setArgumentUnsignedHex2(0, "idx");
            
            setResultUnsignedHex2(0, "idx");
            setResultSeparator(1);
            setResultUnsignedHex2(2, "a");
            setResultSeparator(3);
            setResultUnsignedHex2(4, "s");
            setResultSeparator(5);
            setResultUnsignedHex2(6, "smax");
            setResultSeparator(7);
            setResultUnsignedHex4(8, "t1");
            setResultSeparator(9);
            setResultUnsignedHex4(10, "t2");
            setResultSeparator(11);
            setResultUnsignedHex4(12, "t3");
            setResultSeparator(13);
            setResultUnsignedHex6(14, "p1");
            setResultSeparator(15);
            setResultUnsignedHex6(16, "p2");
            setResultSeparator(17);
            setResultUnsignedHex6(18, "p3/nextPosition");
            setResultSeparator(19);
            setResultUnsignedChar1(20, "profileType");
            setResultSeparator(21);
            setResultUnsignedChar1(22, "motionParameterType");
            setResultSeparator(23);
            setResultUnsignedChar1(24, "pidType");
        }
        return commandLengthValueForMode(mode, 2, 53);
    }
	else if (commandHeader == COMMAND_PID_MOTION_PARAMETER_DEBUG) {
		if (fillDeviceArgumentList) {
			setFunctionNoArgumentAndNoResult("pidMotionParameterDebug");
		}
		return commandLengthValueForMode(mode, 0, 0);
	}
	return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceHeader = PID_DEVICE_HEADER,
    .deviceGetName = &getPIDDeviceName,
    .deviceGetInterface = &devicePIDGetInterface
};

DeviceInterface* getPIDDeviceInterface() {
    return &deviceInterface;
}
