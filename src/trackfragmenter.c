/* responsible for division between curves and straight lines.
Takes the plotted track data and divides it into sections according to the start and end of curves.
This will be done by looking at the angle and tilt data.
Necessary for making track sections.
This generates another batch of track data as output.
If there aren't any straight parts, the beggining and the end of the sections will be the
start and end of curves, when the track changes direction for instance.
*/