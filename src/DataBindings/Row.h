/*
 * Row.h
 *
 *  Created on: Jul 10, 2011
 *      Author: mullins
 */

#ifndef ROW_H_
#define ROW_H_

#include <string>
#include <vector>

using namespace std;

class Row {
public:
	Row(const std::vector<std::string>&);
	~Row();

    inline const std::string& operator [](int index) {
        return this->get_column(index);
    }

    inline const std::string& get_column(int index) {
    	return ((*columns)[index]);
    }

    inline const int num_cols() {
		return columns->size();
	}

private:
	std::vector<std::string> *columns;
};


#endif /* ROW_H_ */
