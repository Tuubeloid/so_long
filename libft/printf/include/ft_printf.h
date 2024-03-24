/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:26:21 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/19 14:09:36 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_ret
{
	int	output_count;
	int	error_return;
}	t_ret;

int		ft_printf(const char *s, ...);
void	ft_format_spec_check(va_list args, char specifier, t_ret *ret);
void	ft_printf_char(int c, t_ret *ret);
void	ft_printf_str(char *s, t_ret *ret);
void	ft_printf_ptr(unsigned long long ptr, t_ret *ret);
void	ft_printf_hex_lowercase(unsigned long long ptr, t_ret *ret);
void	ft_printf_hex_uppercase(unsigned int nbr, t_ret *ret);
void	ft_printf_nbr(long long nbr, t_ret *ret);
void	ft_printf_nbr_unsigned(unsigned int nbr, t_ret *ret);

#endif
