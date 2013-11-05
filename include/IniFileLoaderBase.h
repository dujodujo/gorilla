#include <fstream>
#include <string>
#include <cassert>
#include <iostream>
#pragma warning(disable:4800)

class IniFileLoaderBase {

private:
	std::ifstream file;
	std::string current_line;
	void get_parameter_value_string(std::string& line);
	std::string get_next_token();
	std::string get_next_parameter();
	bool valid_file;

public:
	//atof convert string to float.
	double get_next_parameter_double() {if(valid_file) return std::atof(get_next_parameter().c_str()); /*throw std::runtime_error("bad file");*/}
	float get_next_parameter_float() {if(valid_file) return (float)std::atof(get_next_parameter().c_str()); /*throw std::runtime_error("bad file");*/}
	int get_next_parameter_integer() {if(valid_file) return std::atoi(get_next_parameter().c_str()); /*throw std::runtime_error("bad file");*/}
	bool get_next_parameter_bool() {return (bool)(std::atoi(get_next_parameter().c_str())); /*throw std::runtime_error("bad file");*/}

	double get_next_token_double() {if(valid_file) return std::atof(get_next_token().c_str()); /*throw std::runtime_error("bad file");*/}
	float get_next_token_float() {if(valid_file) return (float)std::atof(get_next_token().c_str()); /*throw std::runtime_error("bad file");*/}
	int get_next_token_int() {if(valid_file) return std::atoi(get_next_token().c_str()); /*throw std::runtime_error("bad file");*/}
	std::string get_next_token_string() {if(valid_file) return get_next_token(); /*throw std::runtime_error("bad file");*/}

	bool eof() const {if(valid_file) return file.eof(); /*throw std::runtime_error("bad file");*/}
	bool file_is_valid() const {return valid_file;}

	IniFileLoaderBase(char* file_name) : current_line(""), valid_file(true) {
		file.open(file_name);
		if(!file)
			valid_file = false;
	}
};