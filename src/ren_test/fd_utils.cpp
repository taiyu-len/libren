#include <ren/fd_utils.h>
#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include <doctest/doctest.h>
#include <cstring>
#include <string>

TEST_CASE("fd capturing"
	  * doctest::skip()
	  * doctest::description("does not play well with other tests"))
{
	int fd[2];
	char buffer[0xFF];
	char err1[0xFF];
	char err2[0xFF];

	pipe(fd);
	const auto old = capture_fd(fileno(stdout), fd[1]);
	strerror_r(errno, err1, sizeof err1);

	const auto str = "Cute Cat";
	printf("%s", str);

	const auto res = restore_fd(stdout, old);
	strerror_r(errno, err2, sizeof err2);

	const auto len = read(fd[0], buffer, sizeof buffer);
	close(fd[0]);

	REQUIRE_MESSAGE(old >= 0, err1);;
	REQUIRE_MESSAGE(res >= 0, err2);
	REQUIRE(std::string(str) == std::string(buffer, buffer+len));
}
