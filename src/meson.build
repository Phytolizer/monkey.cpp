monkey_lib = library(
    'monkey',
    'lexer.cpp',
    'token.cpp',
    include_directories : incdir
)

monkey_repl = executable(
    'monkey-repl',
	'repl_main.cpp',
    'repl.cpp',
    include_directories : incdir,
    link_with : monkey_lib,
	dependencies : [subprocess_dep]
)

monkey_test = executable(
    'monkey_test',
    'lexer_test.cpp',
    include_directories : incdir,
    link_with : monkey_lib,
    dependencies : [gtest_dep, gtest_main_dep]
)

test('monkey tests', monkey_test)

