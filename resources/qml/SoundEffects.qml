import QtQuick 2.0
import QtMultimedia 5.0

/**
 * Provides sound effects for the game.
 */
Item
{
    id: sound

    /**
     * Whether sound should be muted.
     */
    property bool isMuted: false

    /**
     * Sound volume.
     */
    property real volume: 1.0

    /**
     * Sound effect when the first player drops a token.
     */
    property alias dropFirstPlayerSound: dropFirstPlayerSound

    /**
     * Sound effect when the second player drops a token.
     */
    property alias dropSecondPlayerSound: dropSecondPlayerSound

    /**
     * Sound effect when a token could not be dropped.
     */
    property alias dropFailSound: dropFailSound

    /**
     * Sound effect for game over/win.
     */
    property alias winSound: winSound

    /**
     * Sound effect for a draw.
     */
    property alias drawSound: drawSound

    SoundEffect
    {
        id: dropFirstPlayerSound
        source: "../sounds/twoTone1.wav"
        muted: sound.isMuted
        volume: sound.volume
    }

    SoundEffect
    {
        id: dropSecondPlayerSound
        source: "../sounds/twoTone2.wav"
        muted: sound.isMuted
        volume: sound.volume
    }

    SoundEffect
    {
        id: dropFailSound
        source: "../sounds/lowRandom.wav"
        muted: sound.isMuted
        volume: sound.volume
    }

    SoundEffect
    {
        id: winSound
        source: "../sounds/zapThreeToneUp.wav"
        muted: sound.isMuted
        volume: sound.volume
    }

    SoundEffect
    {
        id: drawSound
        source: "../sounds/spaceTrash1.wav"
        muted: sound.isMuted
        volume: sound.volume
    }
}
