// Server side C/C++ program to demonstrate Socket programming
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;

#define pose_read_data_cmd 0
#define pose_read_data_1 1
#define pose_read_data_2 2
#define pose_read_data_3 3
#define pose_read_data_4 4

#define pose_read_data_cmd 0
#define pose_read_data_1 1
#define pose_read_data_2 2
#define pose_read_data_3 3
#define pose_read_data_4 4
#define pose_read_w_0 5
#define pose_read_w_1 6
#define pose_read_w_2 7
#define pose_read_w_3 8
#define pose_read_w_4 9
#define pose_read_w_5 10
#define pose_read_w_6 11
#define pose_read_w_7 12
#define pose_read_w_8 13
#define pose_read_w_9 14
#define pose_read_w_10 15
#define pose_read_w_11 16
#define pose_read_w_12 17
#define pose_read_w_13 18
#define pose_read_w_14 19
#define pose_read_w_15 20
#define pose_read_w_16 21
#define pose_read_w_17 22
#define pose_read_w_18 23
#define pose_read_w_19 24
#define pose_read_w_20 25
#define pose_read_w_21 26
#define pose_read_w_22 27
#define pose_read_w_23 28
#define pose_read_w_24 29

#define pose_write_cmd 0
#define pose_write_data_1 1
#define pose_write_data_2 2
#define pose_write_data_3 3
#define pose_write_data_4 4
#define pose_write_data_5 5
#define pose_write_w_0 6
#define pose_write_w_1 7
#define pose_write_w_2 8
#define pose_write_w_3 9
#define pose_write_w_4 10

#define pose_write_cmd 0
#define pose_write_status 1

/*
00F2
000A0000000000000000
11
00
00
00
00
00
00
00
00
11
  */

uint16_t req_read_gent[5];

uint16_t req_read_data_cmd = 0xF100;
uint16_t req_read_data_1 = 0x1000;
uint16_t req_read_data_2 = 0x1000;
uint16_t req_read_data_3 = 0x1000;
uint16_t req_read_data_4 = 0x1000;

uint16_t res_read_gent[30];

uint16_t res_read_data_cmd = 0x1F00;
uint16_t res_read_data_1;
uint16_t res_read_data_2;
uint16_t res_read_data_3;
uint16_t res_read_data_4;
uint16_t res_read_w_0;
uint16_t res_read_w_1;
uint16_t res_read_w_2;
uint16_t res_read_w_3;
uint16_t res_read_w_4;
uint16_t res_read_w_5;
uint16_t res_read_w_6;
uint16_t res_read_w_7;
uint16_t res_read_w_8;
uint16_t res_read_w_9;
uint16_t res_read_w_10;
uint16_t res_read_w_11;
uint16_t res_read_w_12;
uint16_t res_read_w_13;
uint16_t res_read_w_14;
uint16_t res_read_w_15;
uint16_t res_read_w_16;
uint16_t res_read_w_17;
uint16_t res_read_w_18;
uint16_t res_read_w_19;
uint16_t res_read_w_20;
uint16_t res_read_w_21;
uint16_t res_read_w_22;
uint16_t res_read_w_23;
uint16_t res_read_w_24;
bool *test;
uint16_t req_write_gent[11];

uint64_t req_write_cmd = 0xF200;
uint16_t req_write_data_1 = 0xA000;
uint16_t req_write_data_2 = 0xB000;
uint16_t req_write_data_3 = 0xC000;
uint16_t req_write_data_4 = 0xD000;
uint16_t req_write_data_5 = 0xE000;
uint16_t req_write_w_0 = 0x100A;
uint16_t req_write_w_1 = 0x200A;
uint16_t req_write_w_2 = 0x300A;
uint16_t req_write_w_3 = 0x400A;
uint16_t req_write_w_4 = 0x500A;

uint16_t res_write_gent[2];

uint16_t res_write_cmd = 0x2F00;
uint16_t res_write_status;

#define PORT 80

bool *Dec2BinWord(uint16_t d)
{

	static bool b[16];
	int i = 0;
	while (d > 0)
	{
		b[i] = d % 2;
		d = d / 2;
		i++;
	}

	return b;
}
bool ReadBit(uint16_t Data, int Pose)
{
	bool Status;
	Status = Data & 1 << Pose;
	return Status;
}

uint16_t WriteBit(uint16_t &Data, bool Status, int Pose)
{
	if (Status == 1)
	{
		Data = Data | 1 << Pose;
	}
	else
	{
		Data = Data ^ 1 << Pose;
	}
	return Data;
}

int WriteOutputGent(int SocketIP, int OutputSet)
{
	req_write_gent[pose_write_cmd] = req_write_cmd;

	if (OutputSet == 1)
	{
		req_write_gent[pose_write_data_1] = req_write_data_1;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 2)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = req_write_data_2;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 3)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = req_write_data_3;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 4)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = req_write_data_4;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 5)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = req_write_data_5;
	}
	else
	{
		/* code */
	}
	req_write_gent[pose_write_w_0] = req_write_w_0;
	req_write_gent[pose_write_w_1] = req_write_w_1;
	req_write_gent[pose_write_w_2] = req_write_w_2;
	req_write_gent[pose_write_w_3] = req_write_w_3;
	req_write_gent[pose_write_w_4] = req_write_w_4;
	send(SocketIP, req_write_gent, 22, 0);
	bool ReadOk = 1;
	cout << " chuan bi roi ne " << endl;
	while (ReadOk)
	{
		cout << "doi tin nhan gent" << endl;
		read(SocketIP, res_write_gent, 2);

		cout << " gia tri nhan duoc ne " << res_write_gent << endl;
		if (res_write_gent[0] == 0x2F00 && res_write_gent[1] == 0x0000)
		{
			cout << "gui ok roi day" << endl;
			ReadOk = 0;
			break;
		}

		/* code */
	}

	//send(SocketIP,(const void *)&req_write_cmd,4,0);
}
int WriteOutputGentBit(int SocketIP, int OutputSet, uint16_t Data0, uint16_t Data1, uint16_t Data2, uint16_t Data3, uint16_t Data4)
{
	req_write_gent[pose_write_cmd] = req_write_cmd;

	if (OutputSet == 1)
	{
		req_write_gent[pose_write_data_1] = req_write_data_1;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 2)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = req_write_data_2;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 3)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = req_write_data_3;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 4)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = req_write_data_4;
		req_write_gent[pose_write_data_5] = 0;
	}
	else if (OutputSet == 5)
	{
		req_write_gent[pose_write_data_1] = 0;
		req_write_gent[pose_write_data_2] = 0;
		req_write_gent[pose_write_data_3] = 0;
		req_write_gent[pose_write_data_4] = 0;
		req_write_gent[pose_write_data_5] = req_write_data_5;
	}
	else
	{
		/* code */
	}
	req_write_gent[pose_write_w_0] = Data0;
	req_write_gent[pose_write_w_1] = Data1;
	req_write_gent[pose_write_w_2] = Data2;
	req_write_gent[pose_write_w_3] = Data3;
	req_write_gent[pose_write_w_4] = Data4;
	send(SocketIP, req_write_gent, 22, 0);
	bool ReadOk = 1;
	cout << " chuan bi roi ne " << endl;
	while (ReadOk)
	{
		cout << "doi tin nhan gent" << endl;
		read(SocketIP, res_write_gent, 2);

		//	cout << " gia tri nhan duoc ne " << res_write_gent << endl;
		if (res_write_gent[0] == 0x2F00 && res_write_gent[1] == 0x0000)
		{
			cout << "gui ok roi day" << endl;
			ReadOk = 0;
			break;
		}

		/* code */
	}
}
int ReadInputGent(int SocketIP, int InputRead)

{
	bool CheckSend = 0;
	bool CheckRead = 0;
	bool SendOk;
	uint16_t temp[30];
	req_read_gent[pose_read_data_cmd] = 0xF100;
	if (InputRead == 1)
	{
		req_read_gent[pose_read_data_1] = req_read_data_1;
		req_read_gent[pose_read_data_2] = 0;
		req_read_gent[pose_read_data_3] = 0;
		req_read_gent[pose_read_data_4] = 0;
	}
	else if (InputRead == 2)
	{
		req_read_gent[pose_read_data_1] = 0;
		req_read_gent[pose_read_data_2] = req_read_data_2;
		req_read_gent[pose_read_data_3] = 0;
		req_read_gent[pose_read_data_4] = 0;
	}
	else if (InputRead == 3)
	{
		req_read_gent[pose_read_data_1] = 0;
		req_read_gent[pose_read_data_2] = 0;
		req_read_gent[pose_read_data_3] = req_read_data_3;
		req_read_gent[pose_read_data_4] = 0;
	}
	else if (InputRead == 4)
	{
		req_read_gent[pose_read_data_1] = 0;
		req_read_gent[pose_read_data_2] = 0;
		req_read_gent[pose_read_data_3] = 0;
		req_read_gent[pose_read_data_4] = req_read_data_4;
	}
	else
	{
		/* code */
	}

	CheckSend = send(SocketIP, req_read_gent, 10, 0);
	for (size_t i = 0; i < 6; i++)
	{
		cout << "  Buffer" << i << " = " << req_read_gent[i];
	}
	cout << "send  xong roi ne" << endl;
	cout << "---------------------------------------------" << endl;
	if (CheckSend > 0)
	{
		SendOk = 1;
		while (SendOk)
		{
			CheckRead = read(SocketIP, temp, 60);
			if (CheckRead > 0)
			{
				if (temp[0] == 0x1F00 && temp[1] == 0x3200)
				{
					for (size_t i = 0; i < 30; i++)
					{
						res_read_gent[i] = temp[i];
					}
					res_read_data_cmd = res_read_gent[pose_read_data_cmd];
					res_read_data_1 = res_read_gent[pose_read_data_1];
					res_read_data_2 = res_read_gent[pose_read_data_2];
					res_read_data_3 = res_read_gent[pose_read_data_3];
					res_read_data_4 = res_read_gent[pose_read_data_4];
					res_read_w_0 = res_read_gent[pose_read_w_0];
					res_read_w_1 = res_read_gent[pose_read_w_1];
					res_read_w_2 = res_read_gent[pose_read_w_2];
					res_read_w_3 = res_read_gent[pose_read_w_3];
					res_read_w_4 = res_read_gent[pose_read_w_4];
					res_read_w_5 = res_read_gent[pose_read_w_5];
					res_read_w_6 = res_read_gent[pose_read_w_6];
					res_read_w_7 = res_read_gent[pose_read_w_7];
					res_read_w_8 = res_read_gent[pose_read_w_8];
					res_read_w_9 = res_read_gent[pose_read_w_9];
					res_read_w_10 = res_read_gent[pose_read_w_10];
					res_read_w_11 = res_read_gent[pose_read_w_11];
					res_read_w_12 = res_read_gent[pose_read_w_12];
					res_read_w_13 = res_read_gent[pose_read_w_13];
					res_read_w_14 = res_read_gent[pose_read_w_14];
					res_read_w_15 = res_read_gent[pose_read_w_15];
					res_read_w_16 = res_read_gent[pose_read_w_16];
					res_read_w_17 = res_read_gent[pose_read_w_17];
					res_read_w_18 = res_read_gent[pose_read_w_18];
					res_read_w_19 = res_read_gent[pose_read_w_19];
					res_read_w_20 = res_read_gent[pose_read_w_20];
					res_read_w_21 = res_read_gent[pose_read_w_21];
					res_read_w_22 = res_read_gent[pose_read_w_22];
					res_read_w_23 = res_read_gent[pose_read_w_23];
					res_read_w_24 = res_read_gent[pose_read_w_24];
					for (size_t i = 0; i < 30; i++)
					{
						cout << "Buffer" << i << " = " << res_read_gent[i] << endl;
					}
					cout << "read xong roi ne" << endl;
					cout << "---------------------------------------------" << endl;
					/* 			for (size_t i = 0; i < 24; i++)
			{
				cout << "res_read_gent " << i << " = " << res_read_gent[i] << endl;
			} */
					break;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}
int ReadInputGentBit(int SocketIP, int InputRead)
{
	//ReadInputGent(SocketIP,InputRead);
}
int Bin2DecWord(int n)
{
	int DecNumber = 0;
	int base = 1;
	int temp = n;
	while (temp)
	{
		int lastDigit = temp % 10;
		temp = temp / 10;
		DecNumber += lastDigit * base;
		base = base * 2;
	}
	cout << "Bin2Dec " << DecNumber << endl;
}

int main(int argc, char const *argv[])
{

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	uint16_t buffer[4] = {0};
	const char *hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		WriteOutputGent(new_socket, 1);
		ReadInputGent(new_socket, 1);
	}

	//WriteOutputGent(new_socket, 1);
	//WriteOutputGent(new_socket, 1);

	/* 	}
 */
	return 0;
}
