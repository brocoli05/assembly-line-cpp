// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 10/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>
namespace sdds {
	class Station {
		int m_id{ 0 };
		std::string m_name{};
		std::string m_desc{};
		unsigned m_serialNumber{ 0 };
		unsigned m_quantity{ 0 };
		inline static size_t m_widthField{ 0 };
		inline static size_t id_generator{ 0 };
	public:
		Station() = default;
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif // !SDDS_STATION_H

