// This project showcases blinking the built-in  LED using the Zephyr Project RTOS. 
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

/* 1000 milliseconds = 1 second */
#define SLEEP_TIME_MS   1000

/* Pull the led0 definition out of the Devicetree overlay */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{
        int ret;
        bool led_state = true;

        printk("Zephyr Blinky Application Started!\n");

        if (!gpio_is_ready_dt(&led)) {
                printk("Error: GPIO device %s is not ready\n", led.port->name);
                return -1;
        }

        ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
        if (ret < 0) {
                printk("Error: Failed to configure GPIO pin (error %d)\n", ret);
                return -1;
        }

        printk("Successfully configured GPIO 2. Starting blink loop...\n");

        while (1) {
                ret = gpio_pin_toggle_dt(&led);
                if (ret < 0) {
                        printk("Error: Failed to toggle GPIO pin (error %d)\n", ret);
                        return -1;
                }

                led_state = !led_state;
                printk("LED State: %s\n", led_state ? "ON" : "OFF");

                k_msleep(SLEEP_TIME_MS);
        }

        return 0;
}



