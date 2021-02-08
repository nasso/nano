local tek = require "@nasso/epine-tek/v0.1.0-alpha8"

tek:project "NanoTekSpice" {"nanotekspice"}

tek:binary "nanotekspice" {
    language = "C++",
    srcs = {find "./src/*.cpp"}
}

return {
    tek:make(),
    epine.br,
    action "run" {
        prerequisites = {"$(NAME)"},
        quiet("./$(NAME)")
    }
}
