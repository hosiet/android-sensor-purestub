/*
 * Copyright (C) 2015 Anna-Lena Marx
 * Copyright (C) 2019 Boyuan Yang <by.yang@pitt.edu>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
 *
 * @param module seems to be the pointer to HAL_MODULE_INFO_SYM
 * @param list Output variable, provide a pointer to a list of sensors_t.
 * @return Number of sensors on the list
 * */
static int sensors__get_sensors_list(struct sensors_module_t* module, struct sensor_t const** list) {
    *list = sSensorsList;
    return sensors;
}

/**
 * The implementation of activate() for accelerometer
 * */
static int sensor_accelerometer__activate(struct sensors_poll_device_t *dev, int sensor_handle, int enabled) {
    // TODO Activate the accelerometer
    return 0;
}

static int sensor_accelerometer__batch(struct sensors_poll_device_1* dev,
        int sensor_handle,
        int flags,
        int64_t sampling_period_ns,
        int64_t max_report_latency_ns) {
    // TODO finish batch function
    return 0;
}

static int sensor_accelerometer__flush(struct sensors_poll_device_1* dev, int sensor_handle) {
    // TODO finish flush function
    return 0;
}

static int sensor_accelerometer__poll(struct sensors_poll_device_t *dev, sensors_event_t* data, int count) {
    // TODO FIXME return a data
    return -1;
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
common: {                                  /* type: hw_module_t */
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


/** Using a C++-Specific way to handle poll context! */
struct sensors_poll_context_t {
    sensors_poll_device_1_t device; /* where the hw_device_t* pointer points to */

    sensors_poll_context_t();
    ~sensors_poll_context_t();
    int activate(int handle, int enabled);
    int setDelay(int handle, int64_t ns);
    int pollEvents(sensors_event_t* data, int count);
    int batch(int handle, int flags, int64_t period_ns, int64_t timeout);

    bool isValid() { return mInitialized; };
    int flush(int handle);

private:
    bool mInitialized;
    bool mAccelerometerEnabled;
};

sensors_poll_context_t::sensors_poll_context_t() {
    mInitialized = false;
    // TODO init works
    mAccelerometerEnabled = false;
    mInitialized = true;
}

sensors_poll_context_t::~sensors_poll_context_t() {
    // TODO takedown works
    mInitialized = false;
}

int sensors_poll_context_t::activate(int handle, int enabled) {
    if (!mInitialized) {
        return -EINVAL;
    }
    // TODO activate the sensor
    int err = 0;
    return err;
}

int sensors_poll_context_t::setDelay(int handle, int64_t ns) {
    // TODO FIXME
    return -1;
}

int sensors_poll_context_t::pollEvents(sensors_event_t *data, int count) {
    // TODO FIXME
    return -1;
}

int sensors_poll_context_t::batch(int handle, int flags, int64_t period_ns, int64_t timeout) {
    // Do nothing at this moment
    return 0;
}

int sensors_poll_context_t::flush(int handle) {
    // Do nothing at this moment
    return 0;
}

/* ********************************************************** */
/*
 * Static wrapper for poll activities.
 *
 * The real actions are wrapped in the methods of sensors_poll_context_t class.
 * */

static int poll__close (struct hw_device_t *dev) {
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    if (ctx) {
        delete ctx;
    }
    return 0;
}

static int poll__activate (struct sensors_poll_device_t *dev, int handle, int enabled) {
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->activate(handle, enabled);
}

static int poll__setDelay (struct sensors_poll_device_t *dev, int handle, int64_t ns) {
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    int s = ctx->setDelay(handle, ns);
    return s;
}

static int poll__poll (struct sensors_poll_device_t *dev, sensors_event_t* data, int count) {
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->pollEvents(data, count);
}

static int poll__batch (struct sensors_poll_device_1 *dev, int handle, int flags,
            int64_t period_ns, int64_t timeout) {
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->batch(handle, flags, period_ns, timeout);
}

static int poll__flush (struct sensors_poll_device_1 *dev, int handle) {
    sensors_poll_context_t *ctx = (sensors_poll_context_t *)dev;
    return ctx->flush(handle);
}


/* ENDOF Static Wrappers ********************************************************/


static int open_sensors (const struct hw_module_t* module, const char* id, struct hw_device_t ** device) {
    int status = -EINVAL;
    // TODO Init the device
    sensors_poll_context_t *dev = new sensors_poll_context_t();
    /* Check if we successfully initialized the device */
    if (! dev->isValid()) {
        return status;
    }
    /* Set the whole sensors_poll_device_1_t structure to be 0 */
    memset(&dev->device, 0, sizeof(sensors_poll_device_1_t));  // TODO FIXME _t or not?
    /* Assign value to dev->device, which is ??? */
    dev->device.common.tag = HARDWARE_DEVICE_TAG;
    dev->device.common.version = SENSORS_DEVICE_API_VERSION_1_3;
    dev->device.common.module = const_cast<hw_module_t*>(module);
    dev->device.common.close = poll__close;
    dev->device.activate = poll__activate;
    dev->device.setDelay = poll__setDelay;
    dev->device.poll = poll__poll;
    dev->device.batch = poll__batch;
    dev->device.flush = poll__flush;

    *device = &dev->device.common;

    /* Finish all */
    status = 0;
    return status;
}
