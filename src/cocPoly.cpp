//
//  cocPoly.cpp
//  Rutherford
//
//  Created by Lukasz Karluk on 10/04/2016.
//
//

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
std::vector<glm::vec2> PolyArc(glm::vec2 centre, float radius, int resolution, float angleStart, float angleEnd) {

    std::vector<glm::vec2> polyOut;

    for(int i=0; i<resolution; i++) {
        float angle = coc::map(i, 0, resolution-1, angleStart, angleEnd) - angleStart;
        glm::vec2 point = coc::direction(angle, angleStart);
        point *= glm::vec2(radius);
        point += centre;
        polyOut.push_back(point);
    }
    
    return polyOut;
}

};
