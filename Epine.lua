local tek = require "@nasso/epine-tek/v0.2.0-alpha"

tek:project "NanoTekSpice" {"nanotekspice"}
tek:name "nanotekspice"

tek:binary "nanotekspice" {
    language = "C++",
    srcs = {find "./cli/src/*.cpp"},
    incdirs = {"./cli/include"},
    libs = {tek:ref "libnts"}
}

tek:static "libnts" {
    language = "C++",
    srcs = {find "./nts/src/*.cpp"},
    incdirs = {"./nts/include"}
}

tek:binary "unit_tests" {
    language = "C++",
    srcs = {find "./tests/*.cpp"},
    libs = {"criterion", tek:ref "libnts"}
}

return {
    tek:make(),
    epine.br,
    action "run" {
        prerequisites = {"$(NAME)"},
        quiet("./$(NAME) $(ARGS)")
    }
}
