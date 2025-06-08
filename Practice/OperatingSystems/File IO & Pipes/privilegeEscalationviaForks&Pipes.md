# Privilege Escalation via Fork & Pipes

Some exploits use forked processes to manipulate file descriptors and escalate privileges.

#### How It Works

A malicious process forks into a child running with higher privileges.

Pipes are used to inject commands into a privileged process.

Example: Hijacking Privileged Execution
```
echo "malicious_command" > /proc/1234/fd/1
```
Impact: The attacker redirects output/input to a privileged process.
