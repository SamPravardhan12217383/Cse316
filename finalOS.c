#include <stdio.h>

struct Process {
    int pid;
    int priority;
    int burst_time;
};

void enqueue(struct Process queue[], struct Process process, int *rear, int max_size) {
    if (*rear < max_size) {
        queue[*rear] = process;
        (*rear)++;
    } else {
        printf("Queue is full. Cannot enqueue.\n");
    }
}

struct Process dequeue(struct Process queue[], int *front, int *rear) {
    if (*front < *rear) {
        return queue[(*front)++];
    } else {
        struct Process null_process = {0, 0, 0};
        printf("Queue is empty. Returning a null process.\n");
        return null_process;
    }
}

int is_empty(int front, int rear) {
    return front == rear;
}

int main() {
    struct Process queue1[100], queue2[100], queue3[100];
    int rear1 = 0, rear2 = 0, rear3 = 0;
    int front1 = 0, front2 = 0, front3 = 0;
    int max_size = 100; 
    int time_quantum = 4; 

   
    int queue1_priority_range[] = {1, 3};
    int queue2_priority_range[] = {4, 6};
    int queue3_priority_range[] = {7, 9};

   
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

   
    for (int i = 0; i < num_processes; i++) {
        struct Process process;
        process.pid = i + 1;
        printf("Enter priority for process %d: ", process.pid);
        scanf("%d", &process.priority);
        printf("Enter burst time for process %d: ", process.pid);
        scanf("%d", &process.burst_time);

       
        if (process.priority >= queue1_priority_range[0] && process.priority <= queue1_priority_range[1]) {
            enqueue(queue1, process, &rear1, max_size);
        } else if (process.priority >= queue2_priority_range[0] && process.priority <= queue2_priority_range[1]) {
            enqueue(queue2, process, &rear2, max_size);
        } else if (process.priority >= queue3_priority_range[0] && process.priority <= queue3_priority_range[1]) {
            enqueue(queue3, process, &rear3, max_size);
        } else {
            printf("Priority %d is not within the valid range for any queue.\n", process.priority);
        }
    }

    int time_elapsed = 0;

    while (!(is_empty(front1, rear1) && is_empty(front2, rear2) && is_empty(front3, rear3))) {
        if (time_elapsed >= 10) {
           
            time_elapsed = 0;
            printf("Switching queues.\n");
            enqueue(queue1, dequeue(queue1, &front1, &rear1), &rear1, max_size);
            enqueue(queue2, dequeue(queue2, &front2, &rear2), &rear2, max_size);
            enqueue(queue3, dequeue(queue3, &front3, &rear3), &rear3, max_size);
        }

        if (!is_empty(front1, rear1)) {
            
            struct Process process = dequeue(queue1, &front1, &rear1);
            if (process.burst_time <= time_quantum) {
                time_elapsed += process.burst_time;
                printf("Running process %d with priority %d and burst time %d\n", process.pid, process.priority, process.burst_time);
                process.burst_time = 0;
                printf("Process %d completed.\n", process.pid);
            } else {
                time_elapsed += time_quantum;
                printf("Running process %d with priority %d and burst time %d\n", process.pid, process.priority, time_quantum);
                process.burst_time -= time_quantum;
                enqueue(queue1, process, &rear1, max_size);
            }
        } else if (!is_empty(front2, rear2)) {
           
            struct Process process = dequeue(queue2, &front2, &rear2);
            printf("Running process %d with priority %d and burst time %d\n", process.pid, process.priority, process.burst_time);
            process.burst_time = 0;
            printf("Process %d completed.\n", process.pid);
        } else if (!is_empty(front3, rear3)) {
            
            struct Process process = dequeue(queue3, &front3, &rear3);
            printf("Running process %d with priority %d and burst time %d\n", process.pid, process.priority, process.burst_time);
            process.burst_time = 0;
            printf("Process %d completed.\n", process.pid);
        }
    }

    printf("All processes have been executed.\n");

    return 0;
}
