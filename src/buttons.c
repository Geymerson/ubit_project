#include "buttons.h"

static s64_t a_timestamp;
static s64_t b_timestamp;

void button_pressed(struct device *dev, struct gpio_callback *cb, u32_t pins) {
	/* Filter out spurious presses */
	if (pins & BIT(SW0_GPIO_PIN)) {
		printk("A pressed\n");
		if (k_uptime_delta(&a_timestamp) < K_MSEC(100)) {
			printk("Too quick A presses\n");
			return;
		}
	} else {
		printk("B pressed\n");
		if (k_uptime_delta(&b_timestamp) < K_MSEC(100)) {
			printk("Too quick B presses\n");
			return;
		}
	}
}

void configure_buttons(void) {
	static struct gpio_callback button_cb;
	struct device *gpio;

	gpio = device_get_binding(SW0_GPIO_NAME);

	gpio_pin_configure(gpio, SW0_GPIO_PIN,
			   (GPIO_DIR_IN | GPIO_INT | GPIO_INT_EDGE |
			    GPIO_INT_ACTIVE_LOW));
	gpio_pin_configure(gpio, SW1_GPIO_PIN,
			   (GPIO_DIR_IN | GPIO_INT | GPIO_INT_EDGE |
			    GPIO_INT_ACTIVE_LOW));
	gpio_init_callback(&button_cb, button_pressed,
			   BIT(SW0_GPIO_PIN) | BIT(SW1_GPIO_PIN));
	gpio_add_callback(gpio, &button_cb);

	gpio_pin_enable_callback(gpio, SW0_GPIO_PIN);
	gpio_pin_enable_callback(gpio, SW1_GPIO_PIN);
}
