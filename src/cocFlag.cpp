/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2015-2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

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
