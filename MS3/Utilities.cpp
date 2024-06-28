// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <cstring>
#include <string>
#include "Utilities.h"

using namespace std;
namespace sdds {
	// Initialize class variable
	//char Utilities::m_delimiter = '\0';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	};
	
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	};

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	};
	char Utilities::getDelimiter() {
		return m_delimiter;
	};

	string Utilities::trim(string& str) {
		string trimStr{};
		/*trimStr = str.erase(0, str.find_first_not_of(' '));
		trimStr = str.erase(str.find_last_not_of(' ') + 1);*/
		size_t first = str.find_first_not_of(' ');
		size_t last = str.find_last_not_of(' ');
		(std::string::npos == first) ? trimStr = str : trimStr = str.substr(first, (last - first + 1));
		return trimStr;
	}

	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		// uses the delimiter to extract the next token from str starting at position next_pos
		size_t endPos = str.find(m_delimiter, next_pos);
		string extractedToken{};

		if (endPos != string::npos) {
			extractedToken = str.substr(next_pos, endPos - next_pos);
			next_pos = endPos + 1;
			more = true;			
		}
		else {
			extractedToken = str.substr(next_pos);
			more = false;			
		}
		extractedToken = trim(extractedToken); // without spaces at the beginning/end

		// updates the current object's m_widthField data member if its current value is less than the size of the token extracted
		(m_widthField < extractedToken.length()) ? m_widthField = extractedToken.length() : m_widthField;

		// reports an exception if a delimiter is found at next_pos
		if (extractedToken.empty() && more) {
			more = false;
			throw "ERROR: No token.";
		}

		return extractedToken;
	};	 
}