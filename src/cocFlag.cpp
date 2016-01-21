//
//  Flag.cpp
//  Created by Lukasz Karluk on 17/11/2015.
//  http://codeoncanvas.cc
//

#include "cocFlag.h"

namespace coc {

Flag::Flag() {
    bValue = false;
    bValueNew = false;
    bValueChanged = false;
    bDirty = false;
}

void Flag::update() {
    bValueChanged = (bValue != bValueNew);
    bValue = bValueNew;
    bDirty = false;
}

void Flag::operator = (const bool & value) {
    setValue(value);
}

bool Flag::operator == (const bool & value) {
    return (getValue() == value);
}

void Flag::setValue(bool value) {
    bValueNew = value;
    bDirty = true;
}

bool Flag::getValue() {
    if(bDirty == true) {
        return bValueNew;
    }
    return bValue;
}

bool Flag::hasChanged() {
    if(bDirty == true) {
        return (bValue != bValueNew);
    }
    return bValueChanged;
}

}