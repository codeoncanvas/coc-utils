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
    
    void update();
    
    void operator = (const bool & value);
    bool operator == (const bool & value);
    
    void setValue(bool value);
    bool getValue();
    bool hasChanged();
    
    bool bValue;
    bool bValueNew;
    bool bValueChanged;
    bool bDirty;
};

}