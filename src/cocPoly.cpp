//
//  cocPoly.cpp
//  Rutherford
//
//  Created by Lukasz Karluk on 10/04/2016.
//
//

#include "cocPoly.h"

namespace coc {

Poly::Poly() {
    //
}

Poly::~Poly() {
    //
}

bool PolyInside(float x, float y, std::vector<glm::vec2> poly) {
	int counter = 0;
	int i;
	double xinters;
	glm::vec2 p1,p2;
    
	int N = poly.size();
    
	p1 = poly[0];
	for (i=1;i<=N;i++) {
		p2 = poly[i % N];
		if (y > coc::min(p1.y,p2.y)) {
            if (y <= coc::max(p1.y,p2.y)) {
                if (x <= coc::max(p1.x,p2.x)) {
                    if (p1.y != p2.y) {
                        xinters = (y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || x <= xinters)
                            counter++;
                    }
                }
            }
		}
		p1 = p2;
	}
    
	if (counter % 2 == 0) return false;
	else return true;
}

};
