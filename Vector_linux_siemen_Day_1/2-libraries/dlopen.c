#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void) {
    void *handle;
    void (*hello_func)(void);
    char *error;

    // Load the shared library
    handle = dlopen("./libhello.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    // Clear any existing errors
    dlerror();

    // Load the symbol (function)
    *(void **)(&hello_func) = dlsym(handle, "hello");

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "Error loading symbol: %s\n", error);
        dlclose(handle);
        exit(EXIT_FAILURE);
    }

    // Call the function
    hello_func();

    // Close the library
    dlclose(handle);
    return 0;
}

