//
//  cocPoly.h
//  Created by Lukasz Karluk on 10/04/2016.
//  http://codeoncanvas.cc
//

#pragma once

#include "cocCore.h"

namespace coc {
  
class Poly {
public:

    Poly();
    ~Poly();

};

bool PolyInside(float x, float y, std::vector<glm::vec2> poly); // ported from OF.

std::vector<glm::vec2> PolyNormals(const std::vector<glm::vec2> & poly,
                                   bool bClosed = false);

std::vector<glm::vec2> PolyGrow(const std::vector<glm::vec2> & poly,
                                float amount,
                                bool bClosed = false);
  
};