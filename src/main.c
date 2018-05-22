#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <display/mb_display.h>
#include <sensor.h>
#include <stdio.h>

// #include "version.h"
// #include "i2c_util.h"

// struct i2c_dev acc, compass;

// #define ACC_DEV_ADDR     0x1D
// #define ACC_WHO_AM_I_REG 0x0D
// #define ACC_TEST_VALUE   0x5A

// #define COMPASS_DEV_ADDR     0x0e
// #define COMPASS_WHO_AM_I_REG 0x07
// #define COMPASS_TEST_VALUE   0xC4


void main(void) {
	//struct mb_display *disp = mb_display_get();
	
	//Scrolling text ("ECOM042.2017.2")
//	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP, K_MSEC(500), "ECOM042.2017.2");

	// SYS_LOG_WRN("Firmware version: v%d.%d.%d",
    //                     VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

	// i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
    //                             ACC_TEST_VALUE);
	// i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS",
    //                             COMPASS_WHO_AM_I_REG, COMPASS_TEST_VALUE);
/**
	struct device *temp_dev;

	printf("Thermometer Example! %s\n", CONFIG_ARCH);

	temp_dev = device_get_binding("TEMP_0");
	if (!temp_dev) {
		printf("error: no temp device\n");
		return;
	}

	printf("temp device is %p, name is %s\n",
	       temp_dev, temp_dev->config->name);

	while (1) {
		int r;
		struct sensor_value temp_value;

		r = sensor_sample_fetch(temp_dev);
		if (r) {
			printf("sensor_sample_fetch failed return: %d\n", r);
			break;
		}

		r = sensor_channel_get(temp_dev, SENSOR_CHAN_TEMP,
				       &temp_value);
		if (r) {
			printf("sensor_channel_get failed return: %d\n", r);
			break;
		}

		printf("Temperature is %gC\n",
		       sensor_value_to_double(&temp_value));

		k_sleep(1000);
	}**/
}


