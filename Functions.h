#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//Author - Arnas Steponavicius - G00361891
//Header file that stores all the functions used.

int Menu(struct node* top, int option);
void AddPatient(struct node** top); 
void DisplayAllPatients(struct node* top);
void DisplaySpecificPatient(struct node* top);
void UpdatePatientDetails(struct node* top);
void DeletePatient(struct node* top, int pps);
void DeletePatientAtStart(struct node** top);
void GenerateStatistics(struct node* top);
void PrintPatientDetailsToFile(struct node* top);
void IsValidEmail(struct node* top, char email[20]);
int CheckPatients(struct node* top, int searchPps);
int PatientListLength(struct node* top);

#endif