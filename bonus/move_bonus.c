#include "../cub3d.h"

void init_key_state(t_key_state *keys)
{
    keys->forward = 0;
    keys->backward = 0;
    keys->left = 0;
    keys->right = 0;
    keys->rotate_left = 0;
    keys->rotate_right = 0;
}

void ft_move(t_cub3d *data, double *newPosX, double *newPosY, t_direction move)
{
    if (move == FORWARD)
    {
        *newPosX += cos(data->player->angle) * MOVE_SPEED;
        *newPosY += sin(data->player->angle) * MOVE_SPEED;
    }
    else
    {
        *newPosX -= cos(data->player->angle) * MOVE_SPEED;
        *newPosY -= sin(data->player->angle) * MOVE_SPEED;
    }
}

void strafing(t_cub3d *data, double *newPosX, double *newPosY, t_direction dir)
{
    if (dir == LEFT)
    {
        *newPosX += sin(data->player->angle) * MOVE_SPEED;
        *newPosY -= cos(data->player->angle) * MOVE_SPEED;
    }
    else
    {
        *newPosX -= sin(data->player->angle) * MOVE_SPEED;
        *newPosY += cos(data->player->angle) * MOVE_SPEED;
    }
}

void check_wall_colision(t_cub3d *data, double newPosX, double newPosY)
{
    if (data->map2->map[(int)floor(newPosY - MARGIN)][(int)floor(newPosX - MARGIN)] != '1' &&
        data->map2->map[(int)floor(newPosY - MARGIN)][(int)floor(newPosX + MARGIN)] != '1' &&
        data->map2->map[(int)floor(newPosY + MARGIN)][(int)floor(newPosX - MARGIN)] != '1')
    {
        data->player->posX = newPosX;
        data->player->posY = newPosY;
        // render(data);
    }
}



void handle_movement(t_cub3d *data)
{
    double newPosX = data->player->posX;
    double newPosY = data->player->posY;

    float sensitivity = 0.5; 

    if (data->keys.forward)
        ft_move(data, &newPosX, &newPosY, FORWARD);
    if (data->keys.backward)
        ft_move(data, &newPosX, &newPosY, BACKWARD);
    if (data->keys.left)
        strafing(data, &newPosX, &newPosY, LEFT);
    if (data->keys.right)
        strafing(data, &newPosX, &newPosY, RIGHT);

    if (data->keys.rotate_left)
        data->player->angle -= ROT_SPEED;
    else if (data->keys.rotate_left == 2)
        data->player->angle -= data->keys.delta_x * sensitivity;

    if (data->keys.rotate_right)
        data->player->angle += ROT_SPEED;
    else if (data->keys.rotate_right == 2)
        data->player->angle += data->keys.delta_x * sensitivity;

    check_wall_colision(data, newPosX, newPosY);

   
    data->keys.rotate_left = 0;
    data->keys.rotate_right = 0;
    data->keys.delta_x = 0;
}


int mouse_move(int x, int y, t_cub3d *data)
{
    static int last_x = -1;
    int window_center_x = WIDTH / 2;

    if (last_x != -1) 
    {
        data->keys.delta_x = (x - window_center_x);

        if (data->keys.delta_x != 0) 
        {
            if (data->keys.delta_x > 0)
                data->keys.rotate_right = 2; 
            else if (data->keys.delta_x < 0)
                data->keys.rotate_left = 2;  
        }

       
        if (x != window_center_x)
            mlx_mouse_move(data->mlx, data->win, window_center_x, y);
    }

    last_x = x;

    return (0);
}


int key_press(int key, t_cub3d *data)
{
    if (key == ESC_KEY)
        exit(0);
    else if (key == W_KEY)
        data->keys.forward = 1;
    else if (key == S_KEY)
        data->keys.backward = 1;
    else if (key == A_KEY)
        data->keys.left = 1;
    else if (key == D_KEY)
        data->keys.right = 1;
    else if (key == LEFT_KEY)
        data->keys.rotate_left = 1;
    else if (key == RIGHT_KEY)
        data->keys.rotate_right = 1;
    return (0);
}

int key_release(int key, t_cub3d *data)
{
    if (key == W_KEY)
        data->keys.forward = 0;
    else if (key == S_KEY)
        data->keys.backward = 0;
    else if (key == A_KEY)
        data->keys.left = 0;
    else if (key == D_KEY)
        data->keys.right = 0;
    else if (key == LEFT_KEY)
        data->keys.rotate_left = 0;
    else if (key == RIGHT_KEY)
        data->keys.rotate_right = 0;
    return (0);
}
