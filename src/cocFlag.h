//
//  Flag.h
//  Created by Lukasz Karluk on 17/11/2015.
//  http://codeoncanvas.cc
//

#pragma once

namespace coc {

class Flag {
    
public:
    
    Flag();
    Flag(const Flag & copy);
    
    void operator = (const bool & value);
    void operator = (const Flag & value);
    
    bool operator == (const bool & value) const;
    bool operator == (const Flag & value) const;
    
    operator bool() const {
        return getValue();
    }
    
    void update();
    
    void setValue(bool value);
    const bool & getValue() const;
    bool hasChanged() const;
    
    bool bValue;
    bool bValueNew;
    bool bValueChanged;
    bool bDirty;
};

}