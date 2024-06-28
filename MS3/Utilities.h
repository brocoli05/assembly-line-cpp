// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <iostream>
namespace sdds {
	class Utilities {
		size_t m_widthField{ 1 };
		inline static char m_delimiter{};
	public:
		Utilities() = default;
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
		std::string trim(std::string& str);

		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);		
	};
}	

#endif // !SDDS_UTILITIES_H
