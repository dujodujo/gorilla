#include "IniFileLoaderBase.h"

void remove_comments(std::string& line) {
	std::string::size_type id = line.find("//");
	// ? != -1
	if(id != std::string::npos)
		line = line.substr(0,id);
}

std::string IniFileLoaderBase::get_next_parameter() {
	std::string line;
	std::getline(this->file, line);
	remove_comments(line);
	if(line.length() == 0) {
		return get_next_parameter();
	}
	get_parameter_value_string(line);
	return line;
}

void IniFileLoaderBase::get_parameter_value_string(std::string& line) {
	std::string::size_type start_id;
	std::string::size_type end_id;
	//delimeters
	std::string delim(" \,=;");
	
	//find start of parameter description.
	start_id = line.find_first_not_of(delim);
	if(start_id != std::string::npos) {
		end_id = line.find_first_of(delim, start_id);
		if(end_id == std::string::npos) {
			end_id = line.length();
		}
	}
	//find start of parameter value.
	start_id = line.find_first_not_of(delim, end_id);
	//find end of parameter value.
	if(start_id != std::string::npos) {
		end_id = line.find_first_of(delim, start_id);
		//end of word is the end of line
		if(end_id == std::string::npos) {
			end_id = line.length();
		}
	}
	line = line.substr(start_id, end_id);
}

std::string IniFileLoaderBase::get_next_token() {
	//strip line of comments.
	while(current_line.length() == 0) {
		std::getline(file, current_line);
		remove_comments(current_line);
	}
	std::string::size_type start_id;
	std::string::size_type end_id;
	std::string delims(" \,=;");

	start_id = current_line.find_first_not_of(delims);
	//find the end of the parameter description
	if(start_id != std::string::npos) {
		end_id = current_line.find_first_of(delims, start_id);
		//end of word is the end of the line
		if(end_id == std::string::npos) {
			end_id = current_line.length();
		}
	}
    
	std::string s = current_line.substr(start_id, end_id);
	if (end_id != current_line.length()) {
    //strip the token from the line
		current_line = current_line.substr(end_id+1, current_line.length());
	} else { 
		current_line = "";
	}
	return s;
}