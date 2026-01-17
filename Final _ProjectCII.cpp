#include <iostream>
#include <vector>
#include <fstream>
#include "Hotel.h"
#include "Rooms.h"
#include "HotelException.h"

using namespace std;
using namespace Hotel_Build;
using namespace All_Rooms;
int Hotel_Build::Hotel::amount = 15;
int Hotel_Build::Hotel::num = 0;

int main() {
	int choice = 0;
    int emcho = 0;
    int youcho = 0;
    Hotel* hotel = nullptr;
	while (choice != 3) {
		cout << "\n=====================\n";
		cout << "|1. Menu of employee|"<<endl;
		cout << "|2. Menu of visitors|" << endl;
		cout << "|3. Exit            |" << endl;
		cout<<"---Enter your choice: ";
		cin >> choice;

		if (choice == 1) {
            youcho = 0;
			while (youcho != 8) {
				cout << "\t===Welcome to Emp-Menu===\t" << endl;
				cout << "\t1) Create hotel" << endl;
				cout << "\t2) Add new room" << endl;
				cout << "\t3) Delete room" << endl;
				cout << "\t4) Edit room" << endl;
				cout << "\t5) Find cheaper room" << endl;
				cout << "\t6) Rooms you can add" << endl;
				cout << "\t7) Show all info about Hotel" << endl;
				cout << "\t8) Exit." << endl;
				cout << "\t---Additional------" << endl;
                cout << "\t9) Save to file." << endl;
                cout << "\t10) Read from file." << endl;
				cin >> youcho;
                if (youcho == 1) {
                    if (hotel != nullptr) {
                        cout << "\tCannot create new hotel!\n";
                        continue;
                    }
                    string nh;
                    cout << "\t -Enter name of hotel: ";
                    cin.ignore();
                    getline(cin, nh);

                    int t;
                    cout << "\t -Enter info about first room:\n";
                    cout << "\t --Enter type of room (1.Standart 2.Middle 3.Lux): ";
                    cin >> t;

                    if (t == 1) {
                        int people;
                        float price;
                        bool cond;

                        cout << "\t ---Amount of people: ";
                        cin >> people;
                        cout << "\t ---Base price: ";
                        cin >> price;
                        cout << "\t ---Conditioner (1-yes 0-no): ";
                        cin >> cond;

                        StandRoom a(people, price, cond);
                        a.showInfo();

                        Room* r = new StandRoom(people, price, cond);
                        hotel = new Hotel(nh, r);
                    }

                    else if (t == 2) {
                        int people;
                        float price;
                        bool lunch;

                        cout << "\t ---Amount of people: ";
                        cin >> people;
                        cout << "\t ---Base price: ";
                        cin >> price;
                        cout << "\t ---Lunch (1-yes 0-no): ";
                        cin >> lunch;

                        MiddleRoom a(people, price, lunch);
                        a.showInfo();

                        Room* r = new MiddleRoom(people, price, lunch);
                        hotel = new Hotel(nh, r);
                    }

                    else if (t == 3) {
                        int people, minT, maxT;
                        float price;
                        bool jac, vip, br;

                        cout << "\t ---Amount of people: ";
                        cin >> people;
                        cout << "\t ---Base price: ";
                        cin >> price;
                        cout << "\t ---Jacuzzi (1-yes 0-no): ";
                        cin >> jac;
                        cout << "\t ---VIP service (1-yes 0-no): ";
                        cin >> vip;
                        cout << "\t ---Breakfast (1-yes 0-no): ";
                        cin >> br;
                        cout << "\t ---Min term: ";
                        cin >> minT;
                        cout << "\t ---Max term: ";
                        cin >> maxT;

                        LuxRoom a(people, price, jac, vip, br, minT, maxT);
                        a.showInfo();

                        Room* r = new LuxRoom(people, price, jac, vip, br, minT, maxT);
                        hotel = new Hotel(nh, r);
                    }
                }

                if (youcho == 2) {
                    try {
                        int t;
                        cout << "\t --Enter type of room (1.Standart 2.Middle 3.Lux): ";
                        cin >> t;

                        if (t == 1) {
                            int people;
                            float price;
                            bool cond;

                            cout << "\t ---Amount of people: ";
                            cin >> people;
                            cout << "\t ---Base price: ";
                            cin >> price;
                            cout << "\t ---Conditioner (1-yes 0-no): ";
                            cin >> cond;

                            Room* r = new StandRoom(people, price, cond);
                            hotel->addNew(r);
                        }

                        else if (t == 2) {
                            int people;
                            float price;
                            bool lunch;

                            cout << "\t ---Amount of people: ";
                            cin >> people;
                            cout << "\t ---Base price: ";
                            cin >> price;
                            cout << "\t ---Lunch (1-yes 0-no): ";
                            cin >> lunch;

                            Room* r = new MiddleRoom(people, price, lunch);
                            hotel->addNew(r);
                        }

                        else if (t == 3) {
                            int people, minT, maxT;
                            float price;
                            bool jac, vip, br;

                            cout << "\t ---Amount of people: ";
                            cin >> people;
                            cout << "\t ---Base price: ";
                            cin >> price;
                            cout << "\t ---Jacuzzi (1-yes 0-no): ";
                            cin >> jac;
                            cout << "\t ---VIP service (1-yes 0-no): ";
                            cin >> vip;
                            cout << "\t ---Breakfast (1-yes 0-no): ";
                            cin >> br;
                            cout << "\t ---Min term: ";
                            cin >> minT;
                            cout << "\t ---Max term: ";
                            cin >> maxT;

                            Room* r = new LuxRoom(people, price, jac, vip, br, minT, maxT);
                            hotel->addNew(r);
                        }
                    }
                    catch (HotelException& ex) {
                        cout<<ex.showMessage();
                    }
                }

                if (youcho == 3) {
                    try {
                        int n;
                        cout << "\t --Enter room number to delete: ";
                        cin >> n;
                        hotel->delRoom(n);
                        cout << "\t Room deleted!\n";
                    }
                    catch (const HotelException& ex) {
                        cout << ex.showMessage();
                    }
                  
                }

                if (youcho == 4) {
                    try {
                        int n, price, cap;
                        cout << "\t --Enter room number: ";
                        cin >> n;
                        cout << "\t --New price: ";
                        cin >> price;
                        cout << "\t --New capacity: ";
                        cin >> cap;

                        hotel->editRoom(n, price, cap);
                   }
                    catch (HotelException& ex) {
                        cout << ex.showMessage();
                    }
                }

                if (youcho == 5) {///!!!!!
                    float price;
                    cout << "\t --Enter max price: ";
                    cin >> price;

                    Room sample(1, price);
                    hotel->findCheaperThan(sample);
                }

                if (youcho == 6) {
                    cout << "\tRooms you can add: " << hotel->getAmount() << endl;
                }

                if (youcho == 7) {
                    if (hotel == nullptr) {
                        cout << "\t No rooms or hotel!\n";
                    }
                    else {
                        hotel->showInfo();
                    }
                   
                }

                if (youcho == 9) {
                    if (!hotel)
                        cout << "Hotel not created!\n";
                    else {
                        hotel->saveToFile("hotel.txt");
                        cout << "Saved successfully!\n";
                    }
                }

                if (youcho == 10) {
                    if (!hotel)
                        hotel = new Hotel();

                    hotel->loadFromFile("hotel.txt");
                    cout << "Loaded successfully!\n";
                }


			}
		}

        else if (choice == 2) {
            emcho = 0;
            while (emcho !=3) {
                if (hotel == nullptr) {
                    cout << "\t No hotel created!\n";
                    break;
                }
                else {
                    cout << "\t============= Welcome to hotel " << hotel->getName() << " =============\n";
                    cout << "\t 1)Show all rooms" << endl;
                    cout << "\t 2)Sort rooms by price" << endl;
                    cout << "\t 3)Exit" << endl;
                    cout << "\t Enter your choice: ";
                    cin >> emcho;

                    if (emcho == 1) {
                        cout << "\n\n\t -==== All rooms in hotel ====-" << endl;
                        hotel->showInfo();
                    }
                    if (emcho == 2) {
                        if (hotel->getAmount() == 14) {
                            cout << "\t -Not enough rooms int the hotel to sort!-" << endl;
                        }
                        else {
                            hotel->sortByPrice(true);
                            cout << "\t Rooms sorted by price!" << endl;
                            hotel->showInfo();
                        }
                    
                    }
                    
                }
           }
            
        }

        else if(choice == 3) {
            cout << "Finish program!\n";
        }
        else {
            cout << "Error\n";
        }
	}
}
