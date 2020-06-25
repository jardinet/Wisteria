/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 17:25:32 by niboute           #+#    #+#             */
/*   Updated: 2020/06/25 11:56:29 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define FLOOR_COLOR 0x00C8AD7F
# define SKY_COLOR 0x000061F2
# define MIN_MAP 5
# define MAX_MAP 1000
# define SPACE ' '
# define TRUE 1
# define FALSE 0
# define NB_TEXT_MAX 255
# define FULLBLOCK 15
# define WINWID 960
# define WINHEI 680
# define CPU_THREADS 4
# define TEXTURE_SIZE 64
# define M_PI 3.14159265358979323846
# define MAX_REDIRECTS 50
# define MAX_RAY_DIST 1000
# define MOVESPEED 0.10

# include "../inc/bitmap.h"
# include "../SDL2/include/SDL2/SDL.h"
# include <unistd.h>
# include <pthread.h>
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct		s_cam
{
	double			x;
	double			y;
	double			z;
	double			sdirx;
	double			sdiry;
	double			splanex;
	double			splaney;
	float			angle;
	double			dirx;
	double			diry;
	double			fov;
}					t_cam;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			dirx;
	double			diry;
}					t_vector;

typedef struct		s_block
{
	unsigned int	iswall;
	unsigned int	isredirect;
	int				nextx;
	int				nexty;
	unsigned int	texid;
	unsigned int	rot;
}					t_block;

typedef struct		s_map
{
	t_block			**map;
	int				hei;
	int				wid;
}					t_map;

typedef struct		s_sdl_data
{
	char			*desc;
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	SDL_Texture		*maintext;
	int				*img;
	SDL_Rect		mainrect;
}					t_sdl_data;

typedef struct		s_raydata
{
	t_block			**map;
	short			screenx;
	double			x;
	double			y;
	double			dirx;
	double			diry;
	double			deltax;
	double			deltay;
	double			block_dist_x;
	double			block_dist_y;
	double			dist;
	char			stepx;
	char			stepy;
	int				posx;
	int				posy;
	char			side;
	short			count;
	double			wallx;
	unsigned int	redir_count;
}					t_raydata;

typedef struct		s_events
{
	char			dir;
	char			rot_dir;
}					t_events;

typedef struct		s_texture
{
	short			width;
	short			height;
	int				**text;
}					t_texture;

typedef struct		s_texlist
{
	t_texture		**textures;
	int				nb_text;
}					t_texlist;

typedef struct		s_wolf
{
	t_events		events;
	t_cam			eye;
	t_vector		plane;
	t_sdl_data		win;
	t_map			map;
	t_texlist		text;
}					t_wolf;

typedef struct		s_thread
{
	int				x;
	pthread_t		thread;
	t_wolf			*data;
	t_raydata		ray;
}					t_thread;

/*
** dda_algo.c
*/
void				dda_alg(t_wolf *data, t_raydata *ray);
void				dda_ray_step(t_raydata *ray);
int					is_out_of_bounds(t_raydata *ray, t_map *map);
void				setup_calculations(t_raydata *ray);
void				wall_hit(t_wolf *data, t_raydata *ray, t_block *block);

/*
** display.c
*/
void				copy_floor_roof(t_sdl_data *win);
void				draw_line(t_wolf *data, t_raydata *ray, t_block *block);
void				rotate_cam(t_cam *eye, t_vector *plane);

/*
** events.c
*/
void				handle_events(SDL_Event *event, t_wolf *data);
void				keyboard_events(t_wolf *data);
int					move(t_cam *eye, t_block **map, t_wolf *data);
void				setup_move(double *move, unsigned char *side, t_cam *eye,
						t_block **map);
/*
** init.c
*/
int					init_camera(t_cam *eye, t_vector *plane);

/*
** init_sdl.c
*/
int					create_window(t_sdl_data *win);
int					init_sdl(t_sdl_data *win);

/*
** loadbmp.c
*/
void				*check_data(t_bmp_if *inf, t_texture *text);
void				*destroy_texture_str(int **texture, char *str,
			t_bmp_if *inf);
int					**get_texture(int fd, int **texture, t_bmp_if *inf);
int					**get_texture_p2(int fd, int **texture, t_bmp_if *inf,
			char *buff);
void				*read_check_data(int fd, t_bmp_hd *head, t_bmp_if *inf,
			t_texture *text);

/*
** loop.c
*/
void				init_threads(t_thread *threads, t_wolf *data);
void				loop(t_wolf *data);
void				*raycast(void *ptr);
void				raycast_threads(t_thread *threads);

/*
** parsing.c
*/
int					check_player_pos(t_cam *eye, t_map *map);
int					get_dimensions(char *line, int *a, int *b);
int					get_dimensions_double(char *line, double *a, double *b,
			t_map *map);
int					parsing(char *file, t_wolf *data);

/*
** parsing_map.c
*/
int					check_block(t_block *block, t_map *map, int y, int x);
int					check_map_line(t_map *map, int y, char *line, int nbtext);
int					get_map(int fd, t_map *map, int nbtext);

/*
** parsing_portals.c
*/
int					assign_portal_values(char *line, int *i, t_map *map);
int					check_portal(t_block *block, t_map *map, int y, int x);
int					get_portals(int fd, t_map *map);
int					parsing_portals(int fd, t_map *map, int nbpor);
int					skip_to_number(char *line, int *i, int endl);

/*
** player_controls.c
*/
int					dda_get_side(t_raydata *ray, t_map *map);
int					get_move_wallx(t_raydata *ray);
int					move_get_side (t_cam *eye, double *move,
			t_map *map, t_raydata *ray);
int					redirect_player(t_wolf *data, t_raydata *ray,
			t_block *block, double *move);
int					redirect_player_p2(t_wolf *data, t_raydata *ray,
					t_cam *eye, t_block *block);

/*
** raycast_portals.c
*/
void				redirect_ray(t_raydata *ray, t_block *block);
void				redirect_ray_horizontal(t_raydata *ray, t_block *block);

/*
** textures.c
*/
t_texture			*bmp_to_texture(char *name);
t_texture			*bmp_to_texture_p2(t_bmp_if *inf, int fd,
			t_texture *texture);
int					get_paths_text(int fd, t_texlist *text);
int					get_textures(int fd, t_texlist *text);

/*
** wipeout.c
*/
void				free_map(t_map *map);
void				free_textures(t_texlist *text);
void				wipeout(t_wolf *data, int ret);

#endif
