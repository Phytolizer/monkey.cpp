monkey_lib = library(
    'monkey',
    'token.cpp',
    include_directories : incdir
)

monkey_test = executable(
    'monkey_test',
    'lexer_test.cpp',
    dependencies : [gtest_dep, gtest_main_dep]
)

test('monkey tests', monkey_test)

