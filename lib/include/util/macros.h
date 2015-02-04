#ifndef MACROS_H
#define MACROS_H

#define ASSERT(i, ...)                           \
if(i) { \
fprintf(stderr, "\033[31m[ERROR]\033[0m %s:%d, %s -> %s (%d)\n\033[31m[ERROR]\033[0m ", \
 __FILE__, __LINE__, __func__, strerror(errno), errno); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "\n"); \
exit(i); \
}

#define WARN(...) \
{ \
fprintf(stderr, "\033[33m[WARN]\033[0m  %s:%d, %s -> %s (%d)\n\033[33m[WARN]\033[0m ", \
 __FILE__, __LINE__, __func__, strerror(errno), errno); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "\n"); \
}

#define INFO(...) \
{ \
fprintf(stderr, "\033[36m[INFO]\033[0m "); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "\n"); \
}

#ifdef IS_DEBUG

#define DEBUG(...) \
{ \
fprintf(stderr, "\033[32m[DEBUG]\033[0m "); \
fprintf(stderr, __VA_ARGS__); \
fprintf(stderr, "\n"); \
}

#else

#define DEBUG(...) \
{}

#endif // IS_DEBUG

#endif // MACROS_H
