#include <stdio.h>
#include <stdlib.h>
#include "rply.h"

static int vertex_cb(p_ply_argument argument) {
    long eol;
    ply_get_argument_user_data(argument, NULL, &eol);
    printf("%g", ply_get_argument_value(argument));
    if (eol) printf("\n");
    else printf(" ");
    return 1;
}

static int face_cb(p_ply_argument argument) {
    long length, value_index;
    ply_get_argument_property(argument, NULL, &length, &value_index);
    if (value_index == -1) {
        return 1;
    }
    if (value_index != length - 1) {
        printf("%g ", ply_get_argument_value(argument));
    } else {
        printf("%g\n", ply_get_argument_value(argument));
    }
    return 1;
}

int main(int argc, char *argv[]) {
    long nvertices, ntriangles;
    p_ply ply;
    if(argc > 1) {
        ply = ply_open(argv[1], NULL, 0, NULL);
    } else {
        printf("error: missing ply file name\n");
        return EXIT_FAILURE;
    }
    if (!ply) return EXIT_FAILURE;
    if (!ply_read_header(ply)) return EXIT_FAILURE;
    nvertices = ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, 0);
    ply_set_read_cb(ply, "vertex", "y", vertex_cb, NULL, 0);
    ply_set_read_cb(ply, "vertex", "z", vertex_cb, NULL, 1);
    ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, NULL, 0);
    printf("%ld\n%ld\n", nvertices, ntriangles);
    if (!ply_read(ply)) return EXIT_FAILURE;
    ply_close(ply);
    return EXIT_SUCCESS;
}

