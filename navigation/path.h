#ifndef PATH_H
#define PATH_H

#include <stdbool.h>

#include "location.h"

/**
 * Contains all Information about a path, which is the minimal information to use a bspline by a robot.
 */
typedef struct PathData {
    /** first point (with name). */
    Location* location1;
    /** second point (with name). */
    Location* location2;
    /** Cost of the path. */
    unsigned int cost;
    /** Distance of the control point P0-P1 in mm (can be negative). */     
    int controlPointDistance1;
    /** Distance of the control point P1->P3 in mm. */     
    int controlPointDistance2;
    /** angle1 (when at P0) in decidegree. */
    int angle1;
    /** angle2 (when at P3) in decidegree. */
    int angle2;
    /** TODO : Convert into enum AccelerationFactor factor (min = 1, max = 16). */
    unsigned char accelerationFactor;
    /** Speed factor (min = 1, max = 16). */
    unsigned char speedFactor;
    /** When reversed, the path must be done backward. */
    bool mustGoBackward;
} PathData;

/**
 * TODO
 */
int getAngle1Path(PathData* pathData);

/**
* TODO
*/
int getAngle2Path(PathData* pathData);

/**
 * Initializes the PathData structure with all informations.
 */
void initPathData(PathData* pathData,
                        Location* location1,
                         Location* location2, 
                         int cost,
                         int controlPointDistance1,
                         int controlPointDistance2,
                         int angle1,
                         int angle2,
                         unsigned char accelerationFactor,
                         unsigned char speedFactor);

/** 
 * Fills the data of an asymmetric path, a path on which 
 * the robot must move backward when reversed.
 */
void initAsymmetricPathData(PathData* pathData, 
                        Location* location1,
                         Location* location2, 
                         int cost,
                         int controlPointDistance1,
                         int controlPointDistance2,
                         int angle1,
                         int angle2,
                         unsigned char accelerationFactor,
                         unsigned char speedFactor);

/**
 * Return if the path contains the location passed in parameter
 * @param pathData the path for which we try to find if one point contains the location passed in parameter
 */
bool pathContainsLocation(PathData* pathData, Location* location);

/**
 * Returns the opposite location on the path.
 * @param path (this) the path for which we want to find the opposite location
 * @param location the location for which we want to search the opposite
 * @return the opposite location on the path
 */
Location* getOtherEnd(PathData* pathData, Location* location);

/**
 * Print debugguable path.
 * @param outputStream the outputStream in which we print PathData information
 * @param pathData the pathData to print
 */
void printPath(OutputStream* outputStream, PathData* pathData);

#endif
