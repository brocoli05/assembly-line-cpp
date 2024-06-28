// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Workstation.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	// The queues (global variables) hold the orders at either end of the assembly line
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(const std::string& str) : Station(str) {};
	//Workstation::Workstation(const std::string& str) : Station(str), m_pNextStation(nullptr) {};

	void Workstation::fill(std::ostream& os) {
		//fills the order at the front of the queue if there are CustomerOrders in the queue
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	};
	bool Workstation::attemptToMoveOrder() {
		bool res = false;

		if (!m_orders.empty()) {
			auto& frontOrder = m_orders.front();

			// if the order requires no more service at this station or cannot be filled 
			// (not enough inventory), move it to the next station
			if (this->getQuantity() == 0 || frontOrder.isItemFilled(getItemName())) {	
				if (!m_pNextStation) {
					if (frontOrder.isOrderFilled()) {
						g_completed.push_back(std::move(frontOrder));
					}
					else {
						g_incomplete.push_back(std::move(frontOrder));
					}
				}
				else {
					*m_pNextStation += std::move(frontOrder);
				}

				m_orders.pop_front();
				res = true;		
			}
		}
		
		return res;
	};
	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	};
	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	};
	void Workstation::display(std::ostream& os) const {
		os << this->getItemName() << " --> ";
		if (m_pNextStation) {
			os << m_pNextStation->getItemName();
		}
		else {
			os << "End of Line";
		}
		os << '\n';
	};
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		//moves the CustomerOrder referenced in parameter newOrder to the back of the queue
		m_orders.push_back(std::move(newOrder));
		return *this;
	};
}