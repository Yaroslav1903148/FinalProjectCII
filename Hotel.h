#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include "Rooms.h"
#include "HotelException.h"
using std::cout;
using std::endl;
using std::string;


namespace Hotel_Build {
	class Hotel
	{
	private:
		static int amount;
		static int num;

		void setAmount(int amount) {
			this->amount = amount;
		}
		
		std::list<All_Rooms::Room*> arr;
	protected:
		string name;
	public:
		Hotel() {
			cout << "\nCreated noname hotel!\n";
			amount = 15;
			num = 0;
			name = " ";
		}
		Hotel(string name, All_Rooms::Room* obj) {
			this->name = name;
			arr.push_back(obj);
			amount--;
			num++;
			obj->setNum(num);
			cout << "\nCreated room with num: " << num << endl;
			cout << "\nRooms you can add: " << amount << endl;
		}
		~Hotel() {
			for (auto r : arr) {
				delete r;
				cout << "\nDeleted room!\n";
			}
		}


		void setName(string name) {
			this->name = name;
		}
		string getName()const {
			return name;
		}

		int getAmount()const {
			return amount;
		}

		void addNew(All_Rooms::Room* obj) {
			if (amount <= 0) {
				throw HotelFullException("Cannot add more rooms", name);
			}
			arr.push_back(obj);
			amount--;
			num++;
			obj->setNum(num);
			cout << "\Added room with num: " << num << endl;
			cout << "\nRooms you can add: " << amount << endl;
		}

		void delRoom(int num) {
			bool found = false;
			for (auto it = arr.begin(); it != arr.end(); ++it) {
				if ((*it)->getNum() == num) {
					delete* it;       
					arr.erase(it);     
					amount++;
					found = true;    
					break;
				}
			}
			if (!found) {
				throw RoomNotFoundException("Cannot delete room", num);
			}
		}


		void editRoom(int roomNum, int price, int capacity) {
			if (price < 0 || capacity <= 0) {
				throw InvalidRoomDataException("Invalid room data", roomNum);
			}

			bool found = false;
			for (auto it = arr.begin(); it != arr.end(); ++it) {
				if ((*it)->getNum() == roomNum) {
					(*it)->setPrice(price);
					(*it)->setAmOfPeop(capacity);
					found = true;
					break;
				}
			}
			if (!found) {
				throw RoomNotFoundException("Cannot edit room", roomNum);
			}
		}

		void findCheaperThan(const All_Rooms::Room& sample) const {
			for (auto r : arr) {
				if (*r < sample) {  
					r->showInfo();
				}
			}
		}

		void sortByPrice(bool ascending = true) {
			if (ascending) {
				arr.sort([](All_Rooms::Room* a, All_Rooms::Room* b) {
					return a->getPrice() < b->getPrice();
					});
				cout << "\nRooms sorted by price ascending.\n";
			}
			else {
				arr.sort([](All_Rooms::Room* a, All_Rooms::Room* b) {
					return a->getPrice() > b->getPrice();
					});
				cout << "\nRooms sorted by price descending.\n";
			}
		}

		void showInfo() const {
			cout << "\n======================================" << endl;
			cout << "Hotel Name: " << name << endl;
			cout << "Rooms available to add: " << amount << endl;
			cout << "Total rooms: " << arr.size() << endl;
			cout << "--------------------------------------" << endl;

			if (arr.empty()) {
				cout << "No rooms in this hotel." << endl;
			}
			else {
				for (auto r : arr) {
					r->showInfo();  
					cout << "--------------------------------------" << endl;
				}
			}

			cout << "======================================\n" << endl;
		}

		void saveToFile(const string& filename) const {
			std::ofstream fout(filename);

			fout << name << "\n";
			fout << amount << " " << num << "\n";
			fout << arr.size() << "\n";

			for (auto r : arr)
				r->save(fout);

			fout.close();
		}

		void loadFromFile(const string& filename) {
			std::ifstream fin(filename);

			for (auto r : arr)
				delete r;
			arr.clear();

			fin >> name;
			fin >> amount >> num;

			int count;
			fin >> count;

			for (int i = 0; i < count; i++) {
				int type;
				fin >> type;

				All_Rooms::Room* r = nullptr;

				if (type == 0) r = new All_Rooms::Room();
				else if (type == 1) r = new All_Rooms::StandRoom();
				else if (type == 2) r = new All_Rooms::MiddleRoom();
				else if (type == 3) r = new All_Rooms::LuxRoom();

				r->load(fin);
				arr.push_back(r);
			}

			fin.close();
		}

	};


}
