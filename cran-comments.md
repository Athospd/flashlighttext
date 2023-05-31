

## R CMD check results

[ FAIL 1 | WARN 0 | SKIP 4 | PASS 61 ]

* This package is not intended to compile on Windows (at least for now).
* This package is bindings for a C++ lib (https://github.com/flashlight/text)
* It depends on C++17
* There is a warning regarding CMakeLists.txt but I believe it is spurious.
* I believe the "Namespace in Imports field not imported from: ‘R6’" is also spurious since the pkg uses R6::R6Class().
* I've successfully checked on macos-latest and ubuntu-latest (https://github.com/Athospd/flashlighttext/actions/runs/5126056367/jobs/9220040282)


