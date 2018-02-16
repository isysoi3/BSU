#pragma once

/* 
 * SPLPv1.c
 * The file is part of practical task for System programming course. 
 * This file contains definitions of the data structures and forward
 * declaration of handle_message() function
 */


static  enum  Conditional current_conditional = 1;
char * current_text;

enum test_status 
{ 
    MESSAGE_INVALID, 
    MESSAGE_VALID 
};


enum Direction 
{ 
    A_TO_B, 
    B_TO_A 
};

enum Conditional
{
	INIT = 1,
	CONNECTING,
	CONNECTED,
	WAITING_VER,
	WAITING_DATA,
	WAITING_B64_DATA,
	DISCONNECTING
};

struct Message /* message */
{
	enum Direction	direction;        
	char			*text_message;
};


extern enum test_status validate_message( struct Message* pMessage ); 
