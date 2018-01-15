#include "patient.h"
#include <iostream>
#include <string>

Patient::Patient(const char * id, const char * fName, const char * lName, Date bDate, int docID) {
	setID(id);
	setFirstName(fName);
	setLastName(lName);
	setBirthDate(bDate);
	setPrimaryDoctorID(docID);
}

Patient & Patient::setID(const char * id) {
	if (strlen(id) > 32) {

		strcpy_s(ID, id);
		return *this;
	}
	else {
		strcpy_s(ID, id);
	}
	return *this;
}

Patient & Patient::setFirstName(const char * fname) {
	if (strlen(fname) > 15) {

		strcpy_s(firstName, fname);
		return *this;
	}
	else {
		strcpy_s(firstName, fname);
	}

	return *this;

}

Patient & Patient::setLastName(const char * lname) {
	if (strlen(lname) > 15) {

		strcpy_s(lastName, lname);
		return *this;
	}
	else {
		strcpy_s(lastName, lname);
	}
	return *this;
}

Patient & Patient::setBirthDate(Date bdate) {
	birthdate = bdate;
	return *this;
}

Patient & Patient::setPrimaryDoctorID(int dID) {
	primaryDoctorID = dID;
	return *this;
}

const char * Patient::getID() {
	return ID;
}

const char * Patient::getFirstName() {
	return firstName;
}

const char * Patient::getLastName() {
	return lastName;
}

Date Patient::getBirthDate() {
	return birthdate;
}

int Patient::getPrimaryDoctorID() {
	return primaryDoctorID;
}
;
bool Patient::enterProcedure(Date procedureDate, int procedureID, int procedureProviderID)
{
	if (currentCountOfProcedures >= 500) {
		cout << "\n no more procedures can be added " << endl;
		return false;
	}

	Date temp;
	temp.setDate(procedureDate.getMonth(), procedureDate.getMonth(), procedureDate.getYear());

	record[currentCountOfProcedures].dateOfProcedure = temp;
	record[currentCountOfProcedures].procedureID = procedureID;
	record[currentCountOfProcedures].procedureProviderID = procedureProviderID;

	if (record[currentCountOfProcedures].procedureID == procedureID) {
		currentCountOfProcedures++;
		//std::cout << "procedure added : date : " << record[currentCountOfProcedures-1].dateOfProcedure << " procedure ID : " << record[currentCountOfProcedures-1].procedureID << " procedure Provider : " << record[currentCountOfProcedures-1].procedureProviderID << endl;
		return true;
	}
	else {
		std::cout << "procedure could not be added" << endl;
		return false;
	}
};//tries to add a new entry to record array, returns  //true if added, false if cannot be added 

void Patient::printAllProcedures(int mode) {
	if (mode == 1) {
		std::cout << currentCountOfProcedures << " ";
		for (int i = 0; i < currentCountOfProcedures; i++) {
			std::cout << record[i].dateOfProcedure.getMonth() << " " << record[i].dateOfProcedure.getDay() << " " << record[i].dateOfProcedure.getYear() << " " << record[i].procedureID << " " << record[i].procedureProviderID << " ";
		}
	}
	else if (mode == 0) {
		std::cout << "| List of Procedures for patient |" << endl;
		std::cout << "| ------------------------------ |" << endl;
		for (int i = 0; i < currentCountOfProcedures; i++) {
			std::cout << "|--date : " << record[i].dateOfProcedure << " --procedure id : " << record[i].procedureID << " --provider id : " << record[i].procedureProviderID <<" --|"  <<  endl;
			
		}
	}
	
	
	

};


Patient::~Patient() {}
