#include "core/cli.h"
#include "core/uprint.h"

#include <string.h>
#include <stddef.h>

#define CLI_BUFFER_SIZE         64

static Comm_Interface_t *cli_comm = NULL;
static command_t *cli_table = NULL;
static uint32_t cli_table_len = 0;

static char cli_buffer[CLI_BUFFER_SIZE];
static uint32_t cli_idx = 0;

void cli_setup(Comm_Interface_t *comm, command_t *table, uint32_t Len)
{
    if(table != NULL)
    {
        cli_comm = comm;
        cli_table = table;
        cli_table_len = Len;
    }
}

void cli_dispatch(char *buffer)
{
    if(cli_table == NULL) return;

    for (int i = 0; i < cli_table_len; i++) // Match command
    {
        if (strcmp(cli_buffer, cli_table[i].name) == 0)
        {
            cli_table[i].execute();
            break;
        }
    }
}

void cli_update(void)
{
    if(cli_comm == NULL) return;

    while(cli_comm->data_available())
    {
        uint8_t ch;
        cli_comm->receive(&ch, 1);
        cli_comm->send(&ch, 1);

        if(ch == '\r')
        {
            ch = '\n';
            cli_comm->send(&ch, 1);
        }

        if(ch == '\n')
        {
             cli_buffer[cli_idx] = '\0'; // command end
             cli_idx = 0;
             cli_dispatch(cli_buffer); // dispatch
        }else if(cli_idx < CLI_BUFFER_SIZE)
        {
            cli_buffer[cli_idx++] = (char)ch;
        }
    }
}

void cli_help(void)
{
    if(cli_table == NULL) return;

    uprint("===================================\r\n");
    for (int i = 0; i < cli_table_len; i++)
    {
    	uprint("%s: %s\r\n", cli_table[i].name, cli_table[i].help);
    }
    uprint("===================================\r\n");
}