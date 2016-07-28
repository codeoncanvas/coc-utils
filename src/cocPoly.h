/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

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

std::vector<glm::vec2> PolyArc(glm::vec2 centre,
                               float radius,
                               int resolution=100,
                               float angleStart=0,
                               float angleEnd=M_PI*2);
    
std::vector<glm::vec2> PolyResample(const std::vector<glm::vec2> & poly,
                                    float sampleDist,
                                    bool bApproximateBestFit=false);
    
float PolyLength(const std::vector<glm::vec2> & poly);

};
