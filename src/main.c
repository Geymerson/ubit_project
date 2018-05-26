#include "buttons.h"
#include "version.h"
#include "i2c_util.h"
#include "ubit_devices.h"

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
static u8_t event_changed = 0;
static s64_t a_timestamp;
static s64_t b_timestamp;

//This function will be executed everytime a button is pressed
void button_pressed(struct device *dev, struct gpio_callback *cb, u32_t pins) {
	/* Filter out spurious presses */
	if (pins & BIT(SW0_GPIO_PIN)) {
		printk("\nChanging to previous state.\nPlease, wait a while...\n\n");
		current_event = PREVIOUS;
		if (k_uptime_delta(&a_timestamp) < K_MSEC(100)) {
			printk("Too quick A presses\n");
			return;
		}
	} else {
		current_event = NEXT;
		printk("\nChanging to next state.\nPlease, wait a while...\n\n");
		if (k_uptime_delta(&b_timestamp) < K_MSEC(100)) {
			printk("Too quick B presses\n");
			return;
		}
	}
	event_changed = 1;
}

mstate_t machine[] = {
	{ .events = {TEMP, BLTH, HELLO}, .action = print_to_display},    
	{ .events = {ACCEL, HELLO, TEMP}, .action = read_temperature},    
    { .events = {MAG, TEMP, ACCEL}, .action = update_accel_display},	
    { .events = {BLTH, ACCEL, MAG}, .action = print_compass_direction},	
    { .events = {HELLO, MAG, BLTH}, .action = connect_to_bluetooth}
};

void main(void) {
	printk("ECOM042.2017.2\n");
	printk("EMBBEDED SYSTEMS\n");
	printk("UBIT_PROJECT\n");
	SYS_LOG_WRN("Firmware version: v%d.%d.%d\n",
                        VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

	//Initiate and configure devices
	init_display();	
	init_accelerometer_sensor();
	init_magnetometer_sensor();	
	configure_buttons();

	//Set the current machine state
	static state_t current_state = HELLO;

	while (1) {
		if(event_changed) {      
            current_state = machine[current_state].events[current_event];           
        }
		machine[current_state].action();
		current_event = CURRENT;
    	event_changed = 0;		
		k_sleep(get_sleep_time());	
	}
}