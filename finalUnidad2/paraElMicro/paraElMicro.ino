enum State {
    STATE_SETUP,
    STATE_SELECT_TRACK,
    STATE_SELECT_VOLUME,
    STATE_PLAYING
};
State currentState = STATE_SETUP;

//Variables
uint32_t volume = 0; // 0 is mute
uint32_t volumeMax = 10;
uint32_t trackDuration = 0;
uint32_t currentTrack = 1;
uint32_t maxTrack = 10;
uint32_t previousTime = 0;

uint32_t trackJump = 1;
uint32_t volumeJump = 1;

bool ledState = false;

void setupState () {
    Serial.begin (115200);
    pinMode (LED_BUILTIN, OUTPUT);
    currentState = STATE_SELECT_TRACK;
}

void selectTrackState () {
    Serial.println ("Please select a track (1-10)");
    while (Serial.available() == 0) {}
    uint32_t selectedTrack = Serial.parseInt();
    if (selectedTrack >= 1 && selectedTrack <= maxTrack) {
        currentTrack = selectedTrack;
        Serial.println ("Now playing " + String (currentTrack));
        currentState = STATE_SELECT_VOLUME;
    } else {
        Serial.println ("Invalid track number, defaulting to track 1");
        currentTrack = 1;
        currentState = STATE_SELECT_VOLUME;
    }
}

void selectVolumeState () {
    Serial.println ("Please select a volume (0-10)");
    while (Serial.available() == 0) {}
    uint32_t selectedVolume = Serial.parseInt();
    if (selectedVolume >= 0 && selectedVolume <= volumeMax) {
        volume = selectedVolume;
        Serial.println ("Volume set to " + String (volume));
        currentState = STATE_PLAYING;
    } else {
        Serial.println ("Invalid volume value, defaulting to volume 0 (mute)");
        volume = 0;
        currentState = STATE_PLAYING;
    }
}

void task1() {
    if (Serial.available() > 0) {
        char command = Serial.read();

        switch (command) {
            uint32_t newVolume;
            case 'V':
                newVolume = Serial.parseInt();
                if (Serial.available() >= 1) {
                    if (newVolume <= volumeMax) {
                        volume = newVolume;
                        Serial.println("Volume set to " + String(volume));
                    } else {
                        Serial.println("Invalid volume value");
                    }
                }
                break;
            case 'D':
                if (Serial.available() >= 1) {
                    uint32_t newDuration = Serial.parseInt();
                    if (newDuration >= 0 && newDuration <= 180) {
                        trackDuration = newDuration;
                        Serial.println("Track duration set to " + String(trackDuration) + " seconds");
                    } else {
                        Serial.println("Invalid duration value");
                    }
                }
                break;
            case 'P':
                if (Serial.available() >= 1) {
                    uint32_t newTrack = Serial.parseInt();
                    if (newTrack >= 1 && newTrack <= maxTrack) {
                        if (newTrack == currentTrack && newTrack != maxTrack) {
                            trackDuration = 10;
                            Serial.println("Playing track " + String(currentTrack));
                        } else {
                            currentTrack = newTrack;
                            Serial.println ("Playing track " + String(currentTrack));
                        }
                    } else {
                        Serial.println("Invalid track number");
                    }
                }
                break;
            default:
                Serial.println("Invalid command");
                break;
        }
    }
}

void task2 () {
    task1 ();
    if (trackDuration > 0) {
        trackDuration--;
        Serial.println ("Track duration: " + String (trackDuration) + " seconds");
    }
    delay (1000);

    // Change volume and track by 1 when the track ends
    if (trackDuration == 0) {
        if (currentTrack < maxTrack) {
            currentTrack += trackJump;
            if (currentTrack > maxTrack) {
                currentTrack = maxTrack;
            }
            Serial.println ("Playing track " + String (currentTrack));
        } else {
            currentTrack = 1;
            Serial.println ("Playing track " + String (currentTrack));
        }
        if (volume < volumeMax) {
            volume += volumeJump;
            if (volume > volumeMax) {
                volume = volumeMax;
            }
            Serial.println ("Volume set to " + String (volume));
        } else {
            volume = 1;
            Serial.println ("Volume set to " + String (volume));
        }
        trackDuration = 10;
    }
}

void playingState () {
    task2 ();

    uint32_t currentTime = millis();
    if (currentTime - previousTime >= 500) {
        previousTime = currentTime;
        ledState = !ledState;
        digitalWrite (LED_BUILTIN, ledState);
    }
}

void setup() {

}

void loop() {
    switch (currentState) {
        case STATE_SETUP:
            Serial.println ("Setup");
            setupState ();
            break;
        case STATE_SELECT_TRACK:
            Serial.println ("Select track");
            selectTrackState ();
            break;
        case STATE_SELECT_VOLUME:
            Serial.println ("Select volume");
            selectVolumeState ();
            break;
        case STATE_PLAYING:
            Serial.println ("Playing");
            playingState ();
            break;
    }
}