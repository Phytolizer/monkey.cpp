monkey_lib = library(
    'monkey',
    'ast.cpp',
    'lexer.cpp',
    'parser.cpp',
    'token.cpp',
    include_directories : incdir
)

monkey_repl = executable(
    'monkey-repl',
    'repl_main.cpp',
    'repl_user.cpp',
    'repl.cpp',
    include_directories : incdir,
    link_with : monkey_lib,
)

monkey_test = executable(
    'monkey_test',
    'lexer_test.cpp',
    'parser_test.cpp',
    'test_main.cpp',
    include_directories : incdir,
    link_with : monkey_lib,
    dependencies : [doctest_dep],
)

test('monkey tests', monkey_test)

