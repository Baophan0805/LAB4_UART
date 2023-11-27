/*
 * command_parser.c
 *
 *  Created on: Nov 23, 2023
 *      Author: ASUS
 */
#include "command_parser.h"

void command_parser_fsm() {
	switch(status_parser) {
	case INIT_STR:
		// If string starts with '!', status = WAIT_END, begins reading the command
		if (temp == '!') {
			status_parser = WAIT_END;
			command_index = 0;
		}
		break;

	case WAIT_END:
		// If string ends with character '#', status = INIT_STR, save the command
		// go to uart_communication_fsm to process command, flag = 1
		if (temp == '#') {
			status_parser = INIT_STR;
			command[command_index] = '\0';
			command_flag = 1;
		}
		else {
			// If got '!', reset command_index, reread the command
			if (temp == '!') command_index = 0;
			else {
				command[command_index++] = temp;
				if (command_index == MAX_BUFFER_SIZE) command_index = 0;
			}
		}
		break;
	default:
		break;
	}
}

