*This project was created as part of the 42 curriculum by juan-her.*

## Description

This project is a C implementation of the **Dining Philosophers problem**, a classic synchronization problem in computer science. The goal is to simulate a number of philosophers sitting around a circular table, who alternate between thinking and eating.

There is a fork between each pair of adjacent philosophers. To eat, a philosopher must pick up both their left and right forks. The challenge is to design a solution that avoids deadlocks (where all philosophers pick up one fork and wait indefinitely for the other) and starvation (where a philosopher is perpetually denied access to the forks).

This implementation uses POSIX threads (`pthreads`) and mutexes to manage the state of the philosophers and forks, ensuring that the simulation runs correctly and without conflicts.

## Instructions

### Compilation

To compile the project, run the `make` command:

```bash
make
```

This will create the `philo` executable.

### Execution

The program is run from the terminal with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers (and forks).
- `time_to_die`: (in ms) If a philosopher doesn't start eating within this time from the beginning of their last meal or the start of the simulation, they die.
- `time_to_eat`: (in ms) The time it takes for a philosopher to eat.
- `time_to_sleep`: (in ms) The time a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]`: (optional) If specified, the simulation stops after all philosophers have eaten this many times. If not, the simulation runs until a philosopher dies.

### Cleaning Up

You can clean the compiled object files and the executable with the following `make` rules:

- `make clean`: Removes the object files.
- `make fclean`: Removes the object files and the `philo` executable.
- `make re`: Cleans and recompiles the project.

## Resources

Here are some resources related to the project's concepts:

- **Documentation:**
    - [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
    - [Mutexes in C](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
- **Articles & Tutorials:**
    - [Dining Philosophers Problem on Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
    - [Dining Philosophers Problem with Semaphores](https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/)

### AI Usage

AI was used to understand the problem and help debug deadlock scenarios.
