
<strings.h>	strerror - 00
<stdlib.h>	malloc, free, exit
			\___00, \_00, \_84
<unistd.h>	write, read, close, fork, getcwd, chdir, execve, dup, dup2, pipe
			\__52, \_52, \__54, \_77, \___00, \__75, \___80, \______96, \120
<fcntl.h>	open - 50
<signal.h>	signal, kill - 109
<dirent.h>	opendir, readdir, closedir - 66
<errno.h>	errno - 00
<sys/wait.h>	wait, waitpid - 87
<sys/types.h>	wait3, wait4 - 88
<sys/stat.h>	stat, lstat, fstat - 61

memset - заполняет первые len байт по указателю dest символом c
printf - умный вывод на экран
malloc - выделение памяти
free - освобождение памяти
write - вывод на экран
usleep - приостанавливает работу потока, на время в микросекундах
gettimeofday - заполняет структуру временем от начала эпохи
pthread_create - создание потока
pthread_join - ожидание завершения процесса
pthread_detach - отсоединяет процесс (при завершении, все занимаемые им
			ресурсы освобождаются и мы не можем отслеживать его завершение)
pthread_mutex_init - создание мьютекса
pthread_mutex_destroy - закрытие мьютекса
pthread_mutex_lock - закрыть мьютекс
pthread_mutex_unlock - открыть мьютекс

колличество философов и вилок - number_of_philo;
время смерти, если столько без еды - time_to_die;
время на еду - time_to_eat;
время на сон - time_to_sleep;
сколько надо поесть всем - number_of_times_each_philo_must_eat;

ft_putendl("---");

ft_putnbr(len);
ft_putendl("");

write(1, "\n", 1);

alias mm="make && ./minishell"

//-----пример_работы_gettimeofday--------
#include <sys/time.h>

struct timeval tv1, tv2, dtv;
struct timezone tz;

void	time_start()
{
	gettimeofday(&tv1, &tz);
}

long	time_stop()
{
	gettimeofday(&tv2, &tz);
	dtv.tv_sec = tv2.tv_sec - tv1.tv_sec;
	dtv.tv_usec = tv2.tv_usec - tv1.tv_usec;
	if(dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

main()

{
	...
	time_start();
		/* какие-то действия */
	printf("Time: %ld\n", time_stop());
	...
}

//------------atos----------
int				ft_atos(char *str, size_t *nb)
{
	if (*str == '\0')
		return (-1);
	*nb = 0;
	while (*str && *str >= '0' && *str <= '9')
		*nb = 10 * *nb + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	return (0);
}
//---------fill_nbr---------------
void			fill_nbr(size_t nbr, char **ptr)
{
	char			c;
	size_t			nnbr;
	long long int	pow;

	pow = 10;
	nnbr = nbr;
	while (nnbr /= 10)
		pow *= 10;
	while ((pow /= 10))
	{
		c = (nbr / pow) % 10 + '0';
		*(*ptr)++ = c;
	}
}

	// print_param(&all);//--print from all
// void	print_param(t_param *all)
// {
// 	printf("%li\n", all->number_of_philo);
// 	printf("%li\n", all->time_to_die);
// 	printf("%li\n", all->time_to_eat);
// 	printf("%li\n", all->time_to_sleep);
// 	printf("%li\n", all->number_of_times_each_philo_must_eat);
// }




// void	*p_time(void *tmp)
// {
// 	t_param	*all = tmp;
// 	int		i;
// 	long	time;

// 	time = 0;
// 	while ()
// }
	// pthread_create(&all.p_time, NULL, p_time, (void *)&all);
	// pthread_join(all.p_exit, NULL);




int	init_philo(t_param *all)
{
	pthread_t	p[all->number_of_philo];
	// pthread_t	p;
	int			i;

	i = 0;
	while (i < all->number_of_philo)
	{
		// if (pthread_create(&p, NULL, philo, (void *)all) == 0)
		// 	pthread_detach(p);
		// else
		if (pthread_create(&p[i], NULL, philo, (void *)all) != 0)
		{
			printf("---|Alart|--- %d philo is not born! ---|Alart|---", i + 1);
			return (1);
		}
		// usleep(50);//--time after born philo
		i++;
	}
	return (0);
}




// void	*philo(void *tmp)
// {
// 	t_param *all = tmp;
// 	int		philo_num;
// 	long	time;
// 	long	time_eat;
// 	pthread_mutex_t	*mutex_left_fork;
// 	pthread_mutex_t	*mutex_right_fork;

// 	time_eat = -1;
// 	philo_num = all->num++;
// 	// printf("Philosopher %i is ready\n", philo_num);//---
// 	mutex_left_fork = &all->fork_mutex[philo_num - 1];
// 	mutex_right_fork = &all->fork_mutex[philo_num % all->number_of_philo];
// 	while (all->exit_status == 0)
// 	{
// 		pthread_mutex_lock(mutex_left_fork);
// 		time = time_passed(all->time_start);
// 		check_exit_status_and_print(all, philo_num, time, "taken a fork\n");
// 		pthread_mutex_lock(mutex_right_fork);
// 		time = time_passed(all->time_start);
// 		check_exit_status_and_print(all, philo_num, time, "taken a fork\n");

// 		time = time_passed(all->time_start);
// 		all->philo_life_status[philo_num - 1] = time_now();
// 		check_exit_status_and_print(all, philo_num, time, "is eating\n");
// 		usleep(all->time_to_eat);
// 		// monie(all->time_to_eat);
// 		pthread_mutex_unlock(mutex_left_fork);
// 		pthread_mutex_unlock(mutex_right_fork);

// 		time = time_passed(all->time_start);
// 		check_exit_status_and_print(all, philo_num, time, "is sleeping\n");
// 		usleep(all->time_to_sleep);

// 		time = time_passed(all->time_start);
// 		check_exit_status_and_print(all, philo_num, time, "is thinking\n");

// 		// while (1)
// 		// {
// 		// 	all->time_to_die;
// 		// }

// 		pthread_mutex_lock(&all->print_mutex);
// 		if (all->exit_status == 0)
// 		{
// 			all->philo_life_status[philo_num - 1] = 1;
// 			all->exit_status = 1;
// 		}
// 		pthread_mutex_unlock(&all->print_mutex);
// 		// pthread_join(all->p_exit, NULL);
// 	}
// 	return (NULL);
// }


// //-----------------------------
// long	time_now()
// {
// 	struct timeval	tv;
// 	struct timezone	tz;

// 	gettimeofday(&tv, &tz);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// long	time_passed(long start_time)
// {
// 	return (time_now() - start_time);
// }

// void	check_exit_status_and_print(t_param *all, int num, long time, char *str)
// {
// 	pthread_mutex_lock(&all->print_mutex);
// 	if (all->exit_status == 0)
// 		printf("%li %i %s", time, num, str);
// 	pthread_mutex_unlock(&all->print_mutex);
// }

// void	monie(long timer)
// {
// 	long start_time;

// 	start_time = time_now();
// 	usleep(timer - 7000);
// 	printf("%ld\n", time_now() - start_time);
// 	while(time_now() - start_time < timer)
// 	{
// 		usleep(100);
// 	}
// 	printf("pozral\n");
// }

// void	*philo(void *tmp)
// {
// 	t_param *all;

// 	all = tmp;
// 	//all->
// }

// int	init_philo(t_param *all)
// {
// 	pthread_t	p[all->number_of_philo];
// 	int			i;

// 	i = 0;
// 	while (i < all->number_of_philo)
// 	{
// 		pthread_create(&p[i], NULL, philo, (void *)all) != 0;
// 		usleep(50);
// 		i++;
// 	}
// 	return (0);
// }





	// int			i;

	// if (!(all->philo_life_status = malloc(sizeof(int) * all->number_of_philo)))
	// 	return (ft_perror("Error: malloc: inits philo_life_status"));
	// i = 0;
	// while (++i < all->number_of_philo)
	// {
	// 	all->philo_life_status[i] = 0;
	// 	i++;
	// }
	// ---