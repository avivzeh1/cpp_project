/*
 * View.h
 *
 *  Created on: Jun 18, 2020
 *      Author: cs313311797
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <memory>
#include <string>
#include <vector>

#include "Geometry.h"
#include "SimObj.h"

class View {

public:
	// default ctor: sets the default size, scale, and origin, outputs constructor message
	View();
    // dtor
    ~View();

	// Saves the supplied name and location for future use in a draw() call
	// If the name is already present,the new location replaces the previous one.
	void update_location();

	bool get_subscripts(int &ix, int &iy, Point location) const;
	// Removes the name and its location; no error if the name is not present.
	void update_remove(const std::string& name);

	// prints out the current map
	void draw() const;

	// Modifies the display parameters:
	// If the size is out of bounds will throw excpt
	void set_size(int size_);

	// If scale is not positive, will throw excpt
	void set_scale(double scale_);

	// Any values are legal for the origin
	void set_origin(Point origin_);

	// Sets the parameters to the default values
	void set_defaults();

private:
	double scale;
	Point origin;
	int size;
	
};

#endif /* VIEW_H_ */
