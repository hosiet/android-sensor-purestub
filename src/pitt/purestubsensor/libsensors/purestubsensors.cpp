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

#include <ctime>
#include <cstdint>
#include <cinttypes>

#include "sensors.h"
#include "purestubsensors.h"

#define _BILLION (1000000000L)

int getEventGyroscope(sensors_event_t *data_single, int serial) {
    struct timespec t_spec = {};
    uint64_t all;
    long int ns;
    time_t sec;

    if (data_single == NULL) {
        return -EINVAL;
    }

    /* Fill in sensor data */
    data_single->version = (int32_t) sizeof(struct sensors_event_t);
    //data_single->sensor = (int32_t) PURESTUB_SENSORS_IDENTIFIER_GYROSCOPE;
    data_single->sensor = (int32_t) PURESTUB_SENSORS_GYROSCOPE_HANDLE;
    data_single->type = SENSOR_TYPE_GYROSCOPE;
    clock_gettime(CLOCK_REALTIME, &t_spec);
    sec = t_spec.tv_sec;
    ns = t_spec.tv_nsec;
    all = (uint64_t) sec * _BILLION + (uint64_t) ns;
    //data_single->timestamp = (int64_t) all;
    data_single->timestamp = 0;
    /* Explicitly provide two sets of different data
     * in order to trigger acceleration data change */
    if (ns % 2 == 0) {
        data_single->gyro.x = 1.1f;
        data_single->gyro.y = 2.2f;
        data_single->gyro.z = 3.3f;
    } else {
        data_single->gyro.x = 0.5f;
        data_single->gyro.y = 0.6f;
        data_single->gyro.z = 0.7f;
    }
    
    return 0;
}

int getEventAccelerometer(sensors_event_t *data_single, int serial) {
    struct timespec t_spec = {};
    uint64_t all;
    long int ns;
    time_t sec;

    if (data_single == NULL) {
        return -EINVAL;
    }

    /* Fill in sensor data first */
    data_single->version = (int32_t) sizeof(struct sensors_event_t);
    //data_single->sensor = (int32_t) PURESTUB_SENSORS_IDENTIFIER_ACCELEROMETER;
    data_single->sensor = (int32_t) PURESTUB_SENSORS_ACCELERATION_HANDLE;
    data_single->type = SENSOR_TYPE_ACCELEROMETER;
    clock_gettime(CLOCK_REALTIME, &t_spec);
    sec = t_spec.tv_sec;
    ns = t_spec.tv_nsec;
    all = (uint64_t) sec * _BILLION + (uint64_t) ns;
    //data_single->timestamp = (int64_t) all;
    data_single->timestamp = 0;
    /* Explicitly provide two sets of different data
     * in order to trigger acceleration data change */
    if (ns % 2 == 0) {
        data_single->acceleration.x = 1.1f;
        data_single->acceleration.y = 2.2f;
        data_single->acceleration.z = 3.3f;
    } else {
        data_single->acceleration.x = 5.5f;
        data_single->acceleration.y = 6.6f;
        data_single->acceleration.z = 7.7f;
    }

    return 0;
}
