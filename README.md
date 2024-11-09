# clsQueueLine: A C++ Ticketing System

`clsQueueLine` is a C++ class designed to simulate a ticketing system using queues. It provides functionality to issue tickets, manage a queue of clients, and display ticket information. This system is useful for managing queues in various service-oriented environments such as banks, hospitals, or customer service centers.

## Features

- **Ticket Issuance**: Generate tickets with a unique number and timestamp.
- **Queue Management**: 
  - Track the number of waiting and served clients.
  - Serve the next client in line.
- **Information Display**: 
  - Print detailed ticket information.
  - Display the queue of tickets in both left-to-right and right-to-left order.
- **Time Estimation**: Calculate expected service time based on average serve time and number of waiting clients.

## Class Overview

### clsQueueLine

- **Constructor**: Initializes the queue with a prefix and average serve time.
- **Methods**:
  - `IssueTicket()`: Issues a new ticket and adds it to the queue.
  - `WhoIsNext()`: Returns the ticket number of the next client to be served.
  - `WaitingClients()`: Returns the number of clients currently waiting.
  - `ServedClients()`: Returns the number of clients that have been served.
  - `PrintInfo()`: Displays information about the queue.
  - `ServeNextClient()`: Serves the next client in the queue.
  - `PrintAllTicket()`: Prints all tickets currently in the queue.
  - `PrintTicketsLineRTL()`: Prints the queue of tickets from right to left.
  - `PrintTicketsLineLTR()`: Prints the queue of tickets from left to left.

### clsTickets (Nested Class)

- **Constructor**: Initializes a ticket with a prefix, number, average serve time, and number of waiting clients.
- **Methods**:
  - `FullNumber()`: Returns the full ticket number including the prefix.
  - `TicketTime()`: Returns the time the ticket was issued.
  - `ExpectedSeveTime()`: Calculates the expected service time for the ticket.
  - `Print()`: Prints detailed information about the ticket.

## Usage

To use the `clsQueueLine` class, include the `clsQueueLine.h` file in your project and create an instance of the class. Use the provided methods to manage the queue and display ticket information.

```cpp
#include "clsQueueLine.h"

int main() {
    clsQueueLine queue("A", 5); // Prefix 'A', average serve time 5 minutes
    queue.IssueTicket();
    queue.PrintInfo();
    queue.PrintAllTicket();
    queue.ServeNextClient();
    return 0;
}
