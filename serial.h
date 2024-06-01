#include "io.h"

#define SERIAL_COM1_BASE 0x3F8 /* COM1 base port */
#define SERIAL_COM2_BASE 0x2F8 /* COM2 base port */

/** serial_is_transmit_fifo_empty:
 * Checks whether the transmit FIFO queue is empty or not for the given COM
 * port.
 *
 * @param com The COM port
 * @return 0 if the transmit FIFO queue is not empty
 *         1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);

void serial_configure_line(unsigned short com);

/** serial_configure_baud_rate:
 * Sets the speed of the data being sent. The default speed of a serial
 * port is 115200 bit/s. The argument is a divisor of that number, hence
 * the resulting speed becomes (115200 / divisor) bit/s.
 *
 * @param com The COM port to configure
 * @param divisor The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

int serial_write(unsigned short com, char *buf, unsigned int len);
