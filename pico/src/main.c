/*
 * Copyright (c) 2023 Space Cubics, LLC.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "pico_csp.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

const struct device *const temp_sensor = DEVICE_DT_GET_ANY(lm75);

int main(void)
{
	const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
	int ret;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

        if (!device_is_ready(temp_sensor)) {
        	LOG_ERR("Temperature sensor not found or not ready!");
        	return 0;
        }

	csp_server_start();

	while (true) {
		(void)gpio_pin_toggle_dt(&led);
		k_sleep(K_SECONDS(1));
	}

	return 0;
}
