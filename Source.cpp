#include <iostream>
#include <fstream>
#include <string>
#include "date.h"
#include "patient.h"
#pragma warning( disable : 4996 )
//#define _SCL_SECURE_NO_WARNINGS
using namespace std;

//checks in a new patient into the checked in patient array
void checkInPatientNew(char * fname, char * lname, char * pID, Date bdate, int doctorID, Patient checkedIn[], Patient patientList[], int checkedInCount, int patientListCount);
//checks in a returning patient, after looking them up in the main array, into the checked in patient array
bool checkInPatientReturning(char * pID, Patient checkedIn[], Patient patientList[], int checkedInCount, int patientListCount);
//adds a procedure to a patient in the checked in array, if patient cannot be found in this array asks for user to check in patient
bool checkOutPatient(char *pID, int procedureID, Date date, int providerID, Patient checkedIn[], Patient patientList[], int checkedInCount, int patientListCount);
//prints a patients info
void printPatientInfo(char * pID, Patient patientlist[], int patientListCount);
//prints out all checked in patients info
void printCheckIn(Patient checkedIn[], int checkedInCount);


int main() {
	bool endFinal = false;
	string line;
	char * patientId = new char[100];
	char * fname = new char[30];
	char * lname = new char[30];
	int date[3], month, day, year, count = 0, patientcount = 0, checkedInCount = 0, doctorId, procedureID, providerID, procedureCount = 0;
	Date birthdate, procedureDate;
	ifstream ifile;
	ofstream ofile;
	char choice;
	Patient checkedIn[50];
	Patient patientList[50];


	std::cout << "enter today's date mmddyyy : " << endl;
	std::cin >> date[0];
	std::cin >> date[1];
	std::cin >> date[2];

	Date today;
	today.setDate(date[0], date[1], date[2]);
	
	ifile.open("patients.dat", ios::in, ios::binary);
	if (ifile.is_open()) {
		ifile >> count;
		std::cout << count << " patients in main array loaded" << endl;
		for (int i = 0; i < count; i++) 
		{
			ifile >> patientId;
			std::cout << "patient ID :  " << patientId << endl;
			ifile >> fname;
			ifile >> lname;
			ifile >> date[0];
			ifile >> date[1];
			ifile >> date[2];
			birthdate.setDate(date[0], date[1], date[2]);
			
			ifile >> doctorId;
			//std::cout << "doc id : " << doctorId << endl;

			patientList[i].setID(patientId);
			patientList[i].setFirstName(fname);
			patientList[i].setLastName(lname);
			patientList[i].setBirthDate(birthdate);
			patientList[i].setPrimaryDoctorID(doctorId);

			ifile >> procedureCount;
			for (int j = 0; j < procedureCount; j++) {
				ifile >> date[0];
				ifile >> date[1];
				ifile >> date[2];
				ifile >> procedureID;
				ifile >> providerID;
				//std::cout << procedureID << endl;

				procedureDate.setDate(date[0], date[1], date[2]);
				patientList[i].enterProcedure(procedureDate, procedureID, providerID);
			}
		}
		
		ifile.close();
	}

	patientcount = count;
	do {
		std::cout << "------------------------------------------" << endl;
		std::cout << "\n        Patient Check-In       \n" << endl;
		std::cout << "------------------------------------------" << endl;

		std::cout << "\n N to check in New Patient" << endl;
		std::cout << " R to check in Returning Patient " << endl;
		std::cout << " O to check out a checked in patient " << endl;
		std::cout << " I to print a patients info " << endl;
		std::cout << " P to print out all checked in patients" << endl;
		std::cout << " Q to quit" << endl;

		std::cout << "\n------------------------------------------" << endl;

		std::cin >> choice;

		//
		if (choice == 'N') {
			std::cout << " Enter First Name : ";
			std::cin >> fname;
			//char *fsname = new char[14];
			//copy(fname+0, fname + 13, fsname);
			/*for (int i = 0; i < 13; i++) {
				fsname[i] = fname[i];
			}*/
			/*if (strlen(fname) > 15) {
				for (int i = 14; i < strlen(fname) + 1; i++) {
					fname[i] = 0;
				}
				cout << "\n shortened fname : " << fname << endl;
			}*/
			std::cout << " Enter Last name : ";
			std::cin >> lname;
			
			

			char * pID;
			char temp[200];

			if (strlen(fname) > 14) {
				for (int i = 15; i < strlen(fname); i++) {
				fname[i] = 0;
				std::cout << "first name too long, shortening" << endl;
				}
			}

			if (strlen(lname) > 14) {
				for (int i = 15; i < strlen(lname); i++) {
				lname[i] = 0;
				std::cout << "last name too long shortening" << endl;
				}
			}

			strcpy_s(temp, lname);
			//cout << "lname : " << lname << endl;
			strcat_s(temp, fname);
			//cout << "fname : " << fname << endl;
			char integer_string[100];
			//sprintf_s(integer_string, "%d", month);
			//strcat_s(temp, integer_string);
			//sprintf_s(integer_string, "%d", day);
			//strcat_s(temp, integer_string);
			std::cout << "\n  Enter birthdate mm dd yyyy : ";
			std::cin >> month;
			std::cin >> day;
			std::cin >> year;
			birthdate.setDate(month, day, year);
			//sprintf_s(integer_string, "%d", year);
			//strcat_s(temp, integer_string);
			//cout << "id: " << temp << endl;

			if (strlen(temp) > 33) {
				for (int i = 32; i < strlen(temp); i++) 
				{
				temp[i] = 0;
				std::cout << "ID too long, shortening" << endl;
				}
			}

			sprintf_s(integer_string, "%d", year);
			strcat_s(temp, integer_string);

			pID = temp;
			//cout << "pID : " << pID << endl;

			std::cout << " \n Enter doctor ID : ";
			std::cin >> doctorId;

			
			checkInPatientNew(fname, lname, pID, birthdate, doctorId, checkedIn, patientList, checkedInCount, patientcount);
			if (strcmp(checkedIn[checkedInCount].getFirstName(), fname) == 0) {
				std::cout << "patient checked in " << fname << " " << lname << " patient ID: " << checkedIn[checkedInCount].getID() <<  endl;
				checkedInCount++;
				patientcount++;
				//endFinal = true;
			}
			else {
				std::cout << "check in failed, try again" << endl;
			}
		}
		//
		else if (choice == 'R') {
			std::cout << "Enter Patient ID : ";
			std::cin >> patientId;
			if (checkInPatientReturning(patientId, checkedIn, patientList, checkedInCount, patientcount) == true)
			{	
				std::cout << "Patient Found and Checked In " << endl;
				checkedInCount++;
			}
			else 
			{
				std::cout << "check in failed, did you mean to check in a new patient? N to check in new or R to try again, T to return to main :  ";
				std::cin >> choice;

				/*if (choice == 'N') {
					std::cout << " Enter First Name : ";
					std::cin >> fname;
					std::cout << " Enter Last name : ";
					std::cin >> lname;

					std::cout << "\n  Enter birthdate mmddyyyy : ";
					std::cin >> month;
					std::cin >> day;
					std::cin >> year;
					birthdate.setDate(month, day, year);

					std::cout << " \n Enter doctor ID : ";
					std::cin >> doctorId;

					checkInPatientNew(fname, lname, p,  birthdate, doctorId, checkedIn, patientList, checkedInCount, patientcount);
					if (strcmp(checkedIn[checkedInCount].getFirstName(), fname) == 0) {
						std::cout << "patient checked in " << fname << endl;
						checkedInCount++;
						patientcount++;
						//endFinal = true;
					}
					else {
						std::cout << "check in failed, try again" << endl;
					}*/


				
				if (choice == 'R') {
					std::cout << "Enter Patient ID : ";
					std::cin >> patientId;
					if (checkInPatientReturning(patientId, checkedIn, patientList, checkedInCount, patientcount) == true) {
						std::cout << "Patient Found and Checked In " << endl;
						checkedInCount++;
						//patientcount++;
					}
				}
				else {
					std::cout << "returning to main menu " << endl;
				}
			}
		}
		//
		else if (choice == 'O') {
			std::cout << "\n Enter Patient ID : ";
			std::cin >> patientId;
			std::cout << "\n Enter procedure ID : ";
			int procedureID, providerID, doctorID;
			std::cin >> procedureID;
			std::cout << " \n Enter provider ID : ";
			std::cin >> providerID;
			std::cout << " \n Enter doctor ID : ";
			std::cin >> doctorID;

			if (checkOutPatient(patientId, procedureID, today, providerID, checkedIn, patientList, checkedInCount, patientcount) == true) {
				std::cout << "Patient Record Updated " << endl;
				checkedInCount--;

			}
			else {
				std::cout << "failed to update " << endl;

			}
			
		}
		//
		else if (choice == 'I') {
			std::cout << "Enter Patient ID : ";
			std::cin >> patientId;
			printPatientInfo(patientId, patientList, patientcount);

		}
		//
		else if (choice == 'P') {
			printCheckIn(checkedIn, checkedInCount);

		}
		//
		else if (choice == 'Q') {
			if (checkedInCount != 0) {
				std::cout << "please check out all patients before exit" << endl;
			}
			else {
				/*  make ostream */
				ofile.open("patients.dat", ios::binary); 
				if (ofile.is_open()) {
					ofile << patientcount << " ";
					for (int i = 0; i < patientcount; i++) {
						ofile << patientList[i].getID() << " " << patientList[i].getFirstName() << " " << patientList[i].getLastName() << " " << patientList[i].getBirthDate().getMonth() << " " << patientList[i].getBirthDate().getDay() << " " << patientList[i].getBirthDate().getYear() << " " << patientList[i].getPrimaryDoctorID() << " ";
						std::streambuf *psbuf, *backup;

						backup = std::cout.rdbuf();

						psbuf = ofile.rdbuf();        
						std::cout.rdbuf(psbuf);

						patientList[i].printAllProcedures(1);

						std::cout.rdbuf(backup);

						ofile << endl;
					}
				}
				
				endFinal = true;
			}

		}
		//
		else if (choice == 'G') {
			printCheckIn(patientList, patientcount);
		}

	} while (endFinal != true);




	//system("PAUSE");
	return 0;
}



void checkInPatientNew(char * fname, char * lname, char * pID, Date bdate, int doctorID, Patient checkedIn[], Patient patientList[], int checkedInCount, int patientListCount) 
{
	
	if (checkedInCount > 50) {
		std::cout << "\ncannot check in more patients" << endl;
		return;
	}

	/*char * pID;
	char temp[200];

	int month = bdate.getMonth();
	int day = bdate.getDay();
	int year = bdate.getYear();

	/*if (strlen(fname) > 14) {
		for (int i = 15; i < strlen(fname); i++) {
			fname[i] = 0;
			std::cout << "first name too long, shortening" << endl;
		}
	}

	if (strlen(lname) > 14) {
		for (int i = 15; i < strlen(lname); i++) {
			lname[i] = 0;
			std::cout << "last name too long shortening" << endl;
		}
	}

	strcpy_s(temp, lname);
	cout << "lname : " << temp << endl;
	strcat_s(temp, fname);
	cout << "fname : " << temp << endl;
	char integer_string[100];
	//sprintf_s(integer_string, "%d", month);
	//strcat_s(temp, integer_string);
	//sprintf_s(integer_string, "%d", day);
	//strcat_s(temp, integer_string);
	sprintf_s(integer_string, "%d", year);
	strcat_s(temp, integer_string);
	cout << "id: " << temp << endl;

	if (strlen(temp) > 33) {
			for (int i = 32; i < strlen(temp); i++) {
				temp[i] = 0;
				std::cout << "ID too long, shortening" << endl;
			}
		}

	pID = temp;
	cout << "pID : " << pID << endl;*/

	checkedIn[checkedInCount].setFirstName(fname);
	checkedIn[checkedInCount].setLastName(lname);
	checkedIn[checkedInCount].setBirthDate(bdate);
	checkedIn[checkedInCount].setPrimaryDoctorID(doctorID);
	checkedIn[checkedInCount].setID(pID);

	patientList[patientListCount].setFirstName(checkedIn[checkedInCount].getFirstName());
	patientList[patientListCount].setLastName(checkedIn[checkedInCount].getLastName());
	patientList[patientListCount].setBirthDate(checkedIn[checkedInCount].getBirthDate());
	patientList[patientListCount].setPrimaryDoctorID(checkedIn[checkedInCount].getPrimaryDoctorID());
	patientList[patientListCount].setID(checkedIn[checkedInCount].getID());


	/*std::cout << "patient checked in" << endl;
	std::cout << "id : " << checkedIn[checkedInCount].getID() << endl;
	std::cout << "main : " << patientList[patientListCount].getID() << endl;*/
	return;

};

bool checkInPatientReturning(char *pID, Patient checkedIn[], Patient patientList[], int checkedInCount, int patientListCount) {

	
	for (int i = 0; i < patientListCount; i++) {
		std::cout << patientList[i].getID() << endl;
		if (strcmp(patientList[i].getID(), pID) == 0) {
			std::cout << "\nfound" << endl;
			//checkedInCount++;
			checkedIn[checkedInCount].setFirstName(patientList[i].getFirstName());
			checkedIn[checkedInCount].setLastName(patientList[i].getLastName());
			checkedIn[checkedInCount].setBirthDate(patientList[i].getBirthDate());
			checkedIn[checkedInCount].setPrimaryDoctorID(patientList[i].getPrimaryDoctorID());
			checkedIn[checkedInCount].setID(patientList[i].getID());

			return true;
		}
	}
	std::cout << "\nno check in" << endl;
	return false;

};

bool checkOutPatient(char *pID, int procedureID, Date date, int providerID, Patient checkedIn[], Patient patientList[], int checkedInCount, int patientListCount) {
	for (int i = 0; i < checkedInCount; i++) {
		std::cout << checkedIn[i].getID() << endl;
		std::cout << pID << endl;
		if (strcmp(checkedIn[i].getID(), pID) == 0) {

			for (int j = 0; j < patientListCount; j++) {

				if (strcmp(patientList[j].getID(), pID) == 0) {

					patientList[j].setFirstName(checkedIn[i].getFirstName());
					patientList[j].setLastName(checkedIn[i].getLastName());
					patientList[j].setBirthDate(checkedIn[i].getBirthDate());
					patientList[j].setPrimaryDoctorID(checkedIn[i].getPrimaryDoctorID());
					patientList[j].setID(checkedIn[i].getID());
					patientList[j].enterProcedure(date, procedureID, providerID);

					std::cout << "\nprocedure added" << endl;

					for (int k = i; k < checkedInCount; k++) {
						checkedIn[k].setFirstName(checkedIn[k+1].getFirstName());
						checkedIn[k].setLastName(checkedIn[k+1].getLastName());
						checkedIn[k].setBirthDate(checkedIn[k+1].getBirthDate());
						checkedIn[k].setPrimaryDoctorID(checkedIn[k+1].getPrimaryDoctorID());
						checkedIn[k].setID(checkedIn[k+1].getID());

					}
					std::cout << "\npatient procedure updated, and patient " << pID << " checked out." << endl;
					return true;
				}
				/*else {
					std::cout << "\nupdate in main array failed" << endl;
					return false;
				}*/
			}
		}
	}
	std::cout << "\nupdate failed" << endl;
	return false;
};

void printPatientInfo(char * pID, Patient patientlist[], int patientListCount) {
	for (int i = 0; i < patientListCount; i++) {
		if (strcmp(patientlist[i].getID(), pID) == 0) {
			std::cout << "\n| --Patient Name : " << patientlist[i].getFirstName() << " " << patientlist[i].getLastName() << " --BirthDAte : " << patientlist[i].getBirthDate().getMonthString() << " " << patientlist[i].getBirthDate().getDay() << " " << patientlist[i].getBirthDate().getYear() << " --Patient Doctor :  " << patientlist[i].getPrimaryDoctorID() << " --|" << endl;
			patientlist[i].printAllProcedures(0);
			return;
		}
	}
	std::cout << "\nnot found" << endl;
	return;
};

void printCheckIn(Patient checkedIn[], int checkedInCount) {
	for (int i = 0; i < checkedInCount; i++) {
		std::cout << "\n|-- Patient ID : " << checkedIn[i].getID() << " --|" << endl;
		std::cout << "|-- Patient Name : " << checkedIn[i].getFirstName() << " " << checkedIn[i].getLastName() << " --|"<< endl;
		std::cout << "|-- Primary Doctor : " << checkedIn[i].getPrimaryDoctorID() << " --|" << endl;
		std::cout << endl;
	}

};


