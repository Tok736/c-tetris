run-clang-format: 
	find | grep "\.h$$" | xargs -n 1 clang-format -n
	find | grep "\.c$$" | xargs -n 1 clang-format -n

run-clang-reformat:
	find | grep "\.h$$" | xargs -n 1 clang-format -i
	find | grep "\.c$$" | xargs -n 1 clang-format -i

run-cppcheck:
	find | grep "\.[h|c|cpp]$$" | xargs -n 1 cppcheck --enable=all --std=c11 --suppress=useStandardLibrary --suppress=missingIncludeSystem

PHONY += \
	run-clang-format \
	run-clang-reformat \
	run-cppcheck
