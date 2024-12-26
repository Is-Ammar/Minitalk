Minitalk Project
================

Overview
--------

Minitalk is a project that demonstrates inter-process communication in UNIX systems using signals. It consists of a client-server communication system where the server receives messages sent by the client one bit at a time using signals `SIGUSR1` and `SIGUSR2`. The server reconstructs the message and displays it, while the client sends these signals based on the message it wants to transmit.

This README provides a detailed explanation of the server and client implementations.

* * * * *

Server Implementation
---------------------

### Code Structure

The server is implemented in C and uses the `sigaction` system call to handle incoming signals. The program includes a global data structure `g_data` to keep track of the current character being constructed and the bit count.

### Global Data Structure

```
typedef struct s_data
{
	int				bit;
	int				bit_count;
	char			character;

}					t_data;
```

-   `**character**`: Temporarily stores the current character being built from the received bits.

-   `**bit_count**`: Keeps track of the number of bits received for the current character. A complete character is formed after 8 bits.

### Signal Handler

The `signal_handler` function processes incoming signals (`SIGUSR1` or `SIGUSR2`):

```
void signal_handler(int signum, siginfo_t *siginfo, void *context)
```

#### Parameters:

-   `**signum**`: The signal number (`SIGUSR1` or `SIGUSR2`).

-   `**siginfo**`: Contains additional information about the signal, such as the PID of the sender.

-   `**context**`: Not used in this implementation.

#### Functionality:

1.  **Bit Manipulation**: The received bit is shifted into the `character` field of `g_data`.

    -   `SIGUSR1` represents a binary `0`.

    -   `SIGUSR2` represents a binary `1`.

2.  **Character Completion**: Once 8 bits are received, the complete character is written to the standard output.

3.  **End of Message**: If a null character (`\0`) is received, it signals the end of the message. The server sends a confirmation signal (`SIGUSR2`) back to the client.

4.  **Reset State**: After processing a character, the `bit_count` and `character` are reset to receive the next character.

### Signal Registration

The server uses the `sigaction` system call to register the `signal_handler` for `SIGUSR1` and `SIGUSR2`.

```
struct sigaction sa;
sa = (struct sigaction){0};
sa.sa_sigaction = signal_handler;
sa.sa_flags = SA_SIGINFO;
sigemptyset(&sa.sa_mask);
sigaction(SIGUSR1, &sa, NULL);
sigaction(SIGUSR2, &sa, NULL);
```

-   `**SA_SIGINFO**`: Ensures that the `siginfo_t` structure is passed to the signal handler.

-   `**sigemptyset**`: Clears the signal set to ensure no other signals are blocked.

### Main Function

The `main` function initializes the server and waits for incoming signals:

1.  **Display PID**: Prints the server's PID to the console for the client to use.

2.  **Infinite Loop**: Uses `pause()` to wait indefinitely for signals.

* * * * *

Client Implementation
---------------------

### Code Structure

The client is implemented in C and handles the conversion of a message into signals sent to the server's PID. It ensures that the server receives the message bit by bit and handles server acknowledgments.

### Signal Sender

The `signal_send` function is responsible for sending the message, one bit at a time:

```
void signal_send(pid_t pid, unsigned char c)
```

#### Parameters:

-   `**pid**`: The server's process ID to which the signals are sent.

-   `**c**`: The character to be sent, encoded in 8 bits.

#### Functionality:

1.  **Bit Manipulation**: Extracts each bit of the character by shifting and masking.

2.  **Signal Transmission**:

    -   Sends `SIGUSR1` for a `0` bit.

    -   Sends `SIGUSR2` for a `1` bit.

3.  **Error Handling**: Validates the PID. If `kill` fails, an error message is displayed, and the program exits.

4.  **Delay**: Uses `usleep` to ensure signals are sent at a manageable pace.

### Signal Handler

The `handle_signal_back` function processes acknowledgment signals from the server:

```
void handle_signal_back(int signum)
```

#### Functionality:

-   Simply prints a message confirming that the server received the full message.

### Main Function

The `main` function validates input, sets up the signal handler, and sends the message to the server:

1.  **Argument Validation**: Ensures the correct number of arguments (`./client <server_PID> <message>`).

2.  **PID Conversion**: Converts the server's PID from string to integer and validates it.

3.  **Signal Handler Setup**: Registers `handle_signal_back` for `SIGUSR2`.

4.  **Message Transmission**: Iterates through each character in the message and sends it using `signal_send`.

5.  **End of Message**: Sends a null character (`\0`) to indicate the end of the message.

* * * * *

How to Use
----------

### Compilation

Compile the server and client with the following commands:

```
gcc -Wall -Wextra -Werror -o server server.c
gcc -Wall -Wextra -Werror -o client client.c
```

### Running the Server

Start the server by executing the compiled program:

```
./server
```

The server will display its PID:

```
Server PID: 12345
```

### Running the Client

Run the client with the server's PID and the message to be sent:

```
./client <server_PID> "Hello, World!"
```

Example:

```
./client 12345 "Hello, Minitalk!"
```

* * * * *
