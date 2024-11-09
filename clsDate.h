#pragma once
#pragma warning (disable: 4996)
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "clsString.h"


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

	static bool IsValiedDay(clsDate Date) {
		return ((Date.Month < 1 || Date.Month > 12) ? false : (Date.Day < 1 || Date.Day >= NumberOfDayInMonth(Date.Year, Date.Month) ? false : true));

	}

	bool IsValiedDay() {
		return IsValiedDay(*this);
	}

	static bool IsLoopYear(short Year) {
		return (Year % 400 == 0 || (Year % 4 == 0) && (Year % 100 != 0));
	}

	static short NumberOfDayInMonth(short Year, short Month) {
		if (Month < 1 || Month > 12)
			return 0;
		short NumberOfDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (IsLoopYear(Year) ? 29 : 28) : NumberOfDay[Month - 1];
	}

	short NumberOfDayInMonth() {
		return NumberOfDayInMonth(_Year, _Month);
	}

	static clsDate GetDataFromDayOrderInYear(short NumberOfDayInYear, short Year) {
		clsDate Data;
		short RemainingDays = NumberOfDayInYear;
		short MonthDays = 0;

		Data.Month = 1;
		Data.Year = Year;
		while (true) {
			MonthDays = NumberOfDayInMonth(Year, Data.Month);
			if (RemainingDays > MonthDays) {

				RemainingDays -= MonthDays;
				Data.Month++;
			}
			else {
				Data.Day = RemainingDays;
				break;
			}

		}
		return Data;

	}

	static int DayOfWeekOrder(short Year, short Month, short Day) {
		short a, y, m;
		a = ((14 - Month) / 12);
		y = Year - a;
		m = Month + 12 * a - 2;
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	}

	int DayOfWeekOrder() {
		return DayOfWeekOrder(_Year, _Month, _Day);
	}

	static string DayShortName(short DayOfWeekOrder) {
		string NameDayInWeek[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return NameDayInWeek[DayOfWeekOrder];
	}

	static string MonthShortName(short MonthOfWeekOrder) {
		string NameMonthInWeek[12] = { "Jan","Feb","Mar","Apr","May","Jun","July",
			"Agu","Sep","Oct","Nov","Des" };
		return NameMonthInWeek[MonthOfWeekOrder - 1];
	}

	static void PrintMonthCalander(short Year, short Month) {

		int current = DayOfWeekOrder(Year, Month, 1);
		int NumberOfDay = NumberOfDayInMonth(Year, Month);

		printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		for (i = 0; i < current; i++) {
			printf("     ");
		}
		for (int j = 1; j <= NumberOfDay; j++) {
			printf("%5d", j);

			if (++i == 7) {
				i = 0;
				printf("\n");
			}

		}
		printf("\n  _________________________________\n\n");

	}

	void PrintMonthCalander() {
		PrintMonthCalander(_Year, _Month);
	}

	static void PrintYearCalandar(short Year) {
		printf("\n  _________________________________\n\n");
		printf("\tCalandar - %d", Year);
		printf("\n  _________________________________\n\n");

		for (int i = 1; i <= 12; i++) {
			PrintMonthCalander(Year, i);
		}
	}

	void PrintYearCalandar() {
		PrintYearCalandar(_Year);
	}

	static int NumOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year) {
		short TotalDays = 0;

		for (int i = 1; i <= Month - 1; i++) {
			TotalDays += NumberOfDayInMonth(Year, i);
		}
		TotalDays += Day;
		return TotalDays;
	}

	int NumOfDaysFromTheBeginingOfTheYear() {
		return NumOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	void AddDays(short AddDays) {

		short RemainingDays = AddDays + NumOfDaysFromTheBeginingOfTheYear(Day, Month, Year);
		short MonthDays = 0;
		Month = 1;
		while (true) {
			MonthDays = NumberOfDayInMonth(Year, Month);

			if (RemainingDays > MonthDays) {

				RemainingDays -= MonthDays;
				Month++;

				if (Month > 12) {
					Month = 1;
					Year++;
				}
			}
			else {
				Day = RemainingDays;
				break;
			}
		}

	}

	static bool IsData1BeforeDate2(clsDate Date1, clsDate Date2) {

		return ((Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? ((Date1.Month < Date2.Month) ? true : ((Date1.Month == Date2.Month) ? (Date1._Day < Date2.Day) : false)) : false));

		/// Using if stastment
		/*if (Date1._Year != Date2._Year) {
			return (Date1._Year < Date2._Year);
		}
		else {
			if (Date1._Month != Date2._Month) {
				return (Date1._Month < Date2._Month);
			}
			else {
				if (Date1._Day != Date2._Day) {
					return (Date1._Day < Date2._Day);
				}
				else {
					return false;
				}
			}

		}*/

	}

	bool IsDataBeforeDate2(clsDate Date2) {
		return IsData1BeforeDate2(*this, Date2);
	}

	static bool IsData1EqualDate2(clsDate Date1, clsDate Date2) {

		return ((Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? (Date1.Day == Date2.Day) : false) : false);

	}

	bool IsDataEqualDate2(clsDate Date2) {
		return IsData1EqualDate2(*this, Date2);
	}

	static bool IsLastMonthInYear(short Month) {
		return (Month == 12);
	}

	bool IsLastMonthInYear() {
		return IsLastMonthInYear(_Month);
	}

	static bool IsLastDayInMonth(clsDate Date) {
		return (Date.Day == NumberOfDayInMonth(Date.Year, Date.Month));
	}

	bool IsLastDayInMonth() {
		return IsLastDayInMonth(*this);
	}

	static clsDate AddOneDay(clsDate Date) {

		if (IsLastDayInMonth(Date)) {

			if (IsLastMonthInYear(Date.Month)) {
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else {
				Date.Day = 1;
				Date.Month++;
			}
		}
		else {
			Date.Day++;
		}

		return Date;
	}

	void AddOneDay() {
		*this = AddOneDay(*this);
	}

	static int GetDiffrenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {
		int Days = 0;
		while (IsData1BeforeDate2(Date1, Date2)) {

			Days++;
			Date1 = AddOneDay(Date1);
		}
		return IncludeEndDay ? ++Days : Days;
	}

	int GetDiffrenceInDays(clsDate Date2, bool IncludeEndDay = false) {
		return GetDiffrenceInDays(*this, Date2, IncludeEndDay);
	}

	static int CalculateMyAgeInDays(clsDate DateOfBirth) {
		int Days = 0;
		while (IsData1BeforeDate2(DateOfBirth, GetSystemDate())) {

			Days++;
			DateOfBirth = AddOneDay(DateOfBirth);
		}
		return  Days;
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2) {
		clsDate Temp;

		Temp = Date1;
		Date1 = Date2;
		Date2 = Temp;
	}

	void SwapDates(clsDate& Date2) {
		SwapDates(*this, Date2);
	}

	static int GetDiffrenceInDaysWithNegativeNumber(clsDate Data1, clsDate Data2, bool IncludeEndDay = false) {
		int Days = 0;
		short SwapFlagValue = 1;
		if (!IsData1BeforeDate2(Data1, Data2)) {
			SwapFlagValue = -1;
			SwapDates(Data1, Data2);
		}
		while (IsData1BeforeDate2(Data1, Data2)) {
			Days++;
			Data1 = AddOneDay(Data1);

		}
		return IncludeEndDay ? (++Days * SwapFlagValue) : (Days * SwapFlagValue);
	}

	int GetDiffrenceInDaysWithNegativeNumber(clsDate Data2, bool IncludeEndDay = false) {
		return GetDiffrenceInDaysWithNegativeNumber(*this, Data2, IncludeEndDay);
	}

	static clsDate IncreaseDateByXDays(clsDate Date, short Days) {
		for (int i = 1; i <= Days; i++) {
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDays(short Days) {
		*this = IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date) {
		for (int i = 1; i <= 7; i++) {
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate Date, short Week) {

		for (int i = 1; i <= Week; i++) {
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeeks(short Week) {
		*this = IncreaseDateByXWeeks(*this, Week);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date) {
		if (Date.Month == 12) {
			Date.Month = 1;
			Date.Year++;
		}
		else {
			Date.Month++;
		}
		short DayMonth = NumberOfDayInMonth(Date.Year, Date.Month);

		if (Date.Day > DayMonth) {
			Date.Day = DayMonth;
		}
		return Date;
	}

	void IncreaseDateByOneMonth() {
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate Date, short Month) {

		for (int i = 1; i <= Month; i++) {
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonths(short Month) {
		*this = IncreaseDateByXMonths(*this, Month);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date) {
		Date.Year++;
		return Date;

		/*return IncreaseDateByXMonths(Data, 12);*/
	}

	void IncreaseDateByOneYear() {
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate Date, short Year) {

		for (int i = 1; i <= Year; i++) {

			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	void IncreaseDateByXYears(short Year) {
		*this = IncreaseDateByXYears(*this, Year);
	}

	static clsDate IncreaseDateByXYearsFaster(clsDate Date, short Years) {

		Date.Year += Years;
		return Date;

	}

	void IncreaseDateByXYearsFaster(short Years) {
		*this = IncreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date) {

		Date.Year += 10;
		return Date;
	}

	void IncreaseDateByOneDecade() {
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate Date, short Decades) {

		for (int i = 1; i <= Decades * 10; i++) {
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}

	void IncreaseDateByXDecades(short Decades) {
		*this = IncreaseDateByXDecades(*this, Decades);
	}

	static clsDate IncreaseDateByXDecadesFaster(clsDate Date, short Decades) {

		Date.Year += 10 * Decades;
		return Date;


	}

	void IncreaseDateByXDecadesFaster(short Decades) {
		*this = IncreaseDateByXDecadesFaster(*this, Decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date) {

		Date.Year += 100;
		return Date;
	}

	void IncreaseDateByOneCentury() {
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date) {

		Date.Year += 1000;
		return Date;
	}

	void IncreaseDateByOneMillennium() {
		*this = IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date) {

		if (Date.Day == 1) {

			if (Date.Month == 1) {
				Date.Month = 12;
				Date.Day = 31;
				Date.Year--;


			}
			else {
				Date.Month--;
				Date.Day = NumberOfDayInMonth(Date.Year, Date.Month);
			}
		}
		else {
			Date.Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay() {
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate Date, short Days) {
		for (int i = 1; i <= Days; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDays(short Days) {
		*this = DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date) {
		for (int i = 1; i <= 7; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByOneWeek() {
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate Date, short Week) {

		for (int i = 1; i <= Week; i++) {
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeeks(short Week) {
		*this = DecreaseDateByXWeeks(*this, Week);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date) {
		if (Date.Month == 1) {
			Date.Month = 12;
			Date.Year--;
		}
		else {
			Date.Month--;
		}
		short DayMonth = NumberOfDayInMonth(Date.Year, Date.Month);

		if (Date.Day > DayMonth) {
			Date.Day = DayMonth;
		}
		return Date;
	}

	void DecreaseDateByOneMonth() {
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate Date, short Month) {

		for (int i = 1; i <= Month; i++) {
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonths(short Month) {
		*this = DecreaseDateByXMonths(*this, Month);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date) {
		Date.Year--;
		return Date;

		/*return IncreaseDateByXMonths(Data, 12);*/
	}

	void DecreaseDateByOneYear() {
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate Date, short Year) {

		for (int i = 1; i <= Year; i++) {

			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	void DecreaseDateByXYears(short Year) {
		*this = DecreaseDateByXYears(*this, Year);
	}

	static clsDate DecreaseDateByXYearsFaster(clsDate Date, short Years) {

		Date.Year -= Years;
		return Date;

	}

	void DecreaseDateByXYearsFaster(short Years) {
		*this = DecreaseDateByXYearsFaster(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date) {

		Date.Year -= 10;
		return Date;
	}

	void DecreaseDateByOneDecade() {
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate Date, short Decades) {

		for (int i = 1; i <= Decades * 10; i++) {
			Date = DecreaseDateByOneYear(Date);
		}
		return Date;
	}

	void DecreaseDateByXDecades(short Decades) {
		*this = DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByXDecadesFaster(clsDate Date, short Decades) {

		Date.Year -= 10 * Decades;
		return Date;


	}

	void DecreaseDateByXDecadesFaster(short Decades) {
		*this = DecreaseDateByXDecadesFaster(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date) {

		Date.Year -= 100;
		return Date;
	}

	void DecreaseDateByOneCentury() {
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date) {

		Date.Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium() {
		*this = DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date) {
		return DayOfWeekOrder(Date.Year, Date.Month, Date.Day) == 6;
	}

	bool IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date) {
		short DayIndex = DayOfWeekOrder(Date.Year, Date.Month, Date.Day);
		return (DayIndex == 5 || DayIndex == 6);

	}

	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date) {
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}

	static int DaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - DayOfWeekOrder(Date.Year, Date.Month, Date.Day);

		/*int Days = 0;
		while (!IsEndOfWeek(Data)) {
			Days++;
			Data.Day++;
		}
		return Days;*/
	}

	int DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}

	static int DaysUntilTheEndOfMonth(clsDate Date) {
		clsDate EndOfMonthData;
		EndOfMonthData.Day = NumberOfDayInMonth(Date.Year, Date.Month);
		EndOfMonthData.Month = Date.Month;
		EndOfMonthData.Year = Date.Year;

		return GetDiffrenceInDays(Date, EndOfMonthData, true);
		/*int Days = 0;
		while (!IsLastDayInMonth(Data)) {
			Days++;
			Data = DataAfterAddOneDay(Data);
		}
		return Days;*/
	}

	int DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}

	static int DaysUntilTheEndOfYear(clsDate Date) {
		clsDate EndOfYearData;
		EndOfYearData.Day = 31;
		EndOfYearData.Month = 12;
		EndOfYearData.Year = Date.Year;

		return GetDiffrenceInDays(Date, EndOfYearData, true);
		/*int Days = 0;
		while (!IsLastMonthInYear(Data.Month)) {
			Days++;
			Data = DataAfterAddOneDay(Data);

		}
		return Days + DaysUntilTheEndOfMonth(Data);*/
	}

	int DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {
		short Days = 0;
		while (IsData1BeforeDate2(DateFrom, DateTo)) {
			if (IsBusinessDay(DateFrom)) {
				Days++;

			}
			DateFrom = AddOneDay(DateFrom);

		}
		return Days;

	}

	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo) {
		return CalculateVacationDays(DateFrom, DateTo);

	}

	short CalculateVacationDays(clsDate DateTo) {
		return  CalculateVacationDays(*this, DateTo);
	}

	static clsDate CalculateVactionDate(clsDate DateFrom, short VactionDays) {

		while (VactionDays > 0) {
			if (IsBusinessDay(DateFrom)) {
				VactionDays--;

			}
			DateFrom = AddOneDay(DateFrom);

		}
		return DateFrom;
	}

	void CalculateVactionDate(short VactionDays) {
		*this = CalculateVactionDate(*this, VactionDays);
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{

			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = AddOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		return DateFrom;
	}

	void CalculateVacationReturnDate(short VacationDays) {
		*this = CalculateVacationReturnDate(*this, VacationDays);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2) {
		return (!IsData1BeforeDate2(Date1, Date2) && !IsData1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2) {
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {
		return (IsDate1AfterDate2(Date1, Date2) ? enDateCompare::After : (IsData1BeforeDate2(Date1, Date2) ? enDateCompare::Before : enDateCompare::Equal));

	}

	enDateCompare CompareDates(clsDate Date2) {
		return CompareDates(*this, Date2);
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


};

