// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <iostream>
#include <deque>
#include "CustomerOrder.h"

namespace sdds {
	// The queues (global variables) hold the orders at either end of the assembly line
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
	private:
		//orders that have been placed on this station to receive service (or already received service)
		std::deque<CustomerOrder> m_orders;
		//a pointer to the next Workstation
		Workstation* m_pNextStation{ nullptr };
	public:
		Workstation() = default;

		//the object cannot be copied or moved
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		//passes it to the Station base class
		Workstation(const std::string&);
		//fills the order at the front of the queue if there are CustomerOrders in the queue
		void fill(std::ostream& os);
		//attempts to move the order order at the front of the queue to the next station
		bool attemptToMoveOrder();
		//stores the address of the referenced Workstation object in the pointer to the m_pNextStation
		void setNextStation(Workstation* station = nullptr);
		//returns the address of next Workstation
		Workstation* getNextStation() const;
		//inserts the name of the Item for which the current object is responsible into stream os
		void display(std::ostream& os) const;
		//moves the CustomerOrder referenced in parameter newOrder to the back of the queue
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif // !SDDS_WORKSTATION_H