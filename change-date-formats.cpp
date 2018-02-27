#include <iostream>
#include <string>
#include <regex>
#include <memory>
#include <algorithm>
#include <vector>

//test case 1
//// 2010/03/30 15/12/2016 11-15-2012 20130720

using namespace std;
struct Date{
	string day;
	string month;
	string year;

	explicit Date(const string &day, const string &month, const string &year) :
		day(day), month(month), year(year) {}

	static string convToValidFormat(Date&& date){
		return string(date.year+date.month+date.day);
	}
};

shared_ptr<vector<string>> change_date_format(shared_ptr<vector<string>> input_dates){
	auto output_dates = make_shared<vector<string>>();
	regex pattern1("[[:digit:]]{2}-[[:digit:]]{2}-[[:digit:]]{4}");//example: 12-25-2014
	regex pattern2("[[:digit:]]{2}\\/[[:digit:]]{2}\\/[[:digit:]]{4}");//example: 24/12/2013
	regex pattern3("[[:digit:]]{4}\\/[[:digit:]]{2}\\/[[:digit:]]{2}");//example: 2012/12/24
	for(const auto& date:*input_dates){
		if(regex_match(date,pattern1)){
			 output_dates->push_back(
				 Date::convToValidFormat(
					 Date(date.substr(3,2),date.substr(0,2),date.substr(6,4))
				 )
			 );
		}
		else if(regex_match(date,pattern2)){
			output_dates->push_back(
				Date::convToValidFormat(
					Date(date.substr(0,2),date.substr(3,2),date.substr(6,4))
				)
			);
		}
		else if(regex_match(date,pattern3)){
			output_dates->push_back(
				Date::convToValidFormat(
					Date(date.substr(8,2),date.substr(5,2),date.substr(0,4))
				)
			);
		}
	}

	return output_dates;
}

int main(int argc, char **argv) {

	auto print = [](const string &str){
		static int i = 0;
		if(i==0) {
			cout << str;
			++i;
		}
		else{
			cout << ','+str;
		}
	}; // utility print function
	auto input_dates = make_shared<vector<string> >();
	cout << "Please enter date formats with space character in between and hit enter when you're done: " << "\n";

	string all_dates;
	getline(cin,all_dates);
	stringstream all_dates_stream(all_dates);

	while(getline(all_dates_stream,all_dates,' ')){
		input_dates->push_back(all_dates);
	}

	cout << "Input size is: " << input_dates->size() << '\n';

	auto output_dates = change_date_format(input_dates);

	cout << "output size is: " << output_dates->size() << '\n';

	for_each(output_dates->begin(),output_dates->end(),print);

	return 0;
}