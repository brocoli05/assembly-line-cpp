// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds {
	class LineManager {
	private:
		//the collection of workstations for the current assembly line
		std::vector<Workstation*> m_activeLine;
		//the total number of CustomerOrder objects
		size_t m_cntCustomerOrder{ 0 };
		//the first active station on the current line
		Workstation* m_firstStation{ nullptr };
	public:
		LineManager() = default;
		//identifies the active stations on the assembly line
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif // !SDDS_LINEMANAGER_H