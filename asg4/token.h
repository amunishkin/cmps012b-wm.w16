// $Id: token.h,v 1.2 2013-02-28 14:13:14-08 - - $
// Authors: Alexey Munishkin (amunishk)
//          Diem Phuong Chau (dhchau)

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdbool.h>

#define NUMBER 256

typedef struct token token;

token *new_token (FILE*);

void free_token (token *);

int scan_token (token *);

char *peek_token (token *);

bool is_token (token *);

#endif

