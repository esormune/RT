/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:47:01 by esormune          #+#    #+#             */
/*   Updated: 2022/04/05 20:47:04 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>// malloc
# include <stdint.h>// int definitions
# include <unistd.h>// write
# include <math.h>//sin, cos
# include "ft_defs.h"

// array utils

size_t			ft_arr_size(char **arr);
void			ft_free_array(char **arr);

// character detection and manipulation

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_is_whitespace(char c);
int				ft_isupper(char c);
int				ft_islower(char c);
int				ft_is_neg(double nb);
int				ft_is_neg_minus(double nb);
int				ft_toupper(char c);
int				ft_tolower(char c);

// graphics functions

int				ft_colour(int r, int g, int b);
t_colour		ft_hsl_to_rgb(t_hsl hsl);
float			ft_lerp(float start, float end, float percentage);
float			ft_smerp(float start, float end, float perc);
float			ft_noise(float x, float y);
void			ft_colour_fset(t_colour *c, double r, double g, double b);

// ft_printf and associates

int				ft_printf(const char *str, ...);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

// linked list utils

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstpush(t_list **alst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
int				ft_lstsize(t_list *lst);

// math

int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_numlength(int nb);
int				ft_numlength_neg(intmax_t nb);
long double		ft_pow(int nb, int pow);
uintmax_t		ft_uintmax_pow(uintmax_t nb, int pow);
long double		ft_neg_pow_ten(long double nb, int pow);
long double		ft_brounding(long double nb, int prec);
long double		ft_brounding_ld(long double nb, int prec);
float			ft_abs(float a);
int				ft_avg(int x, int y);
double			ft_clamp_d(double value, double min, double max);
t_complex		ft_c_multiply(t_complex a, t_complex b);
t_complex		ft_c_add(t_complex a, t_complex b);
t_complex		ft_c_sub(t_complex a, t_complex b);
t_complex		ft_c_sq(t_complex a);
t_complex		ft_c_divide(t_complex a, t_complex b);

// matrix math & utils

t_matrix		ft_arr_to_m(double *arr);
void			ft_m_transform(t_matrix *m, t_vec trans,
					t_vec rot, t_vec scale);
t_matrix		ft_m_inverse(t_matrix m);
t_matrix		ft_arr_to_m(double *arr);
void			ft_m_to_arr(t_matrix m, double *arr);
t_vec4			ft_m_multiply_vec(t_matrix m, t_vec4 v);
t_matrix		ft_m_multiply(t_matrix ma, t_matrix mb);
void			ft_m_rotate_x(t_matrix *m, t_vec rot);
void			ft_m_rotate_y(t_matrix *m, t_vec rot);
void			ft_m_rotate_z(t_matrix *m, t_vec rot);
void			ft_m_translation(t_matrix *m, t_vec trans);
void			ft_m_scale(t_matrix *m, t_vec scale);
void			ft_m_set_value(t_matrix *m, int row, int column, double value);
t_matrix		ft_m_make_identity(void);
void			ft_m_set_identity(t_matrix *m);

// vector math & utils

t_vec			ft_vec_cross(t_vec a, t_vec b);
double			ft_vec_dot(t_vec a, t_vec b);
t_vec			ft_vec_scale(t_vec a, double scale);
t_vec			ft_vec_add(t_vec a, t_vec b);
t_vec			ft_vec_sub(t_vec a, t_vec b);
void			ft_vec_normalise(t_vec *v);
double			ft_vec_magn(t_vec v);
void			ft_vec_copy(t_vec *from, t_vec *to);
void			ft_vec_set(t_vec *v, double x, double y, double z);
void			ft_vec_init(t_vec *v);
t_vec			ft_vec_normed(t_vec v);

// memory utils

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memmove(void *to, const void *from, size_t len);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_calloc(size_t count, size_t size);

// misc utils

int				get_next_line(const int fd, char **line);
int				ft_rand(intmax_t ptr, int lim);
void			ft_getout(const char *str);

// print, put, write output

void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int nb);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnstr_fd(char *str, size_t size, int fd);
void			ft_print_hex(size_t nb);
void			ft_print_bits(unsigned char octet);
void			ft_print_array(char **res);

// string manipulation and utils

size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle, \
				size_t len);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dest, const char *src, size_t dstsize);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
char			*ft_tolower_str(char *str);
char			*ft_toupper_str(char *str);
void			ft_putnstr(char *str, size_t size);
char			*ft_strndup(const char *src, size_t size);
char			*ft_implode(char **str);

// type conversions

int				ft_atoi(const char *str);
int				ft_atoi_base(char *str, int base);
intmax_t		ft_atoi_max(const char *str);
size_t			ft_atoi_sizet(const char *str);
long double		ft_atof(const char *str);
char			*ft_itoa(int n);
char			*ft_itoa_base(int value, int base);
char			*ft_itoa_llong_base(long long nb, int base);
char			*ft_itoa_ulong_base(unsigned long long nb, int base);
char			*ft_itoa_intmax_base(intmax_t nb, int base);
char			*ft_itoa_size_t_base(size_t nb, int base);
char			*ft_itoa_uintmax_base(uintmax_t nb, int base);
char			*ft_flitoa(double nb, int prec);
char			*ft_flitoa_ldouble(long double nb, int prec);
char			*ft_itoa_exp(long double nb, int prec);

#endif
