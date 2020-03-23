#if _DEBUG
#define ASSERT(Expression) if(!(Expression)) {*(int *)0 = 0;}
#else
#define ASSERT(Expression)
#endif