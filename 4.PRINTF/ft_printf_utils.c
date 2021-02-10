/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoncho <yoncho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 21:43:36 by yoncho            #+#    #+#             */
/*   Updated: 2021/02/10 00:58:35 by yoncho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strncpy(char *form_str, t_flags *flag)
{
  char	*ret;
  int	i;
  
  ret = (char *)malloc(sizeof(char) * flag->prec + 1);
  i = 0;
  while (i < flag->prec)
  {
	  ret[i] = form_str[i];
	  i++;
  }
  ret[i] = '\0';
  return ret;
}

char	*ft_strncpy_int(char *form_str, t_flags *flag)
{
  	char	*ret;
	int	form_len;
	int	i;
	int k;
	k = 0;
	
	ret = (char *)malloc(sizeof(flag->prec));
	i = -1;
	form_len = ft_strlen(form_str);
	
	if (flag->prec > form_len)
	{
		while (++i < ((flag->prec) - form_len))
			ret[i] = '0';
		while (i < flag->prec)
	  		ret[i++] = form_str[k++];
		ret[flag->prec] = '\0';
  }
  else
  {
	  ret = form_str;
  }
	return ret;
}

char	*ft_final_proc(char *form_str ,t_flags *flag, int form_len, char a)
{
	char	*ret;
	int	i;
	int k;

	k = 0;
	i = -1;
	ret = (char *)malloc(sizeof(flag->width));
	if (flag->minus)
	{
    	while (++i < form_len)
      		ret[i] = form_str[i];
    	while (i < flag->width)
      		ret[i++] = a;
	}
	else
	{
		while (++i < (flag->width) - form_len)
     		ret[i] = a;
    	while (i < flag->width)
      		ret[i++] = form_str[k++];
	}
	ret[flag->width] = '\0';
	return ret;
}


char	*ft_cs_proc(char *form_str, t_flags *flag)
{
	char	*ret;
	int	form_len;

	ret = (char *)malloc(sizeof(flag->width));
	form_len = ft_strlen(form_str);
	ret = ft_final_proc(form_str, flag, form_len, ' ');
	return ret;
}

char	*ft_di_proc(char *form_str, t_flags *flag)
{
	char	*ret;
	int	form_len;
	
	ret = (char *)malloc(sizeof(flag->width));
	form_len = ft_strlen(form_str);
	if (flag->zero == 1 && flag->minus == 0)
		ret = ft_final_proc(form_str ,flag,form_len, '0');
	else
		ret = ft_final_proc(form_str, flag, form_len, ' ');
	return ret;
}

int		ft_treat_width(const char **format, va_list ap, t_flags *flag)
{
  int  width;

  width = 0;
  if (**format == '*')
  {
    width += va_arg(ap, int);
    if (width < 0)
    {
      flag->minus = 1;
      width *= -1;
    }
    return (width);
  }
  while (ft_isdigit(**format))
  {
    width *= 10;
    width += (**format) - '0';
    (*format)++;
  }
  (*format)--;
  return (width);
}

int   ft_treat_prec(const char **format, va_list ap)
{
  int  prec;

  prec = 0;
  (*format)++;
  if (**format == '*')
    prec += va_arg(ap, int);
  while (ft_isdigit(**format))
  {
    prec *= 10;
    prec += (**format) - '0';
    (*format)++;
  }
  (*format)--;
  return (prec);
}

int   check_format(const char **format)
{
  if (**format == 'c' || **format == 's' || **format == 'd' ||
      **format == 'i' || **format == 'u' || **format == 'p' ||
      **format == 'x' || **format == 'X' || **format == '%')
			return (1);
  return (0);
}

char    *ft_get_char(char c)
{
  char *ret;
  ret = (char *)malloc(sizeof(char) * 2);
  *ret = c;
  ret[1] = '\0';
  return ret;
}

char    *ft_get_string(char *s)
{
  char *ret;
  if (s == 0)
    return (ft_strdup(" "));
  ret = ft_strdup(s);
  return ret;
}

char    *ft_get_integer(int i, t_flags *flag)
{
	char *ret;
	if (i == 0 && flag->dot && (flag->prec != 0))
		return (ft_strdup("0"));
	else if (i == 0 && flag->dot)
		return (ft_strdup(""));
  	ret = ft_strdup(ft_itoa(i));
  	return ret;
}

char    *ft_get_uint(unsigned int i, t_flags *flag)
{
	char *ret;
	if (i == 0 && flag->dot && (flag->prec != 0))
		return (ft_strdup("0"));
	else if (i == 0 && flag->dot)
		return (ft_strdup(""));
  	ret = ft_strdup(ft_itoa(i));
  	return ret;
}

char    *ft_get_hexa(const char **format, unsigned int i)
{
	char	*ret;
	char	*hexa_info;
	unsigned int len_i;
	int		len;
	
	hexa_info = "0123456789abcdef";
	len = 0;
	len_i = i;
	while (len_i != 0)
	{
		len_i /= 16;
		len++;
	}
	ret = (char *)malloc(sizeof(char) * len + 1);
	ret[len] = '\0';
	if (i == 0)
		ret[len] = '0';
	while (i != 0)
	{
		ret[--len] = hexa_info[i % 16];
		if (**format == 'X')
			ret[len] = ft_toupper(ret[len]);
		i /= 16;
	}
  	return ret;
}

