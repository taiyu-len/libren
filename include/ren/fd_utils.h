#ifndef REN_FD_UTILS_H
#define REN_FD_UTILS_H
#pragma once
#include <stdio.h>
/** Capture file descriptor.
 * @param from file descriptor to capture
 * @param to file descriptor to send redirect from to
 * @return -errno | filedescriptor used to restore from
 **/
int capture_fd(int from, int to);

/** Restores captured file descriptor.
 * @param from captured file, (cannot flush fd properly?)
 * @param old value returned by capture_fd
 * @return -errno | 0
 **/
int restore_fd(FILE *from, int old);
#endif
