#include <PR/os.h>

extern void syMainLoop(void);
extern void port_log_init(const char* path);

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    port_log_init(NULL);
    syMainLoop();

    /* Threaded runtime continues after syMainLoop seeds thread graph. */
    while (1) {
        /* spin */
    }

    return 0;
}
