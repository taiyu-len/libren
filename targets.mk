target:=ren_test
shared:=ren
static:=doctest
tested:=ren_test

# Flags used for all tests
TEST_FLAGS := --dt-exit --dt-no-version

ren_test: -ldoctest -lren
