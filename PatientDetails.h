#ifndef PATIENTDETAILS_H
#define PATIENTDETAILS_H

//Author - Arnas Steponavicius - G00361891
//Header file that stores all the functions used.

//Struct
struct node {
	int pps;
	char fname[20];
	char surname[20];
	int yearBorn;
	char gender[10];
	char email[50];
	char nextKinName[30];
	char prevAppointment[9];
	float weight;
	float height;
	bool allergies = false;
	int cigarettesSmoked;
	int alcoholUnits;
	int exerciseAmount;
	float bmi;

	struct node* NEXT;
};

//Functions

#endif