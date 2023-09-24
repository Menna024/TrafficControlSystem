#include<iostream>
#include<string>

using namespace std;

#define MAXDRIVERS 5
#define MAXCARS 3 
#define MAXDETECTEDFINES 10
#define ROADSPEED 100

struct date {
	int day, month, year;
};

struct recordedFines {
	int value;
	string street;
	date fineDate;
	char status = 'N'; //'N' for Not Paid and 'P' for Paid
};

struct ownedCars {
	int plate;
	string model;
	int prodYear;
	int totalFines = 0;
	int howManyFines = 0;
	recordedFines fines[2];
};

struct drivers {
	int license;
	string name;
	date birthDate;
	int carNumbers;
	ownedCars cars[MAXCARS];
}driver[MAXDRIVERS];


void recordViolation(int storeFines[][3])
{
	char detectMore;
	int i = 0;
	do
	{
		cout << " Type the plate of the car : ";
		cin >> storeFines[i][0];
		cout << " Enter the speed of the car : ";
		cin >> storeFines[i][1];

		while ((storeFines[i][0] <= 0) || (storeFines[i][1] <= 0))
		{
		   cout << "\n XX Invalid input . XX" << endl;
		   cout << " XX Type the plate of the car again : ";
		   cin >> storeFines[i][0];
		   cout << " XX Enter the speed of the car again : ";
		   cin >> storeFines[i][1];
        }

		storeFines[i][2] = (storeFines[i][1] > ROADSPEED)? (2 * (storeFines[i][1] - ROADSPEED)) : 0 ;

		cout << "\n Is there more fines? (Y/N) : ";
		cin >> detectMore;
		i++;
	} while (detectMore == 'Y' || detectMore == 'y');
}

void getDriverInfo(int driverCounter) {
	cout << "Enter your license number : ";
	cin >> driver[driverCounter].license;
	cout << " Enter your name : ";
	cin.ignore();
	getline(cin, driver[driverCounter].name);
	cout << " Enter your birthdate (day/month/year) : ";
	cin >> driver[driverCounter].birthDate.day >> driver[driverCounter].birthDate.month >> driver[driverCounter].birthDate.year;

    while(((driver[driverCounter].birthDate.day > 30)||(driver[driverCounter].birthDate.day<1))||((driver[driverCounter].birthDate.month > 12) || (driver[driverCounter].birthDate.month < 1))
				||((driver[driverCounter].birthDate.year <1900) || (driver[driverCounter].birthDate.day > 2020)))
	{
		cout << "\n XX Invalid input of the date . XX"<< endl;
	    cout << " XX Enter your birthdate again (day/month/year) : ";
	    cin >> driver[driverCounter].birthDate.day >> driver[driverCounter].birthDate.month >> driver[driverCounter].birthDate.year;
    }

	cout << " Enter the number of owned cars : ";
	cin >> driver[driverCounter].carNumbers;
	cout << endl;
}

void getCarInfo(int driverCounter) 
{
	int count = 1;
	for (int i = 0; i < driver[driverCounter].carNumbers; i++, count++) {
		cout << " Enter the car plate number of car " << count << " : ";
		cin >> driver[driverCounter].cars[i].plate;
		
		while (driver[driverCounter].cars[i].plate<=0)
		{
			cout << "\n XX Invalid input.XX" << endl;
			cout << " XX Type the plate of the car again : ";
			cin >> driver[driverCounter].cars[i].plate;
		}

		cout << " Enter the model of car " << count << " : ";
		cin.ignore();
		getline(cin, driver[driverCounter].cars[i].model);
		cout << " Enter the production year of car " << count << " : ";
		cin >> driver[driverCounter].cars[i].prodYear;

		while ((driver[driverCounter].cars[i].prodYear <1900)||(driver[driverCounter].cars[i].prodYear>2020))
		{
			cout << " XX Invalid input of the production year of the car. XX" << endl;
			cout << " XX Enter the production year of car " << count << " again : ";
			cin >> driver[driverCounter].cars[i].prodYear;
		}
	}
}

void calculateTotalFines(int driverCounter)
{
	int* p1 = new int(0); //the dynamic variable stores the total value of fines the driver should pay

	for (int i = 0; i < driver[driverCounter].carNumbers; i++)
		*p1 += driver[driverCounter].cars[i].totalFines; 

	cout << "\n>> The value of total fines that should be paid is " << *p1 << "LE " << endl;
	delete p1;
	p1 = NULL;
}

void knowYourFine(int storeFines[][3], int driverCounter)
{
	for (int i = 0; i < driver[driverCounter].carNumbers; i++)
	{
		bool isThereFines = false;
		int k = -1;
		driver[driverCounter].cars[i].totalFines= 0;

		for (int j = 0; j < MAXDETECTEDFINES; j++)
		{
			if ((driver[driverCounter].cars[i].plate == storeFines[j][0]) && (storeFines[j][2] != 0)) //search if the plate of the car has any fines recorded against it or not
			{
				isThereFines = true;
				++k;
				driver[driverCounter].cars[i].fines[k].value = storeFines[j][2]; 
				cout << " The value of the fine recorded against car of plate number " << storeFines[j][0] << " is "<< storeFines[j][2] <<"LE"<< endl;
				driver[driverCounter].cars[i].totalFines += storeFines[j][2];
				driver[driverCounter].cars[i].howManyFines += 1;
			}
		}

		if (!isThereFines)
			cout << "\n No Fines were detected against car of plate number " << driver[driverCounter].cars[i].plate << endl;
	}
	calculateTotalFines(driverCounter);
}

	char payOneCar(int driverCounter) {
		int whichPlate;
		char payMore;
		bool isTheCarHis = false;

		cout << " Enter the plate number of the car you want to pay its fine : ";
		cin >> whichPlate;
		
		while (whichPlate <= 0)
		{
			cout << " XX Invalid input of car plate . XX" << endl;
			cout << " XX Enter the plate number of the car you want to pay its fine again : ";
			cin >> whichPlate;
		}

		for (int i = 0; i < driver[driverCounter].carNumbers; i++)
		{
			if (whichPlate != driver[driverCounter].cars[i].plate)
				continue;
		
				isTheCarHis = true;
				if (driver[driverCounter].cars[i].howManyFines > 0)
				{
					for (int j = 0; j < driver[driverCounter].cars[i].howManyFines; j++) 
					{
						driver[driverCounter].cars[i].fines[j].status = 'P';
						cout << " Your status is updated to " << driver[driverCounter].cars[i].fines[j].status;
						(driver[driverCounter].cars[i].fines[j].status == 'P')? cout << " PAID \n" : cout << " NOT PAID \n";
					}
				}
				else
					cout << " No fines were detected for car of plate " << driver[driverCounter].cars[i].plate << endl;
		}

		if (!isTheCarHis)
			cout << " XX You don't own this car. XX" << endl;

		cout << " Do you want to pay the fine of another car? (Y/N) :";
		cin >> payMore;
		return payMore;
	}

	bool outputSearchByName(string searchByName, int driverCounter) {
		bool isNameFound = false;
		for (int i = 0; i <= driverCounter; i++)
		{
			if (searchByName == driver[i].name)
			{
				isNameFound = true;
			    cout << "\n The license number of the driver is " << driver[i].license << "\n The birthdate of the driver is " << driver[i].birthDate.day << " / " << driver[i].birthDate.month << " / " << driver[i].birthDate.year<< "\n The number of owned cars is " << driver[i].carNumbers << endl;
				
				for (int j = 0; j < driver[i].carNumbers; j++)
				{ 
					cout << "\n The plate of the car is " << driver[i].cars[j].plate << "\n The model of the car is " << driver[i].cars[j].model << "\nThe production year of the car is " << driver[i].cars[j].prodYear << "\n The number of recorded fines is " << driver[i].cars[j].howManyFines << endl;
					
					for (int k = 0; k < driver[i].cars[j].howManyFines; k++)
					{
						cout << " The value of the fine is " << driver[i].cars[j].fines[k].value << "LE" << "\n The street where the fine was detected is " << driver[i].cars[j].fines[k].street << "\n The date when the fine was detected is " << driver[i].cars[j].fines[k].fineDate.day << " / " << driver[i].cars[j].fines[k].fineDate.month << " / " << driver[i].cars[j].fines[k].fineDate.year << endl;
					
						if (driver[i].cars[j].howManyFines != 0)
						{
							cout << " The status of the fine is " << driver[i].cars[j].fines[k].status;
							(driver[i].cars[j].fines[k].status == 'P') ? cout << "  (PAID) \n" : cout<<"  (NOT PAID) \n";
						}
						else if (driver[i].cars[j].howManyFines == 0)
							cout << " No status is found as there were no fines detected against this car ." << endl;
					}

					if (driver[i].cars[j].howManyFines > 1)
						cout << "\n The value of total fines is " << driver[i].cars[j].totalFines <<"LE"<< endl;
				}
			}
		}
		return isNameFound;
	}

	bool outputSearchByPlate(int searchByPlate) {
		bool isPlateFound = false;
		for (int i = 0; i < MAXDRIVERS; i++)
		{
			for (int j = 0; j < driver[i].carNumbers; j++)
			{
				if (searchByPlate == driver[i].cars[j].plate)
				{
					isPlateFound = true;
					cout << "\n The name of the driver is " << driver[i].name<< "\n The license number is " << driver[i].license << "\n The birthdate is " << driver[i].birthDate.day << " / " << driver[i].birthDate.month << " / " << driver[i].birthDate.year << "\n The model of the car is " << driver[i].cars[j].model<< "\n The production year of the car is " << driver[i].cars[j].prodYear<< "\n The number of fines recorded against the car is " << driver[i].cars[j].howManyFines << endl;
					
					for (int k = 0; k < driver[i].cars[j].howManyFines; k++)
					{
						cout << " The value of the fine is " << driver[i].cars[j].fines[k].value << "LE" << "\n The street where the fine was detected is " << driver[i].cars[j].fines[k].street<< "\n The date when the fine was detected is " << driver[i].cars[j].fines[k].fineDate.day << " / " << driver[i].cars[j].fines[k].fineDate.month << " / " << driver[i].cars[j].fines[k].fineDate.year << endl;
					
						if (driver[i].cars[j].howManyFines > 1)
							cout << "\n The value of totalfines is " << driver[i].cars[j].totalFines << "LE" << endl;

						if (driver[i].cars[j].howManyFines != 0)
						{
							cout << " The status of the car is " << driver[i].cars[j].fines[k].status;
							(driver[i].cars[j].fines[k].status == 'P') ? cout << "  (PAID) \n" : cout << "  (NOT PAID) \n";
						}
						else
							cout << " No status is found for this car as there were no fines detected on it" << endl;
				    }
				}
			}
		}
		return isPlateFound;
	}

	int main()
	{
		int choice;
		int driverCounter = -1; 

		do {
			cout << endl;
			cout << "\t--------------------------------------------------------\t" << endl;
			cout << "\t\t Traffic Control System \t\t\n" << endl;
			cout << "1: Traffic Man >>>> Enter the detected fines ." << endl;
			cout << "2: Driver >>>> Enter the driver's information ." << endl;
			cout << "3: Driver >>>> Enter the information of each car owned by the driver ." << endl;
			cout << "4: If the driver wants to know the value of the fines he should pay ." << endl;
			cout << "5: Traffic Man >>>> Enter the details of each fine detected ." << endl;
			cout << "6: If the driver wants to pay for one of his cars or to pay for all of them and update the status of his cars ." << endl;
			cout << "7: To search for a specific car ." << endl;
			cout << "\n====>>>> Type the number of the service you want to receive : ";
			cin >> choice;

			switch (choice)
			{
			default:
				cout << " XX ERROR. You entered an out of range number. XX"<<endl;
				break;

			case 1:
				int storeFines[MAXDETECTEDFINES][3]; //Stores the Plate (in column 1), CarSpeed (in column 2) and the Value of the fine detected by the Traffic Man (in column 3)
				
				cout << "\t\nEnter the detected fines \t\n " << endl;
				recordViolation(storeFines);
				break;

			case 2:
				++driverCounter; 
				cout << "\t\nDriver's info \t\n ";
				getDriverInfo(driverCounter);

				while ((driver[driverCounter].carNumbers > MAXCARS)||(driver[driverCounter].carNumbers<=0))
				{
					cout << " XX ERROR : The max number of owned cars for an individual is 3 cars . XX "<<endl;
					cout << " XX Type the number of owned cars again : ";
					cin >> driver[driverCounter].carNumbers;
				}
				break;

			case 3:
				cout << "\t\nEach car's info \t\n ";
			    getCarInfo(driverCounter);
				break;

			case 4:
				//Display the value of the detected fines
				knowYourFine(storeFines, driverCounter);
				break;

			case 5:
				//Details of each fine detected by Traffic Man
				for (int i = 0; i < driver[driverCounter].carNumbers; i++)
				{
					if (driver[driverCounter].cars[i].howManyFines == 0)
					{
						cout << " No fines were detected for car of plate number " << driver[driverCounter].cars[i].plate << endl;
					    continue;
			     	}
			
						for (int j = 0, countfine = 1; j < driver[driverCounter].cars[i].howManyFines; j++, countfine++)
						{
							cout << " Enter the street where fine " << countfine << " of car plate number " << driver[driverCounter].cars[i].plate << " was recorded : ";
							cin.ignore();
							getline(cin, driver[driverCounter].cars[i].fines[j].street);
							cout << " Enter the date when fine " << countfine << " of car plate number " << driver[driverCounter].cars[i].plate << " was recorded (day/month/year) : ";
							cin >> driver[driverCounter].cars[i].fines[j].fineDate.day >> driver[driverCounter].cars[i].fines[j].fineDate.month >> driver[driverCounter].cars[i].fines[j].fineDate.year;

							while (((driver[driverCounter].cars[i].fines[j].fineDate.day > 30) || (driver[driverCounter].cars[i].fines[j].fineDate.day < 1)) || ((driver[driverCounter].cars[i].fines[j].fineDate.month > 12) || (driver[driverCounter].cars[i].fines[j].fineDate.month < 1))
								|| ((driver[driverCounter].cars[i].fines[j].fineDate.year < 1900) || (driver[driverCounter].cars[i].fines[j].fineDate.year > 2020)))
							{
								cout << " XX Invalid input of the date when the fine was recorded . XX" << endl;
								cout << " XX Enter the date when fine " << countfine << " of car plate number " << driver[driverCounter].cars[i].plate << " was recorded again (day/month/year) : ";
								cin >> driver[driverCounter].cars[i].fines[j].fineDate.day >> driver[driverCounter].cars[i].fines[j].fineDate.month >> driver[driverCounter].cars[i].fines[j].fineDate.year;
							}
						}
				}
				break;

			case 6:
				//To pay for the fines
				char whatUSay;
				char payMore;

				cout << "\t\nDo you want to pay the fine for all your cars or one of them? (A/O) : "; //A for all the fines and O for one of the cars//
				cin >> whatUSay;  

					while ((whatUSay != 'O') && (whatUSay != 'A'))
					{
							cout << " XX Invalid input of character .XX\n XX Enter the character again 'O' for one car and 'A' for all of the owned cars : ";
							cin >> whatUSay;
					}

					if (whatUSay == 'O')
					{
						do 
						{
							payMore = payOneCar(driverCounter);
						} while ((payMore == 'Y') || (payMore == 'y'));
					}
					else if (whatUSay == 'A')
					{
						int noFines = 0;
						for (int i = 0; i < driver[driverCounter].carNumbers; i++)
						{
							if (driver[driverCounter].cars[i].howManyFines == 0)
							{
								noFines += 1;
								continue;
							}
							
							for (int j = 0; j < driver[driverCounter].cars[i].howManyFines; j++)
							{
									driver[driverCounter].cars[i].fines[j].status = 'P';
									cout << " Your status is updated to " << driver[driverCounter].cars[i].fines[j].status;
									(driver[driverCounter].cars[i].fines[j].status == 'P')? cout << " (PAID) " : cout << " (NOT PAID) " << endl;
							}
						}

						if (noFines == driver[driverCounter].carNumbers)
							cout << " No fines were found." << endl;
					}					
				break;

			case 7:
				char searchTool;
				string searchByName;
				int searchByPlate;

				cout << "\t\n  Search for a specific car. \n\t" << endl;
				cout<<" Enter your Name or the Car Plate : " << endl;
				cout << " Which one will you enter? (N/P) : "; //N for Name and P for Plate
				cin >> searchTool;

				while ( (searchTool!='P') && (searchTool!='N') )
				{
					cout << " XX Invalid input of character . XX\n XX Enter the character again 'P' to search by plate and 'N' to search by the driver's name : ";
					cin >> searchTool;
				}

				if (searchTool == 'N')
				{
					cout << " Enter the Name of the driver : ";
					cin.ignore();
					getline(cin, searchByName);
					bool isNameFound = outputSearchByName(searchByName, driverCounter);

					if (!isNameFound)
						cout << "\n    \t XX Error : The Name that was entered is not found on the system. XX \t" << endl;
				}
				else if (searchTool == 'P')
				{
					cout << " Enter the Plate number : ";
					cin >> searchByPlate;
					bool isPlateFound = outputSearchByPlate(searchByPlate);

					if(!isPlateFound)
						cout << "\n    \t XX Error : The Plate that was entered is not found on the system. XX \t" << endl;
				}
				break;
			}
		} while (driverCounter < MAXDRIVERS);
		return 0;
	}
