/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 00:31:06 by aes-sarg          #+#    #+#             */
/*   Updated: 2024/09/22 22:16:11 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(void *cub)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)cub;
	handle_movement(cub3d);
	cast_all_rays(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->image->img, 0, 0);
	return (0);
}

void	init(t_cub3d *cub3d)
{
	cub3d->player = malloc(sizeof(t_player));
	cub3d->ray = malloc(sizeof(t_ray));
	cub3d->image = malloc(sizeof(t_image));
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "cub3d");
	cub3d->image->img = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->image->img)
		ft_exit(cub3d);
	cub3d->image->addr = mlx_get_data_addr(cub3d->image->img,
			&cub3d->image->bits_per_pixel, &cub3d->image->line_length,
			&cub3d->image->endian);
	cub3d->fov = deg_to_rad(60.0);
}

void	load_images(t_cub3d *cub3d)
{
	int		i;
	char	*textures[4];

	i = 0;
	textures[0] = cub3d->textures->north;
	textures[1] = cub3d->textures->south;
	textures[2] = cub3d->textures->east;
	textures[3] = cub3d->textures->west;
	while (i < 4)
	{
		cub3d->wall_t[i].img = mlx_xpm_file_to_image(cub3d->mlx, textures[i],
				&cub3d->wall_t[i].width, &cub3d->wall_t[i].height);
		if (!cub3d->wall_t[i].img)
			ft_exit(cub3d);
		cub3d->wall_t[i].addr = mlx_get_data_addr(cub3d->wall_t[i].img,
				&cub3d->wall_t[i].bits_per_pixel, &cub3d->wall_t[i].line_length,
				&cub3d->wall_t[i].endian);
		if (!cub3d->wall_t[i].addr)
			ft_exit(cub3d);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_cub3d	cub3d;

	if (ac == 2)
	{
		cub3d.bonus = 0;
		if (!parse_cub3d(&cub3d, av[1], cub3d.bonus))
		{
			write(2, "error\n", 6);
			exit(1);
		}
		init(&cub3d);
		load_images(&cub3d);
		get_player_pos(&cub3d);
		init_key_state(&cub3d.keys);
		mlx_hook(cub3d.win, 2, 1L << 0, key_press, &cub3d);
		mlx_hook(cub3d.win, 3, 1L << 1, key_release, &cub3d);
		mlx_hook(cub3d.win, 17, 1L << 17, &ft_exit, NULL);
		mlx_loop_hook(cub3d.mlx, render, &cub3d);
		mlx_loop(cub3d.mlx);
	}
	else
		write(2, "USAGE ./cube3d [map]\n", 22);
	return (0);
}
