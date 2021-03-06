#ifndef I2C_SLAVE_DEBUG_DEVICE_H
#define I2C_SLAVE_DEBUG_DEVICE_H

#include "../../../common/i2c/i2cCommon.h"

#include "../../../device/deviceDescriptor.h"

/**
 * The descriptor for the I2C Slave debug device (send some information, ask buffers ...)
 */
DeviceDescriptor* getI2cSlaveDebugDeviceDescriptor(I2cBusConnection* i2cBusConnection);

#endif
