
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
// pthread_mutex_init - создание мьютекса
// pthread_mutex_destroy - закрытие мьютекса
// pthread_mutex_lock - закрыть мьютекс
// pthread_mutex_unlock - открыть мьютекс
sem_open - создает  или открывает семафор
	#include <sys/stat.h>//for mode_t
	#include <fcntl.h>//for O_CREAT
	sem_t *name;
	sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
	name = sem_open(name, O_CREAT, ?, 5);//return указатель на семафор or SEM_FAILED
sem_close - закрывает семафор
	int sem_close(sem_t *name);//return 0 or -1
sem_unlink - удаляет семафор из системы
	int sem_unlink(const char *name);//return 0 or -1
sem_post - увеличивает/разблокирует семафор на который указывает name 
	int sem_post(sem_t *sem);//return 0 or -1
sem_wait - уменьшает/блокирует семафор на который указывает name

// # include <sys/stat.h>//for mode_t
// # include <fcntl.h>//for O_CREAT

колличество философов и вилок - number_of_philo;
время смерти, если столько без еды - time_to_die;
время на еду - time_to_eat;
время на сон - time_to_sleep;
сколько надо поесть всем - number_of_times_each_must_eat;

//---for_testing_philo---
cat file1 | grep " 1 is eating" | wc -l

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

//---print_parse_param---
printf("%i\n", all.number_of_philo);
printf("%i\n", all.time_to_die);
printf("%i\n", all.time_to_eat);
printf("%i\n", all.time_to_sleep);
printf("%i\n", all.number_of_times_each_must_eat);
//-----------------------

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
// 		tl_check_and_print(all, philo_num, time, "taken a fork\n");
// 		pthread_mutex_lock(mutex_right_fork);
// 		time = time_passed(all->time_start);
// 		tl_check_and_print(all, philo_num, time, "taken a fork\n");

// 		time = time_passed(all->time_start);
// 		all->philo_life_status[philo_num - 1] = tl_time_now();
// 		tl_check_and_print(all, philo_num, time, "is eating\n");
// 		usleep(all->time_to_eat);
// 		// monie(all->time_to_eat);
// 		pthread_mutex_unlock(mutex_left_fork);
// 		pthread_mutex_unlock(mutex_right_fork);

// 		time = time_passed(all->time_start);
// 		tl_check_and_print(all, philo_num, time, "is sleeping\n");
// 		usleep(all->time_to_sleep);

// 		time = time_passed(all->time_start);
// 		tl_check_and_print(all, philo_num, time, "is thinking\n");

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

	// int			i;

	// if (!(all->philo_life_status = malloc(sizeof(int) * all->number_of_philo)))
	// 	return (tl_perror("Error: malloc: inits philo_life_status"));
	// i = 0;
	// while (++i < all->number_of_philo)
	// {
	// 	all->philo_life_status[i] = 0;
	// 	i++;
	// }
	// ---



	//----------------------------
// void	*p_exit(void *tmp)
// {
// 	t_param	*all = tmp;
// 	int		i;
// 	long	time;

// 	while (1)
// 	{
// 		// time = sleep_and_time(all, 10000);
// 		// usleep(5000);
// 		// time = time_passed(all->time_start);
// 		i = 0;
// 		while (i < all->number_of_philo)
// 		{
// 			// printf("---| %li %li |---\n", (tl_time_now() - all->philo_life_status[i]), all->time_to_die);

// 			// if ((tl_time_now() - all->philo_life_status[i]) > all->time_to_die && all->philo_life_status[i] != 0)
// 			if (all->philo_life_status[i] == 0)
// 			{
// 				printf("%li %i is died\n", time, i + 1);
// 				write(1, "Exit\n", 5);
// 				return (0);
// 			}
// 			i++;
// 		}
// 	}
// }

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}