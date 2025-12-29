#include "parse.h"
#include "error.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    t_game_data game_data;
    t_error_code error_code;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map.cub>\n", argv[0]);
        return EXIT_FAILURE;
    }
    memset(&game_data, 0, sizeof(t_game_data));
    if (parse(argv[1], &game_data) != 0)
    {
        error_code = get_error_status();
        if (error_code != 0)
            error_exit_simple(error_code);
        else
            write(2, "Error\nFailed to parse map\n", 26);
        free_config_data(&game_data.config);
        if (game_data.map.map)
            free_map((void **)game_data.map.map);
        return EXIT_FAILURE;
    }
    if (game_data.map.map)
        free_map((void **)game_data.map.map);
    free_config_data(&game_data.config);
    return EXIT_SUCCESS;
}
