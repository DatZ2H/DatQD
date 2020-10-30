// Server side C/C++ program to demonstrate Socket programming
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

using namespace std;
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

uint16_t req_read_data_cmd = 0x00F1;
uint16_t req_read_data_1 = 0x0001;
uint16_t req_read_data_2 = 0x0001;
uint16_t req_read_data_3 = 0x0001;
uint16_t req_read_data_4 = 0x0001;

uint16_t res_read_gent[30];

uint16_t res_read_data_cmd = 0x001F;
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

uint64_t req_write_cmd = 0x00F2;
uint16_t req_write_data_1 = 0x000A;
uint16_t req_write_data_2 = 0x000B;
uint16_t req_write_data_3 = 0x000C;
uint16_t req_write_data_4 = 0x000D;
uint16_t req_write_data_5 = 0x000E;
uint16_t req_write_w_0=0xA001;
uint16_t req_write_w_1=0xA002;
uint16_t req_write_w_2=0xA003;
uint16_t req_write_w_3=0xA004;
uint16_t req_write_w_4=0xA005;

uint16_t res_write_gent[2];

uint16_t res_write_cmd = 0x002F;
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
	req_write_gent[10] = req_write_cmd;

	if (OutputSet == 1)
	{
		req_write_gent[9] = req_write_data_1;
		req_write_gent[8] = 0;
		req_write_gent[7] = 0;
		req_write_gent[6] = 0;
		req_write_gent[5] = 0;
	}
	else if (OutputSet == 2)
	{
		req_write_gent[9] = 0;
		req_write_gent[8] = req_write_data_2;
		req_write_gent[7] = 0;
		req_write_gent[6] = 0;
		req_write_gent[5] = 0;
	}
	else if (OutputSet == 3)
	{
		req_write_gent[9] = 0;
		req_write_gent[8] = 0;
		req_write_gent[7] = req_write_data_3;
		req_write_gent[6] = 0;
		req_write_gent[5] = 0;
	}
	else if (OutputSet == 4)
	{
		req_write_gent[9] = 0;
		req_write_gent[8] = 0;
		req_write_gent[7] = 0;
		req_write_gent[6] = req_write_data_4;
		req_write_gent[5] = 0;
	}
	else if (OutputSet == 5)
	{
		req_write_gent[9] = 0;
		req_write_gent[8] = 0;
		req_write_gent[7] = 0;
		req_write_gent[6] = 0;
		req_write_gent[5] = req_write_data_5;
	}
	else
	{
		/* code */
	}
	req_write_gent[4]=req_write_w_0;
	req_write_gent[3]=req_write_w_1;
	req_write_gent[2]=req_write_w_2;
	req_write_gent[1]=req_write_w_3;
	req_write_gent[0]=req_write_w_4;
	send(SocketIP, req_write_gent, 22, 0);
	bool ReadOk=0;
	while (ReadOk)
	{
		read(SocketIP, res_write_gent, 4);
		if (res_write_gent[3]==0x002F)
		{
			for()
		}
		

		/* code */
	}
	

	//send(SocketIP,(const void *)&req_write_cmd,4,0);
	

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
	uint16_t h = 11;
	cout << "day la gia tri write =  " << WriteBit(h, 0, 1) << endl;
	cout << " gia tri cua H ===  == " << h << endl;
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
	uint16_t k = 17732;

	test = Dec2BinWord(k);
	for (size_t i = 0; i < 16; i++)
	{
		cout << "bit thu " << i << " : " << test[i] << endl;
	}
	Bin2DecWord(10101);

	while (1)
	{
		valread = read(new_socket, buffer, 10);
		cout << "day la buffer " << hex << buffer << endl;
		/* 	cout<<"buffer 0 : "<<buffer[0]<<endl;
	cout<<"buffer 1 : "<<buffer[1]<<endl;
	cout<<"buffer 2 : "<<buffer[2]<<endl;
	cout<<"buffer 3 : "<<buffer[3]<<endl;
	cout<<"buffer 4 : "<<buffer[4]<<endl; */
		for (int i = 0; i < 5; i++)
		{
			cout << "buffer " << i << " :aaa " << buffer[i] << endl;
			if (buffer[i] == 17732)
			{
				break;
			}
		}

		cout << "------------- : " << endl;
		WriteOutputGent(new_socket,1);
	}

	return 0;
}
