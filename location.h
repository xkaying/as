#ifndef LOCATION_H
#define LOCATION_H

typedef struct _sourcelocation{
        int line;
        int column;
}SourceLocation;

SourceLocation *resetLocation(SourceLocation *location);
SourceLocation *moveLocation(SourceLocation *location);
SourceLocation *enterLocation(SourceLocation *location);

#endif // LOCATION_H
