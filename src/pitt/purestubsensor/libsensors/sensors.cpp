#define LOG_TAG "PureStubSensors"

#include <errno.h>

#include <hardware/sensors.h>

#include "sensors.h"


/* Real code below */

static int open_sensors (const struct hw_module_t* module, const char* id, struct hw_device_t ** device);

/**
 * The sensor_t struct, describing all available sensors
 * */
struct sensors_t sSensorsList[] = {
    {
        "Pure Stub 3-axis Accelerometer",  // const char* name;
        "University of Pittsburgh",        // const char* vendor;
        1,                                 // int         version,
        SENSORS_ACCELERATION_HANDLE,       // int         handle;
        SENSOR_TYPE_ACCELEROMETER,         // int         type;
        (GRAVITY_EARTH * 16.0f),           // float       maxRange;
        (GRAVITY_EARTH * 16.0f) / 4096.0f, // float       resolution;
        0.0001f,                           // float       power;
        10000,                             // int32_t     minDelay;    // in ms
        0,                                 // uint32_t    fifoReservedEventCount; // TODO
        0,                                 // uint32_t    fifoMaxEventCount;      // TODO
        0,                                 // const char* stringType;             // TODO
        0,                                 // const char* requiredPermission;
        0,                                 // int??_t     maxDelay;               // TODO
        0,                                 // uint??_t    flags;                  // TODO
        { 0 },
    },
};

static int sensors = (sizeof (sSensorsList) / sizeof (sensors_t));

/**
 * Returns sensor_t struct describing available sensors
 * */
static int sensors__get_sensors_list(struct sensors_module_t* module, struct sensor_t const** list) {
    *list = sSensorsList;
    return sensors;
}

/**
 * Set sensor operation mode, not supported so currently always returns -EINVAL
 * */
staic int sensors__set_operation_mode(unsigned int mode) {
    if (mode == 0) {
        return 0;
    } else {
        return -EINVAL;
    }
}


static struct hw_module_methods_t sensors_module_methods = {
    open: open_sensors,
};



/**
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 * followed by module specific information.
 *
 * Note: hw_module_t (type of common) was defined in <hardware/hardware.h>.
 */
struct sensors_module_t HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id: SENSOR_HARDWARE_MODULE_ID,
        name: "Pure Stub Sensor module",
        author: "Boyuan Yang",
        methods: &sensors_module_methods,      // TODO
        dso: NULL,                             // TODO
        reserved: {0},
    },
    get_sensors_list: sensors__get_sensors_list,
    set_operation_mode: sensors__set_operation_mode,
};
