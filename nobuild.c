#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"

#define CFLAGS "-Wall", "-Wextra", "-pedantic", "-g"

void build_src(const char *file) {
    INFO("Building %s...", file);
    Cstr src_path = PATH("src", file);
    Cstr build_path = PATH("build", file);
    CMD("cc", CFLAGS, "-o", NOEXT(build_path), src_path);
}

void build_src_files(void) {
    FOREACH_FILE_IN_DIR(file, "src", {
        if (ENDS_WITH(file, ".c")) {
            build_src(file);
        }
    });
}

int main(int argc, char **argv) {
    GO_REBUILD_URSELF(argc, argv);

    MKDIRS("build");
    build_src_files();
    return 0;
}
