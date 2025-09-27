// main program.
// uses the inserted data.
/* takes section speed, tries to create a curve from initial heading and tilt with minimum radius
taking in consideration speed and max angle, max lateral g and vertical g, and at the same time
does the same thing beggining at the end point and heading, little by little until the first
curve and the last curve are pointing at the each other, and then tries to male a straight line
between them.
It only needs to deduce if the curve needs to go right or left.
Obviously if it is set to max speed both curves will end at the same place.
Height map is calculated after this to avoid issues.
changes in curve, angle, tilt have to be gradual taking in consideration speed.*/
