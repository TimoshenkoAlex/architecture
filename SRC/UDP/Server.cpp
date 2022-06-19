#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

enum class event
{
	press_on,
	press_off,
	read_coords,
	trajectory_draw,
	transfer_date,
};

enum class states
{
	on,
	off,
	reading,
	drawing,
	transfering,
};

class cam_sys {
	states state;
public:

	void pevent(const event& input)
	{
		switch (input)
		{
		case event::press_on:
			f_on();
			state = states::on;
			break;

		case event::press_off:
			f_off();
			state = states::off;
			break;

		case event::read_coords:
			f_read_coords();
			state = states::reading;
			break;

		case event::trajectory_draw:
			f_trajectory_draw();
			state = states::drawing;
			break;

		case event::transfer_date:
			f_transfer_date();
			state = states::transfering;
			break;
		}
	}

	void f_on() {
		state = states::on;
		cout << "successfully" << endl;
		sendMessageToServ(System is on now);
	}

	void f_off() {
		state = states::off;
		cout << "successfully" << endl;
		sendMessageToServ(System is off now);
	}

	void f_read_coords() {
		state = states::reading;
		cout << "successfully" << endl;
		sendMessageToServ(reading...);
	}

	void f_trajectory_draw() {
		state = states::drawing;
		cout << "successfully" << endl;
		sendMessageToServ(drawing...);
	}

	void f_transfer_date() {
		state = states::transfering;
		cout << "successfully" << endl;
		sendMessageToServ(transfering...);
	}

	void sendMessageToServ(string replyy)
	{
		int sock;
		struct sockaddr_in addr;
		sock = socket(AF_INET, SOCK_DGRAM, 0);

		addr.sin_family = AF_INET;
		addr.sin_port = htons(3425);
		addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		sendto(sock, replyy.c_str(), sizeof(replyy), 0, (struct sockaddr*)&addr, sizeof(addr));
		close(sock);
	}
};

class Controler
{
public:
	virtual event get_command() = 0;
};

class InternetCommand : public Controler
{
public:
	event get_command()
	{
		return event::press_off;
	}
};


class ConsoleCommand : public Controler
{
public:
	event get_command()
	{
		char c;

		while (true)
		{
			cin >> c;

			switch (c)
			{
			case '0':
				return event::press_off;

			case '1':
				return event::press_on;

			case '2':
				return event::read_coords;

			case '3':
				return event::trajectory_draw;

			case '4':
				return event::transfer_date;
			default:
				cout << "this command does not exist" << endl;

			}
		}
	}
};

int main() {
	cam_sys a;
	Controler* cmd;
	cmd = new ConsoleCommand();

	while (true)
	{
		event e = cmd->get_command();
		a.pevent(e);
	}
}