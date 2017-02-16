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

#include "cocPoly.h"
#include "glm/gtx/perpendicular.hpp"

namespace coc {

Poly::Poly() {
    //
}

Poly::~Poly() {
    //
}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
std::vector<glm::vec2> PolyNormals(const std::vector<glm::vec2> & poly, bool bClosed) {

    std::vector<glm::vec2> normals;
    int numOfPoints = poly.size();

    if(numOfPoints < 2) {
        normals.push_back(glm::vec2(0));
        return normals;
    }

    bClosed = bClosed && (numOfPoints > 2);

    for(int i=0; i<numOfPoints; i++) {

        glm::vec2 normal;

        bool bEndings = false;
        bEndings = bEndings || (i == 0);
        bEndings = bEndings || (i == numOfPoints-1);
        bEndings = bEndings && (bClosed == false);
        if(bEndings == true) {

            if(i == 0) { // poly start.

                const glm::vec2 & p0 = poly[i];
                const glm::vec2 & p1 = poly[i+1];
                normal = p0 - p1;

            } else { // poly end.

                const glm::vec2 & p0 = poly[i-1];
                const glm::vec2 & p1 = poly[i];
                normal = p0 - p1;
            }

            normal = perpendicular(normal);
            normals.push_back(normal);

            continue;
        }

        int i0 = i-1;
        if(i0 < 0) {
            i0 += numOfPoints;
        }

        int i1 = (i + 1);
        if(i1 > numOfPoints-1) {
            i1 -= numOfPoints;
        }

        const glm::vec2 & p0 = poly[i0];
        const glm::vec2 & p1 = poly[i];
        const glm::vec2 & p2 = poly[i1];

        glm::vec2 n0 = perpendicular(p0 - p1);
        glm::vec2 n1 = perpendicular(p1 - p2);

        normal = glm::normalize(n0 + n1);
        normals.push_back(normal);
    }

    return normals;
}

//--------------------------------------------------------------
std::vector<glm::vec2> PolyGrow(const std::vector<glm::vec2> & poly, float amount, bool bClosed) {

    if(poly.size() < 2) {
        return poly;
    }

    std::vector<glm::vec2> polyOut;
    std::vector<glm::vec2> polyNormals = PolyNormals(poly, bClosed);
    int numOfPoints = poly.size();

    bClosed = bClosed && (numOfPoints > 2);

    glm::vec2 point;

    for(int i=0; i<numOfPoints; i++) {

        const glm::vec2 & p1 = poly[i];
        const glm::vec2 & n1 = polyNormals[i];

        bool bEndings = false;
        bEndings = bEndings || (i == 0);
        bEndings = bEndings || (i == numOfPoints-1);
        bEndings = bEndings && (bClosed == false);
        if(bEndings == true) {

            point = p1 + (n1 * amount);
            polyOut.push_back(point);

            continue;
        }

        int i0 = i-1;
        if(i0 < 0) {
            i0 += numOfPoints;
        }

        const glm::vec2 & p0 = poly[i0];
        glm::vec2 n0 = coc::perpendicular(p0 - p1);

        float angle = atan2((n0.x * n1.y - n0.y * n1.x), (n0.x * n1.x + n0.y * n1.y));
        float length = amount / cos(angle);

        point = p1 + (n1 * length);
        polyOut.push_back(point);
    }

    return polyOut;
}

//--------------------------------------------------------------
std::vector<glm::vec2> PolyArc(glm::vec2 center, float radius, int resolution, float angleStart, float angleEnd) {

    std::vector<glm::vec2> polyOut;

    for(int i=0; i<resolution; i++) {
        float angle = coc::map(i, 0, resolution-1, angleStart, angleEnd) - angleStart;
        glm::vec2 point = coc::direction(angle, angleStart);
        point *= glm::vec2(radius);
        point += center;
        polyOut.push_back(point);
    }

    return polyOut;
}

//--------------------------------------------------------------
std::vector<glm::vec2> PolyArc(glm::vec2 center, float radiusX, float radiusY, int resolution, float angleStart, float angleEnd) {

    std::vector<glm::vec2> polyOut;

#ifdef COC_CI

    float res = (angleEnd - angleStart) / resolution;
    for (float i=angleStart; i<angleEnd + res; i+=res) {
        glm::vec2 point;
        point.x = radiusX * ci::math<float>::cos( i ) + center.x;
        point.y = radiusY * ci::math<float>::sin( i ) + center.y;
        polyOut.push_back(point);
    }
    return polyOut;

#else

    std::cerr<<"This PolyArc not implemented for OF yet!"<<endl;
    return polyOut;

#endif

}

void PolyArcAppend(glm::vec2 center, float radiusX, float radiusY, std::vector<glm::vec2> &polyOut, int resolution, float angleStart, float angleEnd) {

#ifdef COC_CI

    float res = (angleEnd - angleStart) / resolution;
    for (float i=angleStart; i<angleEnd; i+=res) {// + res
        glm::vec2 point;
        point.x = radiusX * ci::math<float>::cos( i ) + center.x;
        point.y = radiusY * ci::math<float>::sin( i ) + center.y;
        polyOut.push_back(point);
    }

#else

    std::cerr<<"This PolyArc not implemented for OF yet!"<<endl;
    return polyOut;

#endif

}

//--------------------------------------------------------------
std::vector<glm::vec2> PolyResample(const std::vector<glm::vec2> & poly,
                                    float sampleDist,
                                    bool bApproximateBestFit) {
    if(poly.size() < 2) {
        return poly;
    }

    std::vector<glm::vec2> polyOut;
    polyOut.push_back(poly[0]); // add start point.
    
    if(bApproximateBestFit) {
        float length = PolyLength(poly);
        int numOfSamplesRoundedDown = length / sampleDist;
        sampleDist = length / (float)numOfSamplesRoundedDown;
    }
    
    float linePos = 0.0;
    for(int i=0; i<poly.size()-1; i++) {
        
        const glm::vec2 & p0 = poly[i];
        const glm::vec2 & p1 = poly[i+1];
        
        float segmentLength = glm::length(p1 - p0);
        float linePos0 = linePos;
        float linePos1 = linePos + segmentLength;
        linePos = linePos1;
        
        bool bSegmentFound = true;
        bSegmentFound = bSegmentFound && (sampleDist > linePos0);
        bSegmentFound = bSegmentFound && (sampleDist <= linePos1);
        if(bSegmentFound == false) {
            continue;
        }
        
        float segmentPos = coc::map(sampleDist, linePos0, linePos1, 0.0, segmentLength);
        while(segmentPos <= segmentLength) {

            float p = segmentPos / segmentLength;
            glm::vec2 point = (p1 - p0) * p + p0;
            polyOut.push_back(point);
            
            segmentPos += sampleDist;
        }
        segmentPos -= sampleDist; // segmentPos was over incremented in the while loop, so it needs to be adjusted again.
        linePos = segmentLength - segmentPos;
    }
    
    return polyOut;
}

//--------------------------------------------------------------
float PolyLength(const std::vector<glm::vec2> & poly) {
    float length = 0;
    if(poly.size() < 2) {
        return length;
    }
    
    for(int i=0; i<poly.size()-1; i++) {
        const glm::vec2 & p0 = poly[i];
        const glm::vec2 & p1 = poly[i+1];
        length += glm::length(p1 - p0);

    }
    
    return length;
}

};
