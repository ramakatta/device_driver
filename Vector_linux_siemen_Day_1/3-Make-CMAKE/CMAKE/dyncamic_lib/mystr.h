int mystrlen(char*);
void mystrcpy(char*);
int mystrcmp();
void mystrrev(char*);
static int xl;
#ifdef MAIN
#define global extern
#else
#define global 
#endif
