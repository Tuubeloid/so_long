/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 12:10:46 by tvalimak          #+#    #+#             */
/*   Updated: 2023/11/19 13:11:14 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_nbr(long long nbr, t_ret *ret)
{
	if (nbr < 0)
	{
		ft_printf_char('-', ret);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		ft_printf_nbr(nbr / 10, ret);
		ft_printf_nbr(nbr % 10, ret);
	}
	else
		ft_printf_char(nbr + '0', ret);
}

void	ft_printf_nbr_unsigned(unsigned int nbr, t_ret *ret)
{
	if (nbr > 9)
	{
		ft_printf_nbr_unsigned(nbr / 10, ret);
		ft_printf_nbr_unsigned(nbr % 10, ret);
	}
	else
		ft_printf_char(nbr + '0', ret);
}
