#include <zephyr.h>
#include <misc/printk.h>
#include <board.h>
#include <gpio.h>
#include <device.h>
//#include <display/mb_display.h>
//#include <sensor.h>
//#include <stdio.h>

void configure_buttons(void);

void button_pressed(struct device *dev, struct gpio_callback *cb, u32_t pins);
