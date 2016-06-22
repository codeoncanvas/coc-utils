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
