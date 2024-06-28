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
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
namespace sdds {	
	CustomerOrder::CustomerOrder(const std::string& str) {
		
		size_t next_pos = 0;
		bool more = true;
		Utilities util;
		string itemList{};
		size_t newStart = 0;

		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);

		newStart = next_pos;

		while (more) {
			itemList = util.extractToken(str, next_pos, more);
			m_cntItem++;
		}	

		m_lstItem = new Item * [m_cntItem];
		
		// reset them for items extraction
		next_pos = newStart;
		more = true;

		for(size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
		}

		//if the current value is smaller than the value stored in Utilities::m_widthField
		//updates CustomerOrder::m_widthField
		(m_widthField < util.getFieldWidth()) ? m_widthField = util.getFieldWidth() : m_widthField;
	};
	
	CustomerOrder::CustomerOrder(const CustomerOrder& co) {
		throw "----> ERROR: Cannot make copies.";
	};

	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
		m_name = co.m_name;
		m_product = co.m_product;
		m_cntItem = co.m_cntItem;
		m_lstItem = co.m_lstItem;
		
		co.m_name = "";
		co.m_product = "";
		co.m_cntItem = 0;
		co.m_lstItem = nullptr;
	};
	
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
		if (this != &co) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_name = co.m_name;
			m_product = co.m_product;
			m_cntItem = co.m_cntItem;
			m_lstItem = co.m_lstItem;

			co.m_name = "";
			co.m_product = "";
			co.m_cntItem = 0;
			co.m_lstItem = nullptr;
		}
		return *this;
	};

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	};

	bool CustomerOrder::isOrderFilled() const {
		bool res = true;

		// if all the items in the order have been filled
		for (size_t i = 0; i < m_cntItem && res; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				res = false;
			}
		}
		return res;
	};
	
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool res = true;

		// if all items specified by itemName have been filled
		for (size_t i = 0; i < m_cntItem && res; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				res = false;
			}
		}
		return res;
	};
	
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool chk = false;

		for (size_t i = 0; i < m_cntItem && !chk; i++) {
			// if the order contains items handled, and the Station's inventory contains at least one item
			if ((m_lstItem[i]->m_itemName == station.getItemName()) && !m_lstItem[i]->m_isFilled && station.getQuantity() > 0) {
				// subtracts 1 from the inventory
				station.updateQuantity();

				// updates Item::m_serialNumber and Item::m_isFilled
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;

				chk = true;

				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}			
			//if the order contains items handled but unfilled, and the inventory is empty
			else if ((m_lstItem[i]->m_itemName == station.getItemName()) && !m_lstItem[i]->m_isFilled && station.getQuantity() == 0) {
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
		}
	};
	
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<< std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - "
				<< (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
		}	
	};
}