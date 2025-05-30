/* Copyright (c) 2024 Nordic Semiconductor ASA
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <testlib/conn.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci_types.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/__assert.h>

int bt_testlib_disconnect(struct bt_conn **connp, uint8_t reason)
{
	int err;

	__ASSERT_NO_MSG(connp);
	__ASSERT_NO_MSG(*connp);

	err = bt_conn_disconnect(*connp, BT_HCI_ERR_REMOTE_USER_TERM_CONN);

	if (!err) {
		bt_testlib_wait_disconnected(*connp);
		bt_testlib_conn_unref(connp);
	}

	return err;
}
