#ifndef __UBIT_DEVICES_H
#define __UBIT_DEVICES_H

#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <display/mb_display.h>
#include <sensor.h>

#define ACC_DEV_ADDR        0x1D
#define ACC_WHO_AM_I_REG    0x0D
#define ACC_TEST_VALUE      0x5A
#define ACC_CTRL_REG        0x2A
#define ACC_OUT_X_MSB       0x01
#define ACC_OUT_X_LSB       0x02
#define ACC_OUT_Y_MSB       0x03
#define ACC_OUT_Y_LSB       0x04
#define ACC_OUT_Z_MSB       0x05
#define ACC_OUT_Z_LSB       0x06

#define COMPASS_DEV_ADDR        0x0e
#define COMPASS_WHO_AM_I_REG    0x07
#define COMPASS_TEST_VALUE      0xC4
#define COMPASS_CTRL_REG        0x10
#define MAG_OUT_X_MSB           0x01
#define MAG_OUT_X_LSB           0x02
#define MAG_OUT_Y_MSB           0x03
#define MAG_OUT_Y_LSB           0x04
#define MAG_OUT_Z_MSB           0x05
#define MAG_OUT_Z_LSB           0x06

u16_t get_sleep_time();

//** Device initiation functions**//
void init_display();
void init_temperature_sensor();
void init_accelerometer_sensor();
void init_magnetometer_sensor();

//Prints the message "ECOM042.2017.2"
//to microbit display
void print_to_display();

//Read temperature value in degrees Celsius
void read_temperature();

//Read accelerometer axis values
void read_accelerometer();

//Return accelerometer's axis red values
u16_t get_accelerometer_x();
u16_t get_accelerometer_y();
u16_t get_accelerometer_z();
u8_t get_accel_col(u16_t x_accel);
u8_t get_accel_row(u16_t y_accel);

//Print a dot on microbit display
//according with the accelerometer readings
void update_accel_display();

//Read magnetometer axis values
void read_magnetometer();

//Return magnetometer's axis red values
u16_t read_compass_x();
u16_t read_compass_y();
u16_t read_compass_z();

//Print the direction which the board is pointing
void print_compass_direction();

void connect_to_bluetooth();

#endif //__UBIT_DEVICESL_H