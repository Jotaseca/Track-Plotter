// will store data structures.
#include <stdbool.h>

typedef struct coordinates {

    double latitude;
    double longitude;

}   Coordinates;

typedef struct trackInsertedPoint {

    float tiltBeg;
    float tiltEnd;
    Coordinates coordBeg;
    Coordinates coordEnd;
    float headBeg;
    float headEnd;
    float speed;

} TrackInsertedPoint;

typedef struct trackPoint {

    Coordinates coord;
    float Height; //meters
    float tilt; //  percentage
    float head; //  deg
    float angle; // deg

} TrackPoint;

typedef struct fragmentedTrackData {

    Coordinates coordBeg;
    Coordinates coordEnd;
    float speedBeg;
    float speedEnd;
    bool straight;

} FragmentedTrackData;

typedef struct segmentatedTrackData {

    unsigned int sectionNum;
    Coordinates coordBeg;
    Coordinates coordEnd;
    unsigned short int recSpeed;
    float length;

} SegmentatedTrackData;