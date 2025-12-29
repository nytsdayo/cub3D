#include "parse.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    t_game_data game_data;

    if (argc != 2)
        return EXIT_FAILURE;
    memset(&game_data, 0, sizeof(t_game_data));
    if (parse(argv[1], &game_data) != 0)
    {
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
