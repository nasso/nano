local tek = require "@nasso/epine-tek/v0.1.0-alpha8"

tek:project "NanoTekSpice" {"nanotekspice"}

tek:binary "nanotekspice" {
    language = "C++",
    srcs = {find "./cli/src/*.cpp"},
    incdirs = {"./cli/include"},
    libs = {tek:ref "libnts", tek:ref "librtk"}
}

tek:static "libnts" {
    language = "C++",
    srcs = {find "./nts/src/*.cpp"},
    incdirs = {"./nts/include"},
    libs = {tek:ref "librtk"}
}

tek:binary "unit_tests" {
    language = "C++",
    srcs = {find "./tests/*.cpp"},
    libs = {"criterion", tek:ref "libnts", tek:ref "librtk"}
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
