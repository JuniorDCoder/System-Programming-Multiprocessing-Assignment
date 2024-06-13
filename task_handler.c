#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024

void write_to_file(char *filename, char *content) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    fwrite(content, sizeof(char), strlen(content), fp);
    fclose(fp);

    printf("Process %d: Wrote '%s' to '%s'\n", getpid(), content, filename);
}

void create_file(char *filename) {
    int fd = open(filename, O_CREAT | O_RDONLY, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    close(fd);

    printf("Process %d: Created file '%s'\n", getpid(), filename);
}

void continuous_sound_alert(int duration) {
    // Simulate sound alert with beeps and sleep
    printf("Process %d: Playing continuous sound alert for %d seconds...\n", getpid(), duration);
    for (int i = 0; i < duration; i++) {
        printf("\a");  // Beep sound
        fflush(stdout); 
        /* 
        	* Here i am flushing the stdout to ensure the beep is heard immediately 
        	* I faced a bug here where the sound only beeped at the last second of the duration
        	* Noticed that this was becasue the stdout was not flushed
        */
        sleep(1);
    }
}

void display_content(char *message) {
    printf("Process %d: %s\n", getpid(), message);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <task1> [arguments1] <task2> [arguments2] ...\n", argv[0]);

        return 1;
    }

    int num_tasks = (argc - 1) / 2;  // Calculate number of tasks

    pid_t pid;
    for (int i = 0; i < num_tasks; i++) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) {  // Child process
            char *task = argv[i * 2 + 1];
            char *arg1 = argv[i * 2 + 2];
            char *arg2 = argv[i * 2 + 3];

            if (strcmp(task, "write") == 0) {
                if (arg1 == NULL || arg2 == NULL) {
                    fprintf(stderr, "Usage: %s write <filename> <content>\n", argv[0]);
                    exit(1);
                }
                write_to_file(arg1, arg2);
            } else if (strcmp(task, "create") == 0) {
                if (arg1 == NULL) {
                    fprintf(stderr, "Usage: %s create <filename>\n", argv[0]);
                    exit(1);
                }
                create_file(arg1);
            } else if (strcmp(task, "alert") == 0) {
                if (arg1 == NULL) {
                    fprintf(stderr, "Usage: %s alert <duration>\n", argv[0]);
                    exit(1);
                }
                int duration = atoi(arg1);
                continuous_sound_alert(duration);
            } else if (strcmp(task, "display") == 0) {
                if (arg1 == NULL) {
                    fprintf(stderr, "Usage: %s display <message>\n", argv[0]);
                    exit(1);
                }
                display_content(arg1);
            } else {
                fprintf(stderr, "Error: Unknown task '%s'\n", task);
                exit(1);
            }
            exit(0);  // Child process exits after completing its task
        }
    }

    // Parent process waits for all child processes to finish
    while (wait(NULL) > 0);

    return 0;
}

