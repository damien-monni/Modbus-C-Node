/*
#include <stdio.h>
#include <modbus.h>
#include <unistd.h>
#include <errno.h>

int main(){

    int i;
    int rc;
    int s = -1;
    int header_length;
    uint8_t *query;
    modbus_t *mb;
    modbus_mapping_t *mb_mapping;
    uint16_t tab_reg[32];

    int result = 0;

    //Modbus context
    mb = modbus_new_tcp("127.0.0.1", 8085);
    header_length = modbus_get_header_length(mb);

    printf("Context ok\n");

    //Create memory
    mb_mapping = modbus_mapping_new(0, 0, 10, 0);
    for (i=0; i < 10; i++) {
        mb_mapping->tab_registers[i] = 25;
    }

    printf("Memory ok\n");

    if (mb_mapping == NULL) {
        printf("Failed to allocate the mapping.");
        modbus_free(mb);
        return -1;
    }

    printf("Mapping ok\n");

    s = modbus_tcp_listen(mb, 1);

    printf("Listening on 127.0.0.1:1502...\n");
    modbus_tcp_accept(mb, &s);

    printf("Accepted\n");

    for (;;) {

        do {
            rc = modbus_receive(mb, query);
            // Filtered queries return 0
        } while (rc == 0);

        printf("%d\n", errno);
        break;

    }

    modbus_close(mb);
    modbus_free(mb);

    return 0;

}
*/

/*
 * Copyright © 2008-2014 Stéphane Raimbault <stephane.raimbault@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>
#include <errno.h>

#include <modbus.h>

int main(void)
{
    int s = -1;
    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;

    ctx = modbus_new_tcp("127.0.0.1", 8085);
    /* modbus_set_debug(ctx, TRUE); */

    mb_mapping = modbus_mapping_new(500, 500, 500, 500);
    if (mb_mapping == NULL) {
        fprintf(stderr, "Failed to allocate the mapping: %s\n",
                modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    int i;
    for(i = 0 ; i < 10 ; i++){
        mb_mapping->tab_registers[i] = i+20;
    }

    s = modbus_tcp_listen(ctx, 1);
    modbus_tcp_accept(ctx, &s);

    for (;;) {
        uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
        int rc;

        rc = modbus_receive(ctx, query);
        if (rc > 0) {
            /* rc is the query size */
            modbus_reply(ctx, query, rc, mb_mapping);
        } else if (rc == -1) {
            /* Connection closed by the client or error */
            break;
        }
    }

    printf("Quit the loop: %s\n", modbus_strerror(errno));

    if (s != -1) {
        close(s);
    }
    modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
