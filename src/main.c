#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
#include <display/mb_display.h>
#include <sensor.h>
#include <stdio.h>


#include "buttons.h"

#include "version.h"
#include "i2c_util.h"

struct i2c_dev acc, compass;

#define ACC_DEV_ADDR     0x1D
#define ACC_WHO_AM_I_REG 0x0D
#define ACC_TEST_VALUE   0x5A

#define COMPASS_DEV_ADDR     0x0e
#define COMPASS_WHO_AM_I_REG 0x07
#define COMPASS_TEST_VALUE   0xC4

static struct mb_display *disp;
static s64_t a_timestamp;
static s64_t b_timestamp;
static uint16_t sleep_interval = 8000;

typedef enum {
	HELLO,
	TEMP,
	ACCEL,
	MAG,
	BLTH
} state_t;

typedef enum {
    NEXT,
    PREVIOUS,
    CURRENT
} event_t;

typedef struct {
    state_t events[3];
    void (*action)(void);
} mstate_t;

static event_t current_event = CURRENT;

int event_changed = 0;

//Scrolling text ("ECOM042.2017.2")
void hello_world() {
	current_event = CURRENT;
    printf("ECOM042.2017.2\n");	
	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP, K_MSEC(500), "ECOM042.2017.2");	
    event_changed = 0;
}

// K_THREAD_DEFINE(hello_world_id, 128, hello_world, NULL, NULL, NULL, 7, 0, K_NO_WAIT);

int r;
struct sensor_value temp_value;
struct device *temp_dev;
void temperature_read() {
    printf("Reading temperature!\n");
	current_event = CURRENT;
    event_changed = 0;
	sleep_interval = 5000;

	r = sensor_sample_fetch(temp_dev);
	if (r) {
		printf("sensor_sample_fetch failed return: %d\n", r);
		return;
	}

	r = sensor_channel_get(temp_dev, SENSOR_CHAN_TEMP, &temp_value);
	if (r) {
		printf("sensor_channel_get failed return: %d\n", r);
		return;
	}

	printf("Temperature is %gC\n", sensor_value_to_double(&temp_value));
}

void accelerometer_read() {
    printf("Reading acceleration data\n");
	current_event = CURRENT;
    event_changed = 0;
}

void magnetometer_read() {
    printf("Reading magnetometer data\n");
	current_event = CURRENT;
    event_changed = 0;
}

void connect_to_bluetooth() {
    printf("Connecting to bluetooth...\n");
	current_event = CURRENT;
    event_changed = 0;

}

void button_pressed(struct device *dev, struct gpio_callback *cb, u32_t pins) {
	/* Filter out spurious presses */
	if (pins & BIT(SW0_GPIO_PIN)) {
		printk("A pressed\n");
		current_event = PREVIOUS;
		if (k_uptime_delta(&a_timestamp) < K_MSEC(100)) {
			printk("Too quick A presses\n");
			return;
		}
	} else {
		current_event = NEXT;
		printk("B pressed\n");
		if (k_uptime_delta(&b_timestamp) < K_MSEC(100)) {
			printk("Too quick B presses\n");
			return;
		}
	}
	event_changed = 1;
}

mstate_t machine[] = {
    { .events = {TEMP, BLTH, HELLO}, .action = hello_world},
    { .events = {ACCEL, HELLO, TEMP}, .action = temperature_read},
    { .events = {MAG, TEMP, ACCEL}, .action = accelerometer_read},
    { .events = {BLTH, ACCEL, MAG}, .action = magnetometer_read},
    { .events = {HELLO, MAG, BLTH}, .action = connect_to_bluetooth}
};

void main(void) {

	//Setup buttons	
	configure_buttons();

	//Setup temperature sensor	
	printf("Thermometer Example! %s\n", CONFIG_ARCH);
	temp_dev = device_get_binding("TEMP_0");
	if (!temp_dev) {
		printf("error: no temp device\n");
		return;
	}
	printf("temp device is %p, name is %s\n", temp_dev, temp_dev->config->name);

	//Setup the display
	disp = mb_display_get();

	//Set the current state
	static state_t current_state = HELLO;

	// while (1) {
    //     if(event_changed) {      
    //         current_state = machine[current_state].events[current_event];            
    //     }
	// 	machine[current_state].action();
	// 	k_sleep(sleep_interval);
	// }
	
	//struct mb_display *disp = mb_display_get();
	
	//Scrolling text ("ECOM042.2017.2")
//	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP, K_MSEC(500), "ECOM042.2017.2");

	SYS_LOG_WRN("Firmware version: v%d.%d.%d",
                        VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

	//CTRL_REG = 0x2A
	i2c_util_dev_init(&acc, ACC_DEV_ADDR, "ACC", ACC_WHO_AM_I_REG,
                                ACC_TEST_VALUE);

	//CTRL_REG = 0x10
	i2c_util_dev_init(&compass, COMPASS_DEV_ADDR, "COMPASS",
                                COMPASS_WHO_AM_I_REG, COMPASS_TEST_VALUE);
	i2c_util_test_connection(&acc);
	u8_t temp = 1;
	// i2c_util_write_bytes(&acc, 0x2A, &temp, sizeof(u8_t));
	i2c_util_write_bytes(&compass, 0x10, &temp, sizeof(u8_t));
		
	u8_t data[2];
	while (1) {
		// //X_LSB = 0x2 | Y_LSB = 0x4 | Z_LSB = 0x6
		// i2c_util_read_bytes(&acc, 0x2, data, sizeof(data));
		// SYS_LOG_DBG("ACC X: %d", (data[1] << 8) | data[0]);

		// i2c_util_read_bytes(&acc, 0x4, data, sizeof(data));
		// SYS_LOG_DBG("ACC Y: %d", (data[1] << 8) | data[0]);

		// i2c_util_read_bytes(&acc, 0x6, data, sizeof(data));
		// SYS_LOG_DBG("ACC Z: %d\n", (data[1] << 8) | data[0]);

		i2c_util_read_bytes(&compass, 0x2, data, sizeof(data));
		SYS_LOG_DBG("COMPASS X: %d", (data[1] << 8) | data[0]);

		i2c_util_read_bytes(&compass, 0x4, data, sizeof(data));
		SYS_LOG_DBG("COMPASS Y: %d", (data[1] << 8) | data[0]);

		i2c_util_read_bytes(&compass, 0x6, data, sizeof(data));
		SYS_LOG_DBG("COMPASS Z: %d\n", (data[1] << 8) | data[0]);
		k_sleep(500);
	}						


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


