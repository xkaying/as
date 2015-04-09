#include "location.h"
#include <assert.h>

SourceLocation *resetLocation(SourceLocation *location)
{
    assert(location);
    location->column=0;
    location->line=1;
    return location;
}

SourceLocation *moveLocation(SourceLocation *location)
{
    assert(location);
    location->column++;
    return location;
}

SourceLocation *enterLocation(SourceLocation *location)
{
    assert(location);
    location->column=0;
    location->line++;
    return location;
}
