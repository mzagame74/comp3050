// Copyright 2020 Matt Zagame
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>

int main(void) {
    pid_t pid, ppid;
    int ruid, rgid, euid, egid;
    int priority;
    char msg_buf[100];
    int msg_pipe[2];

    printf("\nThis is the Parent process report:\n");
    pid = getpid();     // process ID
    ppid = getppid();   // parent process ID
    ruid = getuid();    // real user ID
    euid = geteuid();   // effective user ID
    rgid = getgid();    // real group ID
    egid = getegid();   // effective group ID
    priority = getpriority(PRIO_PROCESS, 0);

    printf("\nPARENT:  Process ID is:\t\t%ld\n"
    "PARENT:  Process parent ID is:\t%ld\n"
    "PARENT:  Real UID is:\t\t%d\n"
    "PARENT:  Real GID is:\t\t%d\n"
    "PARENT:  Effective UID is:\t%d\n"
    "PARENT:  Effective GID is:\t%d\n"
    "PARENT:  Process priority:\t%d\n",
    (long)pid, (long)ppid, ruid, euid, rgid, egid, priority);

    printf("\nPARENT:  will now create a child, write pipe, and do a normal "
    "termination\n");

    // prepare pipe for communication between parent and child
    if (pipe(msg_pipe) < 0) {
        perror("\npipe(msg_pipe) failed, exiting");
        exit(1);
    }
    sprintf(msg_buf, "\nThis is the pipe message from the parent with PID "
    "%d\n", pid);

    // parent calls fork()
    switch (pid = fork()) {
        case -1:
            perror("\nfork() failed, exiting");
            exit(1);
        case 0:
            printf("\nThis is the Child process report:\n");
            // get child process IDs
            pid = getpid();
            ppid = getppid();
            ruid = getuid();
            euid = geteuid();
            rgid = getgid();
            egid = getegid();
            priority = getpriority(PRIO_PROCESS, 0);

            printf("\nCHILD:  Process ID is:\t\t%ld\n"
            "CHILD:  Process parent ID is:\t%ld\n"
            "CHILD:  Real UID is:\t\t%d\n"
            "CHILD:  Real GID is:\t\t%d\n"
            "CHILD:  Effective UID is:\t%d\n"
            "CHILD:  Effective GID is:\t%d\n"
            "CHILD:  Process priority:\t%d\n",
            (long)pid, (long)ppid, ruid, euid, rgid, egid, priority);

            printf("\nCHILD: about to read pipe and report parent message:\n");
            read(msg_pipe[0], msg_buf, sizeof(msg_buf));    // read from pipe
            printf("CHILD: parent's message is: %s\n", msg_buf);
            sleep(1);
            printf("CHILD: Process parent ID is now:   %d\n", getppid());
            printf("CHILD: ### Goodbye ###\n");
            exit(0);
        default:
            write(msg_pipe[1], msg_buf, sizeof(msg_buf));   // write to pipe
            printf("\nPARENT: created Child with PID %d\n", pid);
            printf("PARENT: ### Goodbye ###\n");
            exit(0);
    }
}
