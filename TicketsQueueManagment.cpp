#include <iostream>
#include "clsQueueLine.h"

using namespace std;

int main()
{
    clsQueueLine PlayBillsQueue("A0", 10);
    clsQueueLine SubscriptionsQueue("B0", 5);

    PlayBillsQueue.IssueTicket();
    PlayBillsQueue.IssueTicket();
    PlayBillsQueue.IssueTicket();

    cout << "\nPlay Bills Queue Info: \n";
    PlayBillsQueue.PrintInfo();
    PlayBillsQueue.PrintTicketsLineRTL();
    PlayBillsQueue.PrintTicketsLineLTR();

    PlayBillsQueue.PrintAllTicket();

    PlayBillsQueue.ServeNextClient();
    cout << "\nPlay Bills Queue After serving one Client\n";
    PlayBillsQueue.PrintInfo();

    cout << "\nSubscriptions Queue Info: \n";
    SubscriptionsQueue.IssueTicket();
    SubscriptionsQueue.IssueTicket();
    SubscriptionsQueue.IssueTicket();
    SubscriptionsQueue.IssueTicket();

    SubscriptionsQueue.PrintInfo();

    SubscriptionsQueue.PrintTicketsLineRTL();
    SubscriptionsQueue.PrintAllTicket();

    SubscriptionsQueue.ServeNextClient();
    cout << "\nSubscriptions Queue After serving one Client\n";
    SubscriptionsQueue.PrintInfo();



    system("pause>0");

}