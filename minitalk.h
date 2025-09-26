/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgregori <rgregori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:10:15 by rgregori          #+#    #+#             */
/*   Updated: 2025/09/26 13:58:23 by rgregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

typedef struct s_siginfo {
	int		pids;
	int		current_bit;
	int		current_char;
	char	*msg;

}	t_siginfo;

typedef struct s_data
{
	t_siginfo	*data;
	t_data		*next;
}	t_data;

#endif