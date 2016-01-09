#ifndef SGREP_DATA_H
#define SGREP_DATA_H

typedef struct sgrep_data_ {
  int   case_sensitive; /* 0 means ignore case, 1 means use case */
  char *reg_exp;
  int matches;
  int mode;
  FILE *in; /* which file to search in (defaults to stdin) */
} sgrep_data;


#endif /* SGREP_DATA_H */
