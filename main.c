#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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

void	instruct(void)
{
	ft_printf("\n-------BIG5 MACHINE-------\n");
	ft_printf("以下の50問を読んで、\n1 ：全くちがう\n2 ：ちがう\n3 ：どちらともいえない\n");
	ft_printf("4 ：そうだ\n5 ：全くそうだ\nという5点満点でそれぞれお答えください。\n\n");
}

int	reverse_question(int question_num)
{
	int	to_reverse[16] = {2, 5, 13, 14, 17, 20, 21, 22, 25, 27, 29, 34, 40, 42, 47, -1};
	int	i;

	i = 0;
	while (to_reverse[i] != -1)
	{
		if (question_num == to_reverse[i])
			return (1);
		i++;
	}
	return (0);
}

int	update_data(t_data *data, int question_num, int input)
{
	if (question_num >= 1 && question_num <= 10)
	{
		data->Ex += input;
		// ft_printf("DEBUG: data->Ex += %d\ncurrent value is %d\n", input, data->Ex);
	}
	else if (question_num >= 11 && question_num <= 20)
	{
		data->A += input;
		// ft_printf("DEBUG: data->A += %d\ncurrent value is %d\n", input, data->A);
	}
	else if (question_num >= 21 && question_num <= 30)
	{
		data->C += input;
		// ft_printf("DEBUG: data->C += %d\ncurrent value is %d\n", input, data->C);
	}
	else if (question_num >= 31 && question_num <= 40)
	{
		data->Em += input;
		// ft_printf("DEBUG: data->Em += %d\ncurrent value is %d\n", input, data->Em);
	}
	else if (question_num >= 41 && question_num <= 50)
	{
		data->P += input;
		// ft_printf("DEBUG: data->P += %d\ncurrent value is %d\n", input, data->P);
	}
	else
		return (1);
	return (0);
}

void	put_percent(char *type, int value)
{
	int	i;

	i = 0;
	ft_printf("%s: [", type);
	while (i < value / 5)
	{
		ft_printf("#");
		i++;
	}
	while (i < 10)
	{
		ft_printf(".");
		i++;
	}
	ft_printf("] %d%%\n", value * 2);
}

void	put_result(t_data *data, char *name)
{
	time_t	whattime;

	whattime = time(NULL);

	ft_printf("\n----------Result----------\n");
	ft_printf("Name: %s\n", name);
	ft_printf("Date: %s\n", ctime(&whattime));

	put_percent("外向性", data->Ex);
	put_percent("協調性", data->A);
	put_percent("誠実性", data->C);
	put_percent("情動性", data->Em);
	put_percent("開放性", data->P);

	ft_printf("--------------------------\n");
}

void	postscript(void)
{
	ft_printf("\n解説:\n");
	ft_printf("外向性: この要素が高ければ社交的で明るく、低ければ謙虚で物静か。\n");
	ft_printf("協調性: この要素が高ければ他人に優しく友好的で、低ければ他人に冷たく敵対的。\n");
	ft_printf("誠実性: この要素が高ければ計画性があり責任感が強く、低ければ無計画で適当。\n");
	ft_printf("情動性: この要素が高ければ心配性で緊張しやすく、低ければ安定した精神を持っている。\n");
	ft_printf("開放性: この要素が高ければ好奇心が高く遊び心があり、低ければ堅実的で保守的である。\n");
}

int	main(void)
{
	char	*line;
	int		fd;
	int		input;
	int		question_num;
	char	name[256];
	t_data	data = {0, 0, 0, 0, 0};

	fd = open("questions.txt", O_RDONLY);
	if (fd < 0)
		return (1);

	ft_printf("Type your name: ");
	if (scanf("%255s", name) != 1)
		return (put_err("ERROR: wrong format\n"));

	instruct();
	question_num = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("--------------------------\n");
		ft_printf("問%d %s1~5で解答: ", question_num, line);
		free(line);
		if (scanf("%d", &input) != 1)
			return (put_err("ERROR: scanf\n"));
		if (!(input >= 1 && input <= 5))
			return (put_err("ERROR: invaild input value\n"));
		if (reverse_question(question_num))
		{
			input = 6 - input;
			// ft_printf("DEBUG: question_num is %d, so the input value has been reversed into %d\n", question_num, input);
		}
		if(update_data(&data, question_num, input) == 1)
			return (put_err("ERROR: invaild text file\n"));
		question_num++;
	}
	close(fd);
	put_result(&data, name);
	postscript();
	return (0);
}
