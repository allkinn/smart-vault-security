#ifndef KEYPAD_HANDLER_H
#define KEYPAD_HANDLER_H

void initKeypad();
bool checkPassword(unsigned long timeout);
char getSingleKey();

#endif