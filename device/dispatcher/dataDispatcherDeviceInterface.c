#include "dataDispatcherDeviceInterface.h"

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

const char* deviceDataDispatcherDebugGetName(void) {
    return "dataDispatcher";
}

int deviceDataDispatcherGetInterface(char header, int mode, bool fillDeviceArgumentList) {
    if (header == COMMAND_DISPATCHER_LIST) {
        if (fillDeviceArgumentList) {
            setFunctionNoArgumentAndNoResult("showDispatcherList");
        }
        return 0;
    }

    return DEVICE_HEADER_NOT_HANDLED;
}

static DeviceInterface deviceInterface = {
    .deviceGetName = &deviceDataDispatcherDebugGetName,
    .deviceHeader = DATA_DISPATCHER_DEVICE_HEADER,
    .deviceGetInterface = &deviceDataDispatcherGetInterface
};

DeviceInterface* getDataDispatcherDeviceInterface(void) {
    return &deviceInterface;
}