/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:30:59 by esormune          #+#    #+#             */
/*   Updated: 2022/02/23 16:36:46 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <stdlib.h> // malloc
# include <math.h> // math
# include <fcntl.h> // open/close
# include <time.h> // time
//SDL
# include "SDL.h"
//libft
# include "libft.h"
//defs
# include "rt_defs.h"
# include "pthread.h"

typedef struct s_uv
{
	double	u;
	double	v;
}			t_uv;

typedef struct s_m3
{
	double	m[3][3];
}			t_m3;

typedef struct s_flags
{
	int	cam;
	int	objs;
	int	lights;
	int	images;
	int	scene;
}		t_flags;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	sqroot;
}			t_quadratic;

typedef struct s_bmp
{
	unsigned char	*i_head;
	unsigned char	*f_head;
	uint8_t			padding_size;
}					t_bmp;

typedef struct s_8colour
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}			t_8colour;

typedef struct s_buffer
{
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_buffer;

typedef struct s_ray
{
	t_vec	start;
	t_vec	end;
	t_vec	dir;
}			t_ray;

typedef struct s_channels
{
	double		*r;
	double		*g;
	double		*b;
	uint32_t	w;
	uint32_t	h;
}				t_channels;

typedef struct s_uchar_rgb
{
	unsigned char	*r;
	unsigned char	*g;
	unsigned char	*b;
}					t_uchar_rgb;

typedef struct s_point
{
	t_vec		poi;
	t_vec		normal;
	t_colour	colour;
	double		intensity;
	t_uv		uv;
}				t_point;

typedef struct s_image
{
	SDL_Surface		*surface;
	SDL_PixelFormat	*format;
	uint32_t		*pixels;
	uint8_t			bpp;
	uint32_t		w;
	uint32_t		h;
	uint32_t		size;
	int				pitch;
	uint32_t		linesize;
	t_bool			loaded;
	t_m3			tform;
	t_uv			trans;
	double			rot;
	t_uv			scale;
	t_bool			incorrect_bpp;
}					t_image;

typedef struct s_texture
{
	int		type;
	t_m3	tform;
	t_uv	trans;
	double	rot;
	t_uv	scale;
}			t_texture;

typedef struct s_obj
{
	t_colour	colour;
	t_matrix	tform;
	t_matrix	inv;
	t_vec		trans;
	t_vec		rot;
	t_vec		scale;
	t_m3		ltform;
	t_texture	txt;
	t_bool		is_neg;
	int			has_image;
	int			shape;
	double		reflectivity;
	double		shine;
	double		transparency;
	double		ior;
	t_bool		((*get_t)(t_ray, struct s_obj, t_point *));
}				t_obj;

typedef struct s_light
{
	t_vec		pos;
	t_colour	colour;
	double		intensity;
}				t_light;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	look_at;
	t_vec	up;
	t_vec	u;
	t_vec	v;
	t_vec	centre;
	t_vec	alignment;
	double	length;
	double	horizon;
	double	aspect_ratio;
}				t_camera;

typedef struct s_scene
{
	int			objcount;
	t_obj		*objs;
	int			at_obj;
	int			lcount;
	t_light		*lights;
	int			at_light;
	int			imgcount;
	t_image		*imgs;
	int			at_img;
	t_camera	camera;
	t_point		closest;
	t_point		current;
	t_colour	max;
	int			raycount;
	t_light		ambient;
	int			filter;
	t_ray		r_ray;
}				t_scene;

typedef struct s_img
{
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	void			*win_pixels;
	t_buffer		*win_buffer;
	t_channels		*channels;
	int				win_pixel_pitch;
	t_bool			run;
	t_scene			scene;
	double			x_fact;
	double			y_fact;
	uint			nb;
	uint			max_nb;
	double			max_color;
}					t_img;

//main & initialisation
void		init(t_img *img);
void		init_point(t_point *p);
void		init_colour(t_colour *c);
void		init_camera(t_camera *cam);

//parsing
void		parser(t_scene *scene, char *str);
void		parse_camera(char **words, t_camera *cam, t_flags *flags);
void		parse_light(char **words, t_scene *s, t_flags *flags);
void		parse_object(char **words, t_scene *s, t_flags *flags);
void		parse_image(char **words, t_scene *s, t_flags *flags);
void		parse_scene(char **words, t_scene *s, t_flags *flags);
int			parse_texture(char *str);
void		parse_line(char *str, t_scene *scene, t_flags *flags);

//keys
void		e_keys(SDL_Event e, t_img *img);

//camera
void		init_camera(t_camera *cam);
void		camera_update(t_camera *cam);

//drawing & rendering
void		render(t_img *img);
void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		draw_image(t_img *img, t_channels *c);
void		draw_img_to_window(t_img *img);

//rays
t_ray		ray_gen(t_vec start, t_vec end);
t_ray		ray_gen_cam(t_img *img, int x, int y);
void		ray_copy(t_ray *from, t_ray *to);
void		ray_print(t_ray ray);

//sphere
t_bool		sphere_t(t_ray ray, t_obj obj, t_point *p);
double		get_intersect(t_ray *ray);

//plane
t_bool		plane_t(t_ray ray, t_obj obj, t_point *p);

//cylinder & cone
t_bool		cylinder_t(t_ray ray, t_obj obj, t_point *p);
t_bool		cone_t(t_ray ray, t_obj obj, t_point *p);
t_bool		cc_area_intersect(t_obj obj, t_point *p);
t_bool		cc_base_intersect(t_obj obj, t_point *p);
void		cc_calc_t(t_quadratic q, double *t, t_vec v, t_ray ray);
void		cc_calc_poi(t_vec *poi, double *t, t_vec v, t_ray ray);

//vector
void		ft_vec_init(t_vec *v);
void		vec_copy(t_vec *from, t_vec *to);
void		vec_set(t_vec *v, double x, double y, double z);

//4x4 matrices
void		m_apply_vec(t_vec *vec, t_matrix m);
void		m_apply_ray(t_ray *ray, t_obj obj, t_bool flag);

//3x3 matrices
t_m3		m3_multiply(t_m3 ma, t_m3 mb);
void		m3_apply_tform(t_m3 m, t_uv *uv);
t_vec		m3_multiply_vec(t_m3 m, t_vec v);
t_m3		m3_linear(t_matrix m4);
void		m3_set_identity(t_m3 *m3);
t_m3		m3_inverse(t_m3 m3);

//lights
void		init_light(t_light *light);
double		light_check_illum(t_scene *s, int currentObj,
				t_light *light, t_point *p);
t_bool		light_check(t_scene *s, t_point *closest, int obj);
void		print_light(t_light *l);
void		ambient_add(t_light amb, t_point *p);

//colours
void		colour_check_max(t_colour *max, t_colour c);
void		colour_fset_clamp(t_colour *c, double r, double g, double b);
uint32_t	convert_colour(double r, double g, double b, double max);
uint32_t	get_colour(int filter, t_colour og, double max);
void		colour_add_intensity(t_colour *a, t_colour b, double i);
void		colour_at_poi(t_scene *s, t_point *closest, int obj, t_colour c);
t_colour	find_max_colour(t_channels *c);
double		calc_max(t_colour max);

//materials
t_bool		compute_colour(t_scene *s, t_point *this, t_ray ray, int obj);
t_colour	mat_reflection(t_scene *s, t_point *current, t_ray ray, int obj);
t_colour	mat_refraction(t_scene *s, t_point *this, t_ray ray, int obj);
t_colour	mat_highlight(t_scene *s, t_point *this, t_ray ray, int obj);

//textures
void		texture_sort(t_point *p, t_texture *txt);
void		texture_checkers(t_point *p, t_texture *txt);
void		texture_wave(t_point *p, t_texture txt);
void		texture_perlin(t_point *p);
void		texture_cloud(t_point *p);
void		texture_wood(t_point *p);
void		texture_marble(t_point *p);
void		texture_rainbow(t_point *p);
void		set_texture(t_texture *t, int txt);
float		turbulence(float x, float y, float size);

//image handling
void		image_texture(t_point *p, t_image *i);
void		image_load(const char *file, t_image *image);
void		image_error(const char *str);

//filters
uint32_t	filter_bw(double r, double g, double b, double max);
uint32_t	filter_sepia(double r, double g, double b, double max);
void		antialiasing_draw_image(t_img *img, t_channels *c);

//screenshoting & bitmap creation
void		screenshot_image(t_img *img);
void		create_bmp(unsigned char *image, char *file_name);
void		bmp_name(char *str);

//uv mapping handling
void		uv_set(t_uv *uv, double u, double v);
void		uv_transform(t_m3 *tform, t_uv trans, double rot, t_uv scale);

//utils
void		print_vec(t_vec v);
void		print_vec_nl(t_vec v);
void		print_pixel(t_pixel p);
void		print_obj(t_obj obj);
void		print_colour(t_colour c);
t_bool		close_enough(double a, double b);
double		d_to_rad(int deg);
void		print_colour_as_vec(t_colour c);
void		m3_print(t_m3 m);

#endif
