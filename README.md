# **Philosophers**

**Philosophers** is a project from the École 42 curriculum designed to introduce key concepts in concurrent programming and synchronization. The project focuses on solving the classical **Dining Philosophers Problem**, with mandatory and bonus implementations showcasing the use of threads, mutexes, semaphores, and processes.

---

## **Overview**

In this project, you simulate philosophers seated around a circular table. Each philosopher alternates between **eating**, **thinking**, and **sleeping**, and requires two forks to eat. The challenge lies in managing the shared resources (forks) without creating deadlocks or race conditions.

---

## **Features**

### **Mandatory Part**
- **Threads and Mutexes**:
  - Each philosopher is implemented as a separate thread.
  - Forks are protected using mutexes to prevent race conditions.

- **Synchronization**:
  - Ensure philosophers can only eat when they have access to two forks.
  - Avoid deadlocks and starvation while managing forks and philosopher states.

- **State Management**:
  - Each philosopher alternates between:
    - **Thinking**: Philosopher is pondering life.
    - **Eating**: Philosopher picks up two forks and eats.
    - **Sleeping**: Philosopher sleeps after eating.

### **Bonus Part**
- **Processes and Semaphores**:
  - Philosophers are implemented as separate processes.
  - Forks are managed using semaphores for synchronization.
  - Semaphores are used to manage access to critical sections, ensuring safe and efficient sharing of resources.

- **Avoiding Deadlocks**:
  - By limiting the number of philosophers that can attempt to eat simultaneously.
  - Efficient use of semaphores to avoid unnecessary blocking.

---

## **How It Works**

1. **Program Input**:
   - The program takes the following arguments:
     ```
     ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
     ```
   - **Parameters**:
     - `number_of_philosophers`: Total number of philosophers and forks.
     - `time_to_die`: Maximum time a philosopher can go without eating.
     - `time_to_eat`: Time a philosopher spends eating.
     - `time_to_sleep`: Time a philosopher spends sleeping.
     - `[number_of_times_each_philosopher_must_eat]`: Optional argument to limit the simulation.

2. **States**:
   - Each philosopher alternates between **thinking**, **eating**, and **sleeping**, ensuring proper synchronization to avoid deadlocks and race conditions.

3. **Termination**:
   - The program ends when all philosophers have eaten the required number of times (if specified) or if one philosopher dies (exceeds `time_to_die` without eating).

---
