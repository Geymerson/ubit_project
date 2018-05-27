#ifndef __UBIT_DEVICES_H
#define __UBIT_DEVICES_H

/*! \file ubit_devices.h
    \brief Device functions definition.    
    This library will define functions to initiate sensors, 
    read data and print to microbit's display.
*/

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


/*! \fn u16_t get_sleep_time()
    \brief Get the required sleep time to the current device.

    When temperature, accelerometer or magnetometer sensors are
    being used, their information require a certain time the be shown
    on microbit's display. This function return the required time.
*/
u16_t get_sleep_time();

/*! \fn void init_display()
    \brief Initiate the display device.

    This function must be called before printing anything to
    microbit's display.
*/
void init_display();

/*! \fn void init_temperature_sensor()
    \brief Initiate the display device.

    This function must be called in order to
    use the temperature sensor.
*/
void init_temperature_sensor();

/*! \fn void init_accelerometer_sensor()
    \brief Initiate the accelerometer device.

    This function must be called in order to
    use the accelerometer sensor.
*/
void init_accelerometer_sensor();

/*! \fn void init_magnetometer_sensor()
    \brief Initiate the magnetometer device.

    This function must be called in order to
    use the magnetometer sensor.
*/
void init_magnetometer_sensor();

/*! \fn void print_to_display(()
    \brief Print the message "ECOM042.2017.2" to microbit's display

*/
void print_to_display();

/*! \fn void read_temperature()
    \brief Read temperature value in degrees Celsius
*/
void read_temperature();

/*! \fn void read_accelerometer()
    \brief Read accelerometer x, y and z axis values
*/
void read_accelerometer();

/*! \fn void get_accelerometer_x()
    \brief Return accelerometer's x value

    Before use this function, read_accelerometer() must be called.
*/
u16_t get_accelerometer_x();

/*! \fn void get_accelerometer_y()
    \brief Return accelerometer's y value

    Before use this function, read_accelerometer() must be called.
*/
u16_t get_accelerometer_y();

/*! \fn void get_accelerometer_z()
    \brief Return accelerometer's z value

    Before use this function, read_accelerometer() must be called.
*/
u16_t get_accelerometer_z();

/*! \fn u8_t get_accel_col(u16_t x_accel)
    \brief Return the a display column
    \param x_accel The accelerometer x reading

    This function receives the current x acceleration data and returns a 
    valid column value to be set on the microbits display
*/
u8_t get_accel_col(u16_t x_accel);

/*! \fn u8_t get_accel_row(u16_t y_accel)
    \brief Return the a display column
    \param y_accel The accelerometer y reading

    This function receives the current y acceleration data and returns a 
    valid row value to be set on the microbits display
*/
u8_t get_accel_row(u16_t y_accel);

//Print a dot on microbit display
//according with the accelerometer readings

/*! \fn void update_accel_display()
    \brief Update a display pixel position    

    This function shows a moving dot on microbit's display. The dot
    moves according to the accelerometer sensor readings
*/
void update_accel_display();

/*! \fn void read_magnetometer()
    \brief Read magnetometer axis values
    
*/
void read_magnetometer();

/*! \fn u16_t read_compass_x()
    \brief Return magnetometer's x value

    Before use this function, read_magnetometer() must be called.
*/
u16_t read_compass_x();

/*! \fn u16_t read_compass_y()
    \brief Return magnetometer's y value

    Before use this function, read_magnetometer() must be called.
*/
u16_t read_compass_y();

/*! \fn u16_t read_compass_z()
    \brief Return magnetometer's z value

    Before use this function, read_magnetometer() must be called.
*/
u16_t read_compass_z();

/*! \fn print_compass_direction()
    \brief Print the direction which the board is pointing

    Print the direction which the board is pointing based on the
    magnetometer sensor readings. Possible directions are 'N', 'S',
    'L' and 'O'. If no direction is detected, a '?' will be displayed.
*/
void print_compass_direction();

/*! \fn connect_to_bluetooth()
    \brief Stablish a bluetooth connection with an external device

*/
void connect_to_bluetooth();

#endif //__UBIT_DEVICESL_H
