#include <board.h>
#include <gpio.h>

void configure_buttons(void);

void button_pressed(struct device *dev, struct gpio_callback *cb, u32_t pins);
