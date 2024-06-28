// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
namespace sdds {
	class Station {
		size_t m_id{ 0 };
		std::string m_name{};
		std::string m_desc{};
		unsigned m_serialNumber{ 0 };
		unsigned m_quantity{ 0 };
		inline static size_t m_widthField{ 0 };
		inline static size_t id_generator{ 0 };
	public:
		Station() = default;
		//extracts each token from the record and populates the Station object accordingly
		Station(const std::string& str);
		//returns the name of the current Station object
		const std::string& getItemName() const;
		//returns the next serial number to be used on the assembly line and increments m_serialNumber
		size_t getNextSerialNumber();
		//returns the remaining quantity of items in the Station object
		size_t getQuantity() const;
		//subtracts 1 from the available quantity; should not drop below 0
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H

