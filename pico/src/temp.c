/*
 * Copyright (c) 2024 Space Cubics, LLC.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/i2c.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <csp/csp.h>
#include <csp/drivers/usart.h>
#include "temp.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(temp, LOG_LEVEL_DBG);

#define DEV_ADDR   (0x4e)
#define START_ADDR (0x00)
#define RESOLUTION (0.0625f)
#define BIT_SHIFT  (4)

extern const struct device *const temp_sensor;

void get_temp(csp_conn_t *conn)
{
	struct sensor_value temp_val;
	int rc = sensor_sample_fetch(temp_sensor);

	if (rc < 0) {
		LOG_ERR("Failed to fetch sensor data, error: %d", rc);
        return;
	} else {
		LOG_INF("Sensor data fetch successful");
	}

	/* get temp_data */
	rc = sensor_channel_get(temp_sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp_val);
	if (rc < 0) {
		LOG_ERR("Failed to get sensor data, error: %d", rc);
		return;
	} else {
		LOG_INF("Sensor data get successful");
	}

	/* creating a packet to send temp_data */
	csp_packet_t *send_packet = csp_buffer_get(0);
	if (send_packet == NULL) {
		LOG_ERR("Failed to get CSP buffer");
		return;
	}

	/* Convert temperature data to the appropriate format*/
	float temp = (float)(temp_val.val1  + (float)(temp_val.val2)/1000000.0f);

	memcpy(send_packet->data, &temp, sizeof(temp));
	send_packet->length = sizeof(temp);
	csp_send(conn, send_packet);

}
