#ifndef PATIENT_H 
#define PATIENT_H
#include <iostream>
#include <string>
#include "date.h"

struct Procedure
{
	Date dateOfProcedure;
	int procedureID;
	int procedureProviderID;
};

class Patient {
public:
	Patient(const char * ID = "SmithJohn1900", const char * firstName = "John", const char * lastName = "Smith", Date birthDate = { 1,1,1900 }, int docid = 0);
	//Put in default values just as in Date class 
	//Use the set functions so input values are checked   
	~Patient();
	Patient & setID(const char *);  //check if length of name string is < 32. 
									// if not, shorten to 32 letters. 

	Patient & setFirstName(const char *); //check if length of name string is <  
										  // 15, if not, shorten to 14 letters. 
	Patient & setLastName(const char *);  //check if length of name string is <  
										  // 15, if not, shorten to 14 letters. 
	Patient & setBirthDate(Date);
	Patient & setPrimaryDoctorID(int);

	const char * getID();
	const char * getFirstName();
	const char * getLastName();
	Date getBirthDate();
	int getPrimaryDoctorID();

	bool enterProcedure(Date procedureDate, int procedureID,
		int procedureProviderID);//tries to add a new entry to record array, returns  //true if added, false if cannot be added 
	void printAllProcedures(int mode);

private:
	char ID[100];
	char firstName[100];
	char lastName[100];
	Date  birthdate;
	int primaryDoctorID;
	Procedure record[100];
	int currentCountOfProcedures = 0;  // keeps track of how many procedures have //been recorded.  if it reaches 500, no new procedures can //be entered. 
};







#endif

