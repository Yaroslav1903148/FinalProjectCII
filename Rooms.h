#pragma once
#include <iostream>
#include <string>
#include <fstream>
using std::cout;
using std::endl;

namespace All_Rooms {

	class Room {
	protected:
		int Num;
		int AmofPeop;
		float Price;
	public:
		Room() {
			Num = 0;
			AmofPeop = 0;
			Price = 0;
		}

		Room(int amofPeop, float price) {
			this->AmofPeop = amofPeop;
			this->Price = price;
			this->Num = 0;
		}
		virtual ~Room() {}

		virtual int getType() const { return 0; }

		virtual void save(std::ofstream& fout) const {
			fout << getType() << " "
				<< Num << " "
				<< AmofPeop << " "
				<< Price << "\n";
		}

		virtual void load(std::ifstream& fin) {
			fin >> Num >> AmofPeop >> Price;
		}

		void setNum(int num) {
			this->Num = num;
		}
		int getNum() {
			return Num;
		}

		void setAmOfPeop(int amofPeop) {
			this->AmofPeop = amofPeop;
		}
		int getAmountofPeop() {
			return AmofPeop;
		}

		void setPrice(float price) {
			this->Price = price;
		}
		float getPrice() {
			return Price;
		}

		Room operator+(const Room& obj) const {
			Room tmp;
			tmp.Price = this->Price + obj.Price;
			tmp.AmofPeop = this->AmofPeop + obj.AmofPeop;
			return tmp;
		}

		Room operator-(const Room& obj) const {
			Room tmp;
			tmp.Price = this->Price - obj.Price;
			tmp.AmofPeop = this->AmofPeop - obj.AmofPeop;
			return tmp;
		}

		Room operator*(const Room& obj) const {
			Room tmp;
			tmp.Price = this->Price * obj.Price;
			tmp.AmofPeop = this->AmofPeop * obj.AmofPeop;
			return tmp;
		}

		Room operator/(const Room& obj) const {
			Room tmp;
			tmp.Price = (obj.Price != 0) ? this->Price / obj.Price : 0;
			tmp.AmofPeop = (obj.AmofPeop != 0) ? this->AmofPeop / obj.AmofPeop : 0;
			return tmp;
		}

		bool operator<(const Room& obj) const {
			return this->Price < obj.Price;
		}

		bool operator>(const Room& obj) const {
			return this->Price > obj.Price;
		}

		bool operator==(const Room& obj) const {
			return this->Price == obj.Price && this->AmofPeop == obj.AmofPeop;
		}

		bool operator!=(const Room& obj) const {
			return !(*this == obj);
		}

		virtual void showInfo() const {
			cout << "===== Room Info =====" << endl;
			cout << "Room number:   " << Num << endl;
			cout << "Capacity:      " << AmofPeop << " people" << endl;
			cout << "Price for night(24h):         " << Price << " UAH" << endl;
			cout << "=====================" << endl;
		}

		friend std::ostream& operator<<(std::ostream& out, const Room& r) {
			out << "===== Room Info =====\n"
				<< "Room number:   " << r.Num << "\n"
				<< "Capacity:      " << r.AmofPeop << " people\n"
				<< "Price for night(24h):         " << r.Price << " $\n"
				<< "=====================\n";
			return out;
		}

	};

	class StandRoom : public Room {
	protected:
		bool Conditioner;
	public:
		StandRoom() : Room() {
			Conditioner = false;
		}

		StandRoom(int amofPeop, float price, bool conditioner)
			: Room(amofPeop, price)
		{
			this->Conditioner = conditioner;
			if (Conditioner) {
				Price += 200;
			}
		}
		int getType() const override { return 1; }

		void save(std::ofstream& fout) const override {
			fout << getType() << " "
				<< Num << " "
				<< AmofPeop << " "
				<< Price << " "
				<< Conditioner << "\n";
		}

		void load(std::ifstream& fin) override {
			fin >> Num >> AmofPeop >> Price >> Conditioner;
		}

		void setConditioner(bool conditioner) {
			this->Conditioner = conditioner;
		}
		bool getCOnditioner() {
			return Conditioner;
		}

		void showInfo() const override {
			cout << "===== Standart Room Info =====" << endl;
			cout << "Room number:   " << Num << endl;
			cout << "Capacity:      " << AmofPeop << " people" << endl;
			cout << "Conditioner:   " << (Conditioner ? "Yes" : "No") << endl;
			cout << "Price for night(24h):         " << Price << " UAH" << endl;
			cout << "=====================" << endl;
		}
	};

	class MiddleRoom : public Room {
	protected:
		bool Lunch;
	public:
		MiddleRoom() : Room() {
			Lunch = false;
		}

		MiddleRoom(int amofPeop, float price, bool lunch)
			: Room(amofPeop, price)
		{
			this->Lunch = lunch;
			if (Lunch) {
				Price += 150;
			}
		}
		int getType() const override { return 2; }

		void save(std::ofstream& fout) const override {
			fout << getType() << " "
				<< Num << " "
				<< AmofPeop << " "
				<< Price << " "
				<< Lunch << "\n";
		}

		void load(std::ifstream& fin) override {
			fin >> Num >> AmofPeop >> Price >> Lunch;
		}

		void setLunch(bool lunch) {
			this->Lunch = lunch;
		}

		bool getLunch() const {
			return Lunch;
		}

		void showInfo() const override {
			cout << "===== Middle Room Info =====" << endl;
			cout << "Room number:   " << Num << endl;
			cout << "Capacity:      " << AmofPeop << " people" << endl;
			cout << "Lunch:         " << (Lunch ? "Included" : "No") << endl;
			cout << "Price for night(24h):         " << Price << " UAH" << endl;
			cout << "============================" << endl;
		}
	};

	class LuxRoom : public Room {
	protected:
		bool Jacuzzi;
		bool VipService;
		bool Breakfast;
		int MinTerm;
		int MaxTerm;
	public:
		LuxRoom() : Room() {
			Jacuzzi = false;
			VipService = false;
			Breakfast = false;
			MinTerm = 0;
			MaxTerm = 0;
		}

		LuxRoom(int amofPeop, float price,
			bool jacuzzi, bool vipService, bool breakfast,
			int minTerm, int maxTerm)
			: Room(amofPeop, price)
		{
			Jacuzzi = jacuzzi;
			VipService = vipService;
			Breakfast = breakfast;
			MinTerm = minTerm;
			MaxTerm = maxTerm;

			if (Jacuzzi)    Price += 500;
			if (VipService) Price += 800;
			if (Breakfast)  Price += 200;
		}
		int getType() const override { return 3; }

		void save(std::ofstream& fout) const override {
			fout << getType() << " "
				<< Num << " "
				<< AmofPeop << " "
				<< Price << " "
				<< Jacuzzi << " "
				<< VipService << " "
				<< Breakfast << " "
				<< MinTerm << " "
				<< MaxTerm << "\n";
		}

		void load(std::ifstream& fin) override {
			fin >> Num >> AmofPeop >> Price
				>> Jacuzzi >> VipService >> Breakfast
				>> MinTerm >> MaxTerm;
		}
		void showInfo() const override {
			cout << "===== Luxury Room Info =====" << endl;
			cout << "Room number:   " << Num << endl;
			cout << "Capacity:      " << AmofPeop << " people" << endl;
			cout << "Jacuzzi:       " << (Jacuzzi ? "Yes" : "No") << endl;
			cout << "VIP service:   " << (VipService ? "Yes" : "No") << endl;
			cout << "Breakfast:     " << (Breakfast ? "Included" : "No") << endl;
			cout << "Min term:      " << MinTerm << " days" << endl;
			cout << "Max term:      " << MaxTerm << " days" << endl;
			cout << "Total price:   " << Price << " UAH" << endl;
			cout << "=============================" << endl;
		}
	};
}
