#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <uv.h>

void exit_cb(uv_process_t *req, int64_t exit_status, int term_signal) {
    fprintf(stderr, "Process exited with status %" PRId64 ", signal %d\n", exit_status, term_signal);
    uv_close((uv_handle_t*) req, NULL);
}

int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    char* args[4];
    args[0] = "/bin/bash";
    args[1] = "-c";
    args[2] = "cat - &";
    args[3] = NULL;

    uv_stdio_container_t child_stdio[3];
    child_stdio[0].flags = UV_INHERIT_FD;
    child_stdio[0].data.fd = 0;
    child_stdio[1].flags = UV_INHERIT_FD;
    child_stdio[1].data.fd = 1;
    child_stdio[2].flags = UV_INHERIT_FD;
    child_stdio[2].data.fd = 2;

    uv_process_options_t options = {0};
    options.exit_cb = exit_cb;
    options.file = args[0];
    options.args = args;
    options.stdio_count = 3;
    options.stdio = child_stdio;

    int r;
    uv_process_t child_req = {0};
    if ((r = uv_spawn(loop, &child_req, &options))) {
        fprintf(stderr, "%s\n", uv_strerror(r));
        return 1;
    } else {
        fprintf(stderr, "Launched process with ID %d\n", child_req.pid);
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}
