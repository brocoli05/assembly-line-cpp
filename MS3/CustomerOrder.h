// Name: MINJI KIM
// Seneca Student ID: 112030226
// Seneca email: mkim284@myseneca.ca
// Date of completion: 25/NOV/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

namespace sdds {
	class CustomerOrder	{
		struct Item
		{
			std::string m_itemName{};
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};

		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{ 0 };
		Item** m_lstItem{ nullptr };
		inline static size_t m_widthField{ 0 };
	public:
		CustomerOrder() = default;
		//extracts the tokens from the string and populate the current instance
		CustomerOrder(const std::string& str);
		//throw an exception if called and the copy operator= should be deleted
		CustomerOrder(const CustomerOrder& co);
		CustomerOrder& operator=(const CustomerOrder& co) = delete;
		//doesn't throw exceptions; Use the noexcept keyword
		CustomerOrder(CustomerOrder&& co) noexcept;
		CustomerOrder& operator=(CustomerOrder&& co) noexcept;
		~CustomerOrder();

		//returns true if all the items in the order have been filled
		bool isOrderFilled() const;
		//returns true if all items specified by itemName have been filled
		bool isItemFilled(const std::string& itemName) const;
		//fills one item in the current order that the Station specified in the first parameter
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_CUSTOMERORDER_H