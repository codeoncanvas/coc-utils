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

Flag::Flag(const Flag & copy) {

    // just doing a straight copy.
    // there is an option to override this behaviour
    // and do something tricky dicky.

    bValue = copy.bValue;
    bValueNew = copy.bValueNew;;
    bValueChanged = copy.bValueChanged;
    bDirty = copy.bDirty;
}

//--------------------------------------------------------------
void Flag::operator = (const bool & value) {
    setValue(value);
}

void Flag::operator = (const Flag & value) {
    setValue(value.getValue());
}

//--------------------------------------------------------------
bool Flag::operator == (const bool & value) const {
    return (getValue() == value);
}

bool Flag::operator == (const Flag & value) const {
    return (getValue() == value.getValue());
}

//--------------------------------------------------------------
void Flag::update() {
    bValueChanged = (bValue != bValueNew);
    bValue = bValueNew;
    bDirty = false;
}

void Flag::setValue(bool value) {
    bValueNew = value;
    bDirty = true;
}

const bool & Flag::getValue() const {
    if(bDirty == true) {
        return bValueNew;
    }
    return bValue;
}

bool Flag::hasChanged() const {
    if(bDirty == true) {
        return (bValue != bValueNew);
    }
    return bValueChanged;
}

}