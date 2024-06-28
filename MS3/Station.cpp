// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	/*int Station::m_widthField = 0;
	int Station::id_generator = 0;*/

	Station::Station(const string& str) {
		Utilities util;

		string nameStr, serialNumberStr, quantityStr, descStr;
		size_t next_pos = 0;
		bool more = true;

		nameStr = util.extractToken(str, next_pos, more);
		serialNumberStr = util.extractToken(str, next_pos, more);
		quantityStr = util.extractToken(str, next_pos, more);
		descStr = util.extractToken(str, next_pos, more);	

		m_name = nameStr;
		m_serialNumber = std::stoi(serialNumberStr);
		m_quantity = std::stoi(quantityStr);

		m_widthField = std::max(m_widthField, m_name.length());

		m_desc = descStr;

		m_id = ++id_generator;
	};
	
	const string& Station::getItemName() const {
		return m_name;
	};
	
	size_t Station::getNextSerialNumber() {		
		return m_serialNumber++;
	};
	
	size_t Station::getQuantity() const {
		return m_quantity;
	};
	
	void Station::updateQuantity() {
		(getQuantity() > 0) ? m_quantity -= 1 : m_quantity;
	};

	void Station::display(std::ostream& os, bool full) const {
		os << std::right << std::setw(3) << std::setfill('0') << m_id
			<< " | " << std::left << std::setw(m_widthField) << std::setfill(' ') << m_name
			<< " | " << std::right << std::setw(6) << std::setfill('0') << m_serialNumber 
			<< " | ";
		if(full) {
			os << std::right << std::setw(4) << std::setfill(' ') << m_quantity 
				<< " | " << std::left << m_desc;
		}
		os << std::endl;
	};
}