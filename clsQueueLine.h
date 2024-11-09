#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <iomanip>
#include "clsDate.h"

using namespace std;

class clsQueueLine
{
	string _Prefix = "";
	short _AverageServeTime = 0;
	short _TotalTickets = 0;


	class clsTickets {

	private:
		string _Prefix;
		short _Number;
		string _TicketTime;
		short _WaitingClients = 0;
		short _AverageServeTime = 0;
		short _ExpectedSeveTime = 0;



	public:

		clsTickets(string Prefix, short Number, short AverageServeTime, short WaitingClients) {
			_Prefix = Prefix;
			_Number = Number;
			_TicketTime = clsDatee::DateToString(clsDate::GetSystemDate())
				+ " " + clsDate::GetSystemTime();
			_AverageServeTime = AverageServeTime;
			_WaitingClients = WaitingClients;
		}

		string FullNumber() {
			return _Prefix + to_string(_Number);
		}

		short Number() {
			return _Number;
		}

		string TicketTime() {
			return _TicketTime;
		}

		short WaitingClients() {
			return _WaitingClients;
		}

		short ExpectedSeveTime() {
			return (_AverageServeTime * _WaitingClients);
		}

		void Print() {
			cout << setw(37) << left << "" << "=================================\n\n";
			cout << setw(51) << left << "" << FullNumber() << "\n\n";
			cout << setw(45) << left << "" << _TicketTime << endl;
			cout << setw(45) << left << "" << "Wating Clients : " << _WaitingClients << endl;
			cout << setw(45) << left << "" << "Serve Time In\n";
			cout << setw(45) << left << "" << ExpectedSeveTime() << " Minutes\n\n";
			cout << setw(37) << left << "" << "=================================\n\n";
		}

	};


public:
	queue <clsTickets> QueueLine;

	clsQueueLine(string Prefix, short AverageServeTime) {
		_Prefix = Prefix;
		_TotalTickets = 0;
		_AverageServeTime = AverageServeTime;
	}

	void IssueTicket() {
		_TotalTickets++;
		clsTickets Tickets(_Prefix, _TotalTickets, _AverageServeTime, WaitingClients());

		QueueLine.push(Tickets);

	}

	string WhoIsNext() {
		if (QueueLine.empty())
			return "No Clients Left.";
		else
			return QueueLine.front().FullNumber();

	}

	short WaitingClients() {
		return QueueLine.size();
	}

	short ServedClients() {
		return _TotalTickets - QueueLine.size();
	}

	void PrintInfo() {
		cout << setw(37) << left << "" << "*********************************\n";
		cout << setw(37) << left << "" << "\t\tQueue Info \n";
		cout << setw(37) << left << "" << "*********************************\n\n";
		cout << setw(45) << left << "" << "Prefix = " << _Prefix << "\n";
		cout << setw(45) << left << "" << "TotalTickets = " << _TotalTickets << "\n";
		cout << setw(45) << left << "" << "ServedClients = " << ServedClients() << "\n";
		cout << setw(45) << left << "" << "WatingClients = " << WaitingClients() << "\n";
		cout << setw(37) << left << "" << "*********************************\n\n";

	}

	bool ServeNextClient() {
		if (QueueLine.empty()) {
			cout << endl;
			cout << setw(30) << left << "" << "There No Client to Serve? \n";
			return false;
		}

		QueueLine.pop();
		return true;

	}

	bool PrintAllTicket() {
		cout << "\n\n";
		cout << setw(45) << left << "" << " ---Tickets---\n\n";

		if (QueueLine.empty()) {
			cout << setw(45) << left << "" << " ---No Tickets---\n\n";
			return false;
		}


		queue <clsTickets> Temp = QueueLine;
		while (!Temp.empty()) {
			Temp.front().Print();
			Temp.pop();
		}
	}

	bool PrintTicketsLineRTL() {
		if (QueueLine.empty()) {
			cout << setw(30) << left << "" << " ---No Tickets---\n\n";
			return false;
		}
		else {
			cout << "\n\n";
			cout << setw(30) << left << "" << "Tickets: ";

		}

		queue <clsTickets> Temp = QueueLine;

		while (!Temp.empty()) {
			cout << Temp.front().FullNumber() << " <-- ";
			Temp.pop();
		}
		cout << "\n";
		return true;
	}

	bool PrintTicketsLineLTR() {
		if (QueueLine.empty()) {
			cout << setw(30) << left << "" << " ---No Tickets---\n\n";
			return false;
		}
		else {
			cout << "\n\n";
			cout << setw(30) << left << "" << "Tickets: ";

		}

		queue <clsTickets> TempQueueLine = QueueLine;
		stack <clsTickets> TempStackLine;

		while (!TempQueueLine.empty()) {
			TempStackLine.push(TempQueueLine.front());
			TempQueueLine.pop();
		}


		while (!TempStackLine.empty()) {

			cout << " " << TempStackLine.top().FullNumber() << " --> ";
			TempStackLine.pop();
		}

		cout << "\n";
		return true;

	}





};

