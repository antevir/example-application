
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/drivers/uart.h>

static void iface_uart_async_callback(const struct device *dev,
				      struct uart_event *evt,
				      void *user_data)
{
}


int main(void)
{
	const struct device *dev = NULL;
	dev = device_get_binding("uart0");
	if (dev == NULL) {
		printf("NULL!\n");
	}
	if (!device_is_ready(dev)) {
		printf("UART %s is not ready", dev->name);
	}

	uart_callback_set(dev, iface_uart_async_callback, NULL);

	for (int i = 0; i < 100; i++) {
		k_sleep(K_MSEC(1000));
		int ret = uart_tx(dev, "testing\n", 8, SYS_FOREVER_MS);
		printf("muu %d\n", ret);
	}
	printf("Hello World! %s\n", CONFIG_BOARD);
	return 0;
}
