//
//  Sleep.h
//
//  A cross-platform sleep function.
//

#ifndef SLEEP_H
#define SLEEP_H

//
//  sleep
//
//  Purpose: To cause the process to sleep for the specified
//	     time.
//  Parameter(s):
//	<1> seconds: The time to sleep in seconds
//  Precondition(s):
//	<1> seconds >= 0.0
//  Returns: N/A
//  Side Effect: The curent thread sleeps for seconds seconds.
//

void sleep (double seconds);

#endif
