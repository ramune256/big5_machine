/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:50:15 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/01 20:59:38 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"

typedef struct s_data
{
	int	Ex;
	int	A;
	int	C;
	int	Em;
	int	P;
}	t_data;

int	put_err(char *message)
{
	ft_printf("%s\n", message);
	return (1);
}

int	update_data(t_data *data, int question_num, int input)
{
	if (question_num >= 1 && question_num <= 10)
	{
		data->Ex += input;
		ft_printf("DEBUG: data->Ex += %d\ncurrent value is %d\n", input, data->Ex);
	}
	else if (question_num >= 11 && question_num <= 20)
	{
		data->A += input;
		ft_printf("DEBUG: data->A += %d\ncurrent value is %d\n", input, data->A);
	}
	else if (question_num >= 21 && question_num <= 30)
	{
		data->C += input;
		ft_printf("DEBUG: data->C += %d\ncurrent value is %d\n", input, data->C);
	}
	else if (question_num >= 31 && question_num <= 40)
	{
		data->Em += input;
		ft_printf("DEBUG: data->Em += %d\ncurrent value is %d\n", input, data->Em);
	}
	else if (question_num >= 41 && question_num <= 50)
	{
		data->P += input;
		ft_printf("DEBUG: data->P += %d\ncurrent value is %d\n", input, data->P);
	}
	else
		return (1);
	return (0);
}

void	instruct(void)
{
	ft_printf("-------BIG5 MACHINE-------\n");
	ft_printf("以下の50問を読んで、\n1 ：全くちがう\n2 ：ちがう\n3 ：どちらともいえない\n");
	ft_printf("4 ：そうだ\n5 ：全くそうだ\nという5点満点でそれぞれお答えください。\n");
}

void	put_result(t_data *data)
{
	ft_printf("-------結果-------\n");
	ft_printf("外向性: %d\n", data->Ex);
	ft_printf("協調性: %d\n", data->A);
	ft_printf("誠実性: %d\n", data->C);
	ft_printf("情動性: %d\n", data->Em);
	ft_printf("開放性: %d\n", data->P);
}

int	main(void)
{
	char	*line;
	int		fd;
	int		input;
	int		question_num;
	t_data	data = {0, 0, 0, 0, 0};

	fd = open("questions.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	instruct();
	question_num = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("問%d %s\n1~5で解答: ", question_num, line);
		free(line);
		if (scanf("%d", &input) != 1)
			return (put_err("ERROR: scanf\n"));
		if (!(input >= 1 && input <= 5))
			return (put_err("ERROR: invaild input value\n"));
		if (question_num == 2 || question_num == 5 || question_num == 13 || question_num == 14
				|| question_num == 17 || question_num == 20 || question_num == 21 || question_num == 22
				|| question_num == 25 || question_num == 27 || question_num == 29 || question_num == 34
				|| question_num == 40 || question_num == 42 || question_num == 47)
		{
			input = 6 - input;
			ft_printf("DEBUG: question_num is %d, so the input value has been reversed into %d\n", question_num, input);
		}
		if(update_data(&data, question_num, input) == 1)
			return (put_err("ERROR: invaild text file\n"));
		question_num++;
	}
	close(fd);
	put_result(&data);
	return (0);
}
