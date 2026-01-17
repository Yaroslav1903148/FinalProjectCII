#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::endl;

class HotelException {
protected:
    string text;
public:
    HotelException() : text("Undefined error") {}
    HotelException(string text) : text(text) {}

    virtual string showMessage() const = 0;
};


class HotelFullException : public HotelException {
protected:
    string hotelName;
public:
    HotelFullException() : hotelName("Unknown") {}
    HotelFullException(string text, string hotelName) : HotelException(text), hotelName(hotelName) {}

    string showMessage() const override {
        return "\n=========\nException!!!\nHotel \"" + hotelName + "\" has no more available rooms!\n=========\n";
    }
};


class RoomNotFoundException : public HotelException {
protected:
    int roomNum;
public:
    RoomNotFoundException() : roomNum(0) {}
    RoomNotFoundException(string text, int roomNum) : HotelException(text), roomNum(roomNum) {}

    string showMessage() const override {
        return "\n=========\nException!!!\nRoom number " + std::to_string(roomNum) + " not found!\n=========\n";
    }
};


class InvalidRoomDataException : public HotelException {
protected:
    int roomNum;
public:
    InvalidRoomDataException() : roomNum(0) {}
    InvalidRoomDataException(string text, int roomNum) : HotelException(text), roomNum(roomNum) {}

    string showMessage() const override {
        return "\n=========\nException!!!\nRoom number " + std::to_string(roomNum) + " has invalid data!\n=========\n";
    }
};
