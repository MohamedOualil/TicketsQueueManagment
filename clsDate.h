#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include <string>
#include <ctime>
#include <vector>


using namespace std;

class clsDate
{
	/*short _Second = 1;
	short _Min = 1;
	short _Hours = 1;*/

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;



public:

	clsDate() {

		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;

	}

	clsDate(string sDate) {
		vector<string> vDate = clsString::SplitString(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);

	}

	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short NumberOfDayInYear, short Year) {
		clsDate Date;
		Date = GetDataFromDayOrderInYear(NumberOfDayInYear, Year);
		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;

	}

	void SetDay(short Day) {
		_Day = Day;

	}

	void SetMonth(short Month) {
		_Month = Month;

	}

	void SetYear(short Year) {
		_Year = Year;

	}

	short GetDay() {
		return _Day;
	}

	short GetMonth() {
		return _Month;
	}

	short GetYear() {
		return _Year;
	}

	__declspec (property(get = GetDay, put = SetDay)) short Day;
	__declspec (property(get = GetMonth, put = SetMonth)) short Month;
	__declspec (property(get = GetYear, put = SetYear)) short Year;

	void Print() {
		cout << DateToString() << endl;;
	}

	static clsDate GetSystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;

		Day = now->tm_mday;
		Month = now->tm_mon + 1;
		Year = now->tm_year + 1900;

		return clsDate(Day, Month, Year);
	}

	static string GetSystemTime() {

		time_t t = time(0);
		tm* now = localtime(&t);
		short Second, Min, Hours;

		Second = now->tm_sec;
		Min = now->tm_min;
		Hours = now->tm_hour;

		return to_string(Hours) + ":" + to_string(Min) + ":" + to_string(Second);
	}

	static clsDate StringToDate(string StringDate) {
		vector<string> vData = clsString::SplitString(StringDate, "/");
		clsDate Date;

		Date.Day = stoi(vData[0]);
		Date.Month = stoi(vData[1]);
		Date.Year = stoi(vData[2]);

		return Date;
	}

	static string DateToString(clsDate Date) {
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString() {
		return DateToString(*this);
	}

	static string DateFormats(clsDate Date, string Format = "dd/mm/yyyy") {
		string FinalFormat = "";
		FinalFormat = clsString::ReplaceWord(Format, "dd", to_string(Date.Day));
		FinalFormat = clsString::ReplaceWord(FinalFormat, "mm", to_string(Date.Month));
		FinalFormat = clsString::ReplaceWord(FinalFormat, "yyyy", to_string(Date.Year));
		return FinalFormat;


	}

	string DateFormats(string Format = "dd/mm/yyyy") {
		return  DateFormats(*this, Format);
	}