
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
fork - создание дочернего процесса
	pid_t fork(void);
waitpid - ожидание указанного дочернего процесса
	pid_t waitpid(pid_t pid, int *status, int options);

//---for_testing_philo---
./philo_one 5 800 200 200 4 > file1
cat file1 | grep " 1 is eating" | wc -l

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
