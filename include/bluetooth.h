#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <string.h>

#include <display/mb_display.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/conn.h>
#include <bluetooth/gatt.h>

void ble_init(void);
void ble_connect(void);
void conn_ready(bool initiator);
void ble_send_packet(s8_t data);
void packet_received(s8_t data);
void remote_disconnected(void);
void remote_lost(void);
void ble_send_lost(void);
void ble_cancel_connect(void);