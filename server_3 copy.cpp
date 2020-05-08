/*
 * server_3.cpp
 * 
 * Copyright 2020 Alex <alex@alex-pc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>

#define NAME_LENGTH 35
#define GROUP_NUMBER_LENGTH 20
#define BIRTHDAY_LENGTH 20
#define TEL_LENGTH 20
#define FIRST_YEAR_LENGTH 20

struct Student
{
	char Name[NAME_LENGTH];
	char GroupNumber[GROUP_NUMBER_LENGTH];
	char BirthDay[BIRTHDAY_LENGTH];
	char tel[TEL_LENGTH];
	char FirstYear[FIRST_YEAR_LENGTH];
};

std::vector<Student> StudentList;

int numSud = 5; // default number student

Student ClearStudentBuf(Student StudentBuf);

int Func2 (int newS){
	char p, p1, s;
	int i, PointToList;
	int NumParam;
	char buf[256], b[256];
	char const *pchar;
	std::string st;
	Student StudentBuf;
	while(true) {
		recv(newS, buf, sizeof(buf), 0);
		p = buf[0];
		switch(p)
		{
			case '1':
            // add
			{
				recv(newS, buf, sizeof(buf), 0);
				strcpy(StudentBuf.Name, buf);
				recv(newS, buf, sizeof(buf), 0);
				strcpy(StudentBuf.GroupNumber, buf);
				recv(newS, buf, sizeof(buf), 0);
				strcpy(StudentBuf.BirthDay, buf);
				recv(newS, buf, sizeof(buf), 0);
				strcpy(StudentBuf.tel, buf);
				recv(newS, buf, sizeof(buf), 0);
				strcpy(StudentBuf.FirstYear, buf);
				StudentList.push_back(StudentBuf);
				StudentBuf = ClearStudentBuf(StudentBuf);
				strcpy(buf, "New student has been added");
				printf("%s\n", buf);
				send(newS, buf, sizeof(buf), 0);
			}			
			break;

			case '2':
			// del	
			{
				st = std::to_string(StudentList.size());	
				pchar = st.c_str();
				strcpy(buf, pchar);
				send(newS, buf, sizeof(buf), 0);
				for (i = 0; i < StudentList.size(); i++)
				{
					strcpy(buf, StudentList[i].Name);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].GroupNumber);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].BirthDay);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].tel);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].FirstYear);
					send(newS, buf, sizeof(buf), 0);
				}
				recv(newS, buf, sizeof(buf), 0);
				PointToList = atoi(buf) -1;
				if(PointToList >= 0 && PointToList < StudentList.size())
				{
					StudentList.erase(StudentList.begin()+PointToList);
					strcpy(buf, "Student has been deleted");
					printf("%s\n", buf);
					send(newS, buf, sizeof(buf), 0);
				}
				else
				{
					strcpy(buf, "Student hasn't been deleted");
					printf("%s\n", buf);
					send(newS, buf, sizeof(buf), 0);
				}	
			}							
			break;

			case '3':
			// edit
			{
				st = std::to_string(StudentList.size());	
				pchar = st.c_str();
				strcpy(buf, pchar);
				send(newS, buf, sizeof(buf), 0);
				for (i = 0; i < StudentList.size(); i++)
				{
					strcpy(buf, StudentList[i].Name);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].GroupNumber);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].BirthDay);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].tel);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].FirstYear);
					send(newS, buf, sizeof(buf), 0);
				}
				recv(newS, buf, sizeof(buf), 0);
				PointToList = atoi(buf) -1;
				if(PointToList >= 0 && PointToList < StudentList.size())
				{
					//ok
					st = std::to_string(0);	
					pchar = st.c_str();
					strcpy(buf, pchar);
					printf("%s\n", buf);
					send(newS, buf, sizeof(buf), 0);
					// params
					recv(newS, buf, sizeof(buf), 0);
					NumParam = atoi(buf);
					if(NumParam < 1 || NumParam > 5)
					{
						//stop
						st = std::to_string(1);	
						pchar = st.c_str();
						strcpy(buf, pchar);
						printf("%s\n", buf);
						send(newS, buf, sizeof(buf), 0);
					}
					else
					{
						// ok
						st = std::to_string(0);	
						pchar = st.c_str();
						strcpy(buf, pchar);
						printf("%s\n", buf);
						send(newS, buf, sizeof(buf), 0);
						switch(NumParam)
						{
							case 1:
								// Name
								recv(newS, buf, sizeof(buf), 0);
								strcpy(StudentList[PointToList].Name, buf);
								strcpy(buf, "Edit has been Successful");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
							case 2:
								// Group
								recv(newS, buf, sizeof(buf), 0);
								strcpy(StudentList[PointToList].GroupNumber, buf);
								strcpy(buf, "Edit has been Successful");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
							case 3:
								// Birthday
								recv(newS, buf, sizeof(buf), 0);
								strcpy(StudentList[PointToList].BirthDay, buf);
								strcpy(buf, "Edit has been Successful");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
							case 4:
								// tel
								recv(newS, buf, sizeof(buf), 0);
								strcpy(StudentList[PointToList].tel, buf);
								strcpy(buf, "Edit has been Successful");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
							case 5:
								// FirstYear
								recv(newS, buf, sizeof(buf), 0);
								strcpy(StudentList[PointToList].FirstYear, buf);
								strcpy(buf, "Edit has been Successful");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;							
						}
					}
					
				}
				else
				{
					// stop
					st = std::to_string(1);	
					pchar = st.c_str();
					strcpy(buf, pchar);
					printf("%s\n", buf);
					send(newS, buf, sizeof(buf), 0);
				}
			}	
			break;

			case '4':
			//view all
			{
					st = std::to_string(StudentList.size());	
				pchar = st.c_str();
				strcpy(buf, pchar);
				send(newS, buf, sizeof(buf), 0);
				for (i = 0; i < StudentList.size(); i++)
				{
					strcpy(buf, StudentList[i].Name);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].GroupNumber);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].BirthDay);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].tel);
					send(newS, buf, sizeof(buf), 0);
					strcpy(buf, StudentList[i].FirstYear);
					send(newS, buf, sizeof(buf), 0);
				}
				}
			break;

			case '5':
			// view filter
			{
				
			}
			break;

			case '6':
			// view sort
			{

			}
			break;

			case '7':
			// exit
			 exit(0);			
		}
	}
}

void reaper(int sig)
{
	int status;
	while(wait3(&status, WNOHANG, (struct rusage*)0)>= 0);
}

Student ClearStudentBuf(Student StudentBuf)
{
	StudentBuf.Name[0] = '\0';
	StudentBuf.GroupNumber[0] = '\0';
	StudentBuf.BirthDay[0] = '\0';
	StudentBuf.tel[0] = '\0';
	StudentBuf.FirstYear[0] = '\0';
	return StudentBuf;
}

int main()
{
	#pragma region InitStartListStudent
	Student StudentBuf;
	strcpy(StudentBuf.Name, "SIDOROV ANDREY PETROVICH");
	strcpy(StudentBuf.GroupNumber, "12");
	strcpy(StudentBuf.BirthDay, "26.05.1997");
	strcpy(StudentBuf.tel, "88005553535");
	strcpy(StudentBuf.FirstYear, "2012");
	StudentList.push_back(StudentBuf);
	StudentBuf = ClearStudentBuf(StudentBuf);

	strcpy(StudentBuf.Name, "SIDOROV PETR ANDREEVICH");
	strcpy(StudentBuf.GroupNumber, "12");
	strcpy(StudentBuf.BirthDay, "15.05.1999");
	strcpy(StudentBuf.tel, "88005553536");
	strcpy(StudentBuf.FirstYear, "2012");
	StudentList.push_back(StudentBuf);
	StudentBuf = ClearStudentBuf(StudentBuf);

	strcpy(StudentBuf.Name, "SIDOROVA ALENA ANTONOVNA");
	strcpy(StudentBuf.GroupNumber, "14");
	strcpy(StudentBuf.BirthDay, "14. 06.1999");
	strcpy(StudentBuf.tel, "88005553537");
	strcpy(StudentBuf.FirstYear, "2014");
	StudentList.push_back(StudentBuf);
	StudentBuf = ClearStudentBuf(StudentBuf);

	strcpy(StudentBuf.Name, "ALENOV PAVEL PETROVICH");
	strcpy(StudentBuf.GroupNumber, "14");
	strcpy(StudentBuf.BirthDay, "13.07.1999");
	strcpy(StudentBuf.tel, "88005553538");
	strcpy(StudentBuf.FirstYear, "2014");
	StudentList.push_back(StudentBuf);
	StudentBuf = ClearStudentBuf(StudentBuf);

	strcpy(StudentBuf.Name, "SAMOILOVA ANNA MIHAILOVNA");
	strcpy(StudentBuf.GroupNumber, "15");
	strcpy(StudentBuf.BirthDay, "12.08.1999");
	strcpy(StudentBuf.tel, "88005553539");
	strcpy(StudentBuf.FirstYear, "2015");
	StudentList.push_back(StudentBuf);
	StudentBuf = ClearStudentBuf(StudentBuf);
	#pragma endregion

	struct sockaddr_in local;
		int s, newS, rc;
		
		local.sin_family = AF_INET;
		local.sin_port = htons(7500);
		local.sin_addr.s_addr = htonl(INADDR_ANY);
		
		s = socket(AF_INET, SOCK_STREAM, 0);
		rc = bind(s, (struct sockaddr *)&local, sizeof(local));
		rc = listen(s, 5);
		(void) signal(SIGCHLD, reaper);
		while(true) {
			newS = accept(s, NULL, NULL);
			switch(fork()){
				case 0:
					(void)close(s);
					exit(Func2(newS));
				default:
					(void)close(newS);
			}
		}
	return 0;
}