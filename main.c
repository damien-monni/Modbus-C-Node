#include <stdio.h>
#include <modbus.h>

void main(){

    modbus_t *mb;
    uint16_t tab_reg[32];
    int result = 0;

    printf("\n\nTry to connect...\n");

    mb = modbus_new_tcp("127.0.0.1", 8085);
    result = modbus_connect(mb);

    printf("Connected : %d\n", result);

    /* Read 10 register from the address 0 */
    getchar();
    result = modbus_read_registers(mb, 0, 10, tab_reg);

    printf("Read : %d\n\n", tab_reg[4]);

    while(1);

    modbus_close(mb);
    modbus_free(mb);

}
