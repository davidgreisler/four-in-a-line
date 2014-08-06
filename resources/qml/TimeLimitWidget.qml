import QtQuick 2.0

/**
 * Time limit display widget
 */
AbstractWidget
{
    id: timeLimitDisplay

    style: TimeLimitWidgetStyle {}

    /**
     * Remaining time, minutes part.
     */
    property int remainingMinutes: 0

    /**
     * Remaining time, seconds part.
     */
    property int remainingSeconds: 0

    /**
     * Updates the remaining time.
     *
     * @param totalMinutes Time limit (minutes part).
     * @param totalSeconds Time limit (seconds part).
     * @param remainingMinutes Remaining time (minutes part).
     * @param remainingSeconds Remaining time (seconds part).
     */
    function updateRemainingTime(totalMinutes, totalSeconds, remainingMinutes, remainingSeconds)
    {
        timeLimitDisplay.remainingMinutes = remainingMinutes;
        timeLimitDisplay.remainingSeconds = remainingSeconds;
    }

    /**
     * Creates a string in the format "m:ss" from the given number of minutes/seconds.
     */
    function createTimeString(minutes, seconds)
    {
        if (seconds < 10) {
            return minutes + ":0" + seconds;
        }
        else
        {
            return minutes + ":" + seconds;
        }
    }
}
