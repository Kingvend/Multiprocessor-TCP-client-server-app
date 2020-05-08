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
#include <iostream>
#include <algorithm>

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

struct StudentString
{
	std::string Name;
	std::string GroupNumber;
	std::string BirthDay;
	std::string tel;
	std::string FirstYear;
};

std::vector<Student> StudentList;
std::vector<StudentString> StudentStringList;

void CharToString()
{
	StudentStringList.clear();
	for(int i = 0; i < StudentList.size();i++)
	{
		StudentString SST;
		
		SST.Name = (const char*) StudentList[i].Name;
		SST.GroupNumber = (const char*) StudentList[i].GroupNumber;
		SST.BirthDay = (const char*) StudentList[i].BirthDay;
		SST.tel = (const char*) StudentList[i].tel;
		SST.FirstYear = (const char*) StudentList[i].FirstYear;
		StudentStringList.push_back(SST);
	}
}

bool sortName(StudentString k, StudentString j)
{
	return k.Name < j.Name;
}

bool sortGroup(StudentString k, StudentString j)
{
	return k.GroupNumber < j.GroupNumber;
}

bool sortBirth(StudentString k, StudentString j)
{
	return k.BirthDay < j.BirthDay;
}

bool sortTel(StudentString k, StudentString j)
{
	return k.tel < j.tel;
}

bool sortYear(StudentString k, StudentString j)
{
	return k.FirstYear < j.FirstYear;
}
int numSud = 5; // default number student

void clearBuf(char* buf)
{
	for(int i = 0; i < 256;i++)
		buf[i] = '\0';
}

Student ClearStudentBuf(Student StudentBuf);

int Func2 (int newS){
	char p, p1, s;
	
	int i, PointToList, j;
	int NumParam;
	char buf[256], b[256];
	char const *pchar;
	bool Check;
	std::string st;
	Student StudentBuf;
	while(true) {
		clearBuf(buf);
		clearBuf(b);
		fflush(stdin); fflush(stdout);
		std::vector<Student> StudentListFilter;
		recv(newS, buf, sizeof(buf), 0);
		printf("%s\n", buf);
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
				//std::cout << "st: "<< st << std::endl;
				//printf("%s%lu\n", "real size: ", StudentList.size());
				pchar = st.c_str();
				//printf("%s%s\n", "pchar: ", pchar);
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
				recv(newS, buf, sizeof(buf), 0);
					NumParam = atoi(buf);
					if(NumParam < 1 || NumParam > 5)
					{
						//stop
						st = std::to_string(1);	
						pchar = st.c_str();
						strcpy(buf, pchar);
						//printf("%s\n", buf);
						send(newS, buf, sizeof(buf), 0);
					}
					else
					{
						// ok
						st = std::to_string(0);	
						pchar = st.c_str();
						strcpy(buf, pchar);
						//printf("%s\n", buf);
						send(newS, buf, sizeof(buf), 0);
						switch(NumParam)
						{
							case 1:
								// Name
								recv(newS, buf, sizeof(buf), 0);
								//printf("%s\n", "TEST");
								//printf("%s%s\n","buf: ", buf);
								for(i = 0; i < StudentList.size(); i++)
								{
									Check = true;
									j = 0;
									strcpy(StudentBuf.Name,buf);
									while(StudentBuf.Name[j] != '\0')
									{
										if(StudentBuf.Name[j] != StudentList[i].Name[j])
										{
											Check = false;
										}
										j++;
									}
									//printf("%s%s\n","StudentBufName: ", StudentBuf.Name);
									//printf("%s%s\n","StudentListName: ", StudentList[i].Name);
									if(Check)
									{
										//printf("%s\n", "found!");
										StudentListFilter.push_back(StudentList[i]);
									}
								}
								st = std::to_string(StudentListFilter.size());	
								pchar = st.c_str();
								strcpy(buf, pchar);
								//printf("%s%s\n", buf, " number");
								send(newS, buf, sizeof(buf), 0);
								for (i = 0; i < StudentListFilter.size(); i++)
								{
									strcpy(buf, StudentListFilter[i].Name);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].GroupNumber);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].BirthDay);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].tel);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].FirstYear);
									send(newS, buf, sizeof(buf), 0);
								}
								StudentBuf = ClearStudentBuf(StudentBuf);

								strcpy(buf, "FILTERING ENDED");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
							case 2:
								// Group
								recv(newS, buf, sizeof(buf), 0);
								//printf("%s\n", "TEST");
								//printf("%s%s\n","buf: ", buf);
								for(i = 0; i < StudentList.size(); i++)
								{
									Check = true;
									j = 0;
									strcpy(StudentBuf.GroupNumber,buf);
									while(StudentBuf.GroupNumber[j] != '\0')
									{
										if(StudentBuf.GroupNumber[j] != StudentList[i].GroupNumber[j])
										{
											Check = false;
										}
										j++;
									}
									//printf("%s%s\n","StudentBufName: ", StudentBuf.Name);
									//printf("%s%s\n","StudentListName: ", StudentList[i].Name);
									if(Check)
									{
										//printf("%s\n", "found!");
										StudentListFilter.push_back(StudentList[i]);
									}
								}
								st = std::to_string(StudentListFilter.size());	
								pchar = st.c_str();
								strcpy(buf, pchar);
								//printf("%s%s\n", buf, " number");
								send(newS, buf, sizeof(buf), 0);
								for (i = 0; i < StudentListFilter.size(); i++)
								{
									strcpy(buf, StudentListFilter[i].Name);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].GroupNumber);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].BirthDay);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].tel);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].FirstYear);
									send(newS, buf, sizeof(buf), 0);
								}
								StudentBuf = ClearStudentBuf(StudentBuf);

								strcpy(buf, "FILTERING ENDED");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
								break;

							case 3:
								// Birthday
								recv(newS, buf, sizeof(buf), 0);
								//printf("%s\n", "TEST");
								//printf("%s%s\n","buf: ", buf);
								for(i = 0; i < StudentList.size(); i++)
								{
									Check = true;
									j = 0;
									strcpy(StudentBuf.BirthDay,buf);
									while(StudentBuf.BirthDay[j] != '\0')
									{
										if(StudentBuf.BirthDay[j] != StudentList[i].BirthDay[j])
										{
											Check = false;
										}
										j++;
									}
									//printf("%s%s\n","StudentBufName: ", StudentBuf.Name);
									//printf("%s%s\n","StudentListName: ", StudentList[i].Name);
									if(Check)
									{
										//printf("%s\n", "found!");
										StudentListFilter.push_back(StudentList[i]);
									}
								}
								st = std::to_string(StudentListFilter.size());	
								pchar = st.c_str();
								strcpy(buf, pchar);
								//printf("%s%s\n", buf, " number");
								send(newS, buf, sizeof(buf), 0);
								for (i = 0; i < StudentListFilter.size(); i++)
								{
									strcpy(buf, StudentListFilter[i].Name);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].GroupNumber);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].BirthDay);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].tel);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].FirstYear);
									send(newS, buf, sizeof(buf), 0);
								}
								StudentBuf = ClearStudentBuf(StudentBuf);

								strcpy(buf, "FILTERING ENDED");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
								break;

							case 4:
								// tel
								recv(newS, buf, sizeof(buf), 0);
								//printf("%s\n", "TEST");
								//printf("%s%s\n","buf: ", buf);
								for(i = 0; i < StudentList.size(); i++)
								{
									Check = true;
									j = 0;
									strcpy(StudentBuf.tel,buf);
									while(StudentBuf.tel[j] != '\0')
									{
										if(StudentBuf.tel[j] != StudentList[i].tel[j])
										{
											Check = false;
										}
										j++;
									}
									//printf("%s%s\n","StudentBufName: ", StudentBuf.Name);
									//printf("%s%s\n","StudentListName: ", StudentList[i].Name);
									if(Check)
									{
										//printf("%s\n", "found!");
										StudentListFilter.push_back(StudentList[i]);
									}
								}
								st = std::to_string(StudentListFilter.size());	
								pchar = st.c_str();
								strcpy(buf, pchar);
								//printf("%s%s\n", buf, " number");
								send(newS, buf, sizeof(buf), 0);
								for (i = 0; i < StudentListFilter.size(); i++)
								{
									strcpy(buf, StudentListFilter[i].Name);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].GroupNumber);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].BirthDay);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].tel);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].FirstYear);
									send(newS, buf, sizeof(buf), 0);
								}
								StudentBuf = ClearStudentBuf(StudentBuf);

								strcpy(buf, "FILTERING ENDED");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
								break;
								
							case 5:
								// FirstYear
								recv(newS, buf, sizeof(buf), 0);
								//printf("%s\n", "TEST");
								//printf("%s%s\n","buf: ", buf);
								for(i = 0; i < StudentList.size(); i++)
								{
									Check = true;
									j = 0;
									strcpy(StudentBuf.FirstYear,buf);
									while(StudentBuf.FirstYear[j] != '\0')
									{
										if(StudentBuf.FirstYear[j] != StudentList[i].FirstYear[j])
										{
											Check = false;
										}
										j++;
									}
									//printf("%s%s\n","StudentBufName: ", StudentBuf.Name);
									//printf("%s%s\n","StudentListName: ", StudentList[i].Name);
									if(Check)
									{
										//printf("%s\n", "found!");
										StudentListFilter.push_back(StudentList[i]);
									}
								}
								st = std::to_string(StudentListFilter.size());	
								pchar = st.c_str();
								strcpy(buf, pchar);
								//printf("%s%s\n", buf, " number");
								send(newS, buf, sizeof(buf), 0);
								for (i = 0; i < StudentListFilter.size(); i++)
								{
									strcpy(buf, StudentListFilter[i].Name);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].GroupNumber);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].BirthDay);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].tel);
									send(newS, buf, sizeof(buf), 0);
									strcpy(buf, StudentListFilter[i].FirstYear);
									send(newS, buf, sizeof(buf), 0);
								}
								StudentBuf = ClearStudentBuf(StudentBuf);

								strcpy(buf, "FILTERING ENDED");
								printf("%s\n", buf);
								send(newS, buf, sizeof(buf), 0);
								break;
								break;							
						}
					}
			}
			break;

			case '6':
			// view sort
			{
				CharToString();
				recv(newS, buf, sizeof(buf), 0);
					NumParam = atoi(buf);
					if(NumParam < 1 || NumParam > 5)
					{
						//stop
						st = std::to_string(1);	
						pchar = st.c_str();
						strcpy(buf, pchar);
						//printf("%s\n", buf);
						send(newS, buf, sizeof(buf), 0);
					}
					else
					{
						// ok
						st = std::to_string(0);	
						pchar = st.c_str();
						strcpy(buf, pchar);
						//printf("%s\n", buf);
						send(newS, buf, sizeof(buf), 0);
						switch (NumParam)
						{
						case 1:
						{
							std::sort(StudentStringList.begin(),StudentStringList.end(), sortName);
							
						}
						break;	
						case 2:
						{
							std::sort(StudentStringList.begin(),StudentStringList.end(), sortGroup);
						}
						break;	
						case 3:
						{
							std::sort(StudentStringList.begin(),StudentStringList.end(), sortBirth);
						}
						break;	
						case 4:
						{
							std::sort(StudentStringList.begin(),StudentStringList.end(), sortTel);
						}
						break;	
						case 5:
						{
							std::sort(StudentStringList.begin(),StudentStringList.end(), sortYear);
						}
						break;						
						}
						st = std::to_string(StudentList.size());	
							pchar = st.c_str();
							strcpy(buf, pchar);
							send(newS, buf, sizeof(buf), 0);
							for (i = 0; i < StudentStringList.size(); i++)
							{
								pchar = StudentStringList[i].Name.c_str();
								strcpy(buf, pchar);
								send(newS, buf, sizeof(buf), 0);
								pchar = StudentStringList[i].GroupNumber.c_str();
								strcpy(buf, pchar);
								send(newS, buf, sizeof(buf), 0);
								pchar = StudentStringList[i].BirthDay.c_str();
								strcpy(buf, pchar);
								send(newS, buf, sizeof(buf), 0);
								pchar = StudentStringList[i].tel.c_str();
								strcpy(buf, pchar);
								send(newS, buf, sizeof(buf), 0);
								pchar = StudentStringList[i].FirstYear.c_str();
								strcpy(buf, pchar);
								send(newS, buf, sizeof(buf), 0);
							}
					}
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