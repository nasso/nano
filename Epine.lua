local tek = require "@nasso/epine-tek/v0.1.0-alpha8"

tek:project "NanoTekSpice" {"nanotekspice"}

tek:binary "nanotekspice" {
    language = "C++",
    srcs = {find "./cli/src/*.cpp"},
    incdirs = {"./cli/include", "./lib/librtk/include"},
    libs = {tek:ref "libnts"}
}

tek:static "libnts" {
    language = "C++",
    srcs = {find "./nts/src/*.cpp"},
    incdirs = {"./nts/include", "./lib/librtk/include"}
}

tek:binary "unit_tests" {
    language = "C++",
    srcs = {find "./tests/*.cpp"},
    incdirs = {"./nts/include", "./lib/librtk/include"},
    libs = {"criterion", tek:ref "libnts"}
}

tek:pull "librtk" {
    git = "git@github.com:Arcahub/librtk"
}

return {
    tek:make(),
    epine.br,
    action "run" {
        prerequisites = {"$(NAME)"},
        quiet("./$(NAME)")
    }
}
