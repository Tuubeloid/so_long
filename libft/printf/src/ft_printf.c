/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:26:06 by tvalimak          #+#    #+#             */
/*   Updated: 2024/03/20 16:20:17 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;
	t_ret	ret;

	ret.output_count = 0;
	ret.error_return = 0;
	i = 0;
	va_start(args, s);
	while (s[i] && ret.error_return == 0)
	{
		if (s[i] == '%' && s[i + 1])
		{
			ft_format_spec_check(args, s[i + 1], &ret);
			i++;
		}
		else
			ft_printf_char(s[i], &ret);
		i++;
	}
	va_end(args);
	if (ret.error_return < 0)
		return (-1);
	return (ret.output_count);
}

void	ft_format_spec_check(va_list args, char specifier, t_ret *ret)
{
	if (specifier == 'c')
		ft_printf_char(va_arg(args, int), ret);
	else if (specifier == 's')
		ft_printf_str(va_arg(args, char *), ret);
	else if (specifier == 'p')
		ft_printf_ptr(va_arg(args, unsigned long long), ret);
	else if (specifier == 'd' || specifier == 'i')
		ft_printf_nbr(va_arg(args, int), ret);
	else if (specifier == 'u')
		ft_printf_nbr_unsigned(va_arg(args, unsigned int), ret);
	else if (specifier == 'x')
		ft_printf_hex_lowercase(va_arg(args, unsigned int), ret);
	else if (specifier == 'X')
		ft_printf_hex_uppercase(va_arg(args, unsigned int), ret);
	else if (specifier == '%')
		ft_printf_char('%', ret);
}

void	ft_printf_char(int c, t_ret *ret)
{
	if (ret->error_return < 0)
		return ;
	if (write(1, &c, 1) < 0)
		ret->error_return = -1;
	else
		ret->output_count++;
}

void	ft_printf_str(char *s, t_ret *ret)
{
	if (s == NULL)
		ft_printf_str("(null)", ret);
	else
	{
		while (*s)
		{
			ft_printf_char(*s, ret);
			s++;
		}
	}
}
