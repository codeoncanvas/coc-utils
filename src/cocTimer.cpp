//
//  cocTimer.h
//  Created by Lukasz Karluk on 10/10/2015.
//  http://codeoncanvas.cc
//

#include "cocTimer.h"
#include "cocCore.h"

namespace coc {

Timer::Timer() {
    reset();
}

Timer::~Timer() {
    //
}

void Timer::start(double _timeDurationInSeconds, double _optionalTimeOffsetInSeconds) {
    reset();
    
    bStarted = true;
    
    timeDurationInSeconds = _timeDurationInSeconds;
    if(timeDurationInSeconds <= 0.0) {
        
        // if timer duration is zero or less the zero,
        // the timer finishes straight away,
        // without update having to be called.
        
        timeDurationInSeconds = 0.0;
        progress = 1.0;
        bFinished = true;
        bFinishedOnLastUpdate = true;
        
        return;
    }

    timeRunningInSeconds = _optionalTimeOffsetInSeconds;
    if(timeRunningInSeconds < 0.0) {
        timeRunningInSeconds = 0.0;
    }
}

void Timer::stop() {
    reset();
}

void Timer::reset() {
    timeRunningInSeconds = 0.0;
    timeDurationInSeconds = 0.0;
    progress = 0;
    bStarted = false;
    bPaused = false;
    bFinished = false;
    bFinishedOnLastUpdate = false;
}

void Timer::setPaused(bool value) {
    bPaused = value;
}

void Timer::update(double _optionalTimeElapsedSinceLastUpdateInSeconds) {

    bFinishedOnLastUpdate = false;
    
    if(isRunning() == false) {
        return;
    }
    
    if(isPaused() == true) {
        return;
    }
    
    double timeElapsedSinceLastUpdateInSeconds = _optionalTimeElapsedSinceLastUpdateInSeconds;
    if(timeElapsedSinceLastUpdateInSeconds < 0.0) {
        timeElapsedSinceLastUpdateInSeconds = coc::getTimeElapsedSinceLastFrame();
    }
    
    timeRunningInSeconds += timeElapsedSinceLastUpdateInSeconds;
    if(timeRunningInSeconds > timeDurationInSeconds) {
        timeRunningInSeconds = timeDurationInSeconds;
    }
    
    progress = timeRunningInSeconds / timeDurationInSeconds;
    
    bool bFinishedNew = (progress >= 1.0);

    bFinishedOnLastUpdate = true;
    bFinishedOnLastUpdate = bFinishedOnLastUpdate && (bFinished == false);
    bFinishedOnLastUpdate = bFinishedOnLastUpdate && (bFinishedNew == true);
    
    bFinished = bFinishedNew;
}

bool Timer::isRunning() const {
    bool bRunning = true;
    bRunning = bRunning && (bStarted == true);
    bRunning = bRunning && (bFinished == false);
    return bRunning;
}

bool Timer::isPaused() const {
    return bPaused;
}

bool Timer::hasStarted() const {
    return bStarted;
}

bool Timer::hasFinished() const {
    return bFinished;
}

bool Timer::hasFinishedOnLastUpdate() const {
    return bFinishedOnLastUpdate;
}

double Timer::getTimeRunningInSeconds() const {
    return timeRunningInSeconds;
}

double Timer::getTimeDurationInSeconds() const {
    return timeDurationInSeconds;
}

double Timer::getProgress() const {
    return progress;
}

}