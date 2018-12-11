#include <ren/fd_utils.h>
#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

int capture_fd(int from, int to)
{
	int old;
	bool r = false;
	r=r || (old = fcntl(from, FD_CLOEXEC, 0)) == -1;
	r=r || dup2(to, from) == -1;
	r=r || close(to) == -1;
	return r ? -errno : old;
}

int restore_fd(FILE *from, int old)
{
	bool r = false;
	r=r || fflush(from) == -1;
	r=r || dup2(old, fileno(from)) == -1;
	r=r || close(old) == -1;
	return r ? -errno : 0;
}
