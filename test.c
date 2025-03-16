int main(int ac, char **av) {
    t_game game;
    t_data img;
    int i;
    
    if (ac != 2)
        ft_error_message("Error input", 1);
    
    ft_memset(&game, 0, sizeof(game));
    game.map = parse_map(av[1], &game);
    
    if (game.map != NULL) {
        if(!(check_map(game.map))) {
            i = 0;
            while(game.map[i])
                free(game.map[i++]);
            free(game.map);
            return(1);
        }
    }
    
    game.mlx = mlx_init();
    if (!game.mlx)
        exit(EXIT_FAILURE);
    
    // Use consistent dimensions for window and image
    int tile_size = 64; // Adjust based on your sprite size
    game.mlx_window = mlx_new_window(game.mlx, game.win_x * tile_size, 
                                    game.win_y * tile_size, "Man7waaa");
    if (!game.mlx_window) {
        ERROR("Error : Window creation failed");
        free(game.mlx);
        return (1);
    }
    
    // Initialize the image
    img.img_window = mlx_new_image(game.mlx, game.win_x * tile_size, 
                                    game.win_y * tile_size);
    if (!img.img_window) {
        ERROR("Error : Image creation failed");
        mlx_destroy_window(game.mlx, game.mlx_window);
        free(game.mlx);
        return (1);
    }
    
    // Get image data address
    img.addr = mlx_get_data_addr(img.img_window, &img.bits_per_pixel, 
                                &img.line_length, &img.endian);
    
    // Store a reference to the image in the game struct
    game.img = img.img_window;
    
    // Load textures/sprites
    if (!load_textures(&game)) {
        // Clean up and exit if texture loading fails
        mlx_destroy_image(game.mlx, img.img_window);
        mlx_destroy_window(game.mlx, game.mlx_window);
        free(game.mlx);
        return (1);
    }
    
    // Render the initial map
    render_map(&game);
    
    // Set up event hooks
    mlx_key_hook(game.mlx_window, key_handler, &game);
    mlx_hook(game.mlx_window, 17, 0, close_window, &game); // For window close button
    
    mlx_loop(game.mlx);
    return (0);
}
