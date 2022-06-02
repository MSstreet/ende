#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int         asymmetric_encrypt_sample           ();
int         asymmetric_sign_sample              ();
int         auth_crypto_sample                  ();
int         drbg_sample                         ();
int         hash_sample                         ();
int         keyagreement_sample                 ();
int         mac_sample                          ();
int         symmetric_sample                    ();
int         rsa_sample();
void        hexdump                             (const char *title, void *mem, unsigned int len);
void		printf_red							(const char *const Format, ...);
void		print_result						(const char * p_function, int p_result);


const char *	crypto_getStatusString			(int p_status);;
