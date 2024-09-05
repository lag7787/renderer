#include "glad/glad.h"
#include <signal.h>

#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define glCall(x) glClearError();\
    x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__));


void glClearError();
const char* glTranslateError(GLenum error);
bool glLogCall(const char* function, const char* file, int line);