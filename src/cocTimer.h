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

class Timer {

public:

    Timer();
    ~Timer();

    void start(double timeDurationInSeconds, double optionalTimeOffsetInSeconds=-1);
    void stop();
    void reset();
    void setPaused(bool value);

    void update(double optionalTimeElapsedSinceLastUpdateInSeconds=-1);

    bool isRunning() const;
    bool isPaused() const;
    bool hasStarted() const;
    bool hasFinished() const;
    bool hasFinishedOnLastUpdate() const;

    double getTimeRunningInSeconds() const;
    double getTimeDurationInSeconds() const;
    double getProgress() const;

protected:

    double timeRunningInSeconds;
    double timeDurationInSeconds;
    float progress;
    bool bStarted;
    bool bPaused;
    bool bFinished;
    bool bFinishedOnLastUpdate;
};

}
