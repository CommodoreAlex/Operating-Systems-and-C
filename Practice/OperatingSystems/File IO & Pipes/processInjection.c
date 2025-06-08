pid_t pid = fork();
if (pid == 0) { 
    execve("/bin/malicious_payload", NULL, NULL); 
}
