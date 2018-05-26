#include "ubit_devices.h"
#include "i2c_util.h"

static struct mb_display *disp;
static struct sensor_value temp_value;
static struct device *temperature_device;
static struct i2c_dev acc;
static struct i2c_dev compass;

static u8_t __init_display = 0;
static u8_t __init_temperature = 0;
static u8_t __init_accelerometer = 0;
static u8_t __init_magnetometer = 0;

static u16_t __accelerometer_x = 0;
static u16_t __accelerometer_y = 0;
static u16_t __accelerometer_z = 0;

static u16_t __magnetometer_x = 0;
static u16_t __magnetometer_y = 0;
static u16_t __magnetometer_z = 0;

static u16_t __sleep_time = 0;

static struct mb_image image = MB_IMAGE(
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }
);
static u8_t __row = 2;
static u8_t __col = 2;

u16_t get_sleep_time() {
    return __sleep_time;
}

void init_display() {
    if(!__init_display) {
        disp = mb_display_get();
        __init_display = 1;
        return;
    }
    printk("Display already initiated.\n");
}

void init_temperature_sensor() {
    if(!__init_temperature) {
        temperature_device = device_get_binding("TEMP_0");
        __init_temperature = 1;
    }
}

void init_accelerometer_sensor() {    
    u8_t temp = 0x01;
	i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                                ACC_TEST_VALUE);
    i2c_util_test_connection(&acc);
    i2c_util_write_bytes(&acc, ACC_CTRL_REG, &temp, sizeof(u8_t));
    __init_accelerometer = 1;
}

void init_magnetometer_sensor() {    
    u8_t temp = 0x01;
	i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS", COMPASS_WHO_AM_I_REG,
                                 COMPASS_TEST_VALUE);
    i2c_util_write_bytes(&compass, COMPASS_CTRL_REG, &temp, sizeof(u8_t));
    __init_magnetometer = 1;
}


void print_to_display() {
    if(!__init_display) {
        init_display();
    }
	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP, 
    K_MSEC(500), "ECOM042.2017.2");
    printk("ECOM042.2017.2\n");
    __sleep_time = 8000;
}

void read_temperature() {
    if(!__init_temperature) {
        init_temperature_sensor();
    }
    	
    int r;    
	r = sensor_sample_fetch(temperature_device);
	if (r) {
		printf("sensor_sample_fetch failed return: %d\n", r);
		return;
	}

	r = sensor_channel_get(temperature_device, SENSOR_CHAN_TEMP, &temp_value);
	if (r) {
		printf("sensor_channel_get failed return: %d\n", r);
		return;
	}    
    int val = (int)sensor_value_to_double(&temp_value);
    mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP, 
    K_MSEC(500), "%dC\n", val);
    printf("Temperature is %d ºC\n", val);
    __sleep_time = 2500;    
}

void read_accelerometer() {
    if(!__init_accelerometer) {
        init_accelerometer_sensor();        
    }
    u8_t data[6];
    
    i2c_util_read_bytes(&acc, ACC_OUT_X_MSB, data, sizeof(data));
    __accelerometer_x = data[0];
    __accelerometer_y = data[2];
    __accelerometer_z = data[4];

    SYS_LOG_DBG("ACC X: %d", data[0]);
    SYS_LOG_DBG("ACC Y: %d", data[2]);
    SYS_LOG_DBG("ACC Z: %d\n", data[4]);

    __sleep_time = 1000;
}

u16_t get_accelerometer_x() {    
    return __accelerometer_x;
}

u16_t get_accelerometer_y() {
    return __accelerometer_y;
}

u16_t get_accelerometer_z() {    
    return __accelerometer_z;
}

void read_magnetometer() {
    if(!__init_magnetometer) {
        init_magnetometer_sensor();        
    }
    u8_t data[2];
    
    i2c_util_read_bytes(&compass, MAG_OUT_X_MSB, data, sizeof(data));
    __magnetometer_x = ((data[1] << 8) | data[0]);    
    SYS_LOG_DBG("MAG X: %d", __magnetometer_x);

    i2c_util_read_bytes(&compass, MAG_OUT_Y_MSB, data, sizeof(data));
    __magnetometer_y = ((data[1] << 8) | data[0]);
    SYS_LOG_DBG("MAG Y: %d", __magnetometer_y);

    i2c_util_read_bytes(&compass, MAG_OUT_Z_MSB, data, sizeof(data));
    __magnetometer_z = ((data[1] << 8) | data[0]);
    SYS_LOG_DBG("MAG Z: %d\n", __magnetometer_z);

    __sleep_time = 100;
}

u16_t get_magnetometer_x() {    
    return __magnetometer_x;
}

u16_t get_magnetometer_y() {    
    return __magnetometer_y;
}

u16_t get_magnetometer_z() {
    return __magnetometer_z;
}

void print_compass_direction() {
    read_magnetometer();
    if( get_magnetometer_x() >= 57000 && get_magnetometer_x() <= 61000 &&
        get_magnetometer_y() >= 30000 && get_magnetometer_y() <= 34000 &&
        get_magnetometer_z() >= 60000 && get_magnetometer_x() <= 65000) {
        
        mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(500), "N");        
    }
    else if( get_magnetometer_x() >= 4000 && get_magnetometer_x() <= 7000 &&
        get_magnetometer_y() >= 50000 && get_magnetometer_y() <= 54000 &&
        get_magnetometer_z() >= 14000 && get_magnetometer_x() <= 18000) {

        mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(500), "S");        
    }
    else if( get_magnetometer_x() >= 46000 && get_magnetometer_x() <= 50000 &&
        get_magnetometer_y() >= 55000 && get_magnetometer_y() <= 60000 &&
        get_magnetometer_z() >= 58000 && get_magnetometer_x() <= 64000) {

        mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(500), "O");        
    }
    else if( get_magnetometer_x() >= 4000 && get_magnetometer_x() <= 7000 &&
        get_magnetometer_y() >= 50000 && get_magnetometer_y() <= 54000 &&
        get_magnetometer_z() >= 14000 && get_magnetometer_x() <= 18000) {

        mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(500), "L");        
    }

    mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(500), "?");    
}

void connect_to_bluetooth() {
    printk("No bluetooth interface implemented.\n");    
    printk("Connection could not be stablished...\n");
    __sleep_time = 1000;
}

void update_accel_display() {
    // u16_t x, y;
    read_accelerometer();
    //Clear display pixel
    image.row[__row] = image.row[__row] & ~BIT(__col);    

    //Get the new position of the pixel according
    //with the accelerometer
    __col = get_accel_col(get_accelerometer_x());
    __row = get_accel_row(get_accelerometer_y());

    //Set the display pixel
    image.row[__row] = image.row[__row] | BIT(__col);
    mb_display_image(disp, MB_DISPLAY_MODE_SINGLE, K_MSEC(1000), &image, 1);    
}

u8_t get_accel_col(u16_t x_accel) {
    u8_t ret = 2; //center as default
    if( x_accel >= 190 && x_accel < 200 ) {
        ret = 4;
    }
    else if(x_accel >= 200 && x_accel < 220) {
        ret = 3;
    }
    else if(x_accel >= 220 && x_accel <= 255) {
        ret = 2;
    } else if(x_accel >= 0 && x_accel < 20) {
        ret = 1;
    } else if(x_accel >= 20 && x_accel < 70) {
        ret = 0;
    }
    return ret;
}

u8_t get_accel_row(u16_t y_accel) {
    u8_t ret = 2; //center as default
    if( y_accel >= 190 && y_accel < 200 ) {
        ret = 4;
    }
    else if(y_accel >= 200 && y_accel < 220) {
        ret = 3;
    }
    else if(y_accel >= 220 && y_accel <= 255) {
        ret = 2;
    } else if(y_accel >= 0 && y_accel < 20) {
        ret = 1;
    } else if(y_accel >= 20 && y_accel < 70) {
        ret = 0;
    }
    return ret;
}