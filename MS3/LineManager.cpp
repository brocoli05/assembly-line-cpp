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
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		ifstream fin(file);		

        Utilities utils{};
        std::string str{};
        size_t next_pos{ 0 };
        size_t next_copy = next_pos;
        bool more{ true };

        // Designing vectors to determine the first station later in the code
        std::vector<std::string> leftStations;
        std::vector<std::string> rightStations;

        while (std::getline(fin, str)) {
            // Resetting the index
            next_pos = next_copy;
            // Storing the names of the current and the next stations
            std::string tempCurrStation{}, tempNextStation{};
            tempCurrStation = utils.extractToken(str, next_pos, more);
            // This is to prevent the program from extracting twice if there is no delimiter and checking if there is a next station that exists
            if (!(next_pos == next_copy)) {
                tempNextStation = utils.extractToken(str, next_pos, more);

                // Adding the stations to our vectors
                leftStations.push_back(tempCurrStation);
                rightStations.push_back(tempNextStation);
            }
            // Finding the current station in the collection
            auto currStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return station->getItemName() == tempCurrStation;
                });
            // Adding the station to the active line
            m_activeLine.push_back(*currStation);

            // Finding the next station in the collection
            if (tempNextStation.length() > 0) {
                auto nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == tempNextStation;
                    });
                // Setting the next station
                (*currStation)->setNextStation(*nextStation);
            }
        }

        // Algorithm to determine the first station
        size_t count{};
        std::string fStn{};
        for (const auto& leftStation : leftStations) {
            count = 0;
            for (const auto& rightStation : rightStations) {
                if (leftStation == rightStation) {
                    count++;
                }
            }
            if (count == 0) {
                fStn = leftStation;
                break;
            }
        }

        // Setting the fist station
        auto firstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
            return station->getItemName() == fStn;
            });
        m_firstStation = *firstStation;
		
		// updates the attribute that holds the total number of orders in the g_pending queue
		m_cntCustomerOrder = g_pending.size();
	};

	void LineManager::reorderStations() {
		// reorders the workstations present in the instance variable m_activeLine
		// stores the reordered collection in the same instance variable
		std::vector<Workstation*> reorderedStations;
		Workstation* currentStation = m_firstStation;

		// starts with the first station, proceeds to the next, and so forth until the end of the line
		while (currentStation != nullptr) {
			reorderedStations.push_back(currentStation);
			currentStation = currentStation->getNextStation();
		}

		m_activeLine = reorderedStations;
	};

	bool LineManager::run(std::ostream& os) {
        bool res{};
		
		//keeps track of the current iteration number (use a local variable)
		static size_t count = 1;
		os << "Line Manager Iteration: " << count << endl;
		count++;

		//moves the order at the front of the g_pending queue to the m_firstStation and remove it from the queue
		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		//for each station on the line, executes one fill operation
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& i) {
			i->fill(os);
			});

		//for each station on the line, attempts to move an order down the line
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& i) {
			i->attemptToMoveOrder();
			});

		//if all customer orders have been filled or cannot be filled
		if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
			res = true;
		}
        else {
            res = false;
        }

		return res;
	};

	void LineManager::display(std::ostream& os) const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& station) {
			return station->display(os);
		});
	};
}