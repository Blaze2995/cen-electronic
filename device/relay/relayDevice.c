#include <stdbool.h>

#include <p30Fxxxx.h>

#include "relayDevice.h"
#include "relayDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

void deviceRelayInit() {
    
}

void deviceRelayShutDown() {
}

bool deviceRelayIsOk() {
    return true;
}

void deviceRelayHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_SET_RELAY) {
        int relayIndex = readHex2(inputStream);
        unsigned char value = inputStream->readChar(inputStream);
        
        if (relayIndex == 0) {
            LATDbits.LATD8 = value;
        }
        else if (relayIndex == 1) {
            LATDbits.LATD9 = value;
        }
        appendAck(outputStream);
        append(outputStream, COMMAND_SET_RELAY);
    }
}


static DeviceDescriptor descriptor = {
    .deviceInit = &deviceRelayInit,
    .deviceShutDown = &deviceRelayShutDown,
    .deviceIsOk = &deviceRelayIsOk,
    .deviceHandleRawData = &deviceRelayHandleRawData,
};

DeviceDescriptor* getRelayDeviceDescriptor() {
    return &descriptor;
}
