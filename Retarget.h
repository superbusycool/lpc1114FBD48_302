#ifndef __RETARGET_H__
#define __RETARGET_H__

#include <stdio.h>

int fputc(int c, FILE *f);
int fgetc(FILE *f);
int ferror(FILE *f);
void _ttywrch(int c);
void _sys_exit(int return_code);

#endif //__RETARGET_H__
