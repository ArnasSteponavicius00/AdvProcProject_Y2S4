//G00361891 
//Arnas Steponavicius
//Advanced Procedural Programming Assignment 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "PatientDetails.h"
#include "Functions.h"

//main
void main()
{
	struct node* headPtr = NULL;
	FILE* loginFile;
	FILE* patientsFile;

	//variables
	time_t myTime;
	int choice = 0, inputsLogin = 0, patientInputs = 0, i = 0;
	char usernameCheck[20], passwordCheck[20];
	char username[20], password[20], hidePass;

	int pps = 0;
	char fname[20];
	char surname[20];
	int yearBorn = 0;
	char gender[10];
	char email[50];
	char nextKinName[30];
	char prevAppointment[9];
	float weight = 0;
	float height = 0;
	bool allergies = false;
	int cigarettesSmoked = 0;
	int alcoholUnits = 0;
	int exerciseAmount = 0;

	time(&myTime);

	printf("Current Time: %s\n", ctime(&myTime));
	printf("===========================================================\n");
	printf("||          ABC DENTAL PRACTICE PATIENT DATABASE         ||\n");
	printf("===========================================================\n");

	/*
		Open a file with details of user login information
		If file opens successfully ask user to input username and password,
		then using strcmp() compare whether entered information matches with what
		is stored in the file.
	*/
	loginFile = fopen("loginDatabase.txt", "r");
	patientsFile = fopen("patientDetails.txt", "r");

	if (loginFile == NULL)
	{
		printf("\nFile could not be opened!\n");
	}
	else
	{
		printf("Please enter username: ");
		scanf("%s", username);

		printf("Please enter password: ");


		/*Reference: http://www.c4learn.com/c-programs/how-to-input-password-in-c-validation.html */
		while (1) {
			hidePass = getch();

			if (hidePass == 13) //ASCII value of Enter
			{
				password[i] = '\0';
				printf("\n");
				break;
			}
			else if (hidePass == 8) //ASCII value of backspace
			{
				if (i > 0)
				{
					i--;
					printf("\b \b");
				}
			}
			else
			{
				password[i++] = hidePass;
				printf("* \b");
			}
		}

		while (!feof(loginFile))
		{
			inputsLogin = fscanf(loginFile, "%s %s", usernameCheck, passwordCheck);

			if (inputsLogin == 2)
			{
				if (strcmp(username, usernameCheck) == 0 && strcmp(password, passwordCheck) == 0)
				{
					printf("\nLogging in.....\n");
					printf("===========================================================\n");

					printf("All patients currently in the database.\n");
					printf("===========================================================\n");

					if (patientsFile == NULL)
					{
						printf("Database could not load or it is empty.\n");
					}
					else
					{
						while (!feof(patientsFile))
						{
							patientInputs = fscanf(patientsFile, "%d %s %s %d %s %s %s %s %.2fcm %.2fkg %d %d %d %d", &pps, fname, surname, &yearBorn, gender
								, email, nextKinName, &prevAppointment, &height, &weight, allergies, &cigarettesSmoked, &alcoholUnits, &exerciseAmount);

							if (patientInputs == 14)
							{
								fprintf(patientsFile, "%d %s %s %d %s %s %s %s %.2fcm %.2fkg %d %d %d %d\n", pps, fname, surname, yearBorn, gender
									, email, nextKinName, prevAppointment, height, weight, allergies, cigarettesSmoked, alcoholUnits, exerciseAmount);
							}
						}
					}

					Menu(headPtr, choice);
				}
			}
			else
			{
				printf("Login information does not match.");
			}
		}
		fclose(loginFile);
	}
}

//Create a new node and add patient details
void AddPatient(struct node** top)
{
	struct node* newNode;
	time_t currentTime, lastAppTime, timeSinceLast;

	//variables
	char allergy;
	int cigarettesSmoked = 0, alcoholUnits = 0, exerciseAmount = 0;
	int pps = 0, updatePatient = 0;
	float bmi = 0;
	int email = 0;

	currentTime = time(NULL);
	lastAppTime = time(NULL);

	ctime(&currentTime);

	printf("Enter PPS Number: ");
	scanf("%d", &pps);

	//checks if the pps number is already linked to a patient
	if (CheckPatients(*top, pps) == 1)
	{
		printf("The patient is already in the database.\n");

		printf("Would you like to update that patients details? 1 = Yes || 2 = No\n");
		scanf("%d", &updatePatient);

		if (updatePatient == 1)
		{
			UpdatePatientDetails(*top);
		}
		else if (updatePatient == 2)
		{
			return;
		}
		else
		{
			printf("\nPlease pick an option.\n");
		}

		return;
	}

	//allocate memory size of the node 
	newNode = (struct node*)malloc(sizeof(struct node));

	//Ask for patient information
	newNode->pps = pps;

	printf("First & Surname: ");
	scanf("%s %s", newNode->fname, newNode->surname);

	printf("Year Born: ");
	scanf("%d", &newNode->yearBorn);

	printf("Male(m) or Female(f): ");
	scanf("%s", newNode->gender);

	printf("Email : ");
	scanf("%s", newNode->email);

	IsValidEmail(*top, newNode->email);

	printf("Next of Kin : ");
	scanf("%s", newNode->nextKinName);

	printf("Previous Appointment (DD/MM/YYYY) : ");
	scanf("%s", newNode->prevAppointment);

	printf("Height in metres e.g 1.76 : ");
	scanf("%f", &newNode->height);

	printf("Weight in kg e.g 70 : ");
	scanf("%f", &newNode->weight);

	//Calculate BMI and store it
	newNode->bmi = (newNode->weight) / (newNode->height * newNode->height);

	printf("Allergies? y / n : ");
	scanf(" %c", &allergy);

	//set allergies to true if user enter 'y'
	if (allergy == 'y' || allergy == 'Y')
		newNode->allergies = true;
	else
		newNode->allergies = false;
	//end of if()

	printf("Cigarettes smoked per day: 1 (none) | 2 (less than 10) | 3 (more than 10): ");
	scanf("%d", &cigarettesSmoked);

	//assign value to (newNode->cigarettesSmoked) based on user choice, value will be used in BMI calc.
	if (cigarettesSmoked == 1)
	{
		newNode->cigarettesSmoked = 0;
	}
	else if (cigarettesSmoked == 2)
	{
		newNode->cigarettesSmoked = 5;
	}
	else if (cigarettesSmoked == 3)
	{
		newNode->cigarettesSmoked = 11;
	}//end of if()


	printf("Alcohol intake weekly: 1 (none) | 2 (less than 10) | 3 (more than 10): ");
	scanf("%d", &alcoholUnits);

	//assign value to (newNode->alcoholUnits) based on user choice, value will be used in BMI calc.
	if (alcoholUnits == 1)
	{
		newNode->alcoholUnits = 0;
	}
	else if (alcoholUnits == 2)
	{
		newNode->alcoholUnits = 5;
	}
	else if (alcoholUnits == 3)
	{
		newNode->alcoholUnits = 11;
	}//end of if()

	printf("Exercise: 1 = (never), 2 = (less than 2 times), 3 = (more than 2 times) per week: ");
	scanf("%d", &exerciseAmount);

	//assign value to (newNode->exerciseAmount) based on user choice, value will be used in BMI calc.
	if (exerciseAmount == 1)
	{
		newNode->exerciseAmount = 0;
	}
	else if (exerciseAmount == 2)
	{
		newNode->exerciseAmount = 1;
	}
	else if (exerciseAmount == 3)
	{
		newNode->exerciseAmount = 3;
	}//end of if()

	newNode->NEXT = *top;
	*top = newNode;

}//AddPatient()

//Display details of all patients, 1 row = 1 patient
void DisplayAllPatients(struct node* top)
{
	struct node* temp = top;
	int count = 0;

	//display message to show nodes are empty
	if (temp == NULL)
	{
		printf("There are currently no patients in the database\n");
	}

	//loop over node, display details and move onto the next node until next address = NULL
	while (temp != NULL)
	{
		count++;
		printf("%d: %d %s %s %d %s %s %s %s %.2fcm %.2fkg %d %d %d %d\n",
			count, temp->pps, temp->fname, temp->surname, temp->yearBorn, temp->gender, temp->email, temp->nextKinName
			, temp->prevAppointment, temp->height, temp->weight, temp->allergies, temp->cigarettesSmoked
			, temp->alcoholUnits, temp->exerciseAmount);


		temp = temp->NEXT;
	}


}//DisplayAllPatients()

//Display details of patient by entering their PPS number
void DisplaySpecificPatient(struct node* top)
{
	struct node* temp = top;

	int pps = 0, choice = 0;
	char first[20];
	char last[20];

	//ask user if they want to search by PPS or full name
	printf("Would you like to search for patient using PPS (1) or by Name (2)?\n");
	scanf("%d", &choice);

	if (choice == 1)
	{
		printf("Enter PPS Number of Patient: ");
		scanf("%d", &pps);
	}
	else if (choice == 2)
	{
		printf("Please enter patients first and last name: \n");
		scanf("%s %s", first, last);
	}
	else
	{
		//exit if choice is invalid
		printf("\nInvalid Choice.\n");
		return;
	}

	//checks if the pps number or name depending on users choice is already linked to a patient and displays their information	
	//loop over node, display details and move onto the next node until next address = NULL
	while (temp != NULL)
	{
		if (pps == temp->pps || strcmp(temp->fname, first) == 0 && strcmp(temp->surname, last) == 0)
		{
			printf("PPS               : %d\n", temp->pps);
			printf("Name              : %s %s\n", temp->fname, temp->surname);
			printf("D.O.B             : %d\n", temp->yearBorn);
			printf("Gender            : %s\n", temp->gender);
			printf("Email             : %s\n", temp->email);
			printf("Next of Kin       : %s\n", temp->nextKinName);
			printf("Last Apointment   : %s\n", temp->prevAppointment);
			printf("Height & Weight   : %.2fcm %.2fkg\n", temp->height, temp->weight);
			printf("Allergies         : %d\n", temp->allergies); // Convert int value to bool
			printf("Cigarettes Smoked : %d\n", temp->cigarettesSmoked);
			printf("Alcohol Intake    : %d\n", temp->alcoholUnits);
			printf("Weekly Exercise   : %d\n", temp->exerciseAmount);

			return;

		}

		temp = temp->NEXT;
	}

}//DisplaySpecificPatient()

//Update the details of the patient by searching for their PPS or Name,
//Also call this function if user tries to add a patient but patient already exists.
void UpdatePatientDetails(struct node* top)
{
	struct node* temp = top;

	int pps = 0, choice = 0;
	int cigarettesSmoked = 0, alcoholUnits = 0, exerciseAmount = 0;
	char allergy;
	char first[20];
	char last[20];

	//ask user if they want to search by PPS or full name
	printf("Enter patient PPS (1) or Name (2) that you wish to update.\n");
	scanf("%d", &choice);

	if (choice == 1)
	{
		printf("Enter PPS Number of Patient: ");
		scanf("%d", &pps);
	}
	else if (choice == 2)
	{
		printf("Please enter patients first and last name: \n");
		scanf("%s %s", first, last);
	}
	else
	{
		//exit if choice is invalid
		printf("\nInvalid Choice.\n");
		return;
	}

	if (pps == temp->pps || strcmp(temp->fname, first) == 0 && strcmp(temp->surname, last) == 0)
	{
		printf("PPS: ");
		scanf("%d", &temp->pps);

		printf("First & Surname: ");
		scanf("%s %s", temp->fname, temp->surname);

		printf("Year Born: ");
		scanf("%d", &temp->yearBorn);

		printf("Male(m) or Female(f): ");
		scanf("%s", temp->gender);

		printf("Email : ");
		scanf("%s", temp->email);

		printf("Next of Kin : ");
		scanf("%s", temp->nextKinName);

		printf("Previous Appointment (DD/MM/YYYY) : ");
		scanf("%s", temp->prevAppointment);

		printf("Height : ");
		scanf("%f", &temp->height);

		printf("Weight : ");
		scanf("%f", &temp->weight);

		printf("Allergies? y / n : ");
		scanf(" %c", &allergy);

		//set allergies to true if user enter 'y'
		if (allergy == 'y' || allergy == 'Y')
			temp->allergies = true;
		else
			temp->allergies = false;
		//end of if()

		printf("Cigarettes smoked per day: 1 (none) | 2 (less than 10) | 3 (more than 10): ");
		scanf("%d", &cigarettesSmoked);

		//assign value to (newNode->cigarettesSmoked) based on user choice, value will be used in BMI calc.
		if (cigarettesSmoked == 1)
		{
			temp->cigarettesSmoked = 0;
		}
		else if (cigarettesSmoked == 2)
		{
			temp->cigarettesSmoked = 5;
		}
		else if (cigarettesSmoked == 3)
		{
			temp->cigarettesSmoked = 11;
		}//end of if()


		printf("Alcohol intake weekly: 1 (none) | 2 (less than 10) | 3 (more than 10): ");
		scanf("%d", &alcoholUnits);

		//assign value to (newNode->alcoholUnits) based on user choice, value will be used in BMI calc.
		if (alcoholUnits == 1)
		{
			temp->alcoholUnits = 0;
		}
		else if (alcoholUnits == 2)
		{
			temp->alcoholUnits = 5;
		}
		else if (alcoholUnits == 3)
		{
			temp->alcoholUnits = 11;
		}//end of if()

		printf("Exercise: 1 = (none), 2 = (less than 2 times), 3 = (more than 2 times) per week: ");
		scanf("%d", &exerciseAmount);

		//assign value to (newNode->exerciseAmount) based on user choice, value will be used in BMI calc.
		if (exerciseAmount == 1)
		{
			temp->exerciseAmount = 0;
		}
		else if (exerciseAmount == 2)
		{
			temp->exerciseAmount = 1;
		}
		else if (exerciseAmount == 3)
		{
			temp->exerciseAmount = 3;
		}//end of if()

	}

	temp = temp->NEXT;
}

/*
  This function is needed, so when there is only 1 node (determined by finding size of list using a function),
  this one is used instead of the delete at pps.
  As that function will throw out an initialization error if only 1 node is present in the list.
*/
void DeletePatientAtStart(struct node** top)
{
	//Deletes patient at start of list.
	struct node* temp;

	temp = *top;

	*top = temp->NEXT;

	free(temp);
}

//Deletes a patient at user entered PPS if found
void DeletePatient(struct node* top, int pps)
{

	int found = 0;
	struct node* temp;
	struct node* prev_temp;

	temp = top;

	while (temp != NULL)
	{
		if (pps == temp->pps)
		{
			found = 1;
			break;
		}
		prev_temp = temp;
		temp = temp->NEXT;
	}

	if (found == 1)
	{
		prev_temp->NEXT = temp->NEXT;
		free(temp);
	}
}

void GenerateStatistics(struct node* top)
{
	struct node* temp = top;
	//variables
	int choice = 0, cigarettesSmoked = 0, exerciseAmount = 0;
	//counters for the bmi categories
	int countA = 0, countB = 0, countC = 0, countD = 0;

	printf("Calculate BMI based on Cigarettes smoked ( 1 ) or Exercise ( 2 )?\n");
	scanf("%d", &choice);

	//Generate stats based on Cigarettes if choice is 1,
	//If choice is 2 base it on Exercise.
	if (choice == 1)
	{
		printf("How many Cigarettes smoked per day?\n1: (none)\n2: (less than 10)\n3: (more than 10):\nEnter: ");
		scanf("%d", &cigarettesSmoked);

		if (cigarettesSmoked == 1)
		{
			while (temp != NULL)
			{
				if (temp->cigarettesSmoked == 0)
				{
					if (temp->bmi < 18.5)
					{
						countA++;
					}
					else if (temp->bmi > 18.6 || temp->bmi < 25)
					{
						countB++;
					}
					else if (temp->bmi > 25.1 || temp->bmi < 30)
					{
						countC++;
					}
					else if (temp->bmi > 30.1)
					{
						countD++;
					}
				}
				temp = temp->NEXT;
			}
		}
		else if (cigarettesSmoked == 2)
		{
			while (temp != NULL)
			{
				if (temp->cigarettesSmoked == 5)
				{
					if (temp->bmi < 18.5)
					{
						countA++;
					}
					else if (temp->bmi > 18.6 || temp->bmi < 25)
					{
						countB++;
					}
					else if (temp->bmi > 25.1 || temp->bmi < 30)
					{
						countC++;
					}
					else if (temp->bmi > 30.1)
					{
						countD++;
					}
				}
				temp = temp->NEXT;
			}
		}
		else if (cigarettesSmoked == 3)
		{
			while (temp != NULL)
			{
				if (temp->cigarettesSmoked == 11)
				{
					if (temp->bmi < 18.5)
					{
						countA++;
					}
					else if (temp->bmi > 18.6 || temp->bmi < 25)
					{
						countB++;
					}
					else if (temp->bmi > 25.1 || temp->bmi < 30)
					{
						countC++;
					}
					else if (temp->bmi > 30.1)
					{
						countD++;
					}
				}
				temp = temp->NEXT;
			}
		}
	}
	else if (choice == 2)
	{
		printf("How often do you exercise?\n1: (Never)\n2: (less than 2 times)3: (more than 2 times) per week\nEnter: ");
		scanf("%d", &exerciseAmount);

		if (exerciseAmount == 1)
		{
			while (temp != NULL)
			{
				if (temp->exerciseAmount == 0)
				{
					if (temp->bmi < 18.5)
					{
						countA++;
					}
					else if (temp->bmi > 18.6 || temp->bmi < 25)
					{
						countB++;
					}
					else if (temp->bmi > 25.1 || temp->bmi < 30)
					{
						countC++;
					}
					else if (temp->bmi > 30.1)
					{
						countD++;
					}
				}
				temp = temp->NEXT;
			}
		}
		else if (exerciseAmount == 2)
		{
			while (temp != NULL)
			{
				if (temp->exerciseAmount == 1)
				{
					if (temp->bmi < 18.5)
					{
						countA++;
					}
					else if (temp->bmi > 18.6 || temp->bmi < 25)
					{
						countB++;
					}
					else if (temp->bmi > 25.1 || temp->bmi < 30)
					{
						countC++;
					}
					else if (temp->bmi > 30.1)
					{
						countD++;
					}
				}
				temp = temp->NEXT;
			}
		}
		else if (exerciseAmount == 3)
		{
			while (temp != NULL)
			{
				if (temp->exerciseAmount == 3)
				{
					if (temp->bmi < 18.5)
					{
						countA++;
					}
					else if (temp->bmi > 18.6 || temp->bmi < 25)
					{
						countB++;
					}
					else if (temp->bmi > 25.1 || temp->bmi < 30)
					{
						countC++;
					}
					else if (temp->bmi > 30.1)
					{
						countD++;
					}
				}
				temp = temp->NEXT;
			}
		}
	}

	printf("===========================================================\n");
	printf("Patients with a BMI of less than 18.5: %d\n", countA);
	printf("Patients with a BMI of less than   25: %d\n", countB);
	printf("Patients with a BMI of less than   30: %d\n", countC);
	printf("Patients with a BMI of more than   30: %d\n", countD);
	printf("===========================================================\n");
}

void PrintPatientDetailsToFile(struct node* top)
{
	struct node* temp = top;
	FILE* patientDetails;

	patientDetails = fopen("patientDetails.txt", "a");

	if (patientDetails == NULL)
	{
		printf("Sorry the file could not be opened.\n");
	}
	else
	{
		while (temp != NULL)
		{
			fprintf(patientDetails, "%d %s %s %d %s %s %s %s %.2fcm %.2fkg %d %d %d %d\n",
				temp->pps, temp->fname, temp->surname, temp->yearBorn, temp->gender, temp->email, temp->nextKinName
				, temp->prevAppointment, temp->height, temp->weight, temp->allergies, temp->cigarettesSmoked
				, temp->alcoholUnits, temp->exerciseAmount);


			temp = temp->NEXT;
		}

		fclose(patientDetails);
	}
}

void IsValidEmail(struct node* top, char email[20])
{
	struct node* temp = top;
	int i = 0, verifyCount = 0, length;
	char at = '@', dot = '.', c = 'c', o = 'o', m = 'm';

	length = strlen(email);

	for (i = 0; i < length; i++)
	{
		if (email[i] == at)
		{
			verifyCount++;
			break;
		}
	}

	if (email[length - 4] == dot)
	{
		verifyCount++;
	}
	else if (email[length - 3] == c)
	{
		verifyCount++;
	}
	else if (email[length - 2] == o)
	{
		verifyCount++;
	}
	else if (email[length - 1] == m)
	{
		verifyCount++;
	}

	if (verifyCount == 5)
	{
		printf("Email Validated.\n");
	}
	/*	else
		{
			printf("Email is Invalid. Please re-enter email:\n");
			scanf("%s", temp->email);
		}
	*/
}

//Loops over the list and checks if the passed in pps matches and returns 1 to show it was found.
int CheckPatients(struct node* top, int searchPps)
{
	int found = 0;
	struct node* temp = top;

	while (temp != NULL)
	{
		if (temp->pps == searchPps)
		{
			found = 1;
			return found;
		}

		temp = temp->NEXT;
	}
	return found;
}

//Loop over the list and increment the count
int PatientListLength(struct node* top)
{
	struct node* temp;
	int count = 0;

	temp = top;

	while (temp != NULL)
	{
		count++;
		temp = temp->NEXT;
	}

	return count;
}

//Menu
int Menu(struct node* top, int option)
{
	//variables
	int pps = 0;

	option = 0;

	//Print Menu Options
	printf("===========================================================\n");
	printf("|| 1 = Add Patient                                       ||\n");
	printf("|| 2 = Display Details of all Patients                   ||\n");
	printf("|| 3 = Display Patient Details                           ||\n");
	printf("|| 4 = Update Patient Details                            ||\n");
	printf("|| 5 = Delete Patient                                    ||\n");
	printf("|| 6 = Generate Statistics                               ||\n");
	printf("|| 7 = Print Patient Details to file                     ||\n");
	printf("|| 8 = List patients in order of appointment             ||\n");
	printf("||-1 = Exit the program                                  ||\n");
	printf("===========================================================\n");
	printf("Enter: ");
	scanf("%d", &option);
	printf("===========================================================\n");


	//While loop that calls functions depending on users choice
	while (option != -1)
	{
		//call AddPatient() to make a new node and add the patients details
		if (option == 1)
		{
			printf("\nAdd patient\n");
			printf("===========================================================\n");
			AddPatient(&top);
		}
		//call DisplayAllPatients() to display all the patient details stored in the nodes in rows, 1 patient = 1 row
		else if (option == 2)
		{
			printf("\nDisplaying every patients details\n");
			printf("===========================================================\n");
			DisplayAllPatients(top);
		}
		//call DisplaySpecificPatient(), user enters a PPS number and if found that patients details are displayed
		else if (option == 3)
		{
			printf("\nDisplaying patient details\n");
			printf("===========================================================\n");
			DisplaySpecificPatient(top);
		}
		else if (option == 4)
		{
			printf("\nUpdate Patient details\n");
			printf("===========================================================\n");

			UpdatePatientDetails(top);

		}
		else if (option == 5)
		{
			printf("\nDelete Patient details\n");
			printf("===========================================================\n");

			printf("Please enter the PPS number of patient you wish to delete\n");
			scanf("%d", &pps);

			if (PatientListLength(top) == 0)
			{
				printf("\nThere are no patients in the database.\n");
			}
			else if (PatientListLength(top) == 1)
			{
				if (pps == top->pps)
				{
					DeletePatientAtStart(&top);
					printf("\nPatient Deleted - There are no more patients left\n");
				}
			}
			else
			{
				DeletePatient(top, pps);
				printf("\nPatient Deleted - There are %d patient records left.\n", PatientListLength(top));
			}
		}
		else if (option == 6)
		{
			printf("\nGenerate Patient statistics\n");
			printf("===========================================================\n");
			GenerateStatistics(top);
		}
		else if (option == 7)
		{
			printf("\nPrint Patient details to file\n");
			printf("===========================================================\n");
			printf("Printing details to file patientDetails.txt....");
			PrintPatientDetailsToFile(top);
			printf("\nDetails printed to file patientDetails.txt.\n");
		}
		else if (option == 8)
		{
			printf("\nList Patient in order of appointment\n");
			//time.h && sort algorithm
		}
		else
		{
			printf("\nInvalid choice - choose again\n");
		}

		printf("===========================================================\n");
		printf("|| 1 = Add Patient                                       ||\n");
		printf("|| 2 = Display Details of all Patients                   ||\n");
		printf("|| 3 = Display Patient Details                           ||\n");
		printf("|| 4 = Update Patient Details                            ||\n");
		printf("|| 5 = Delete Patient                                    ||\n");
		printf("|| 6 = Generate Statistics                               ||\n");
		printf("|| 7 = Print Patient Details to file                     ||\n");
		printf("|| 8 = List patients in order of appointment             ||\n");
		printf("||-1 = Exit the program                                  ||\n");
		printf("===========================================================\n");
		printf("Enter: ");
		scanf("%d", &option);
		printf("===========================================================\n");
	}

	return option;
}
