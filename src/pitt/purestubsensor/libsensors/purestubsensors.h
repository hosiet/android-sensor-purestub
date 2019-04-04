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
#ifndef PURESTUB_SENSORS_H
#define PURESTUB_SENSORS_H

#ifndef LOG_TAG
#define LOG_TAG "PureStubSensors"
#endif

#include <hardware/hardware.h>
#include <hardware/sensors.h>

int getEventAccelerometer(sensors_event_t *data_single, int serial);
int getEventGyroscope(sensors_event_t *data_single, int serial);
int getEventGameRotationVector(sensors_event_t *data_single, int serial);
int getEventRotationVector(sensors_event_t *data_single, int serial);



#endif /* PURESTUB_SENSORS_H */
