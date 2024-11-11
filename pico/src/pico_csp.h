/*
 * Copyright (c) 2024 Space Cubics, LLC.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <csp/csp.h>

#define PORT_T (11U) /* for get temperature */

#define MAIN_OBC_CAN_ADDR (1U)
#define RPI_ZERO_CAN_ADDR (2U)
#define RPI_ZERO_UART_ADDR (3U)
#define RPI_PICO_UART_ADDR (4U)

int csp_server_start(void);
