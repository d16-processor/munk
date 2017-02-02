void assert_asm(int cond, const char* msg, const char *file, int line);
#ifdef NDEBUG
#define assert(x)
#else
#define assert(EX) assert_asm(EX,#EX, __FILE__, __LINE__)
#endif
