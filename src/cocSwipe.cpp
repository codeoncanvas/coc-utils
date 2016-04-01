//
//  cocTimer.h
//  Created by Lukasz Karluk on 10/10/2015.
//  http://codeoncanvas.cc
//

#include "cocSwipe.h"
#include "cocCore.h"

namespace coc {

Swipe::Swipe() {
    reset();
}

Swipe::~Swipe() {
    //
}

void Swipe::start(double _timeDurationInSeconds, double _optionalTimeOffsetInSeconds) {
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

void Swipe::stop() {
    reset();
}

void Swipe::reset() {
    timeRunningInSeconds = 0.0;
    timeDurationInSeconds = 0.0;
    progress = 0;
    bStarted = false;
    bPaused = false;
    bFinished = false;
    bFinishedOnLastUpdate = false;
}

void Swipe::setPaused(bool value) {
    bPaused = value;
}

void Swipe::update(double _optionalTimeElapsedSinceLastUpdateInSeconds) {

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

bool Swipe::isRunning() const {
    bool bRunning = true;
    bRunning = bRunning && (bStarted == true);
    bRunning = bRunning && (bFinished == false);
    return bRunning;
}

bool Swipe::isPaused() const {
    return bPaused;
}

bool Swipe::hasStarted() const {
    return bStarted;
}

bool Swipe::hasFinished() const {
    return bFinished;
}

bool Swipe::hasFinishedOnLastUpdate() const {
    return bFinishedOnLastUpdate;
}

double Swipe::getTimeRunningInSeconds() const {
    return timeRunningInSeconds;
}

double Swipe::getTimeDurationInSeconds() const {
    return timeDurationInSeconds;
}

double Swipe::getProgress() const {
    return progress;
}

}